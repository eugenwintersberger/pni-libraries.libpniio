.. _nexus-api-file:

=======================
File handling functions
=======================

:cpp:func:`nexus::is_nexus_file`
================================

.. doxygenfunction:: pni::io::nexus::is_nexus_file(const boost::filesystem::path &)

:cpp:func:`nexus::create_file`
==============================

.. doxygenfunction:: pni::io::nexus::create_file(const boost::filesystem::path &, hdf5::file::AccessFlags, const hdf5::property::FileCreationList &, const hdf5::property::FileAccessList &)

:cpp:func:`nexus::open_file`
============================

.. doxygenfunction:: pni::io::nexus::open_file(const boost::filesystem::path &, hdf5::file::AccessFlags, const hdf5::property::FileAccessList &)