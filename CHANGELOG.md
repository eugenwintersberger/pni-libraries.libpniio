# ChangeLog

## 3.2.0 - 2023-10-11
- core sub-section removed from documentation ([#233](https://github.com/pni-libraries/libpniio/pull/233))
- checks if filter is installed added ([#231](https://github.com/pni-libraries/libpniio/pull/231))
- a filter tag added ([#229](https://github.com/pni-libraries/libpniio/pull/229))
- xml from nxsdesigner readable by xml builder ([#227](https://github.com/pni-libraries/libpniio/pull/227))
- string and char arumenets added to Path constructor ([#226](https://github.com/pni-libraries/libpniio/pull/226))
- string and char arumenets added to get_object ([#224](https://github.com/pni-libraries/libpniio/pull/224))

## 3.1.0 - 2023-04-24
- fs::filesystem from h5cpp used ([#212](https://github.com/pni-libraries/libpniio/pull/212))
- support for conan 2 added ([#212](https://github.com/pni-libraries/libpniio/pull/212))
- tests updated ([#208](https://github.com/pni-libraries/libpniio/pull/208) and [#211](https://github.com/pni-libraries/libpniio/pull/211))
- technical release for h5cpp 0.6.0 (https://github.com/ess-dmsc/h5cpp/issues/631)

## 3.0.4 - 2023-02-20
- fix for finding boost library ([#202](https://github.com/pni-libraries/libpniio/pull/202))

## 3.0.3 - 2023-01-11
- relax checks for NeXus names to camel notation ([#199](https://github.com/pni-libraries/libpniio/pull/199))

## 3.0.2 - 2023-01-04
- fixes for windows added ([#195](https://github.com/pni-libraries/libpniio/pull/195))
- windows tests added ([#195](https://github.com/pni-libraries/libpniio/pull/195))
- technical release for libh5cpp v0.5.2 (https://github.com/ess-dmsc/h5cpp/issues/616)

## 3.0.1 - 2022-05-24
- technical release for libh5cpp v0.5.1 (https://github.com/ess-dmsc/h5cpp/issues/602)

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
