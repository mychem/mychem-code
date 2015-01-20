#!/usr/bin/python

# Copyright (c) 2010 CNRS
# Author: Jerome Pansanel <jerome.pansanel@iphc.cnrs.fr>
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the CNRS nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import os
import sys
import getpass
import MySQLdb
from optparse import OptionParser


#-----------------------------------------------------------------------------
# Functions
#-----------------------------------------------------------------------------

def logger(message, logfile=None, mode=0):
    if mode == 2:
        if logfile:
            logfile.write(message)
        sys.stderr.write(message)
    elif mode == 1:
        if logfile:
            logfile.write(message)
        sys.stdout.write(message)
    else:
        if logfile:
            logfile.write(message)
        else:
            sys.stdout.write(message)


#-----------------------------------------------------------------------------
# Options
#-----------------------------------------------------------------------------

usage = "Usage: %prog [options] FILE"

version = "%prog 0.8"

description = "%prog load a file in MDL SDF format into a MySQL database" \
            + " and creates a chemical cartridge with Mychem."

parser = OptionParser(usage=usage, version=version, description=description )

parser.add_option("-H", action="store", type="string", dest="host",
                  help="connect to host [default: %default]", default="localhost")
parser.add_option("-U", action="store", type="string", dest="user",
                  help="user for login to MySQL [default: %default]", default="mychem")
parser.add_option("-P", action="store_true", dest="pwd",
                  help="use a password to connect to MySQL (it will be asked from the tty)",
                  default=False)
parser.add_option("-D", action="store", type="string", dest="db",
                  help="database to use [default: %default]", default="mychem")
parser.add_option("-n", action="store", type="string", dest="nameTag",
                  help="name tag to use in the MDL SDF file", default="")
parser.add_option("-l", action="store", type="string", dest="logfile",
                  help="log file name", default="")
parser.add_option("-t", action="store", type="string", dest="tablePrefix",
                  help="table prefix", default="")
parser.add_option("-a", action="store_true", dest="append",
                  help="append data if the compound table exists",
                  default=False)
parser.add_option("-r", action="store_true", dest="replace",
                  help="replace data if the compound table exists",
                  default=False)
parser.add_option("-u", action="store_true", dest="update",
                  help="update data if the compound table exists",
                  default=False)
parser.add_option("-v", action="store_true", dest="verbose",
                  help="verbose mode", default=False)

# Ajouter une option Filename
(options, args) = parser.parse_args()

if len(args) != 1:
    sys.stdout.write(parser.format_help())
    sys.exit(0)


#-----------------------------------------------------------------------------
# Logfile
#-----------------------------------------------------------------------------

verbose = options.verbose
if options.logfile:
    message = "Opening log file '%s'\n" % (options.logfile)
    if verbose:
        logger(message)
    try:
        logFile = open(options.logfile, 'w')
    except IOError, e:
        sys.stderr.write("Error: Could not open log file '%s': " % options.logfile)
        sys.stderr.write("%s\n" % (e.args[1]))
        sys.exit(1)
else:
    logFile = None


#-----------------------------------------------------------------------------
# Check incompatible options
#-----------------------------------------------------------------------------

if options.append + options.replace + options.update > 1:
    message = "Error: Options [a]ppend, [r]eplace and [u]pdate can not be set" \
            + "simultanously\n"
    logger(message, logFile, 2)
    logFile.close()
    sys.exit(1)


#-----------------------------------------------------------------------------
# Database connexion
# Connect to the database and verify the table structures. If the user asked
# to create new tables, old one will be removed. Else, they will be updated.
# the tables does not exist, the script create new
#-----------------------------------------------------------------------------

host = options.host
user = options.user
db = options.db
if options.pwd:
    passwd = getpass.getpass(prompt="Enter MySQL password: ")
else:
    passwd = ""

try:
    link = MySQLdb.connect(host = host, user = user, passwd = passwd, db = db)
except MySQLdb.Error, e:
    sys.stderr.write("Error: %d: %s\n" % (e.args[0], e.args[1]))
    sys.exit(1)

if verbose:
    message = "Connection to MySQL successufull\n"
    logger(message, logFile)

cursor = link.cursor()


#-----------------------------------------------------------------------------
# Table settings
#-----------------------------------------------------------------------------

if options.tablePrefix:
    compoundTable = options.tablePrefix + "_compounds"
    structure1DTable = options.tablePrefix + "_1D_structures"
    structure3DTable = options.tablePrefix + "_3D_structures"
    structureBinTable = options.tablePrefix + "_bin_structures"
else:
    compoundTable = "compounds"
    structure1DTable = "1D_structures"
    structure3DTable = "3D_structures"
    structureBinTable = "bin_structures"

mychemTables = { 'compoundsTable' : compoundTable,
                  'structure1DTable' : structure1DTable,
                  'structure3DTable' : structure3DTable,
                  'structureBinTable' : structureBinTable }

existingTables = []

for table in mychemTables:
    query = "SHOW TABLES LIKE '%s'" % (mychemTables[table])
    result_len = cursor.execute(query)
    if result_len > 0:
        existingTables.append(table)
        if verbose:
            message = "Table '%s' already exists.\n" % (table)
            logger(message, logFile)

if (len(existingTables) == 4) and not (options.append or options.replace or options.update):
    message = "A complet set of tables alread exists. Which action should " \
            + "be performed:\n"
    sys.stdout.write(message)
    while 1: 
        action = raw_input("[A]ppend, [C]ancel, [R]eplace or [U]pdate?\n").strip()
        if len(action) < 1:
            continue
        if action[0] in ['a','A']:
            options.append = True
            break
        elif action[0] in ['c','C']:
            link.close()
            message = "Database loading cancelled\n"
            logger(message, logFile)
            if logFile:
                logFile.close()
            sys.exit(0)
        elif action[0] in ['r','R']:
            options.replace = True
            break
        elif action[0] in ['u','U']:
            options.update = True
            break
        else:
            continue

elif len(existingTables) in [1,2,3]:
    message = "Some tables (but not all) already exist. Which action should " \
            + "be performed:\n"
    sys.stdout.write(message)
    while 1: 
        action = raw_input("[C]ancel or [R]eplace?\n").strip()
        if len(action) < 1:
            continue
        elif action[0] in ['c','C']:
            link.close()
            message = "Database loading cancelled\n"
            logger(message, logFile)
            if logFile:
                logFile.close()
            sys.exit(0)
        elif action[0] in ['r','R']:
            options.replace = True
            break
        else:
            continue

if options.append and verbose:
    if existingTables:
        message = "As requested, data will be appended to existing tables\n"
    else:
        message = "The tables do not exist. A new table set will be " \
                + "created.\n" 
    logger(message, logFile)
elif options.replace and verbose:
    if existingTables:
        message = "As requested, old tables will be dropped and a new table " \
                + "set will be created.\n"
    else:
        message = "The tables do not exist. A new table set will be " \
                + "created.\n"
    logger(message, logFile)
elif options.update and verbose:
    if existingTables:
        message = "As requested, old data will be updated.\n"
    else:
        message = "The tables do not exist. A new table set will be" \
                + "created.\n"
    logger(message, logFile)

if options.replace:
    if 'compoundsTable' in existingTables:
        query = "DROP TABLE IF EXISTS `%s`" % (compoundTable)
        cursor.execute(query)
        link.commit()
        if verbose:
            message = "The '%s' table has been dropped.\n" % (compoundTable)
            logger(message, logFile)
    if 'structure1DTable' in existingTables:
        query = "DROP TABLE IF EXISTS `%s`" % (structure1DTable)
        cursor.execute(query)
        link.commit()
        if verbose:
            message = "The '%s' table has been dropped.\n" % (structure1DTable)
            logger(message, logFile)
    if 'structure3DTable' in existingTables:
        query = "DROP TABLE IF EXISTS `%s`" % (structure3DTable)
        cursor.execute(query)
        link.commit()
        if verbose:
            message = "The '%s' table has been dropped.\n" % (structure3DTable)
            logger(message, logFile)
    if 'structureBinTable' in existingTables:
        query = "DROP TABLE IF EXISTS `%s`" % (structureBinTable)
        cursor.execute(query)
        link.commit()
        if verbose:
            message = "The '%s' table has been dropped.\n" % (structureBinTable)
            logger(message, logFile)
    existingTables = []
    if verbose:
        message = "All existing tables have been dropped.\n"
        logger(message, logFile)

#-----------------------------------------------------------------------------
# Table creation
#-----------------------------------------------------------------------------

if not existingTables:
    # Create the compound table
    query = """CREATE TABLE IF NOT EXISTS `%s` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `created` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `modified` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY id (`id`),
  KEY name (`name`) )
  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin
  COMMENT='Compound Library';
""" % (compoundTable)
    cursor.execute(query)
    link.commit()
    message = "The '%s' table has been created\n" % (compoundTable)
    if verbose:
        logger(message, logFile)

    # Create the 1D_structures table
    query = """CREATE TABLE IF NOT EXISTS `%s` (
  `compound_id` int(11) unsigned NOT NULL,
  `inchi` text NOT NULL,
  `smiles` text NOT NULL,
  PRIMARY KEY compound_id (`compound_id`) )
  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin
  COMMENT='Compound 1D Structures';
""" % (structure1DTable)
    cursor.execute(query)
    link.commit()
    message = "The '%s' table has been created\n" % (structure1DTable)
    if verbose:
        logger(message, logFile)

    # Create the 3D_structures table
    query = """CREATE TABLE IF NOT EXISTS `%s` (
  `compound_id` int(11) unsigned NOT NULL,
  `molfile` text NOT NULL,
  PRIMARY KEY compound_id (`compound_id`) )
  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin
  COMMENT='Compound 3D Structures';
""" % (structure3DTable)
    cursor.execute(query)
    link.commit()
    message = "The '%s' table has been created\n" % (structure3DTable)
    if verbose:
        logger(message, logFile)

    # Create the bin_structures table
    query = """
CREATE TABLE IF NOT EXISTS `%s` (
  `compound_id` int(11) unsigned NOT NULL,
  `fp2` blob NULL,
  `obserialized` blob NULL,
  PRIMARY KEY compound_id (`compound_id`) )
  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin
  COMMENT='Compound Binary Structures';
""" % (structureBinTable)
    cursor.execute(query)
    link.commit()
    message = "The '%s' table has been created\n" % (structureBinTable)
    if verbose:
        logger(message, logFile)


#-----------------------------------------------------------------------------
# load_structure() function
#-----------------------------------------------------------------------------

def load_structure(name, molfile):
    if options.update:
        query = """
SELECT `id` FROM `%s` WHERE name='%s'
""" % (compoundTable, link.escape_string(name))
        result_len = cursor.execute(query)

        if result_len > 0:
            result = cursor.fetchone()
            compound_id = result[0]

            query = """
UPDATE `%s`,`%s` SET `modified`=CURRENT_TIMESTAMP(),`molfile`='%s'
 WHERE `id`=%i AND `compound_id`=`id`;
""" % (compoundTable, structure3DTable, link.escape_string(molfile), compound_id)
            cursor.execute(query)

            query = """
UPDATE `%s`,`%s` SET
 `inchi`=MOLECULE_TO_INCHI(`molfile`),
 `smiles`=MOLECULE_TO_SMILES(`molfile`)
 WHERE `%s`.`compound_id`=%i
 AND `%s`.`compound_id`=%i
""" % (structure1DTable, structure3DTable, structure1DTable, compound_id, structure3DTable, compound_id)
            cursor.execute(query)

            query = """
UPDATE `%s`,`%s` SET
 `fp2`=FINGERPRINT2(`molfile`),
 `obserialized`=MOLECULE_TO_SERIALIZEDOBMOL(`molfile`)
 WHERE `%s`.`compound_id`=%i
 AND `%s`.`compound_id`=%i
""" % (structureBinTable, structure3DTable, structureBinTable, compound_id, structure3DTable, compound_id)
            cursor.execute(query)

            return True

    query = "INSERT INTO `%s` (`name`,`created`,`modified`)" % (compoundTable) \
            + " VALUES ('%s',CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP())" % (link.escape_string(name))
    cursor.execute(query)
    compound_id = cursor.lastrowid
    query = """
INSERT INTO `%s` (`compound_id`, `molfile`) VALUES (%i, '%s');
""" % (structure3DTable, compound_id, link.escape_string(molfile))
    cursor.execute(query)
    query = """
INSERT INTO `%s` (`compound_id`, `inchi`, `smiles`)
 SELECT `compound_id`, MOLECULE_TO_INCHI(`molfile`),
 MOLECULE_TO_SMILES(`molfile`) FROM `%s` WHERE `compound_id`=%i;
""" % (structure1DTable, structure3DTable, compound_id)
    cursor.execute(query)
    query = """
INSERT INTO `%s` (`compound_id`, `fp2`, `obserialized`)
 SELECT `compound_id`, FINGERPRINT2(`molfile`),
 MOLECULE_TO_SERIALIZEDOBMOL(`molfile`) FROM `%s` WHERE `compound_id`=%i;
""" % (structureBinTable, structure3DTable, compound_id)
    cursor.execute(query)
    return True


#-----------------------------------------------------------------------------
# Parse the file and load the structures
#-----------------------------------------------------------------------------

dbFileName = args[0]

try:
    dbFile = open(dbFileName, 'r')
except IOError, e:
    sys.stderr.write("Error: Could not open MDL Sdfile '%s': " % (dbFileName))
    sys.stderr.write("%s\n" % (e.args[1]))
    sys.exit(1)

molfile = ""
lineCount = 0
molCount = 0
ctEnd = False

while 1:
    line = dbFile.readline()
    if not line:
        break
    lineCount += 1
    if line[0:4] == "$$$$":
        if name == "":
            name = "Mol" + str(molCount)
        if len(name) > 250:
            sys.stderr.write("Error: molecule name is too long for %s" % (name))
        else:
            load_structure(name,molfile)
        molfile = ""
        lineCount = 0
        molCount += 1
        ctEnd = False
    elif not ctEnd:
        molfile += line
        if lineCount == 1:
            name = line.strip()
        if line[0:6] == "M END":
            ctEnd = True


#-----------------------------------------------------------------------------
# Close the handlers and print a summary
#-----------------------------------------------------------------------------

dbFile.close()
link.commit()
cursor.close()
link.close()

if verbose:
    message = "%i structures have been loaded.\n" % (molCount)
    logger(message, logFile)

message = "The MDL SDF file has been successfully loaded.\n"
logger(message, logFile, 1)

if logFile:
    logFile.close()

