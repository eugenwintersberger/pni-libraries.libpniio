.. _nexus-api-file:

=======================
File handling functions
=======================

:cpp:func:`nexus::is_nexus_file`
================================

.. doxygenfunction:: pni::nexus::is_nexus_file(const fs::path&)

:cpp:func:`nexus::create_file`
==============================

.. doxygenfunction:: pni::nexus::create_file(const fs::path&, hdf5::file::AccessFlags, const hdf5::property::FileCreationList&, const hdf5::property::FileAccessList&)

:cpp:func:`nexus::open_file`
============================

.. doxygenfunction:: pni::nexus::open_file(const fs::path&, hdf5::file::AccessFlags, const hdf5::property::FileAccessList&)
