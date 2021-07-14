# ChangeLog

## 2.0.0 - 2021-07-05
- merge pniio and pnicore to pninexus
- move 'pni/core/' and 'pni/io/' to 'pni'
- move pni::io and pni::core to pni namespace

## 1.3.2 - 2021-07-05
- creating string arrays with an empty dimension fixed ([#132](https://github.com/pni-libraries/libpniio/pull/132))
- checks if field/group exist ([#133](https://github.com/pni-libraries/libpniio/pull/133))

## 1.3.1 - 2021-02-20
- HDF5_version attribute changed to HDF5_Version ([#121](https://github.com/pni-libraries/libpniio/pull/121))
- NeXus_version attribute removed ([#121](https://github.com/pni-libraries/libpniio/pull/121))

## 1.3.0 - 2021-02-15
- string are stored in the scalar dataspace by default ([#115](https://github.com/pni-libraries/libpniio/pull/115))
- xml_to_nexus: when data is not provided a field of rank 1 and size 0 is created by default ([#31](https://github.com/pni-libraries/libpniio/pull/31))
