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
 * This file is part of the Mychem software. It contains functions for
 * testing the modification module.
 * @file modification_test.cpp
 * @brief Test the Mychem modification module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
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
   *                      add_hydrogens test                      *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "add_hydrogens";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine.mol";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/hydrogenated_glycine.mol";
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
   *                    remove_hydrogens test                     *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "remove_hydrogens";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/hydrogenated_glycine.mol";
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
   *                       strip_salts test                       *
   ****************************************************************/
  /* Initialize the variables */
  funcName = "strip_salts";
  currentTestFailed = false;

  /* Set input data */
  inputData.clear();
  filename = data_dir + "/glycine_sodium_salt.mol";
  if (!readFile(filename, inputData)) { currentTestFailed = true; }

  /* Set control data */
  controlData.clear();
  filename = data_dir + "/glycine_wo_sodium.mol";
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

  my_handler.disconnect();

  if (testFailed) {
    return 1;
  }

  return 0;
}

