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
 * related to Mychem informations.
 * @file  helper_wrapper.h
 * @short Wrapper for the Mychem helper module.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#ifndef __HELPER_WRAPPER_H
#define __HELPER_WRAPPER_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /**
   * @short Returns the version of the Open Babel library.
   * @return The version of the Open Babel library.
   */
  char *getOpenBabelVersion();

  /**
   * @short Returns the version of the InChI library.
   * @return The version of the InChI library.
   */
  char *getInChIVersion();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __HELPER_WRAPPER_H */

