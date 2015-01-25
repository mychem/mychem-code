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
 * used by MySQL and related to molecule modifications.
 * @file modification.h
 * @short Function declarations of the Mychem modification module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#ifndef __MODIFICATION_H
#define __MODIFICATION_H

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
 * @short Initializes the add_hydrogens function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool add_hydrogens_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by add_hydrogens_init().
 * @param initid The structure filled by add_hydrogens_init()
 */
void add_hydrogens_deinit(UDF_INIT *initid);

/**
 * @short Add hydrogens to a molecule.
 * @param initid A structure filled by add_hydrogens_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The hydrogenated molecule
 */
char *add_hydrogens(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the remove_hydrogens function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool remove_hydrogens_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by remove_hydrogens_init().
 * @param initid The structure filled by remove_hydrogens_init()
 */
void remove_hydrogens_deinit(UDF_INIT *initid);

/**
 * @short Remove hydrogens to a molecule.
 * @param initid A structure filled by remove_hydrogens_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The dehydrogenated molecule
 */
char *remove_hydrogens(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the strip_salts function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool strip_salts_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by strip_salts_init().
 * @param initid The structure filled by strip_salts_init()
 */
void strip_salts_deinit(UDF_INIT *initid);

/**
 * @short Removes all atoms from the molecule, except for the larger contiguous fragment.
 * @param initid A structure filled by strip_salts_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The cleaned molecule
 */
char *strip_salts(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

#endif /* HAVE_DLOPEN */

#endif /* __MODIFICATION_H */

