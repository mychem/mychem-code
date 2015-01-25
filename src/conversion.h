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
 * used by MySQL and related to chemical file conversion.
 * @file conversion.h
 * @short Function declarations of the Mychem conversion module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#ifndef __CONVERSION_H
#define __CONVERSION_H

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

/* static pthread_mutex_t obmtx; */

#ifdef HAVE_DLOPEN

/**
 * @short Initializes the molfile_to_molecule function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molfile_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molfile_to_molecule_init().
 * @param initid The structure filled by molfile_to_molecule_init()
 */
void molfile_to_molecule_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MDL Molfile format to a molecule in MOLECULE_TYPE format.
 * @param initid A structure filled by molfile_to_molecule_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molfile_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the molecule_to_molfile function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molecule_to_molfile_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molecule_to_molfile_init().
 * @param initid The structure filled by molecule_to_molfile_init()
 */
void molecule_to_molfile_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a molecule in MDL Molfile format.
 * @param initid A structure filled by molecule_to_molfile_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molecule_to_molfile(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the V3000_to_molecule function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool V3000_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by V3000_to_molecule_init().
 * @param initid the structure filled by V3000_to_molecule_init()
 */
void V3000_to_molecule_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MDL V3000 format to a molecule in MOLECULE_TYPE format.
 * @param initid A structure filled by V3000_to_molecule_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *V3000_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the molecule_to_V3000 function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molecule_to_V3000_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molecule_to_V3000_init().
 * @param initid The structure filled by molecule_to_V3000_init()
 */
void molecule_to_V3000_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a molecule in MDL V3000 format.
 * @param initid A structure filled by molecule_to_V3000_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molecule_to_V3000(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the smiles_to_molecule function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool smiles_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by smiles_to_molecule_init().
 * @param initid The structure filled by smiles_to_molecule_init()
 */
void smiles_to_molecule_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in SMILES format to a molecule in MOLECULE_TYPE format.
 * @param initid A structure filled by smiles_to_molecule_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *smiles_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the molecule_to_smiles function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molecule_to_smiles_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molecule_to_smiles_init().
 * @param initid The structure filled by molecule_to_smiles_init()
 */
void molecule_to_smiles_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a molecule in SMILES.
 * @param initid A structure filled by molecule_to_smiles_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molecule_to_smiles(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the molecule_to_molecule function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molecule_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molecule_to_molecule_init().
 * @param initid The structure filled by molecule_to_molecule_init()
 */
void molecule_to_molecule_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in OLD_TYPE format to a molecule in MOLECULE_TYPE format.
 * @param initid A structure filled by molecule_to_molecule_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molecule_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the cml_to_molecule function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool cml_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by cml_to_molecule_init().
 * @param initid the structure filled by cml_to_molecule_init()
 */
void cml_to_molecule_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in cml format to a molecule in MOLECULE_TYPE format.
 * @param initid A structure filled by cml_to_molecule_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *cml_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the molecule_to_cml function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molecule_to_cml_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molecule_to_cml_init().
 * @param initid The structure filled by molecule_to_cml_init()
 */
void molecule_to_cml_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a molecule in cml format.
 * @param initid A structure filled by molecule_to_cml_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molecule_to_cml(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the fingerprint function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool fingerprint_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by fingerprint_init().
 * @param initid The structure filled by fingerprint_init()
 */
void fingerprint_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a fingerprint.
 * @param initid A structure filled by fingerprint_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *fingerprint(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the fingerprint2 function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool fingerprint2_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by fingerprint2_init().
 * @param initid The structure filled by fingerprint2_init()
 */
void fingerprint2_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a fingerprint, type FP2.
 * @param initid A structure filled by fingerprint2_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *fingerprint2(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the fingerprint3 function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool fingerprint3_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by fingerprint3_init().
 * @param initid The structure filled by fingerprint3_init()
 */
void fingerprint3_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a fingerprint, type FP3.
 * @param initid A structure filled by fingerprint3_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *fingerprint3(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the fingerprint4 function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool fingerprint4_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by fingerprint4_init().
 * @param initid The structure filled by fingerprint4_init()
 */
void fingerprint4_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a fingerprint, type FP4.
 * @param initid A structure filled by fingerprint4_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *fingerprint4(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the molecule_to_canonical_smiles function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molecule_to_canonical_smiles_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molecule_to_canonical_smiles_init().
 * @param initid The structure filled by molecule_to_canonical_smiles_init()
 */
void molecule_to_canonical_smiles_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a canonical smiles.
 * @param initid A structure filled by molecule_to_canonical_smiles_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molecule_to_canonical_smiles(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the inchi_to_molecule function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool inchi_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by inchi_to_molecule_init().
 * @param initid The structure filled by inchi_to_molecule_init()
 */
void inchi_to_molecule_deinit(UDF_INIT *initid);

/**
 * @short Converts an InChI string to a molecule in MOLECULE_TYPE format.
 * @param initid A structure filled by inchi_to_molecule_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *inchi_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the molecule_to_inchi function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molecule_to_inchi_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molecule_to_inchi_init().
 * @param initid The structure filled by molecule_to_inchi_init()
 */
void molecule_to_inchi_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to an InChI string.
 * @param initid A structure filled by molecule_to_inchi_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molecule_to_inchi(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the molecule_to_serializedOBMol function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molecule_to_serializedOBMol_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molecule_to_serializedOBMol_init().
 * @param initid The structure filled by molecule_to_serializedOBMol_init()
 */
void molecule_to_serializedOBMol_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a serialized OBMol string.
 * @param initid A structure filled by molecule_to_serializedOBMol()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molecule_to_serializedOBMol(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the pdb_to_molecule function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool pdb_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by pdb_to_molecule_init().
 * @param initid The structure filled by pdb_to_molecule_init()
 */
void pdb_to_molecule_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in Protein Data Bank format data to a molecule in MOLECULE_TYPE format.
 * @param initid A structure filled by pdb_to_molecule_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *pdb_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the mol2_to_molecule function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool mol2_to_molecule_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by mol2_to_molecule_init().
 * @param initid The structure filled by mol2_to_molecule_init()
 */
void mol2_to_molecule_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in mol2 format to a molecule in MOLECULE_TYPE format.
 * @param initid A structure filled by mol2_to_molecule_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *mol2_to_molecule(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
/**
 * @short Initializes the molecule_to_mol2 function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molecule_to_mol2_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molecule_to_mol2_init().
 * @param initid The structure filled by molecule_to_mol2_init()
 */
void molecule_to_mol2_deinit(UDF_INIT *initid);

/**
 * @short Converts a molecule in MOLECULE_TYPE format to a molecule in mol2 format.
 * @param initid A structure filled by molecule_to_mol2_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The converted molecule
 */
char *molecule_to_mol2(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

#endif /* HAVE_DLOPEN */

#endif /* __CONVERSION_H */

