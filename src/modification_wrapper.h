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
 * related to molecule modifications.
 * @file modification_wrapper.h
 * @short Wrapper for the Mychem modification module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 * @author Aurelie De Luca <aureliedeluca@gmail.com>
 */

#ifndef __MODIFICATION_WRAPPER_H
#define __MODIFICATION_WRAPPER_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /**
   * @short Adds the hydrogen atoms of a molecule.
   * @param molecule The molecule where to add hydrogens.
   * @return The modified molecule.
   */
  char  *ob_add_hydrogens(const char *molecule);

  /**
   * @short Removes the hydrogen atoms of a molecule.
   * @param molecule The molecule where to remove hydrogens.
   * @return The modified molecule.
   */
  char *ob_remove_hydrogens(const char *molecule);

  /**
   * @short Removes all atoms except for the larger contiguous fragment.
   * @param molecule The molecule where to remove the salts.
   * @return The cleaned molecule.
   */
  char *ob_strip_salts(const char *molecule);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MODIFICATION_WRAPPER_H */

