Mychem Installation
===================


Requirements
------------

The following are required to build Mychem:

*  cmake v3.10 or higher
*  libmysqlclient-dev v5.0 or higher (or the MariaDB equivalent)
*  openbabel-dev v3.0 or higher


Quick Install
-------------

This section describes a simple way to compile and install Mychem on
GNU/Linux. For a more complete documentation about the installation
procedure (in particular on Mac OS X), see the
`online documentation <https://mychem.github.io/docs/installation.html>`_.


Get the last stable release
+++++++++++++++++++++++++++

The last stable release can be downloaded from the
`Mychem GitHub release page <https://github.com/mychem/mychem-code/releases/>`_.

Uncompress the code
+++++++++++++++++++

Once the last stable version has been downloaded, you can extract the
code with:

::

   $ tar xfzv mychem-2.0.0.tgz


Compilation and Installation
++++++++++++++++++++++++++++

CMake can build the libraries and executables into any directory. If
the directory contains the source, the build is called in source. In
other cases, it is called out of source. CMake strongly recommends and
promotes building out of source, and only this method is detailed in
this short tutorial:

::

   $ cd mychem-2.0.0
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make
   $ sudo make install

Once the libraries are installed, you have to create the SQL functions.
It is done with the following command:

::

   $ mysql -u user -p < src/mysqldb.sql

On Ubuntu, the following additional steps are required:

1. Add the following line to the ``/etc/apparmor.d/local/usr.sbin.mysqld``

   ::

      /usr/lib/openbabel/** r,

2. Reload the AppArmor configuration:

   ::

      $ cat /etc/apparmor.d/usr.sbin.mysqld | apparmor_parser -r

