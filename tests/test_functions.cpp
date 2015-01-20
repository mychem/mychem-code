/***************************************************************************
 *   Copyright (C) 2009-2011 by CNRS                                       *
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
 * @file test_functions.cpp
 * @brief Provide functions used by the test programs.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 *
 * This file is part of the Mychem software. It contains functions used
 * by the test programs.
 */

#include "test_functions.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

void splitString(const string str, vector<string> &stringList)
{
  string line;
  string::size_type pos;
  string::size_type lastPos = 0;

  for (pos = 0; pos < str.size(); ++pos) {
    if (str[pos] == '\n') {
      if (pos == 0) {
        /* the first line is empty */
        line = " ";        
      }
      else if ((pos - lastPos) == 1) {
        /* empty line */
        line = " ";
        lastPos = pos;
      }
      else {
        line = str.substr(lastPos+1, pos - lastPos);
        lastPos = pos;
      }
      stringList.push_back(line);
    }
  }
}

bool tokenize(vector<string> &vcr, string buffer, const char *delimstr)
{
  vcr.clear();
  if (buffer.empty() || !delimstr) {
    return false;
  }
  buffer += "\n";
  size_t startpos=0,endpos=0;
  for (;;) {
    startpos = buffer.find_first_not_of(delimstr,startpos);
    endpos = buffer.find_first_of(delimstr,startpos);
    if (endpos <= buffer.size() && startpos <= buffer.size()) {
      vcr.push_back(buffer.substr(startpos,endpos-startpos));
    }
    else {
      break;
    }
    startpos = endpos+1;
  }

  return true;
}


bool compareMoleculeMap(map<string, unsigned int> firstMolMap, map<string, unsigned int> secondMolMap)
{
  map<string, unsigned int>::iterator it;

  if (firstMolMap.size() != secondMolMap.size()) {
    return false;
  }
  for (it = firstMolMap.begin(); it != firstMolMap.end(); ++it) {
    if (secondMolMap.count(it->first) == 0) {
      return false;
    }
    else if (secondMolMap[it->first] != it->second) {
      return false;
    }
  }

  return true;
}

bool compareMolecules(string first_molecule, string second_molecule)
{
  istringstream line;
  string atom;
  unsigned long int i = 0;

  /* Check number of atoms, atom types and connectivity (first molecule) */
  vector<string> firstMoleculeLineList;
  unsigned int firstMoleculeAtomCount = 0;
  unsigned int firstMoleculeBondCount = 0;
  map<string, unsigned int> firstMoleculeAtoms;

  splitString(first_molecule, firstMoleculeLineList);

  for (i = 0; i < firstMoleculeLineList.size(); ++i) {
    if (i < 3) {
      continue;
    }
    else if (i == 3) {
      line.clear();
      line.str(firstMoleculeLineList[i].substr(0,3));
      if (!(line >> firstMoleculeAtomCount)) {
        cerr << "Error: The first molecule is not a valid molecule" << endl;
        return false;
      }
      line.clear();
      line.str(firstMoleculeLineList[i].substr(3,3));
      if (!(line >> firstMoleculeBondCount)) {
        cerr << "Error: The first molecule is not a valid molecule" << endl;
        return false;
      }
    }
    else if (i < (firstMoleculeAtomCount + 4)) {
      atom.clear();
      line.clear();
      line.str(firstMoleculeLineList[i].substr(31,3));
      if (!(line >> atom)) {
        cerr << "Error: The first molecule is not a valid molecule" << endl;
        return false;
      }
      if (firstMoleculeAtoms.count(atom)) {
        firstMoleculeAtoms[atom] += 1;
      }
      else {
        firstMoleculeAtoms[atom] = 1;
      }  
    }
  }

  /* Check number of atoms, atom types and connectivity (second molecule) */
  vector<string> secondMoleculeLineList;
  unsigned int secondMoleculeAtomCount = 0;
  unsigned int secondMoleculeBondCount = 0;
  map<string, unsigned int> secondMoleculeAtoms;

  splitString(second_molecule, secondMoleculeLineList);

  for (i = 0; i < secondMoleculeLineList.size(); ++i) {
    if (i < 3) {
      continue;
    }
    else if (i == 3) {
      line.clear();
      line.str(secondMoleculeLineList[i].substr(0,3));
      if (!(line >> secondMoleculeAtomCount)) {
        cerr << "Error: The second molecule is not a valid molecule" << endl;
        return false;
      }
      line.clear();
      line.str(secondMoleculeLineList[i].substr(3,3));
      if (!(line >> secondMoleculeBondCount)) {
        cerr << "Error: The second molecule is not a valid molecule" << endl;
        return false;
      }
    }
    else if (i < (secondMoleculeAtomCount + 4)) {
      atom.clear();
      line.clear();
      line.str(secondMoleculeLineList[i].substr(31,3));
      if (!(line >> atom)) {
        cerr << "Error: The second molecule is not a valid molecule" << endl;
        return false;
      }
      if (secondMoleculeAtoms.count(atom)) {
        secondMoleculeAtoms[atom] += 1;
      }
      else {
        secondMoleculeAtoms[atom] = 1;
      }  
    }
  }

  /* Check the similarity */
  if (!compareMoleculeMap(firstMoleculeAtoms,secondMoleculeAtoms)) {
    return false;
  }
  if (firstMoleculeBondCount != secondMoleculeBondCount) {
    return false;
  }

  return true;
}

bool compareV3000(string first_molecule, string second_molecule)
{
  vector<string> lineVector;
  bool inAtom = false;
  bool inBond = false;
  unsigned int i;

  /* Check number of atoms, atom types and connectivity (first molecule) */
  vector<string> firstMoleculeLineList;
  unsigned int firstMoleculeBondCount = 0;
  map<string, unsigned int> firstMoleculeAtoms;

  splitString(first_molecule, firstMoleculeLineList);

  for (i = 0; i < firstMoleculeLineList.size(); ++i) {
    if (firstMoleculeLineList[i].find("BEGIN ATOM") != string::npos) {
      if (inBond || inAtom) {
        cerr << "Error: The first molecule is not a valid V3000 molecule" << endl;
        return false;
      }
      inAtom = true;
    }
    else if (firstMoleculeLineList[i].find("END ATOM") != string::npos) {
      if (inBond || !inAtom) {
        cerr << "Error: The first molecule is not a valid V3000 molecule" << endl;
        return false;
      }
      inAtom = false;
    }
    else if (firstMoleculeLineList[i].find("BEGIN BOND") != string::npos) {
      if (inBond || inAtom) {
        cerr << "Error: The first molecule is not a valid V3000 molecule" << endl;
        return false;
      }
      inBond = true;
    }
    else if (firstMoleculeLineList[i].find("END BOND") != string::npos) {
      if (!inBond || inAtom) {
        cerr << "Error: The first molecule is not a valid V3000 molecule" << endl;
        return false;
      }
      inBond = false;
    }
    if (inAtom) {
      lineVector.clear();
      tokenize(lineVector, firstMoleculeLineList[i], " \t\n\r");
      if (lineVector.size() < 4) {
        cerr << "Error: The first molecule is not a valid molecule" << endl;
        return false;
      }
      if (firstMoleculeAtoms.count(lineVector[3])) {
        firstMoleculeAtoms[lineVector[3]] += 1;
      }
      else {
        firstMoleculeAtoms[lineVector[3]] = 1;
      }        
    }
    else if (inBond) {
      firstMoleculeBondCount += 1;
    }
  }

  /* Check number of atoms, atom types and connectivity (second molecule) */
  vector<string> secondMoleculeLineList;
  unsigned int secondMoleculeBondCount = 0;
  map<string, unsigned int> secondMoleculeAtoms;

  splitString(second_molecule, secondMoleculeLineList);

  for (i = 0; i < secondMoleculeLineList.size(); ++i) {
    if (secondMoleculeLineList[i].find("BEGIN ATOM") != string::npos) {
      if (inBond || inAtom) {
        cerr << "Error: The second molecule is not a valid V3000 molecule" << endl;
        return false;
      }
      inAtom = true;
    }
    else if (secondMoleculeLineList[i].find("END ATOM") != string::npos) {
      if (inBond || !inAtom) {
        cerr << "Error: The second molecule is not a valid V3000 molecule" << endl;
        return false;
      }
      inAtom = false;
    }
    else if (secondMoleculeLineList[i].find("BEGIN BOND") != string::npos) {
      if (inBond || inAtom) {
        cerr << "Error: The second molecule is not a valid V3000 molecule" << endl;
        return false;
      }
      inBond = true;
    }
    else if (secondMoleculeLineList[i].find("END BOND") != string::npos) {
      if (!inBond || inAtom) {
        cerr << "Error: The second molecule is not a valid V3000 molecule" << endl;
        return false;
      }
      inBond = false;
    }
    if (inAtom) {
      lineVector.clear();
      tokenize(lineVector, secondMoleculeLineList[i], " \t\n\r");
      if (lineVector.size() < 4) {
        cerr << "Error: The second molecule is not a valid molecule" << endl;
        return false;
      }
      if (secondMoleculeAtoms.count(lineVector[3])) {
        secondMoleculeAtoms[lineVector[3]] += 1;
      }
      else {
        secondMoleculeAtoms[lineVector[3]] = 1;
      }        
    }
    else if (inBond) {
      secondMoleculeBondCount += 1;
    }
  }

  /* Check the similarity */
  if (!compareMoleculeMap(firstMoleculeAtoms,secondMoleculeAtoms)) {
    return false;
  }
  if (firstMoleculeBondCount != secondMoleculeBondCount) {
    return false;
  }

  return true;
}

void printTestResult(string testName, bool testFailed)
{
  unsigned short int count;

  cout << "Testing " << testName << " ...";
  for (count = 0; count < (46-testName.size()); ++count) {
    cout << " ";
  }
  if (testFailed) {
    cout << "[FAILED]\n";
  }
  else {
    cout << "  [OK]\n";
  }
}

bool readFile(string filename, string& buffer)
{
  ifstream fileStream;
  string line;

  fileStream.open(filename.c_str(), ios::in);
  if (!fileStream) {
    cerr << "Error: cannot read " << filename << endl;
    return false;
  }
  while (!fileStream.eof()) {
    getline(fileStream, line);
    buffer += line + "\n";
  }
  fileStream.close();

  /* Remove a newline character added by this function */
  buffer.resize(buffer.size()-1);
  /* Remove a newline character added by Open Babel */
  if (buffer[buffer.size()-1] == '\n') {
    buffer.resize(buffer.size()-1);
  }

  return true;
}

bool readBinaryFile(string filename, string& binaryString)
{
  ifstream fileStream;

  int size = 0;
  int pos = 0;
  fileStream.open(filename.c_str(), ios::binary);
  if (!fileStream.is_open()) {
    cerr << "Error: cannot read " << filename << endl;
    return false;
  }
  fileStream.seekg(0, ios::end);
  size = fileStream.tellg();
  fileStream.seekg(0, ios::beg);
  for (pos = 0; pos < size; ++pos) {
    binaryString.push_back(fileStream.get());
  }

  fileStream.close();

  return true;
}

