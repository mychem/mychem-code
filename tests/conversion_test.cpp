/***************************************************************************
 *   Copyright (C) 2009-2014 by CNRS                                       *
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
 * @file conversion_test.cpp
 * @brief Test the Mychem conversion module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 *
 * This file is part of the Mychem software. It contains functions for
 * testing the conversion module.
 */

#include "mysql_handler.h"
#include "test_functions.h"
#include <mychem/config.h>

#include <openbabel/babelconfig.h>

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void arg_error(void)
{
  cout << "conversion_test: missing some arguments\n";
  cout << "Usage: conversion_test -d data_dir -h host -u user -p password\n\n";
  cout << "Please note that the password option is not mandatory.\n";
}

int main(int argc, char **argv)
{
  unsigned short int count;
  string host;
  string user;
  string passwd;
  string data_dir;
  string db;


  if ((argc != 9) && (argc != 11)) {
    arg_error();
    exit(1);
  }

  for (count = 1; count < argc; count++) {
    if (argv[count][0] == '-') {
      switch(argv[count][1]) {
        case 'h':
          ++count;
          if (count < argc) {
            host = argv[count];
            break;
          }
        case 'u':
          ++count;
          if (count < argc) {
            user = argv[count];
            break;
          }
        case 'p':
          ++count;
          if (count < argc) {
            passwd = argv[count];
            break;
          }
	case 'b':
	  ++count;
	  if (count < argc) {
	    db = argv[count];
	    break;
	  }
	case 'd':
	  ++count;
	  if (count < argc) {
	    data_dir = argv[count];
	    break;
	  }
        default:
          arg_error();
          exit(1);
      }
    }
  }

  /* Initialize the MySQL connection */
  MySQLHandler my_handler;
  if (!my_handler.connect(host.c_str(), user.c_str(), passwd.c_str(), db.c_str())) {
    return 1;
  }

  /* Variable initialisation */
  string funcName;
  string filename;
  string inputData;
  string controlData;
  string controlData2;
  string query;
  string queryResult;
  bool currentTestFailed = false;
  bool testFailed = false;

  /****************************************************************
   *                   molfile_to_molecule test                   *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molfile_to_molecule";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.mol";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                   molecule_to_molfile test                   *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molecule_to_molfile";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.mol";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                    V3000_to_molecule test                    *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "V3000_to_molecule";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.V3000";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                    molecule_to_V3000 test                    *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molecule_to_V3000";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.V3000";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareV3000(queryResult,controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                   smiles_to_molecule test                    *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "smiles_to_molecule";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.smi";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                   molecule_to_smiles test                    *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molecule_to_smiles";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.smi";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                  molecule_to_molecule test                   *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molecule_to_molecule";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.inchi";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                     cml_to_molecule test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "cml_to_molecule";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.cml";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                     molecule_to_cml test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molecule_to_cml";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.cml";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                       fingerprint tests                      *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "fingerprint";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.mol";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData = "0";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT length(" + funcName + "('" + inputData + "','FP2'))";
    query += "-length(fingerprint2('" + inputData + "'))";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT length(" + funcName + "('" + inputData + "','FP3'))";
    query += "-length(fingerprint3('" + inputData + "'))";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT length(" + funcName + "('" + inputData + "','FP4'))";
    query += "-length(fingerprint4('" + inputData + "'))";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *              molecule_to_canonical_smiles test               *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molecule_to_canonical_smiles";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/L-tryptophan.can";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                    inchi_to_molecule test                    *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "inchi_to_molecule";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.inchi";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                    molecule_to_inchi test                    *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molecule_to_inchi";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.inchi";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Add support for libinchi v102 */
  controlData2.clear();
  filename = data_dir + "/glycine.inchi102";
  if (!readFile(filename, controlData2)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(controlData)) {
      if (queryResult.compare(controlData2)) {
          currentTestFailed = true;
      }
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *               molecule_to_serializedOBMol test               *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molecule_to_serializedOBMol";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "348";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!queryResult.compare(0,8, controlData, 0, 8)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                     pdb_to_molecule test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "pdb_to_molecule";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/1CRN.pdb";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/1CRN.molecule";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                     mol2_to_molecule test                    *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "mol2_to_molecule";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.mol2";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (!compareMolecules(queryResult, controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                     molecule_to_mol2 test                    *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molecule_to_mol2";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine.mol2";
  if (!readFile(filename, controlData)) { currentTestFailed = true; }

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  my_handler.disconnect();

  if (testFailed) {
    return 1;
  }

  return 0;
}
