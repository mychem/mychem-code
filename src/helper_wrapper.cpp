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
 * This file is part of the Mychem software. It contains functions related
 * to the helper module.
 * @file helper_wrapper.cpp
 * @short Mychem Helper Wrapper.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#include "helper_wrapper.h"

#include <openbabel/babelconfig.h>

#include <cstring>
#include <string>

using namespace std;

char *getOpenBabelVersion()
{
  // pb: BABEL_VERSION is defined at compilation. BABEL_VERSION should be
  // defined at run time Try to get VERSION for the dynamic lib
  return strdup(BABEL_VERSION);
}

char *getInChIVersion()
{
  string version;

  if (!strncmp(BABEL_VERSION, "2.2.0", 5)) {
    version = "1.0";
  }
  else if (!strncmp(BABEL_VERSION, "2.2.1", 5)) {
    version = "1.0";
  }
  else if (!strncmp(BABEL_VERSION, "2.2.2", 5)) {
    version = "1.02";
  }
  else if (!strncmp(BABEL_VERSION, "2.2.3", 5)) {
    version = "1.02";
  }
  else {
    version = "unknown";
  }

  return strdup(version.c_str());
}
