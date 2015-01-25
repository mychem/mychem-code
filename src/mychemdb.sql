--
-- This SQL script creates the functions provided by Mychem
--
USE mysql;

--
-- Functions related to chemical format conversion
--
DROP FUNCTION IF EXISTS molfile_to_molecule;
CREATE FUNCTION molfile_to_molecule RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molecule_to_molfile;
CREATE FUNCTION molecule_to_molfile RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS V3000_to_molecule;
CREATE FUNCTION V3000_to_molecule RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molecule_to_V3000;
CREATE FUNCTION molecule_to_V3000 RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS smiles_to_molecule;
CREATE FUNCTION smiles_to_molecule RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molecule_to_smiles;
CREATE FUNCTION molecule_to_smiles RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molecule_to_molecule;
CREATE FUNCTION molecule_to_molecule RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS cml_to_molecule;
CREATE FUNCTION cml_to_molecule RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molecule_to_cml;
CREATE FUNCTION molecule_to_cml RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS fingerprint;
CREATE FUNCTION fingerprint RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS fingerprint2;
CREATE FUNCTION fingerprint2 RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS fingerprint3;
CREATE FUNCTION fingerprint3 RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS fingerprint4;
CREATE FUNCTION fingerprint4 RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molecule_to_canonical_smiles;
CREATE FUNCTION molecule_to_canonical_smiles RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS inchi_to_molecule;
CREATE FUNCTION inchi_to_molecule RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molecule_to_inchi;
CREATE FUNCTION molecule_to_inchi RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molecule_to_serializedOBMol;
CREATE FUNCTION molecule_to_serializedOBMol RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS pdb_to_molecule;
CREATE FUNCTION pdb_to_molecule RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS mol2_to_molecule;
CREATE FUNCTION mol2_to_molecule RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molecule_to_mol2;
CREATE FUNCTION molecule_to_mol2 RETURNS STRING SONAME "libmychem.so";

--
-- Functions related to the helper
--
DROP FUNCTION IF EXISTS mychem_version;
CREATE FUNCTION mychem_version RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS openbabel_version;
CREATE FUNCTION openbabel_version RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS inchi_version;
CREATE FUNCTION inchi_version RETURNS STRING SONAME "libmychem.so";

--
-- Functions related to chemical data modifications
--
DROP FUNCTION IF EXISTS add_hydrogens;
CREATE FUNCTION add_hydrogens RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS remove_hydrogens;
CREATE FUNCTION remove_hydrogens RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS strip_salts;
CREATE FUNCTION strip_salts RETURNS STRING SONAME "libmychem.so";

--
-- Functions related to chemical match
--
DROP FUNCTION IF EXISTS match_substruct;
CREATE FUNCTION match_substruct RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS substruct_atom_ids;
CREATE FUNCTION substruct_atom_ids RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS substruct_count;
CREATE FUNCTION substruct_count RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS tanimoto;
CREATE FUNCTION tanimoto RETURNS REAL SONAME "libmychem.so";

DROP FUNCTION IF EXISTS bit_fp_and;
CREATE FUNCTION bit_fp_and RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS bit_fp_or;
CREATE FUNCTION bit_fp_or RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS bit_fp_count;
CREATE FUNCTION bit_fp_count RETURNS INTEGER SONAME "libmychem.so";

--
-- Functions related to chemical property calculations
--
DROP FUNCTION IF EXISTS molweight;
CREATE FUNCTION molweight RETURNS REAL SONAME "libmychem.so";

DROP FUNCTION IF EXISTS exactmass;
CREATE FUNCTION exactmass RETURNS REAL SONAME "libmychem.so";

DROP FUNCTION IF EXISTS number_of_atoms;
CREATE FUNCTION number_of_atoms RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS number_of_heavy_atoms;
CREATE FUNCTION number_of_heavy_atoms RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS number_of_bonds;
CREATE FUNCTION number_of_bonds RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS number_of_rotable_bonds;
CREATE FUNCTION number_of_rotable_bonds RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS total_charge;
CREATE FUNCTION total_charge RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molformula;
CREATE FUNCTION molformula RETURNS STRING SONAME "libmychem.so";

DROP FUNCTION IF EXISTS number_of_acceptors;
CREATE FUNCTION number_of_acceptors RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS number_of_donors;
CREATE FUNCTION number_of_donors RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molpsa;
CREATE FUNCTION molpsa RETURNS REAL SONAME "libmychem.so";

DROP FUNCTION IF EXISTS molmr;
CREATE FUNCTION molmr RETURNS REAL SONAME "libmychem.so";

DROP FUNCTION IF EXISTS mollogp;
CREATE FUNCTION mollogp RETURNS REAL SONAME "libmychem.so";

DROP FUNCTION IF EXISTS is_2D;
CREATE FUNCTION is_2D RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS is_3D;
CREATE FUNCTION is_3D RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS is_chiral;
CREATE FUNCTION is_chiral RETURNS INTEGER SONAME "libmychem.so";

DROP FUNCTION IF EXISTS number_of_rings;
CREATE FUNCTION number_of_rings RETURNS INTEGER SONAME "libmychem.so";

