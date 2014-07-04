/*!
\ingroup nexus_io
\defgroup algorithm_code Nexus Algorithms

Nexus files can be considered as a heterogeneous container (a container holding
instances of different types). This section describes algorithms that work on 
particular Nexus objects.

There are basically three kinds of algorithms 

- general purpose algorithms that can be applied to all objects 
- algorithms related to the group type
- algorithms related to IO types like fields and attributes

General purpose algorithms are 

| function name |             purpose | principal input   |  return type | 
| :------------ | :-------------------------------  | :------- | :- 
| as_attribute  | convert nxobject to nxattribute  | nxobject |  nxattribute | 
| as_field      | convert nxobject to nxfield      | nxobject |  nxfield | 
| as_group      | convert nxobject to nxgroup      | nxobject |  nxgruop | 
| is_attribute  | true if object is an nxattribute | nxobject |  bool | 
| is_field      | true if object is an nxfield     | nxobject |  bool | 
| is_group      | true if object is an nxgroup     | nxobject |  bool | 
| is_valid      | true if object is valid          | all      |  bool | 
| get_name      | return the name of an object     | all      |  string | 
| colse         | close an object                  | all      |  void | 
| create_attribute | create an attribute  | nxobject, nxfield, nxgroup| nxobject | 
| get_attribute    | return an attribute  | nxobject, nxfield, nxgruop| nxobject | 
| get_attributes   |  return attribute container |  nxfield,nxgroup,nxobject | container<nxobject> | 
| get_parent  |  get parent object |  all |  nxobject | 
| get_path    |  get path  | all | nxpath | 
| get_root    |  return root group | all | nxobject | 


Group related algorithms are 

| function name | purpose | principal input | return type | 
| :------------ | :------ | :-------------- | :---------- | 
| get_child_by_index | return child by numeric index | nxgroup, nxobject | nxobject | 
| get_child          | return child by name| nxgroup, nxobject | nxobject |
| get_children       | returns list of children | nxgroup, nxobject | container |
| get_object         | get object by path | nxgroup, nxobject | nxobject | 
| create_field | create a field | nxgroup, nxobject | nxobject | 
| create_group | create a group | nxgroup, nxobject | nxobject |
| get_class | return a groups class | nxgroup, nxobject | string |
| is_class  | check if object is of a particular class | nxgroup,nxobject | bool | 
| set_class | set the class of an object | nxgruop, nxobject | void | 

IO (nxattribute, nxfield) related algorithms 

| function name | purpose | principal input | return type | 
| :------------ | :------ | :-------------- | :---------- | 
| get_shape     | return object shape | nxfield, nxattribute, nxobject | container |
| get_size      | return size of element | nxfield, nxattribute, nxobject | size_t |
| get_type | get type ID of the object | nxfield, nxattribute, nxobject | type_id_t |
| get_unit | return unit of data field | nxfield, nxobject | string | 
| set_unit | set unit for a field  | nxfield, nxobject | void |
| get_rank | return number of dimensions | nxfield, nxattribute, nxobject | size_t | 
| grow     | grow a field | nxfield, nxobject | void |
| read | read data from object | nxfield, nxattribute, nxobject | void |
| write | write data to object | nxfield, nxattribute, nxobject | void | 
*/

/*!
\ingroup algorithm_code
\defgroup algorithm_internal_code Internal classes used by algorithms 

These classes are used internally by the algorithm functions and are thus not of
great interest to the common library user. However, they might be interesting
for library developers.
*/
