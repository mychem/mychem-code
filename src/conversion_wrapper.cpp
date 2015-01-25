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
 * to chemical file conversion.
 * @file conversion_wrapper.cpp
 * @short Mychem Conversion Wrapper.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 */

#include "conversion_wrapper.h"
#include <mychem/config.h>
#include <mychem/dlhandler.h>
#include <mychem/serialization.h>

#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <openbabel/plugin.h>
#include <openbabel/fingerprint.h>
#include "fingerprints/finger2.cpp"
#include "fingerprints/finger3.cpp"

#include <sstream>

using namespace std;
using namespace OpenBabel; 

#if defined(__CYGWIN__) || defined(__MINGW32__)
  // macro to implement static OBPlugin::PluginMapType& Map()
  PLUGIN_CPP_FILE(OBFingerprint)
  PLUGIN_CPP_FILE(OBFormat)
#endif

char *conversion(const char *molecule, const char *inType, const char *outType)
{
  string instring(molecule);
  string outstring;
  istringstream inStream(instring);
  ostringstream outStream;

  char *retVal = NULL;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return retVal;
  }

  OBConversion conv(&inStream,&outStream);

  if (conv.SetInAndOutFormats(inType, outType)) {
    // Set options
    if (!strcmp(outType, "SMI")) {
      /* No molecule name */
      conv.AddOption("n", OBConversion::OUTOPTIONS);
    }

    try {
      conv.Convert();

      outstring = outStream.str();

      if (outstring[outstring.length()-1] == '\n') {
        outstring = outstring.substr(0, outstring.length()-1);
      }

      retVal = strdup(outstring.c_str());
    }
    catch(...) {
    }
  }

  return retVal;
}

char *conversionV3000(const char *V3000)
{
  string instring(V3000);
  string outstring;
  istringstream inStream(instring);
  ostringstream outStream;

  char *retVal = NULL;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return retVal;
  }

  OBConversion conv(&inStream,&outStream);

  if (conv.SetInAndOutFormats(MOLECULE_TYPE, "MOL")) {
    // Set options
    conv.AddOption("3", OBConversion::OUTOPTIONS); 

    conv.Convert();

    outstring = outStream.str();

    // remove the trailling $$$$ from the SDFile
    if (outstring.find("$$$$\n", 0) != string::npos) {
      outstring = outstring.substr(0, outstring.length()-5);
    }
    else if (outstring.find("$$$$\r\n", 0) != string::npos) {
      outstring = outstring.substr(0, outstring.length()-6);
    }

    if (outstring[outstring.length()-1] == '\n') {
      outstring[outstring.length()-1] = '\0';
    }

    retVal = strdup(outstring.c_str());
  }

  return retVal;
}

char *V3000conversion(const char *molecule)
{
  string instring(molecule);
  string outstring;
  istringstream inStream(instring);
  ostringstream outStream;

  char *retVal = NULL;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return retVal;
  }

  OBConversion conv(&inStream, &outStream);

  if (conv.SetInAndOutFormats("MOL", MOLECULE_TYPE)) {
    // Set options
    conv.AddOption("3", OBConversion::INOPTIONS); 

    conv.Convert();
  
    outstring = outStream.str();

    if (outstring[outstring.length()-1] == '\n') {
      outstring = outstring.substr(0, outstring.length()-1);
    }

    retVal = strdup(outstring.c_str());
  }

  return retVal;
}

char *CMLconversion(const char *cml)
{
  string instring(cml);
  string outstring;
  istringstream inStream(instring);
  ostringstream outStream;

  char *retVal = NULL;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return retVal;
  }

  OBConversion conv(&inStream,&outStream);

  if (conv.SetInAndOutFormats("CML", MOLECULE_TYPE)) {
    conv.Convert();

    outstring = outStream.str();

    if (outstring[outstring.length()-1] == '\n') {
      outstring = outstring.substr(0, outstring.length()-1);
    }

    retVal = strdup(outstring.c_str());
  }

  return retVal;
}

char *conversionCML(const char *molecule)
{
  string instring(molecule);
  string outstring;
  istringstream inStream(instring);
  ostringstream outStream;

  char *retVal = NULL;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return retVal;
  }

  OBConversion conv(&inStream,&outStream);

  if (conv.SetInAndOutFormats(MOLECULE_TYPE, "CML")) {
    conv.AddOption("x", OBConversion::OUTOPTIONS);
    conv.Convert();

    outstring = outStream.str();

    if (outstring[outstring.length()-1] == '\n') {
      outstring = outstring.substr(0, outstring.length()-1);
    }

    retVal = strdup(outstring.c_str());
  }

  return retVal;
}

char *conversionFPT(const char *molecule, const char *type)
{
  string instring(molecule);
  string fpType(type);
  istringstream inStream(instring);
  char *fpStruct = NULL;
  unsigned long int fpSize = 0;
  unsigned long int *ulintptr = NULL;
  int *intptr = NULL;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return fpStruct;
  }
  OBConversion conv(&inStream);
  OBMol mol;
  if (conv.SetInFormat(MOLECULE_TYPE)) {
    conv.Read(&mol);
    OBFingerprint *pFingerPrint = NULL;
    vector<unsigned int> fp;
    vector<unsigned int>::iterator fpIt;
    // Check that fingerprint type is available
    pFingerPrint = OBFingerprint::FindFingerprint(fpType.c_str());
    if (!pFingerPrint) {
      return fpStruct;
    }

    pFingerPrint->GetFingerprint(&mol, fp);

    fpSize = fp.size()*sizeof(int);

    fpStruct = (char *) malloc(fpSize + sizeof(unsigned long int));
    memset(fpStruct, 0, fpSize + sizeof(unsigned long int));
    ulintptr = (unsigned long int *) fpStruct;
    memcpy(ulintptr, &fpSize, sizeof(unsigned long int));
    ++ulintptr;
    intptr = (int *) ulintptr;

    for (fpIt = fp.begin(); fpIt != fp.end(); ++fpIt) {
      memcpy(intptr, &(*fpIt), sizeof(int));
      ++intptr;
    }
  }

  return fpStruct;
}

char *conversionCAN(const char *molecule)
{
  string instring(molecule);
  string outstring;
  istringstream inStream(instring);
  ostringstream outStream;

  char *retVal = NULL;

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return retVal;
  }

  OBConversion conv(&inStream,&outStream);

  if (conv.SetInAndOutFormats(MOLECULE_TYPE, "CAN")) {
    // Set options
    /* No molecule name */
    conv.AddOption("n", OBConversion::OUTOPTIONS);

    conv.Convert();
    outstring = outStream.str();

    if (outstring[outstring.length()-1] == '\n') {
      outstring = outstring.substr(0, outstring.length()-1);
    }

    retVal = strdup(outstring.c_str());
  }

  return retVal;
}

char *serializeMolecule(const char *molecule) {
  string instring(molecule);
  string outstring;
  istringstream inStream(instring);

  LibHandler ob_lib;

  if (!ob_lib.isLoaded()) {
    return NULL;
  }

  OBMol mol;
  OBConversion conv;
  conv.SetInFormat(MOLECULE_TYPE);
  conv.Read(&mol,&inStream);

  return serializeOBMol(mol);
}

