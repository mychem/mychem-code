/***************************************************************************
 *   Copyright (C) 2009-2011 by CNRS                                       *
 *   jerome.pansanel@iphc.cnrs.fr -- Project founder and lead developer    *
 *   aureliedeluca@gmail.com -- Developer                                  *
 *   bjoern@gruening.eu -- Developer                                       *
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
 * related to chemical file comparison.
 * @file molmatch_wrapper.h
 * @short Wrapper for the Mychem molmatch module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 * @author Bjoern Gruening <bjoern@gruenings.eu>
 */

#ifndef __MOLMATCH_WRAPPER_H
#define __MOLMATCH_WRAPPER_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /**
   * @short Checks if a molecule is a substructure of an other molecule.
   * @param smarts_pattern The molecule to check (SMARTS format)
   * @param serializedMolecule The reference molecule (serialized OBMol object)
   * @return 1 if query is a substructure of reference
   */
  long long match_substructure(const char *smarts_pattern, const char *serializedMolecule);

  /**
   * @short Returns the atom ids of the reference molecule's atoms that are
   * contained in substructures matching the query.
   * @param smarts_pattern The molecule to check (SMARTS format)
   * @param serializedMolecule The reference molecule (serialized OBMol object)
   * @return The list of atom ids
   */
  char *substructure_atom_ids(const char *smarts_pattern, const char *serializedMolecule);

  /**
   * @short Returns the number of substructures within a reference structure.
   * @param smarts_pattern The substructure to check (SMARTS format)
   * @param serializedMolecule The reference structure (serialized OBMol object)
   * @return The number of substructure
   */
  long long substructure_count(const char *smarts_pattern, const char *serializedMolecule);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MOLMATCH_WRAPPER_H */
