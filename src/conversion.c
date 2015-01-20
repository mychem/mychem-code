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
 * MySQL and related to chemical file conversion.
 * @file conversion.c
 * @short Function definitions of the Mychem conversion module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 */

#include "conversion.h"
#include "conversion_wrapper.h"
#include <mychem/config.h>
#include <mychem/structures.h>

#ifdef HAVE_DLOPEN

my_bool molfile_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLFILE_TO_MOLECULE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLFILE_TO_MOLECULE() requires a STRING");
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

void molfile_to_molecule_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molfile_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *outputMol = NULL;

  const char *inputFormat = "MOL";
  const char *outputFormat = MOLECULE_TYPE;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat);

  if (outputMol == NULL) {
    *error = 1;
    *is_null = 1;
    free(inputMol);

    return NULL;
  }

  *length = strlen(outputMol);
  strncat(initid->ptr, outputMol, *length);

  free(inputMol);
  free(outputMol);

  return initid->ptr;
}

my_bool molecule_to_molfile_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLECULE_TO_MOLFILE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLECULE_TO_MOLFILE() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void molecule_to_molfile_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molecule_to_molfile(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *outputMol = NULL;

  const char *inputFormat = MOLECULE_TYPE;
  const char *outputFormat = "MOL";

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;
  
  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat);

  /* Return NULL if the outputMol is empty */
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

my_bool V3000_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: V3000_TO_MOLECULE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: V3000_TO_MOLECULE() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void V3000_to_molecule_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *V3000_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
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

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = V3000conversion(inputMol);

  /* Return NULL if the outputMol is empty */
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

my_bool molecule_to_V3000_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLECULE_TO_V3000() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLECULE_TO_V3000() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void molecule_to_V3000_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molecule_to_V3000(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
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

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversionV3000(inputMol);

  /* Return NULL if the outputMol is empty */
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

my_bool smiles_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: SMILES_TO_MOLECULE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: SMILES_TO_MOLECULE() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void smiles_to_molecule_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *smiles_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
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

  const char *inputFormat = "SMI";
  const char *outputFormat = MOLECULE_TYPE;

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat);

  /* Return NULL if the outputMol is empty */
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

my_bool molecule_to_smiles_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLECULE_TO_SMILES() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLECULE_TO_SMILES() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void molecule_to_smiles_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molecule_to_smiles(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
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

  const char *inputFormat = MOLECULE_TYPE;
  const char *outputFormat = "SMI";

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;
  
  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat);

  /* Return NULL if the outputMol is empty */
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

my_bool molecule_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLECULE_TO_MOLECULE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLECULE_TO_MOLECULE() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void molecule_to_molecule_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molecule_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
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

  const char *inputFormat = "INCHI";
  const char *outputFormat = MOLECULE_TYPE;

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat);

  /* Return NULL if the outputMol is empty */
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

my_bool cml_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: CML_TO_MOLECULE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: CML_TO_MOLECULE() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void cml_to_molecule_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *cml_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
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
 
  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = CMLconversion(inputMol);

  /* Return NULL if the outputMol is empty */
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

my_bool molecule_to_cml_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLECULE_TO_CML() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLECULE_TO_CML() requires a STRING");
    return 1;
  }
  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void molecule_to_cml_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molecule_to_cml(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
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

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversionCML(inputMol);

  /* Return NULL if the outputMol is empty */
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

my_bool fingerprint_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2) {
    strcpy(message, "Wrong number of arguments: FINGERPRINT() requires two arguments");
    return 1;
  }
  if ((args->arg_type[0] != STRING_RESULT) || (args->arg_type[1] != STRING_RESULT)) {
    strcpy(message,"Wrong argument type: FINGERPRINT() requires a STRING and a STRING");
    return 1;
  }

  if ((strncmp(args->args[1],"FP2",3) && strncmp(args->args[1],"FP3",3) && strncmp(args->args[1],"FP4",3))) {
    strcpy(message,"Wrong type of fingerprint: valid types are FP2, FP3 and FP4");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void fingerprint_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *fingerprint(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *fpType =  (char *) malloc(sizeof(char)*4);
  char *serializedOutput = NULL;
  unsigned long int *intptr = NULL;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  strncpy(fpType, args->args[1], 3);
  fpType[3] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  serializedOutput = conversionFPT(inputMol, fpType);

  /* Return NULL if the fingerprint is empty */
  if (serializedOutput == NULL) {
    *is_null = 1;
    *error = 1;
    free(fpType);
    free(inputMol);

    return NULL;
  }

  intptr = (unsigned long int *) serializedOutput;
  *length = intptr[0] + sizeof(unsigned long int);
  memcpy(initid->ptr, serializedOutput, *length);

  free(inputMol);  
  free(fpType);
  free(serializedOutput);

  return initid->ptr;
}

my_bool fingerprint2_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: FINGERPRINT2() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: FINGERPRINT2() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void fingerprint2_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *fingerprint2(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *serializedOutput = NULL;
  unsigned long int *intptr = NULL;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  serializedOutput = conversionFPT(inputMol, "FP2");

  /* Return NULL if the fingerprint is empty */
  if (serializedOutput == NULL) {
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  intptr = (unsigned long int *) serializedOutput;
  *length = intptr[0] + sizeof(unsigned long int);
  memcpy(initid->ptr, serializedOutput, *length);

  free(inputMol);  
  free(serializedOutput);
  
  return initid->ptr;
}

my_bool fingerprint3_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: FINGERPRINT3() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: FINGERPRINT3() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void fingerprint3_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *fingerprint3(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *serializedOutput = NULL;
  unsigned long int *intptr = NULL;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  serializedOutput = conversionFPT(inputMol, "FP3");

  /* Return NULL if the fingerprint is empty */
  if (serializedOutput == NULL) {
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  intptr = (unsigned long int *) serializedOutput;
  *length = intptr[0] + sizeof(unsigned long int);
  memcpy(initid->ptr, serializedOutput, *length);

  free(inputMol);  
  free(serializedOutput);
  
  return initid->ptr;
}

my_bool fingerprint4_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: FINGERPRINT2() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: FINGERPRINT2() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void fingerprint4_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *fingerprint4(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *serializedOutput = NULL;
  unsigned long int *intptr = NULL;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  serializedOutput = conversionFPT(inputMol, "FP4");

  /* Return NULL if the fingerprint is empty */
  if (serializedOutput == NULL) {
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  intptr = (unsigned long int *) serializedOutput;
  *length = intptr[0] + sizeof(unsigned long int);
  memcpy(initid->ptr, serializedOutput, *length);

  free(inputMol);
  free(serializedOutput);
  
  return initid->ptr;
}

my_bool molecule_to_canonical_smiles_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLECULE_TO_CANONICAL_SMILES() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLECULE_TO_CANONICAL_SMILES() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void molecule_to_canonical_smiles_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molecule_to_canonical_smiles(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
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
  
  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversionCAN(inputMol);

  /* Return NULL if the outputMol is empty */
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

my_bool inchi_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: INCHI_TO_MOLECULE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: INCHI_TO_MOLECULE() requires a STRING");
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

void inchi_to_molecule_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *inchi_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
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

  const char *inputFormat = "INCHI";
  const char *outputFormat = MOLECULE_TYPE;

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat);

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

my_bool molecule_to_inchi_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLECULE_TO_INCHI() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLECULE_TO_INCHI() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void molecule_to_inchi_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molecule_to_inchi(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *outputMol = NULL;

  const char *inputFormat = MOLECULE_TYPE;
  const char *outputFormat = "INCHI";

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;
  
  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat);

  /* Return NULL if the outputMol is empty */
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

my_bool molecule_to_serializedOBMol_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLECULE_TO_BINARY() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLECULE_TO_BINARY() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void molecule_to_serializedOBMol_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molecule_to_serializedOBMol(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  unsigned int *serializedOBMol = NULL;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  serializedOBMol = (unsigned int*) serializeMolecule(inputMol);

  /* Return NULL if the serializedOBMol is empty */
  if (serializedOBMol == NULL) {
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  *length = serializedOBMol[0] + sizeof(unsigned int);
  memcpy(initid->ptr, serializedOBMol, *length);

  free(inputMol);
  free(serializedOBMol);
  
  return initid->ptr;
}

my_bool pdb_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: PDB_TO_MOLECULE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: PDB_TO_MOLECULE() requires a STRING");
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

void pdb_to_molecule_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *pdb_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{

  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *outputMol = NULL;

  const char *inputFormat = "PDB";
  const char *outputFormat = MOLECULE_TYPE;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat);

  /* Return NULL if the outputMol is empty */
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

my_bool mol2_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOL2_TO_MOLECULE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOL2_TO_MOLECULE() requires a STRING");
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

void mol2_to_molecule_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *mol2_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *outputMol = NULL;

  const char *inputFormat = "MOL2";
  const char *outputFormat = MOLECULE_TYPE;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat);

  /* Return NULL if the outputMol is empty */
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

my_bool molecule_to_mol2_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLECULE_TO_MOL2() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLECULE_TO_MOL2() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_VALUE_LENGTH;

  if (!(initid->ptr = (char*) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void molecule_to_mol2_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *molecule_to_mol2(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *outputMol = NULL;

  const char *inputFormat = MOLECULE_TYPE;
  const char *outputFormat = "MOL2";

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;
  
  memset(initid->ptr, 0, sizeof(char)*initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  outputMol = conversion(inputMol, inputFormat, outputFormat); 

  /* Return NULL if the outputMol is empty */
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

