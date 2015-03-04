
\nexus\ groups are instances of the \nxgroup\ template. They can be considered
as containers for fields and other groups and expose an STL compliant interface. 
To start working with groups in a file one hast to first obtain the root group 
with 
\begin{cppcode}
h5::nxfile file = h5::nxfile::open_file("test.nxs");
h5::nxgroup root = file.root();
\end{cppcode}

\subsection{Creating groups}

New groups are created by means of the \cpp{create\_group} member function of
\nxgroup
\begin{cppcode}
h5::nxgroup entry = root.create_group("scan_1","NXentry");
\end{cppcode}
This method takes two arguments where the first one is mandatory and denotes the
name of the group while the second one is optional and determines the
\nexus-class of the group. If the last argument is omitted a simple HDF5 group
is created (without an \cpp{NX\_class}  attribute).

Like files, groups are automatically destroyed when an instance looses scope,
but they can also be deliberately closed using their \cpp{close()} method.

%%%===========================================================================
\subsection{Accessing children}

Access to the direct children of a group instance is given via the 
\cpp{at()} method or the \cpp{[]} operator. Both accept either a numeric index 
of a child or its name as an argument. To loop over all children of the 
root group the following code could be used
\begin{cppcode}
h5::nxfile f = ....;
h5::nxgroup root = f.root();

for(size_t i=0;i<root.size();++i) std::cout<<root[i].name()<<std::endl;
\end{cppcode}
As for STL containers, the \cpp{size()} method returns the number of children 
of a group. To access a particular group via its name one can use
\begin{cppcode}
h5::nxfile f = ....;
h5::nxgroup root = f.root();

h5::nxgroup entry = root["entry"]; //alternatively root.at("entry");
\end{cppcode}
Unlike for STL containers both access variants (\cpp{at()} or \cpp{[]}) will 
throw an exception if a particular child could not be found or the index passed
exceeds the total number of children of the group. In addition to this simple 
access interface \nxgroup\ also exposes a fully STL compliant iterator 
interface. However, in order to use it some more deeper knowledge about 
\libpniio\ is required and thus this topic will be dealt with in
Section~\ref{section:group_iteration}.

%%%===========================================================================
\subsection{Other group related member functions}

Like files, groups posses an \cpp{is\_valid()} method which allows checking the 
state of a group. Similar to files, default constructed instances of \nxgroup\
are not valid. 
\begin{cppcode}
h5::nxgroup entry; 

if(!entry.is_valid()) std::cerr<<"The entry group is not valid!"<<std::endl;
\end{cppcode}
The getter methods \cpp{name()} and \cpp{filename()} return the name of the
group and the name of the file the group is stored in respectively.
Finally the \cpp{parent()} function returns the parent group of the a group.
In order to use the \cpp{parent()} member function a bit more extra care is 
used. When using the method in a simple way like 
\begin{cppcode}
h5::nxgroup p = other_group.parent();
\end{cppcode}
everything will be fine. However, when we want to use the return value of 
\cpp{parent()} as a temporary we have to do an explicit conversion to 
\cpp{nxgroup} like this
\begin{cppcode}
std::cout<<h5::nxgroup(entry_group.parent())<<std::endl;
\end{cppcode}
The reason for this is that \cpp{parent()} does not really return an 
instance of \cpp{nxgroup} but rather of \cpp{nxobject}. 
But \nxobject\ can be converted to \nxgroup\ safely. The reason 
for this behavior will be explained in detail in Section~\ref{section:nxobject}.

