/***************************************************************************
 *   Copyright (C) 2009-2011 by CNRS                                       *
 *   jerome.pansanel@iphc.cnrs.fr -- Project founder and lead developer    *
 *   aureliedeluca@gmail.com -- Developer                                  *
 *   bjoern@gruenings.eu -- Developer                                      *
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
 * to chemical property calculations.
 * @file property_wrapper.cpp
 * @short Mychem Property Wrapper.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 * @author Bjoern Gruening <bjoern@gruenings.eu>
 */

#include "property_wrapper.h"
#include <mychem/config.h>
#include <mychem/dlhandler.h>

#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <openbabel/descriptor.h>
#include <openbabel/groupcontrib.h>
#include "descriptors/groupcontrib.cpp"
#include <sstream>

using namespace std;
using namespace OpenBabel;

#if defined(__CYGWIN__) || defined(__MINGW32__)
  // macro to implement static OBPlugin::PluginMapType& Map()
  PLUGIN_CPP_FILE(OBDescriptor)
#endif

double getMolWeight(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  double molWeight = 0.0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return molWeight;
  }

  OBConversion conv;
  OBMol mol;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol,&inStream);
    molWeight = mol.GetMolWt();
  }

  return molWeight;
}

double getExactMass(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  double exactMass = 0.0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return exactMass;
  }

  OBConversion conv;
  OBMol mol;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    exactMass = mol.GetExactMass();
  }

  return exactMass;
}

long long int getAtomCount(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int atomCount = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return atomCount;
  }

  OBConversion conv;
  OBMol mol;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    atomCount = mol.NumAtoms();
  }

  return atomCount;
}

long long int getHeavyAtomCount(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int heavyAtomCount = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return heavyAtomCount;
  }

  OBConversion conv;
  OBMol mol;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    heavyAtomCount = mol.NumHvyAtoms();
  }

  return heavyAtomCount;
}

long long int getBondCount(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int bondCount = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return bondCount;
  }

  OBConversion conv;
  OBMol mol;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    bondCount = mol.NumBonds();
  }

  return bondCount;
}

long long int getRotableBondCount(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int rotableBondCount = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return rotableBondCount;
  }

  OBConversion conv;
  OBMol mol;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    rotableBondCount = mol.NumRotors();
  }

  return rotableBondCount;
}

long long int getTotalCharge(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int totalCharge = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return totalCharge;
  }

  OBConversion conv;
  OBMol mol;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    totalCharge = mol.GetTotalCharge();
  }

  return(totalCharge);
}

char *getFormula(const char *molecule)
{
  string inString(molecule);
  string outstring;
  istringstream inStream(inString);
  
  char * formula = NULL;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return formula;
  }

  OBConversion conv;
  OBMol mol;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    outstring = mol.GetFormula();
    formula = strdup(outstring.c_str());
  }

  return formula;
}

long long int getAcceptors(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int acceptorCount = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return acceptorCount;
  }

  OBConversion conv;
  OBMol mol;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    OBMolAtomIter atomIter(mol);

    for (; atomIter; ++atomIter) {
      if (atomIter->IsHbondAcceptor()) {
        ++acceptorCount;
      }
    }
  }

  return acceptorCount;
}

long long int getDonors(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int donorCount = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return donorCount;
  }

  OBMol mol;
  OBConversion conv(&inStream);

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    // iterator over each atom
    OBMolAtomIter atomIter(mol);

    for (; atomIter; ++atomIter) {
      if (atomIter->IsHbondDonor()) {
        ++donorCount;
      }
    }
  }

  return donorCount;
}

double getPSA(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  double PSA = 0.0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return PSA;
  }

  OBMol mol;
  OBConversion conv(&inStream);

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol);
    // Make sur that TPSA descriptor exits
    OBDescriptor* pDescr = OBDescriptor::FindType("TPSA");
    if (pDescr) {
      PSA = pDescr->Predict(&mol);
    }
  }

  return PSA;
}

double getMR(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  double MR = 0.0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return MR;
  }

  OBMol mol;
  OBConversion conv(&inStream);

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol);
    // Make sur that MR descriptor exits
    OBDescriptor* pDescr = OBDescriptor::FindType("MR");
    if (pDescr) {
      MR = pDescr->Predict(&mol);
    }
  }

  return MR;
}

double getLogP(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  double logP = 0.0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return logP;
  }

  OBMol mol;
  OBConversion conv;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol,&inStream);
    // Make sur that logP descriptor exits
    OBDescriptor* pDesc = OBDescriptor::FindType("logP");
    if (pDesc) {
      logP = pDesc->Predict(&mol);
    }
  }

  return logP;
}

long long int is2D(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int Bool = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return Bool;
  }

  OBMol mol;
  OBConversion conv;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);

    if (mol.Has2D ()) {
      Bool = 1;
    }
  }

  return Bool;
}

long long int is3D(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int Bool = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return Bool;
  }

  OBMol mol;
  OBConversion conv;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    if (mol.Has3D ()) {
      Bool = 1;
    }
  }

  return Bool;
}

long long int isChiral(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int Bool = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return Bool;
  }

  OBMol mol;
  OBConversion conv;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    mol.FindChiralCenters();

    if (mol.IsChiral()) {
      Bool = 1;
    }
  }

  return Bool;
}

long long int getRingCount(const char *molecule)
{
  string inString(molecule);
  istringstream inStream(inString);

  long long int ringCount = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return ringCount;
  }

  OBMol mol;
  OBConversion conv;

  vector<OBRing*> obring;

  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol, &inStream);
    obring = mol.GetSSSR();
    ringCount = obring.size();
  }

  return ringCount;
}

