/***************************************************************************
 *   Copyright (C) 2009-2012 by CNRS                                       *
 *   jerome.pansanel@iphc.cnrs.fr -- Project founder and lead developer    *
 *   aureliedeluca@gmail.com -- Developer                                  *
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
 * to chemical file comparison.
 * @file molmatch_wrapper.cpp
 * @short Mychem Molmatch Wrapper.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 */

#include "molmatch_wrapper.h"
#include <mychem/config.h>
#include <mychem/dlhandler.h>
#include <mychem/serialization.h>

#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <openbabel/parsmart.h>

#include <sstream>

using namespace std;
using namespace OpenBabel; 

long long match_substructure(const char *smarts_pattern, const char *serializedMolecule)
{
  long long int moleculeMatch = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return moleculeMatch;
  }

  OBMol mol;
  OBSmartsPattern sp;
  bool mol_ok;

  mol_ok = unserializeOBMol(&mol, serializedMolecule,true);

  if (!mol_ok) {
      cerr << "mol is not ok" << endl;
      return 0;
  }

  if (mol.Empty()) {
      cerr << "mol is empty" << endl;
      return 0;
  }
  sp.Init(smarts_pattern);
/*  if (!sp.Init(smarts_pattern)) { return -1;}
  }
*/
  if (mol.NumHvyAtoms() < sp.NumAtoms()) {
    /* More heavy atoms in pattern than in serializedMolecule */
    return 0;
  }

  if (sp.Match(mol,true)) {
      moleculeMatch = 1;
  }
  else {
    moleculeMatch = 0;
  }

  return moleculeMatch;
}

char *substructure_atom_ids(const char *smarts_pattern, const char *serializedMolecule)
{
  vector<vector<int> > maplist;
  ostringstream outstream;

  char *retVal = NULL;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return retVal;
  }

  OBMol mol;
  OBSmartsPattern sp;
  bool mol_ok;

  mol_ok = unserializeOBMol(&mol, serializedMolecule,true);

  if (!mol_ok) {
      cerr << "mol is not ok" << endl;
      return retVal;
  }

  if (mol.Empty()) {
      cerr << "mol is empty" << endl;
      return retVal;
  }

  sp.Init(smarts_pattern);

  if (mol.NumHvyAtoms() < sp.NumAtoms()) {
    /* More heavy atoms in pattern than in serializedMolecule */
    retVal = strdup(outstream.str().c_str());
    return retVal;
  }

  sp.Match(mol);
  maplist = sp.GetUMapList();

  if (maplist.size() > 0) {
    vector<vector<int> >::iterator mit;
    vector<int>::iterator ait;
    for (mit = maplist.begin(); mit != maplist.end(); ++mit) {
      for (ait = (*mit).begin(); ait != (*mit).end(); ++ait) {
        outstream << *ait << " ";
      }
      outstream << "; ";
    }
  }

  retVal = strdup(outstream.str().c_str());

  return retVal;
}

long long substructure_count(const char *smarts_pattern, const char *serializedMolecule)
{
  vector<vector<int> > maplist;

  long long int substructureCount = 0;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return substructureCount;
  }

  OBMol mol;
  OBSmartsPattern sp;
  bool mol_ok;

  mol_ok = unserializeOBMol(&mol, serializedMolecule,true);

  if (!mol_ok) {
      cerr << "mol is not ok" << endl;
      return 0;
  }

  if (mol.Empty()) {
      cerr << "mol is empty" << endl;
      return 0;
  }

  sp.Init(smarts_pattern);

  if (mol.NumHvyAtoms() < sp.NumAtoms()) {
    /* More heavy atoms in pattern than in serializedMolecule */
    return 0;
  }

  sp.Match(mol);
  maplist = sp.GetUMapList();

  substructureCount = maplist.size();

  return substructureCount;
}

