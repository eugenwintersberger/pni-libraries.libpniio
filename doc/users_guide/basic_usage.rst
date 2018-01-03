==========================
Basic usage of NeXus files
==========================

This chapter deals with the basic interface provided by the layer 1 types
implemented in *libpniio*. All types concerning Nexus reside in the
``pni::io::nexus`` namespace. 

To use the Nexus part of the library just add 

.. code-block:: cpp

   #include <pni/io/nexus.hpp>

to your source file. 

.. toctree:: 
   :maxdepth: 1
   
   nexus_files



%%%===========================================================================
\section{Working with groups}
\input{tex/nexus_groups.tex}


%%%===========================================================================
\section{Working with fields}
\input{tex/nexus_fields.tex}


%%%===========================================================================
\section{Working with attributes}
\input{tex/nexus_attributes.tex}

%%%===========================================================================
\section{Working with links}
\input{tex/nexus_links.tex}



