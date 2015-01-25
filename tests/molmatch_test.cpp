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
 * @file molmatch_test.cpp
 * @brief Test the Mychem molmatch module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 *
 * This file is part of the Mychem software. It contains functions for
 * testing the molmatch module.
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
  cout << "property_test: missing some arguments\n";
  cout << "Usage: property_test -d data_dir -h host -u user -p password\n\n";
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
  string referenceStructure;
  string controlData;
  string query;
  string queryResult;
  bool currentTestFailed = false;
  bool testFailed = false;

  /****************************************************************
   *                     match_substruct test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "match_substruct";
  currentTestFailed = false;

  /* Set substructure data */
  inputData.clear();
  filename = data_dir + "/1H-indole.smi";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set reference structure */
  referenceStructure.clear();
  filename = data_dir + "/L-tryptophan.mol";
  if (!readBinaryFile(filename, referenceStructure)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "1";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "',MOLECULE_TO_SERIALIZEDOBMOL('" + referenceStructure + "'))";
    if (!my_handler.performBinaryQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                   substruct_atom_ids test                    *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "substruct_atom_ids";
  currentTestFailed = false;

  /* Set substructure data */
  inputData.clear();
  filename = data_dir + "/1H-indole.smi";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set reference structure */
  referenceStructure.clear();
  filename = data_dir + "/L-tryptophan.mol";
  if (!readBinaryFile(filename, referenceStructure)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "19 17 15 14 13 21 11 10 9 ; ";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "',MOLECULE_TO_SERIALIZEDOBMOL('" + referenceStructure + "'))";
    if (!my_handler.performBinaryQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                     substruct_count test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "substruct_count";
  currentTestFailed = false;

  /* Set substructure data */
  inputData.clear();
  filename = data_dir + "/1H-indole.smi";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set reference structure */
  referenceStructure.clear();
  filename = data_dir + "/L-tryptophan.mol";
  if (!readBinaryFile(filename, referenceStructure)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "1";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "',MOLECULE_TO_SERIALIZEDOBMOL('" + referenceStructure + "'))";
    if (!my_handler.performBinaryQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(controlData)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                         tanimoto test                        *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "tanimoto";
  currentTestFailed = false;

  /* Set substructure data */
  inputData.clear();
  filename = data_dir + "/1H-indole.molecule";
  if (!readBinaryFile(filename, inputData)) { currentTestFailed = true; }

  /* Set reference structure */
  referenceStructure.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readBinaryFile(filename, referenceStructure)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "0.30263157894737";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "(fingerprint2('" + inputData + "'),fingerprint2('" + referenceStructure + "'))";
    if (!my_handler.performBinaryQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(0, 8, controlData, 0, 8)) {
      currentTestFailed = true;
      cout << queryResult << endl;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                        bit_fp_and test                       *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "bit_fp_and";
  currentTestFailed = false;

  /* Set substructure data */
  inputData.clear();
  filename = data_dir + "/1H-indole.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set reference structure */
  referenceStructure.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, referenceStructure)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "1";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT tanimoto(" + funcName + "(fingerprint2('" + inputData + "'),fingerprint2('" + referenceStructure + "')),fingerprint2('" +  inputData + "'))";
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
   *                        bit_fp_or test                        *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "bit_fp_or";
  currentTestFailed = false;

  /* Set substructure data */
  inputData.clear();
  filename = data_dir + "/1H-indole.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set reference structure */
  referenceStructure.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, referenceStructure)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "0.30263157894737";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT tanimoto(" + funcName + "(fingerprint2('" + inputData + "'),fingerprint2('" + referenceStructure + "')),fingerprint2('" +  inputData + "'))";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(0, 8, controlData, 0, 8)) {
      currentTestFailed = true;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                       bit_fp_count test                      *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "bit_fp_count";
  currentTestFailed = false;

  /* Set substructure data */
  inputData.clear();
  filename = data_dir + "/1H-indole.molecule";
  if (!readBinaryFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "55";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "(fingerprint2('" + inputData + "'))";
    if (!my_handler.performBinaryQuery(queryResult, query)) {
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

