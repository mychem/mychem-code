/***************************************************************************
 *   Copyright (C) 2009-2015 by CNRS                                       *
 *   jerome.pansanel@iphc.cnrs.fr -- Project founder and lead developer    *
 *   aureliedeluca@gmail.com -- Developer                                  *
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
 * This file is part of the Mychem software. It contains functions used by
 * MySQL and related to chemical file comparison.
 * @file molmatch.c
 * @short Function definitions of the Mychem molmatch module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 */

#include "molmatch.h"
#include "molmatch_wrapper.h"
#include <mychem/config.h>
#include <mychem/structures.h>
#include <stdio.h>


#ifdef HAVE_DLOPEN

my_bool match_substruct_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2) {
    strcpy(message, "Wrong number of arguments: MATCH_SUBSTRUCT() requires two arguments");
    return 1;
  }
  if ((args->arg_type[0] != STRING_RESULT) || (args->arg_type[1] != STRING_RESULT)) {
    strcpy(message,"Wrong argument type: MATCH_SUBSTRUCT() requires a STRING and a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void match_substruct_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong match_substruct(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  if ((args->args[0] == NULL) || (args->args[1] == NULL)) {
    /* Arguments can not be NULL */
    /* Chose to not set *error=1 to continue with other rows */
    *is_null = 1;
    return 0;
  }

  if (args->lengths[1] < sizeof(unsigned int)) {
    /* Chose to not set *error=1 to continue with other rows */
    *is_null = 1;
    return 0;
  }

  /* Fix a MySQL end string char issue */
  char *queryMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  unsigned int *intptr = (unsigned int *) args->args[1];
  unsigned int totalsize = intptr[0];
  longlong match_bool = 0;

  if (totalsize == 0) {
    /* empty molecule */
    free(queryMol);

    return 0;
  }

  strncpy(queryMol, args->args[0], args->lengths[0]);
  queryMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error = 0;

  match_bool = match_substructure(queryMol, args->args[1]);

  free(queryMol);

  return match_bool;
}

my_bool substruct_atom_ids_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2) {
    strcpy(message, "Wrong number of arguments: SUBSTRUCT_ATOM_IDS() requires two arguments");
    return 1;
  }
  if ((args->arg_type[0] != STRING_RESULT) || (args->arg_type[1] != STRING_RESULT)) {
    strcpy(message,"Wrong argument type: SUBSTRUCT_ATOM_IDS() requires a STRING and a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char *) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void substruct_atom_ids_deinit(UDF_INIT *initid __attribute__((unused)))
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *substruct_atom_ids(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *queryMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  unsigned int *intptr = (unsigned int *) args->args[1];
  unsigned int totalsize = intptr[0];
  char *list = NULL;

  if ((args->args[0] == NULL) || (args->args[1] == NULL)) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(queryMol);

    return NULL;
  }

  if (totalsize == 0) {
    /* empty molecule */
    free(queryMol);

    return 0;
  }

  strncpy(queryMol, args->args[0], args->lengths[0]);
  queryMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  list = substructure_atom_ids(queryMol, args->args[1]);

  /* Return NULL if list is NULL */
  if (list == NULL) {
    *is_null = 1;
    *error = 1;
    free(queryMol);

    return 0;
  }

  *length = strlen(list);
  strncat(initid->ptr, list, *length);

  free(queryMol);
  free(list);

  return initid->ptr;
}

my_bool tanimoto_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2) {
    strcpy(message, "Wrong number of arguments: TANIMOTO() requires two arguments");
    return 1;
  }
  if ((args->arg_type[0] != STRING_RESULT) || (args->arg_type[1] != STRING_RESULT)) {
    strcpy(message, "Wrong argument type: TANIMOTO() requires a STRING and a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void tanimoto_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

double tanimoto(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null __attribute__((unused)), char *error)
{
  int *intptr1 = NULL;
  int *intptr2 = NULL;
  unsigned long int *ulintptr1 = NULL;
  unsigned long int *ulintptr2 = NULL;
  unsigned long int fpLength1 = 0;
  unsigned long int fpLength2 = 0;
  int andfp = 0, orfp = 0;
  unsigned long int andbits = 0, orbits = 0;
  unsigned long int i = 0;

  if ((args->args[0] == NULL) || (args->args[1] == NULL)) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;

    return 0;
  }

  *error = 0;
  ulintptr1 = (unsigned long int *) args->args[0];
  fpLength1 = ulintptr1[0];
  ulintptr2 = (unsigned long int *) args->args[1];
  fpLength2 = ulintptr2[0];

  if (fpLength1 != fpLength2) {
    /* The both fingerprint must have the same length) */
    *is_null = 1;
    *error = 1;

    return 0;
  }

  if ((fpLength1 % sizeof(int)) || (fpLength2 % sizeof(int))) {
    /* The length of the fingerprint must be a multiple of long int */
    *is_null = 1;
    *error = 1;

    return 0;
  }

  ++ulintptr1;
  ++ulintptr2;
  intptr1 = (int*) ulintptr1;
  intptr2 = (int*) ulintptr2;

  /**
   * Tanimoto coefficient is defined by:
   * Number of bits set in (patternFP & targetFP) /
   * Number of bits in (patternFP | targetFP)
   */
  for(i = 0; i < fpLength1/sizeof(int); ++i) {
    andfp = intptr1[i] & intptr2[i];
    orfp = intptr1[i] | intptr2[i];
    for (; andfp; andfp = andfp<<1) {
      if (andfp < 0) { ++andbits; }
    }
    for (; orfp; orfp = orfp<<1) {
      if (orfp < 0) { ++orbits; }
    }
  }

  if (orbits == 0) {
    return 0.0;
  }

  return (double) andbits / (double) orbits;
}

my_bool substruct_count_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2) {
    strcpy(message, "Wrong number of arguments: SUBSTRUCT_COUNT() requires two arguments");
    return 1;
  }
  if ((args->arg_type[0] != STRING_RESULT) || (args->arg_type[1] != STRING_RESULT)) {
    strcpy(message,"Wrong argument type: SUBSTRUCT_COUNT() requires a STRING and a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void substruct_count_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong substruct_count(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *queryMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  unsigned int *intptr = (unsigned int *) args->args[1];
  unsigned int totalsize = intptr[0];
  longlong number_of_substructure = 0;

  if ((args->args[0] == NULL) || (args->args[1] == NULL)) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(queryMol);

    return 0;
  }

  if (totalsize == 0) {
    /* empty molecule */
    free(queryMol);

    return 0;
  }

  strncpy(queryMol, args->args[0], args->lengths[0]);
  queryMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error = 0;

  number_of_substructure = substructure_count(queryMol, args->args[1]);

  free(queryMol);

  return number_of_substructure;
}

my_bool bit_fp_and_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2) {
    strcpy(message, "Wrong number of arguments: BIT_FP_AND() requires two arguments");
    return 1;
  }
  if ((args->arg_type[0] != STRING_RESULT) || (args->arg_type[1] != STRING_RESULT)) {
    strcpy(message, "Wrong argument type: BIT_FP_AND() requires a STRING and a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char *) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void bit_fp_and_deinit(UDF_INIT *initid __attribute__((unused)))
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *bit_fp_and(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  unsigned long int *ulintptr1 = NULL;
  unsigned long int *ulintptr2 = NULL;
  unsigned long int *ulintptr3 = NULL;
  int *intptr1 = NULL;
  int *intptr2 = NULL;
  int *intptr3 = NULL;
  unsigned long int fpLength1 = 0;
  unsigned long int fpLength2 = 0;
  int andInt = 0;
  unsigned long int i = 0;

  if ((args->args[0] == NULL) || (args->args[1] == NULL)) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;

    return 0;
  }

  ulintptr1 = (unsigned long int *) args->args[0];
  fpLength1 = ulintptr1[0];
  ulintptr2 = (unsigned long int *) args->args[1];
  fpLength2 = ulintptr2[0];

  if (fpLength1 != fpLength2) {
    /* The both fingerprint must have the same length) */
    *is_null = 1;
    *error = 1;

    return 0;
  }

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;
  ulintptr3 = (unsigned long int *) initid->ptr;
  memcpy(ulintptr3, &fpLength1, sizeof(unsigned long int));

  ++ulintptr1;
  intptr1 = (int *) ulintptr1;
  ++ulintptr2;
  intptr2 = (int *) ulintptr2;
  ++ulintptr3;
  intptr3 = (int *) ulintptr3;

  for(i = 0; i < fpLength1; ++i) {
    andInt = *intptr1 & *intptr2;
    memcpy(intptr3, &andInt, sizeof(int));
    ++intptr1;
    ++intptr2;
    ++intptr3;
  }

  *length = fpLength1 + sizeof(unsigned long int);

  return initid->ptr;
}

my_bool bit_fp_or_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2) {
    strcpy(message, "Wrong number of arguments: BIT_FP_OR() requires two arguments");
    return 1;
  }
  if ((args->arg_type[0] != STRING_RESULT) || (args->arg_type[1] != STRING_RESULT)) {
    strcpy(message, "Wrong argument type: BIT_FP_OR() requires a STRING and a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char *) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void bit_fp_or_deinit(UDF_INIT *initid __attribute__((unused)))
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *bit_fp_or(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  unsigned long int *ulintptr1 = NULL;
  unsigned long int *ulintptr2 = NULL;
  unsigned long int *ulintptr3 = NULL;
  int *intptr1 = NULL;
  int *intptr2 = NULL;
  int *intptr3 = NULL;
  unsigned long int fpLength1 = 0;
  unsigned long int fpLength2 = 0;
  int orInt = 0;
  unsigned long int i = 0;

  if ((args->args[0] == NULL) || (args->args[1] == NULL)) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;

    return 0;
  }

  ulintptr1 = (unsigned long int *) args->args[0];
  fpLength1 = ulintptr1[0];
  ulintptr2 = (unsigned long int *) args->args[1];
  fpLength2 = ulintptr2[0];

  if (fpLength1 != fpLength2) {
    /* The both fingerprint must have the same length) */
    *is_null = 1;
    *error = 1;

    return 0;
  }

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;
  ulintptr3 = (unsigned long int *) initid->ptr;
  memcpy(ulintptr3, &fpLength1, sizeof(unsigned long int));

  ++ulintptr1;
  intptr1 = (int *) ulintptr1;
  ++ulintptr2;
  intptr2 = (int *) ulintptr2;
  ++ulintptr3;
  intptr3 = (int *) ulintptr3;

  for(i = 0; i < fpLength1; ++i) {
    orInt = *intptr1 | *intptr2;
    memcpy(intptr3, &orInt, sizeof(int));
    ++intptr1;
    ++intptr2;
    ++intptr3;
  }

  *length = fpLength1 + sizeof(unsigned long int);

  return initid->ptr;
}

my_bool bit_fp_count_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: BIT_FP_COUNT() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: BIT_FP_COUNT() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void bit_fp_count_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong bit_fp_count(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null __attribute__((unused)), char *error)
{
  int *intptr = NULL;
  unsigned long int *ulintptr = NULL;
  unsigned long int fpLength = 0;
  long int fpIntVal = 0;
  unsigned long int bitCount = 0;
  unsigned long int i = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;

    return 0;
  }

  *error = 0;

  ulintptr = (unsigned long int *) args->args[0];
  fpLength = ulintptr[0];

  if (fpLength % sizeof(int)) {
    /* The fingerprint is a multiple of int */
    *is_null = 1;
    *error = 1;

    return 0;
  }

  ++ulintptr;

  intptr = (int *) ulintptr;

  for(i = 0; i < fpLength/sizeof(int); ++i) {
    fpIntVal = intptr[i];
    for (; fpIntVal; fpIntVal = fpIntVal<<1) {
      if (fpIntVal < 0) { ++bitCount; }
    }
  }

  return bitCount;
}

#endif /* HAVE_DLOPEN */
