/***************************************************************************
 *   Copyright (C) 2009-2011 by CNRS                                       *
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
 * to molecule modifications.
 * @file modification_wrapper.cpp
 * @short Mychem Modification Wrapper.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 */

#include "modification_wrapper.h"
#include <mychem/config.h>
#include <mychem/dlhandler.h>

#include <openbabel/mol.h>
#include <openbabel/obconversion.h>

#include <sstream>

using namespace std;
using namespace OpenBabel;

char *ob_add_hydrogens(const char *molecule)
{
  string instring(molecule); 
  istringstream inStream(instring);
  ostringstream outStream;
  string outstring;

  char *retVal = NULL;

  LibHandler lib_ob;

  if (!lib_ob.isLoaded()) {
    return retVal;
  }

  OBMol mol;
  OBConversion conv;

  conv.SetInAndOutFormats(MOLECULE_TYPE,MOLECULE_TYPE);

  conv.Read(&mol,&inStream);
  mol.AddHydrogens(false,false);
  conv.Write(&mol,&outStream);

  outstring = outStream.str();
  retVal = strdup(outstring.c_str());

  return retVal;
}

char *ob_remove_hydrogens(const char *molecule)
{
  string instring(molecule); 
  istringstream inStream(instring);
  ostringstream outStream;
  string outstring;

  char *retVal = NULL;

  LibHandler lib_ob;

  if (!lib_ob.isLoaded()) {
    return retVal;
  }

  OBMol mol;
  OBConversion conv;

  if (conv.SetInAndOutFormats(MOLECULE_TYPE,MOLECULE_TYPE)) {
    conv.Read(&mol,&inStream);
    mol.DeleteHydrogens();
    conv.Write(&mol,&outStream);
    outstring = outStream.str();
    retVal = strdup(outstring.c_str());
  }

  return retVal;
}

char *ob_strip_salts(const char *molecule)
{
  string instring(molecule); 
  istringstream inStream(instring);
  ostringstream outStream;
  string outstring;

  char *retVal = NULL;

  LibHandler lib_ob;

  if (!lib_ob.isLoaded()) {
    return retVal;
  }

  OBMol mol;
  OBConversion conv(&inStream, &outStream);

  if (conv.SetInAndOutFormats(MOLECULE_TYPE,MOLECULE_TYPE)) {
    conv.Read(&mol);
    mol.StripSalts(3);
    conv.Write(&mol);
    outstring = outStream.str();
    retVal = strdup(outstring.c_str());
  }

  return retVal;
}

