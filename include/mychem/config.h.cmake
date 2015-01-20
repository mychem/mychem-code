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
 * This file is part of the Mychem software. It defines default values used
 * by Mychem.
 * @file config.h
 * @short Mychem config file.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#ifndef __MYCHEM_CONFIG_H
#define __MYCHEM_CONFIG_H

/* Default molecle type */
#define MOLECULE_TYPE "MOL"

/* Max length for varchar */
#define MAX_NAME_LENGTH 256

/* Max length for a text or a blob */
#define MAX_VALUE_LENGTH 65536

/* Mychem major version */
#define MYCHEM_VERSION_MAJOR "${MYCHEM_VERSION_MAJOR}"

/* Mychem minor version */
#define MYCHEM_VERSION_MINOR "${MYCHEM_VERSION_MINOR}"

/* Mychem release version */
#define MYCHEM_VERSION_RELEASE "${MYCHEM_VERSION_RELEASE}"

/* Mychem version */
#define MYCHEM_VERSION "${MYCHEM_VERSION}"

#endif /* __MYCHEM_CONFIG_H */

