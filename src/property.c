/***************************************************************************
 *   Copyright (C) 2009-2011 by CNRS                                       *
 *   jerome.pansanel@iphc.cnrs.fr -- Project founder and lead              *
 *   aureliedeluca@gmail.com -- Developer                                  *
 *   bjoern@gruenings.eu -- Developer                                      *
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
 * MySQL and related to chemical property calculations.
 * @file property.c
 * @short Function definitions of the Mychem property module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 * @author Bjoern Gruening <bjoern@gruenings.eu>
 */

#include "property.h"
#include "property_wrapper.h"
#include <mychem/config.h>

#ifdef HAVE_DLOPEN

my_bool molweight_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLWEIGHT() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLWEIGHT() requires a STRING");
    return 1;
  }

  initid->decimals = 6;
  initid->max_length=19;
  initid->maybe_null = 1;

  return 0;
}

void molweight_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

double molweight(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  double weight = 0.0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;


  *is_null = 0;
  *error = 0;

  weight = getMolWeight(inputMol);

  free(inputMol);

  return weight;
}

my_bool exactmass_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: EXACTMASS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: EXACTMASS() requires a STRING");
    return 1;
  }

  initid->decimals = 6;
  initid->max_length=19;
  initid->maybe_null = 1;

  return 0;
}

void exactmass_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

double exactmass(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  double weight = 0.0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error = 0;

  weight = getExactMass(inputMol);

  free(inputMol);

  return weight;
}

my_bool number_of_atoms_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: NUMBER_OF_ATOMS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: NUMBER_OF_ATOMS() requires a STRING");
    return 1;
  }
  if (args->arg_count != 1 || args->arg_type[0] != STRING_RESULT)
  {
    strcpy(message,"You have an error in your SQL syntax; Check the Mychem manual for the right syntax to use with the number_of_atoms function");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void number_of_atoms_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong number_of_atoms(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong count = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error = 0;

  count = getAtomCount(inputMol);

  free(inputMol);

  return count;
}

my_bool number_of_heavy_atoms_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: NUMBER_OF_HEAVY_ATOMS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: NUMBER_OF_HEAVY_ATOMS() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void number_of_heavy_atoms_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong number_of_heavy_atoms(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong count = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error = 0;

  count = getHeavyAtomCount(inputMol);

  free(inputMol);

  return count;
}

my_bool number_of_bonds_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: NUMBER_OF_BONDS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: NUMBER_OF_BONDS() requires a STRING");
    return 1;
  }

  initid->maybe_null = 0;

  return 0;
}

void number_of_bonds_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong number_of_bonds(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong count = 0;

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  count = getBondCount(inputMol);

  free(inputMol);

  return count;
}

my_bool number_of_rotable_bonds_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: NUMBER_OF_ROTABLE_BONDS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: NUMBER_OF_ROTABLE_BONDS() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void number_of_rotable_bonds_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong number_of_rotable_bonds(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong count = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error = 0;

  count = getRotableBondCount(inputMol);

  free(inputMol);

  return count;
}

my_bool total_charge_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: TOTAL_CHARGE() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: TOTAL_CHARGE() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void total_charge_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong total_charge(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong count = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error = 0;

  count = getTotalCharge(inputMol);

  free(inputMol);

  return count;
}

my_bool molformula_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLFORMULA() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLFORMULA() requires a STRING");
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

void molformula_deinit(UDF_INIT *initid)
{
  if(initid->ptr) {
    free(initid->ptr);
  }
}

char *molformula(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  char *formula = NULL;

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

  formula = getFormula(inputMol);

  /* Return NULL is the formula is empty */
  if (formula == NULL) {
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return NULL;
  }

  *length = strlen(formula);
  strncat(initid->ptr, formula, *length);

  free(inputMol);
  free(formula);

  return initid->ptr;
}

my_bool number_of_acceptors_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: NUMBER_OF_ACCEPTORS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: NUMBER_OF_ACCEPTORS() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void number_of_acceptors_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong number_of_acceptors(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong acceptors = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  acceptors = getAcceptors(inputMol);

  free(inputMol);

  return acceptors;
}

my_bool number_of_donors_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: NUMBER_OF_DONORS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: NUMBER_OF_DONORS() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void number_of_donors_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong number_of_donors(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong donors = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  donors = getDonors(inputMol);

  free(inputMol);

  return donors;
}

my_bool molpsa_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLPSA() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLPSA() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void molpsa_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

double molpsa(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  double PSA = 0.0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  PSA = getPSA(inputMol);

  free(inputMol);

  return PSA;
}

my_bool molmr_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLMR() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLMR() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void molmr_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

double molmr(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  double MR = 0.0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  MR = getMR(inputMol);

  free(inputMol);

  return MR;
}

my_bool mollogp_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: MOLLOGP() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: MOLOGP() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void mollogp_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

double mollogp(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  double LogP = 0.0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  LogP = getLogP(inputMol);

  free(inputMol);

  return LogP;
}

my_bool is_2D_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: IS_2D() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: IS_2D() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void is_2D_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong is_2D(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong is2DBool = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  is2DBool = is2D(inputMol);

  free(inputMol);

  return is2DBool;
}

my_bool is_3D_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: IS_3D() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: IS_3D() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void is_3D_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong is_3D(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong is3DBool = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  is3DBool = is3D(inputMol);

  free(inputMol);

  return is3DBool;
}

my_bool is_chiral_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: IS_CHIRAL() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: IS_CHIRAL() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void is_chiral_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong is_chiral(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong isChiralBool = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  isChiralBool = isChiral(inputMol);

  free(inputMol);

  return isChiralBool;
}

my_bool number_of_rings_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1) {
    strcpy(message, "Wrong number of arguments: NUMBER_OF_RINGS() requires one argument");
    return 1;
  }
  if (args->arg_type[0] != STRING_RESULT) {
    strcpy(message,"Wrong argument type: NUMBER_OF_RINGS() requires a STRING");
    return 1;
  }

  initid->maybe_null = 1;

  return 0;
}

void number_of_rings_deinit(UDF_INIT *initid __attribute__((unused)))
{
}

longlong number_of_rings(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args, char *is_null, char *error)
{
  /* Fix a MySQL end string char issue */
  char *inputMol = (char *) malloc(sizeof(char)*(args->lengths[0]+1));
  longlong count = 0;

  if (args->args[0] == NULL) {
    /* Arguments can not be NULL */
    *is_null = 1;
    *error = 1;
    free(inputMol);

    return 0;
  }

  strncpy(inputMol, args->args[0], args->lengths[0]);
  inputMol[args->lengths[0]] = 0;

  *is_null = 0;
  *error =0;

  count = getRingCount(inputMol);

  free(inputMol);

  return count;
}

#endif /* HAVE_DLOPEN */

