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
 * @file test_functions.h
 * @brief Provide functions used by the test programs.
 * @author Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
 *
 * This file is part of the Mychem software. It contains functions used
 * by the test programs.
 */

#include <string>
#include <vector>

/**
 * @short Compare two molecules (MDL Mol format)
 * @param first_molecule The first molecule
 * @param second_molecule The second molecule
 * @return true If the molecules are the same
 */
bool compareMolecules(std::string first_molecule, std::string second_molecule);

bool compareV3000(std::string first_molecule, std::string second_molecule);

void printTestResult(std::string testName, bool testFailed);

bool readFile(std::string filename, std::string& buffer);

bool readBinaryFile(std::string filename, std::string& binaryString);
