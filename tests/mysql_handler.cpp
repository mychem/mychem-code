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
 * This file is part of the Mychem software. It contains functions for
 * handling a MySQL connection.
 * @file mysql_handler.cpp
 * @brief MySQL Handler.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#include "mysql_handler.h"

#include <mysql.h>

#include <iostream>

using namespace std;

MySQLHandler::MySQLHandler()
{
  mysql_init(&_mysql);
  _link = NULL;
}

MySQLHandler::~MySQLHandler()
{
  if (_link) {
    mysql_close(_link);
    _link = NULL;
  }
}

bool MySQLHandler::connect(string host, string user, string passwd, string db)
{
  if (!(_link = mysql_real_connect(&_mysql, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), 0, NULL, 0))) {
    cout << "Error: could not connect to MySQL!\n" << mysql_error(&_mysql) << endl;
    return false;
  }

  _mysql.reconnect = 1;

  return true;
}

bool MySQLHandler::performQuery(string& buffer, string query)
{
  MYSQL_RES *res = NULL;

  if (mysql_query(_link, query.c_str())) {
    cerr << "Error: query failed (" << mysql_error(_link) << ")\n";
    return false;
  }

  if (!(res = mysql_store_result(_link))) {
    cerr << "Error: could not get result from " << mysql_error(_link) << endl;
    mysql_free_result(res);
    return false;
  }

  MYSQL_ROW row = mysql_fetch_row(res);

  if (row == NULL) {
    cerr << "Error: query result is empty\n";
    mysql_free_result(res);
    return false;
  }

  if (row[0] == NULL) {
      buffer = "";
  }
  else {
      buffer = row[0];
  }

  mysql_free_result(res);

  return true;
}

bool MySQLHandler::performBinaryQuery(string& buffer, string query)
{
  MYSQL_RES *res = NULL;

  if (mysql_real_query(_link, query.c_str(), query.size())) {
    cerr << "Error: query failed (" << mysql_error(_link) << ")\n";
    return false;
  }

  if (!(res = mysql_store_result(_link))) {
    cerr << "Error: could not get result from " << mysql_error(_link) << endl;
    mysql_free_result(res);
    return false;
  }

  MYSQL_ROW row = mysql_fetch_row(res);

  if (row == NULL) {
    cerr << "Error: query result is empty\n";
    mysql_free_result(res);
    return false;
  }

  buffer = row[0];

  mysql_free_result(res);

  return true;
}

void MySQLHandler::disconnect()
{
  if (_link) {
    mysql_close(_link);
    _link = NULL;
  }
}
