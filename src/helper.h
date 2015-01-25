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
 * This file is part of the Mychem software. It contains function declarations
 * used by MySQL and related to Mychem informations.
 * @file helper.h
 * @short Function declarations of the Mychem helper module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#ifndef __HELPER_H
#define __HELPER_H

#ifdef STANDARD
/* STANDARD is defined, don't use any mysql functions */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong;	/* Microsofts 64 bit types */
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif /*__WIN__*/
#else
#include <my_global.h>
#include <my_sys.h>
#endif /* STANDARD */
#include <mysql.h>
#include <m_ctype.h>
#include <m_string.h>		/* To get strmov() */

#ifdef HAVE_DLOPEN

/**
 * @short Initializes the mychem_version function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool mychem_version_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by mychem_version_init().
 * @param initid The structure filled by mychem_version_init()
 */
void mychem_version_deinit(UDF_INIT *initid);

/**
 * @short Returns the version of Mychem.
 * @param initid A structure filled by mychem_version_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The version of Mychem
 */
char *mychem_version(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the openbabel_version function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool openbabel_version_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by openbabel_version_init().
 * @param initid The structure filled by openbabel_version_init()
 */
void openbabel_version_deinit(UDF_INIT *initid);

/**
 * @short Returns the version of the Open Babel library.
 * @param initid A structure filled by openbabel_version_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The version of the Open Babel library
 */
char *openbabel_version(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the inchi_version function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool inchi_version_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by inchi_version_init().
 * @param initid The structure filled by inchi_version_init()
 */
void inchi_version_deinit(UDF_INIT *initid);

/**
 * @short Returns the version of the InChI library.
 * @param initid A structure filled by inchi_version_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The version of the InChI library
 */
char *inchi_version(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
#endif /* HAVE_DLOPEN */

#endif /* __HELPER_H */

