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
 * This file is part of the Mychem software. It contains function declarations
 * related to chemical file conversion.
 * @file conversion_wrapper.h
 * @short Wrapper for the Mychem conversion module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 */

#ifndef __CONVERSION_WRAPPER_H
#define __CONVERSION_WRAPPER_H

#include <mychem/structures.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /**
   * @short Converts a file format to an other.
   * @param molecule The molecule to convert.
   * @param in_type Input format.
   * @param out_type Output format.
   * @return converted molecule
  */
  char *conversion(const char *molecule, const char *in_type, const char *out_type);

  /**
   * @short Converts a V3000 molecule to the default molecule type.
   * @param V3000 The V3000 molecule to convert.
   * @return converted molecule.
   */
  char *V3000conversion(const char *V3000);

  /**
   * @short Converts a molecule to a V3000 molfile.
   * @param molecule The molecule to convert.
   * @return V3000 molecule.
   */
  char *conversionV3000(const char *molecule);

 /**
   * @short Converts a cml molecule to the default molecule type.
   * @param cml The cml molecule to convert.
   * @return the converted cml.
   */
  char *CMLconversion(const char *cml);

 /**
   * @short Converts a molecule to a cml molecule.
   * @param molecule The cml molecule to convert.
   * @return the converted molecule.
   */
  char *conversionCML(const char *molecule);

  /**
   * @short Converts a molecule to a fingerprint.
   * @param molecule The molecule to convert.
   * @param type The type of fingerprint (FP2, FP3 or FP4).
   * @return The fingerprint.
   */
  char *conversionFPT(const char *molecule, const char *type);

  /**
   * @short Converts a molecule to a canonical SMILES.
   * @param molecule The molecule to convert.
   * @return the canonical SMILES.
   */
  char *conversionCAN(const char *molecule);

  /**
   * @short Converts a molecule to a 1D serialized OBMol object.
   * @param molecule The molecule to convert.
   * @return the serialized OBMol object.
   */
  char *serializeMolecule(const char *molecule);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CONVERSION_WRAPPER_H */
 
