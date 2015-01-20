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
 * This file is part of the Mychem software. It defines structures used
 * by Mychem.
 * @file structures.h
 * @short Mychem structure file.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 */

#ifndef __MYCHEM_STRUCTURES_H
#define __MYCHEM_STRUCTURES_H

typedef struct {
  unsigned long int size;
  char * str;
} binary_string;

typedef struct
{
  unsigned int idx;
  int hybridization;
  unsigned char atomicnum;
  unsigned short isotope;
  char formalcharge;
  unsigned char spinmultiplicity;
  unsigned char aromatic;
} _ATOM;

typedef struct 
{
  unsigned int beginidx;
  unsigned int endidx;
  unsigned char order;
  unsigned char aromatic;
} _BOND;

#endif /* __MYCHEM_STRUCTURES_H */

