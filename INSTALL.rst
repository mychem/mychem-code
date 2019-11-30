Mychem Installation
===================


Requirements
------------

The following are required to build Mychem:

*  cmake v2.4.5 or higher
*  libmysqlclient-dev v5.0 or higher (or the MariaDB equivalent)
*  openbabel-dev v2.3.0 or higher


Quick Install
-------------

This section describes a simple way to compile and install Mychem on
GNU/Linux. For a more complete documentation about the installation
procedure (in particular on Windows and Mac OS X), see the
`online documentation <https://mychem.github.io/docs/installation.html>`_.

Get the last stable release
+++++++++++++++++++++++++++

The last stable release can be downloaded from the `Mychem GitHub repository <https://github.com/mychem/mychem-code/archive/1.0.0.tar.gz>`_.

Uncompress the code
+++++++++++++++++++

Once the last stable version has been downloaded, you can extract the
code with:

::

   $ tar xfzv 1.0.0.tar.gz

Compilation and Installation
++++++++++++++++++++++++++++

CMake can build the libraries and executables into any directory. If
the directory contains the source, the build is called in source. In
other cases, it is called out of source. CMake strongly recommends and
promotes building out of source, and only this method is detailed in
this short tutorial:

::

   $ cd mychem-code-1.0.0
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make
   $ sudo make install

Once the libraries are installed, you have to create the SQL functions.
It is done with the following command:

::

   $ mysql -u user -p < src/mysqldb.sql

