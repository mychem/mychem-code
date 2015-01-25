/***************************************************************************
 *   Copyright (C) 2009-2012 by CNRS                                       *
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
 * This file is part of the Mychem software. It contains functions related
 * to the serialization of OBMol objects.
 * @file serialization.cpp
 * @short OBMol Serialization Methods.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
*/

#ifndef __SERIALIZATION_H
#define __SERIALIZATION_H

#include <openbabel/mol.h>
#include <mychem/structures.h>

/**
 * @short Serialize an OBMol object.
 * @param mol The OBMol object to serialize.
 * @return the serialized object.
 */
char *serializeOBMol(OpenBabel::OBMol &mol);

/**
 * @short Unserialize an OBMol object.
 * @param pOb The OBBase object to initialize.
 * @param serializedInput The OBMol object to unserialize.
 * @param stereoEnabled true if we need stereo informations
 * @return true if the unserialization is successful.
 */
bool unserializeOBMol(OpenBabel::OBBase* pOb, const char *serializedInput, bool stereoEnabled);

#endif /* __SERIALIZATION_H */

