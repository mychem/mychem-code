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
 * @file mysql_handler.h
 * @brief MySQL Handler.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#include <mysql.h>
#include <string>

class MySQLHandler
{
  private:
    MYSQL _mysql;
    MYSQL * _link;

  public:
    /**
     * @brief Default constructor.
     *
     * Initializes @c.
     */
    MySQLHandler();

    /**
     * @brief Default destructor.
     */
    ~MySQLHandler();

    /**
     * @brief desc
     * A complete description
     * @param host The host
     * @param user The user
     * @param passwd The password
     * @param db The database
     * @return bool 
     */
    bool connect(std::string host, std::string user, std::string passwd, std::string db);
    bool performQuery(std::string &buffer, std::string query);
    bool performBinaryQuery(std::string &buffer, std::string query);
    void disconnect();
};


