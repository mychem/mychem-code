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
 * @file property_test.cpp
 * @brief Test the Mychem property module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 *
 * This file is part of the Mychem software. It contains functions for
 * testing the property module.
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
  string controlData;
  string query;
  string queryResult;
  bool currentTestFailed = false;
  bool testFailed = false;

  /****************************************************************
   *                        molweight test                        *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molweight";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "204.225180";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
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
   *                        exactmass test                        *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "exactmass";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "204.089878";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
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
   *                     number_of_atoms test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "number_of_atoms";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "27";

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
   *                  number_of_heavy_atoms test                  *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "number_of_heavy_atoms";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "15";

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
   *                     number_of_bonds test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "number_of_bonds";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "28";

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
   *                 number_of_rotable_bonds test                 *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "number_of_rotable_bonds";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "3";

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
   *                      total_charge test                       *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "total_charge";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "0";

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
   *                       molformula test                        *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molformula";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "C11H12N2O2";

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
   *                   number_of_acceptors test                   *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "number_of_acceptors";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "3";

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
   *                    number_of_donors test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "number_of_donors";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "3";

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
   *                          molpsa test                         *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molpsa";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "79.11";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT ROUND(" + funcName + "('" + inputData + "'),2)";
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
   *                            molmr test                        *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "molmr";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "57.3579";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT ROUND(" + funcName + "('" + inputData + "'),4)";
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
   *                         mollogp  test                        *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "mollogp";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "1.8226";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT ROUND(" + funcName + "('" + inputData + "'),4)";
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
   *                          is_2D test                          *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "is_2D";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "1";

  /* Set and perform the query */
  if (!currentTestFailed) {
    queryResult.clear();
    query = "SELECT " + funcName + "('" + inputData + "')";
    if (!my_handler.performQuery(queryResult, query)) {
      currentTestFailed = true;
    }
    else if (queryResult.compare(controlData)) {
      currentTestFailed = true;
      cout << queryResult << endl;
    }
  }

  if (currentTestFailed) { testFailed = true; }

  printTestResult(funcName, currentTestFailed);

  /****************************************************************
   *                          is_3D test                          *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "is_3D";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "1";

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
   *                        is_chiral test                        *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "is_chiral";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "1";

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
   *                     number_of_rings test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "number_of_rings";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/L-tryptophan.molecule";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  controlData = "2";

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

