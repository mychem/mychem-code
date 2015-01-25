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
 * used by MySQL and related to chemical file comparison.
 * @file molmatch.h
 * @short Function declarations of the Mychem molmatch module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#ifndef __MOLMATCH_H
#define __MOLMATCH_H

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
 * @short Initializes the match_substruct function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool match_substruct_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by match_substruct_init().
 * @param initid The structure filled by match_substruct_init()
 */
void match_substruct_deinit(UDF_INIT *initid);

/**
 * @short Checks if a molecule is a substructure of an other molecule.
 * @param initid A structure filled by match_substruct_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return True if the molecule is a substructure
 */
longlong match_substruct(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the substruct_atom_ids function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool substruct_atom_ids_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by substruct_atom_ids_init().
 * @param initid The structure filled by substruct_atom_ids_init()
 */
void substruct_atom_ids_deinit(UDF_INIT *initid);

/**
 * @short Returns the atom ids of the reference molecule's atom that are
 * contained in substructures matching the query.
 * @param initid A structure filled by substruct_atom_ids_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The list of atom ids
 */
char *substruct_atom_ids(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the tanimoto function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool tanimoto_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by tanimoto_init().
 * @param initid The structure filled by tanimoto_init()
 */
void tanimoto_deinit(UDF_INIT *initid);

/**
 * @short Calculates the Tanimoto coefficient of two fingerprint bitsets.
 * @param initid A structure filled by tanimoto_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The Tanimoto coefficient
 */
double tanimoto(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the substruct_count function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool substruct_count_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by substruct_count_init().
 * @param initid The structure filled by substruct_count_init()
 */
void substruct_count_deinit(UDF_INIT *initid);

/**
 * @short Returns the number of a substructure within a reference structure.
 * @param initid A structure filled by substruct_count_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The number of substructures
 */
longlong substruct_count(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the bit_fp_and function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool bit_fp_and_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by bit_fp_and_init().
 * @param initid The structure filled by bit_fp_and_init()
 */
void bit_fp_and_deinit(UDF_INIT *initid);

/**
 * @short Returns a bitwise AND comparison between two fingerprints.
 * @param initid A structure filled by bit_fp_and_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The bitwise comparison
 */
char *bit_fp_and(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the bit_fp_or function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool bit_fp_or_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by bit_fp_or_init().
 * @param initid The structure filled by bit_fp_or_init()
 */
void bit_fp_or_deinit(UDF_INIT *initid);

/**
 * @short Returns a bitwise OR comparison between two fingerprints.
 * @param initid A structure filled by bit_fp_or_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The bitwise comparison
 */
char *bit_fp_or(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the bit_fp_count function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool bit_fp_count_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by bit_fp_count_init().
 * @param initid The structure filled by bit_fp_count_init()
 */
void bit_fp_count_deinit(UDF_INIT *initid);

/**
 * @short Returns the number of bits that are set in a binary string.
 * @param initid A structure filled by bit_fp_count_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The number of bits
 */
longlong bit_fp_count(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

#endif /* HAVE_DLOPEN */

#endif /* __MOLMATCH_H */

