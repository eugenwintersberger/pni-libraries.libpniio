# ChangeLog

## 3.0.0 - 2022-05-05
- add PNINEXUS_ prefix to libpninexus macros ([#183](https://github.com/pni-libraries/libpniio/pull/183))
- update template parameter names ([#181](https://github.com/pni-libraries/libpniio/pull/181))
- add documentation versioning ([#161](https://github.com/pni-libraries/libpniio/pull/161), [#171](https://github.com/pni-libraries/libpniio/pull/171))
- merge cmake submodule to the main repository ([#168](https://github.com/pni-libraries/libpniio/pull/168))
- add EBool type ([#166](https://github.com/pni-libraries/libpniio/pull/166))
- update core examples in the documentation ([#151](https://github.com/pni-libraries/libpniio/pull/151))
- adopt code to the newer boost version ([#154](https://github.com/pni-libraries/libpniio/pull/154))
- adopt code to libh5cpp >= v0.5.0 (required) ([#162](https://github.com/pni-libraries/libpniio/pull/162))


## 2.0.0 - 2021-07-05
- merge pniio and pnicore to pninexus
- move 'pni/core/' and 'pni/io/' to 'pni'
- move pni::io and pni::core to pni namespace
- change char * parameter types to std::string

## 1.3.2 - 2021-07-05
- creating string arrays with an empty dimension fixed ([#132](https://github.com/pni-libraries/libpniio/pull/132))
- checks if field/group exist ([#133](https://github.com/pni-libraries/libpniio/pull/133))

## 1.3.1 - 2021-02-20
- HDF5_version attribute changed to HDF5_Version ([#121](https://github.com/pni-libraries/libpniio/pull/121))
- NeXus_version attribute removed ([#121](https://github.com/pni-libraries/libpniio/pull/121))

## 1.3.0 - 2021-02-15
- string are stored in the scalar dataspace by default ([#115](https://github.com/pni-libraries/libpniio/pull/115))
- xml_to_nexus: when data is not provided a field of rank 1 and size 0 is created by default ([#31](https://github.com/pni-libraries/libpniio/pull/31))
