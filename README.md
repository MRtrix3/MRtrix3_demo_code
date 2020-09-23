# MRtrix3 demo code

Demonstration code as included in the _MRtrix3_ NeuroImage 2019 paper.


# Installation

This assumes you have the dependencies to build MRtrix3 from source installed using the
[instructions provided in the documentation](https://mrtrix.readthedocs.io/en/latest/).

```
git clone https://github.com/MRtrix3/MRtrix3_demo_code.git
cd MRtrix3_demo_code
./configure_mrtrix3_library
./build
```

at which point you should be able to invoke both the Python and C++ commands as:
```
bin/demo_binary
bin/demo_script
```
# Library version

The library is initialised by default to the latest commit on master. To update the MRtrix3 library simply repeat
```
./configure_mrtrix3_library
./build
```

To select another version for the library, write the branch name, tag or commit sha-1 to the file `mrtrix3_library_version`.

