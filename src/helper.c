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
 * MySQL and related to generic informations.
 * @file helper.c
 * @short Function definitions of the Mychem helper module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 */

#include "helper.h"
#include "helper_wrapper.h"
#include <mychem/config.h>

#ifdef HAVE_DLOPEN

my_bool mychem_version_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 0) {
    strcpy(message, "Wrong number of arguments: MYCHEM_VERSION() requires no argument");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_NAME_LENGTH;
  initid->const_item = 1;

  if (!(initid->ptr  = (char *) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void mychem_version_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *mychem_version(UDF_INIT *initid, UDF_ARGS *args __attribute__((unused)), char *result, unsigned long *length, char *is_null, char *error)
{
  memset(initid->ptr, 0, initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  *length = strlen(MYCHEM_VERSION);
  strncat(initid->ptr, MYCHEM_VERSION, *length);

  return initid->ptr;
}

my_bool openbabel_version_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 0) {
    strcpy(message, "Wrong number of arguments: OPENBABEL_VERSION() requires no argument");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_NAME_LENGTH;
  initid->const_item = 1;

  if (!(initid->ptr  = (char *) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void openbabel_version_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *openbabel_version(UDF_INIT *initid, UDF_ARGS *args __attribute__((unused)), char *result, unsigned long *length, char *is_null, char *error)
{
  char *babel_version = NULL;

  memset(initid->ptr, 0, initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  babel_version = getOpenBabelVersion();

  /* Return NULL if babel_version is NULL */
  if (babel_version == NULL) {
    *is_null=1;
    *error = 1;

    return NULL;
  }

  *length = strlen(babel_version);
  strncat(initid->ptr, babel_version, *length);

  free(babel_version);

  return initid->ptr;
}

my_bool inchi_version_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 0) {
    strcpy(message, "Wrong number of arguments: INCHI_VERSION() requires no argument");
    return 1;
  }

  initid->maybe_null = 1;
  initid->max_length = MAX_NAME_LENGTH;
  initid->const_item = 1;

  if (!(initid->ptr  = (char *) malloc(sizeof(char)*initid->max_length))) {
    strcpy(message, "Couldn't allocate memory");
    return 1;
  }

  return 0;
}

void inchi_version_deinit(UDF_INIT *initid)
{
  if (initid->ptr) {
    free(initid->ptr);
  }
}

char *inchi_version(UDF_INIT *initid, UDF_ARGS *args __attribute__((unused)), char *result, unsigned long *length, char *is_null, char *error)
{
  char *inchi_version = NULL;

  memset(initid->ptr, 0, initid->max_length);
  *result = 0;
  *is_null = 0;
  *error = 0;

  inchi_version = getInChIVersion();

  /* Return NULL if inchi_version is NULL */
  if (inchi_version == NULL) {
    *is_null=1;
    *error = 1;

    return NULL;
  }

  *length = strlen(inchi_version);
  strncat(initid->ptr, inchi_version, *length);

  free(inchi_version);

  return initid->ptr;
}
#endif /* HAVE_DLOPEN */

