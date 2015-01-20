/***************************************************************************
 *   Copyright (C) 2009-2012 by CNRS                                       *
 *   jerome.pansanel@iphc.cnrs.fr -- Project founder and lead developer    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02111-1301, USA.         *
 ***************************************************************************/

/**
 * This file is part of the Mychem software. It contains functions related
 * to the serialization of OBMol objects.
 * @file serialization.cpp
 * @short OBMol Serialization Methods.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
*/

#include <mychem/serialization.h>
#include <openbabel/stereo/stereo.h>
#include <openbabel/stereo/tetrahedral.h>
#include <openbabel/stereo/cistrans.h>
#include <openbabel/stereo/squareplanar.h>

using namespace std;
using namespace OpenBabel;

typedef struct
{
  char type;
  unsigned long atomids[2];
  unsigned long refs[4];
  OBStereo::Shape shape;
  OBStereo::View view;
  OBStereo::Winding winding;
} _STEREO;

char *serializeOBMol(OBMol &mol) {

  if (mol.Empty()) {
    return NULL;
  }

  unsigned int numatoms = mol.NumAtoms();
  unsigned int numbonds = mol.NumBonds();
  vector<OBGenericData*>::iterator data;
  vector<OBGenericData*> stereoData; 
  if (mol.HasData(OBGenericDataType::StereoData)) {
    stereoData = mol.GetAllData(OBGenericDataType::StereoData);
  }
  unsigned int numstereo = stereoData.size();
  unsigned int totalsize = (numatoms*sizeof(_ATOM))+(numbonds*sizeof(_BOND))+(numstereo*sizeof(_STEREO))+(4*sizeof(unsigned int));

  char *retval = new char[totalsize];
  _ATOM *atomptr;
  _BOND *bondptr;
  _STEREO *stereoptr;

  //mol.Kekulize();

  memset(retval,0x0,totalsize);

  unsigned int *uintptr = (unsigned int*) retval;

  *uintptr = totalsize-sizeof(unsigned int);

  ++uintptr;

  *uintptr = numatoms;

  ++uintptr;

  *uintptr = numbonds;

  ++uintptr;

  *uintptr = numstereo;

  ++uintptr;

  atomptr = (_ATOM*) uintptr;

  FOR_ATOMS_OF_MOL(atom, mol) {
    atomptr->idx = atom->GetIdx();
    atomptr->hybridization = atom->GetHyb();
    atomptr->atomicnum = (unsigned char) atom->GetAtomicNum();
    atomptr->formalcharge = (char) atom->GetFormalCharge();
    atomptr->isotope = (unsigned short) atom->GetIsotope();
    atomptr->spinmultiplicity = (unsigned char) atom->GetSpinMultiplicity();
    atomptr->aromatic = atom->IsAromatic() ? 1 : 0;

    ++atomptr;
  }

  bondptr = (_BOND*) atomptr; 

  if (numbonds>0) { 
    FOR_BONDS_OF_MOL(bond, mol) {
      bondptr->beginidx = bond->GetBeginAtomIdx();
      bondptr->endidx = bond->GetEndAtomIdx();
      bondptr->order = (unsigned char) bond->GetBondOrder();
      bondptr->aromatic = bond->IsAromatic() ? 1 : 0;

      ++bondptr;
    }
  }

  stereoptr = (_STEREO*) bondptr;

  for (data = stereoData.begin(); data != stereoData.end(); ++data) {
    OBStereo::Type type;
    type = ((OBStereoBase*)*data)->GetType();
    if (type == OBStereo::Tetrahedral) {
      OBTetrahedralStereo *ts = dynamic_cast<OBTetrahedralStereo*>(*data);
      OBTetrahedralStereo::Config config = ts->GetConfig();
      stereoptr->type = type;
      stereoptr->atomids[0] = config.center;
      stereoptr->atomids[1] = config.towards;
      stereoptr->refs[0] = config.refs[0];
      stereoptr->refs[1] = config.refs[1];
      stereoptr->refs[2] = config.refs[2];
      stereoptr->winding = config.winding;
      stereoptr->view = config.view;
    } else if (type == OBStereo::SquarePlanar) {
      OBSquarePlanarStereo *sp = dynamic_cast<OBSquarePlanarStereo*>(*data);
      OBSquarePlanarStereo::Config config = sp->GetConfig();
      stereoptr->type = type;
      stereoptr->atomids[0] = config.center;
      stereoptr->refs[0] = config.refs[0];
      stereoptr->refs[1] = config.refs[1];
      stereoptr->refs[2] = config.refs[2];
      stereoptr->refs[3] = config.refs[3];
      stereoptr->shape = config.shape;
    } else if  (type == OBStereo::CisTrans) {
      OBCisTransStereo *ct = dynamic_cast<OBCisTransStereo*>(*data);
      OBCisTransStereo::Config config = ct->GetConfig();
      stereoptr->type = type;
      stereoptr->atomids[0] = config.begin;
      stereoptr->atomids[1] = config.end;
      stereoptr->refs[0] = config.refs[0];
      stereoptr->refs[1] = config.refs[1];
      stereoptr->refs[2] = config.refs[2];
      stereoptr->refs[3] = config.refs[3];
      stereoptr->shape = config.shape;
    }

    ++stereoptr;
  }

  return retval;
}

bool unserializeOBMol(OBBase* pOb, const char *serializedInput, bool stereoEnabled)
{
  OBMol* pmol = pOb->CastAndClear<OBMol>();
  map<OBAtom*,OBChiralData*> _mapcd;
  OBMol &mol = *pmol;
  _mapcd.clear();
  bool chiralWatch=false;
  unsigned int i,natoms,nbonds,nstereo;

  unsigned int *intptr = (unsigned int*) serializedInput;

  ++intptr;

  natoms = *intptr;

  ++intptr;

  nbonds = *intptr;

  ++intptr;

  nstereo = *intptr;

  ++intptr;

  _ATOM *atomptr = (_ATOM*) intptr;

  mol.ReserveAtoms(natoms);

  OBAtom atom;

  for (i = 1; i <= natoms; i++) {
    atom.SetIdx(atomptr->idx);
    atom.SetHyb(atomptr->hybridization);
    atom.SetAtomicNum((int) atomptr->atomicnum);
    atom.SetIsotope((unsigned int) atomptr->isotope);
    atom.SetFormalCharge((int) atomptr->formalcharge);

    atom.SetSpinMultiplicity((short) atomptr->spinmultiplicity);

    if(atomptr->aromatic != 0) {
      atom.SetAromatic();
    }

    if (!mol.AddAtom(atom)) {
      return false;
    }

    if (chiralWatch) {
      // fill the map with data for each chiral atom
      _mapcd[mol.GetAtom(i)] = new OBChiralData;
    }
    atom.Clear();

    ++atomptr;
  }

  _BOND *bondptr = (_BOND*) atomptr;

  unsigned int start,end,order,flags;

  for (i = 0;i < nbonds;i++) {
    flags = 0;

    start = bondptr->beginidx;
    end = bondptr->endidx;
    order = (int) bondptr->order;

    if (start == 0 || end == 0 || order == 0 || start > natoms || end > natoms) {
      return false;
    }

    order = (unsigned int) (order == 4) ? 5 : order;

    if (bondptr->aromatic != 0) {
      flags |= OB_AROMATIC_BOND;
    }

    if (!mol.AddBond(start,end,order,flags)) {
      return false;
    }


    ++bondptr;
  }

  if (stereoEnabled) {
    _STEREO *stereoptr = (_STEREO*) bondptr;
  
    for (i=0; i < nstereo; ++i) {
      if (stereoptr->type == OBStereo::Tetrahedral) {
        OBTetrahedralStereo::Config cfg;
        cfg.center = stereoptr->atomids[0];
        cfg.towards = stereoptr->atomids[1];
        cfg.refs = OBStereo::MakeRefs(stereoptr->refs[0],stereoptr->refs[1],stereoptr->refs[2]);
        cfg.winding = stereoptr->winding;
        cfg.view = stereoptr->view;
        OBTetrahedralStereo *obts = new OBTetrahedralStereo(&mol);
        obts->SetConfig(cfg);
        mol.SetData(obts);
      } else if (stereoptr->type == OBStereo::SquarePlanar) {
        OBSquarePlanarStereo::Config cfg;
        cfg.center = stereoptr->atomids[0];
        cfg.refs = OBStereo::MakeRefs(stereoptr->refs[0],stereoptr->refs[1],stereoptr->refs[2],stereoptr->refs[3]);
        cfg.shape = stereoptr->shape;
        OBSquarePlanarStereo *obsp = new OBSquarePlanarStereo(&mol);
        obsp->SetConfig(cfg);
        mol.SetData(obsp);
      } else if (stereoptr->type == OBStereo::CisTrans) {
        OBCisTransStereo::Config cfg;
        cfg.begin = stereoptr->atomids[0];
        cfg.end = stereoptr->atomids[1];
        cfg.refs = OBStereo::MakeRefs(stereoptr->refs[0],stereoptr->refs[1],stereoptr->refs[2],stereoptr->refs[3]);
        cfg.shape = stereoptr->shape;
        OBCisTransStereo *obct = new OBCisTransStereo(&mol);
        obct->SetConfig(cfg);
        mol.SetData(obct);
      }
      ++stereoptr;
    }
    mol.SetChiralityPerceived();
  }
 
  mol.SetAromaticPerceived();
  mol.SetKekulePerceived();

  return true;
}

