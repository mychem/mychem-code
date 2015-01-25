/***************************************************************************
 *   Copyright (C) 2009-2011 by CNRS                                       *
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
 * MySQL and related to molecule modifications.
 * @file modification.c
 * @short Function definitions of the Mychem modification module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 */

#include "modification.h"
#include "modification_wrapper.h"
#include <mychem/config.h>

#ifdef HAVE_DLOPEN

my_bool add_hydrogens_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: ADD_HYDROGENS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: ADD_HYDROGENS() requires a STRING");
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

void add_hydrogens_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *add_hydrogens(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *outputMol = NULL;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = ob_add_hydrogens(inputMol);

  /* Return NULL if outputMol is NULL */
  if (outputMol == NULL) {
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  *length = strlen(outputMol);
  strncat(initid->ptr, outputMol, *length);

  free(inputMol);
  free(outputMol);

  return initid->ptr;
}

my_bool remove_hydrogens_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: REMOVE_HYDROGENS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: REMOVE_HYDROGENS() requires a STRING");
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

void remove_hydrogens_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *remove_hydrogens(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *outputMol = NULL;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = ob_remove_hydrogens(inputMol);

  /* Return NULL if outputMol is NULL */
  if (outputMol == NULL) {
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  *length = strlen(outputMol);
  strncat(initid->ptr, outputMol, *length);

  free(inputMol);
  free(outputMol);

  return initid->ptr;
}

my_bool strip_salts_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: REMOVE_HYDROGENS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: REMOVE_HYDROGENS() requires a STRING");
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

void strip_salts_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *strip_salts(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *outputMol = NULL;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = ob_strip_salts(inputMol);

  /* Return NULL if outputMol is NULL */
  if (outputMol == NULL) {
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  *length = strlen(outputMol);
  strncat(initid->ptr, outputMol, *length);

  free(inputMol);
  free(outputMol);

  return initid->ptr;
}

#endif /* HAVE_DLOPEN */

