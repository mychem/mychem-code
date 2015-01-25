/***************************************************************************
 *   Copyright (C) 2009-2011 by CNRS                                       *
 *   jerome.pansanel@iphc.cnrs.fr -- Project founder and lead developer    *
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
 * This file is part of the Mychem software. It contains function declarations
 * related to chemical property calculations.
 * @file property_wrapper.h
 * @short Wrapper for the Mychem property module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 * @author Bjoern Gruening <bjoern@gruenings.eu>
 */

#ifndef __PROPERTY_WRAPPER_H
#define __PROPERTY_WRAPPER_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /**
   * @short Calculates the molecular weight of a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The molecular weight.
   */
  double getMolWeight(const char *molecule);

  /**
   * @short Calculates the exact mass of a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The exact mass.
   */
  double getExactMass(const char *molecule);

  /**
   * @short Returns the number of atoms in a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The number of atoms.
   */
  long long int getAtomCount(const char *molecule);

  /**
   * @short Returns the number of heavy atoms in a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The number of heavy atoms.
   */
  long long int getHeavyAtomCount(const char *molecule);

  /**
   * @short Returns the number of bonds in a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The number of bonds.
   */
  long long int getBondCount(const char *molecule);

  /**
   * @short Returns the number of rotable bonds in a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The number of rotable bonds.
   */
  long long int getRotableBondCount(const char *molecule);

  /**
   * @short Returns the total charge of a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The total charge.
   */
  long long int getTotalCharge(const char *molecule);

  /**
   * @short Returns the formula of a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The formula.
   */
  char *getFormula(const char *molecule);

  /**
   * @short Returns the number of hydrogen bond acceptors.
   * @param molecule The molecule used for the calculation.
   * @return The number of hydrogen bond acceptors.
   */
  long long int getAcceptors(const char *molecule);

  /**
   * @short Returns the number of hydrogen bond donors.
   * @param molecule The molecule used for the calculation.
   * @return The number of hydrogen bond donors.
   */
  long long int getDonors(const char *molecule);

  /**
   * @short Predicts the TPSA (Topological Polar Surface Area) of a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The topological polar surface area.
   */
  double getPSA(const char *molecule);

  /**
   * @short Predicts the MR (Molar Refractivity) of a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The molar refractivity.
   */
  double getMR(const char *molecule);

  /**
   * @short Predicts the LogP of a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The LogP.
   */
  double getLogP(const char *molecule);

  /**
   * @short Checks if a molecule has 2D coordinates.
   * @param molecule The molecule used for the calculation.
   * @return 1 if the molecule has 2D coordinates.
   */
  long long int is2D(const char *molecule);

  /**
   * @short Checks if a molecule has 3D coordinates.
   * @param molecule The molecule used for the calculation.
   * @return 1 if the molecule has 3D coordinates.
   */
  long long int is3D(const char *molecule);

  /**
   * @short Checks if a molecule is chiral.
   * @param molecule The molecule used for the calculation.
   * @return 1 if the molecule is chiral.
   */
  long long int isChiral(const char *molecule);

  /**
   * @short Returns the number of rings in a molecule.
   * @param molecule The molecule used for the calculation.
   * @return The number of rings (SSSR).
   */
  long long int getRingCount(const char *molecule);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PROPERTY_WRAPPER_H */

