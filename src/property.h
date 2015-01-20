/***************************************************************************
 *   Copyright (C) 2009-2011 by CNRS                                       *
 *   jerome.pansanel@iphc.cnrs.fr -- Project founder and lead developer    *
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
 * This file is part of the Mychem software. It contains function declarations
 * used by MySQL and related to chemical property calculations.
 * @file property.h
 * @short Function declarations of the Mychem property module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Bjoern Gruening <bjoern@gruenings.eu>
 */

#ifndef __PROPERTY_H
#define __PROPERTY_H

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
 * @short Initializes the molweight function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molweight_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molweight_init().
 * @param initid The structure filled by molweight_init()
 */
void molweight_deinit(UDF_INIT *initid);

/**
 * @short Calculates the molecular weight of a molecule.
 * @param initid A structure filled by molweight_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The molecular weight
 */
double molweight(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the exactmass function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool exactmass_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by exactmass_init().
 * @param initid The structure filled by exactmass_init()
 */
void exactmass_deinit(UDF_INIT *initid);

/**
 * @short Calculates the monoisotopic weight of a molecule.
 * @param initid A structure filled by exactmass_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The monoisotopic weight
 */
double exactmass(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the number_of_atoms function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool number_of_atoms_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by number_of_atoms_init().
 * @param initid The structure filled by number_of_atoms_init()
 */
void number_of_atoms_deinit(UDF_INIT *initid);

/**
 * @short Calculates the number of atoms in a molecule.
 * @param initid A structure filled by number_of_atoms_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The number of atoms
 */
longlong number_of_atoms(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the number_of_heavy_atoms function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool number_of_heavy_atoms_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by number_of_heavy_atoms_init().
 * @param initid The structure filled by number_of_heavy_atoms_init()
 */
void number_of_heavy_atoms_deinit(UDF_INIT *initid);

/**
 * @short Calculates the number of heavy atoms in a molecule.
 * @param initid A structure filled by number_of_heavy_atoms_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The number of heavy atoms
 */
longlong number_of_heavy_atoms(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the number_of_bonds function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool number_of_bonds_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by number_of_bonds_init().
 * @param initid The structure filled by number_of_bonds_init()
 */
void number_of_bonds_deinit(UDF_INIT *initid);

/**
 * @short Calculates the number of bonds in a molecule.
 * @param initid A structure filled by number_of_bonds_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The number of bonds
 */
longlong number_of_bonds(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the number_of_rotable_bonds function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool number_of_rotable_bonds_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by number_of_rotable_bonds_init().
 * @param initid The structure filled by number_of_rotable_bonds_init()
 */
void number_of_rotable_bonds_deinit(UDF_INIT *initid);

/**
 * @short Calculates the number of rotable bonds in a molecule.
 * @param initid A structure filled by number_of_rotable_bonds_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The number of rotable bonds
 */
longlong number_of_rotable_bonds(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the total_charge function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool total_charge_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by total_charge_init().
 * @param initid The structure filled by total_charge_init()
 */
void total_charge_deinit(UDF_INIT *initid);

/**
 * @short Calculates the total charge of a molecule.
 * @param initid A structure filled by total_charge_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The total charge of a molecule
 */
longlong total_charge(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the molformula function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molformula_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molformula_init().
 * @param initid The structure filled by molformula_init()
 */
void molformula_deinit(UDF_INIT *initid);

/**
 * @short Returns the molecular formula of a molecule.
 * @param initid A structure filled by molformula_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The molecular formula
 */
char *molformula(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);

/**
 * @short Initializes the number_of_acceptors function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool number_of_acceptors_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by number_of_acceptors_init().
 * @param initid The structure filled by number_of_acceptors_init()
 */
void number_of_acceptors_deinit(UDF_INIT *initid);

/**
 * @short Calculates the number of hydrogen-bond acceptors in a molecule.
 * @param initid A structure filled by number_of_acceptors_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The number of hydrogen-bond acceptors
 */
longlong number_of_acceptors(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the number_of_donors function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool number_of_donors_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by number_of_donors_init().
 * @param initid The structure filled by number_of_donors_init()
 */
void number_of_donors_deinit(UDF_INIT *initid);

/**
 * @short Calculates the number of hydrogen-bond donors in a molecule.
 * @param initid A structure filled by number_of_donors_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The number of hydrogen-bond donors
 */
longlong number_of_donors(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the molpsa function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molpsa_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molpsa_init().
 * @param initid The structure filled by molpsa_init()
 */
void molpsa_deinit(UDF_INIT *initid);

/**
 * @short Predicts the Topological Polar Surface Area (TPSA) of a molecule.
 * @param initid A structure filled by molpsa_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The topological polar surface area
 */
double molpsa(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the molmr function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool molmr_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by molmr_init().
 * @param initid The structure filled by molmr_init()
 */
void molmr_deinit(UDF_INIT *initid);

/**
 * @short Predicts the Molar Refractivity (MR) of a molecule.
 * @param initid A structure filled by molmr_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The molar refactivity
 */
double molmr(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the mollogp function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool mollogp_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by mollogp_init().
 * @param initid The structure filled by mollogp_init()
 */
void mollogp_deinit(UDF_INIT *initid);

/**
 * @short Predicts the LogP of a molecule.
 * @param initid A structure filled by mollogp_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The LogP
 */
double mollogp(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the is_2D function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool is_2D_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by is_2D_init().
 * @param initid The structure filled by is_2D_init()
 */
void is_2D_deinit(UDF_INIT *initid);

/**
 * @short Checks if a molecule has 2D coordinates.
 * @param initid A structure filled by is_2D_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return 1 if the molecule has 2D coordinates
 */
longlong is_2D(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the is_3D function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool is_3D_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by is_3D_init().
 * @param initid The structure filled by is_3D_init()
 */
void is_3D_deinit(UDF_INIT *initid);

/**
 * @short Checks if a molecule has 3D coordinates.
 * @param initid A structure filled by is_3D_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return 1 if a molecule has 3D coordinates.
 */
longlong is_3D(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the is_chiral function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool is_chiral_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by is_chiral_init().
 * @param initid The structure filled by is_chiral_init()
 */
void is_chiral_deinit(UDF_INIT *initid);

/**
 * @short Checks if a molecule is chiral.
 * @param initid A structure filled by is_chiral_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return 1 if the molecule is chiral
 */
longlong is_chiral(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

/**
 * @short Initializes the number_of_rings function.
 * @param initid A structure that the init function should fill
 * @param args A structure which contains arguments and related variables
 * @param message The error message that should be passed to the user on fail
 * @return True if an error is raised during the initialization
 */
my_bool number_of_rings_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

/**
 * @short Should free all resources allocated by number_of_rings_init().
 * @param initid The structure filled by number_of_rings_init()
 */
void number_of_rings_deinit(UDF_INIT *initid);

/**
 * @short Returns the number of rings in a molecule.
 * @param initid A structure filled by number_of_rings_init()
 * @param args A structure which contains arguments and related variables
 * @param result A buffer to save result
 * @param length A pointer to length of the above buffer
 * @param is_null Set to 1 if the result is null
 * @param error Set to 1 if something goes fatally wrong
 * @return The number of rings
 */
longlong number_of_rings(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

#endif /* HAVE_DLOPEN */

#endif /* __PROPERTY_H */

