# MRtrix3 demo code

Demonstration code as included in the _MRtrix3_ NeuroImage 2019 paper.


# Installation

This assumes you have already installed MRtrix3 from source, using the 
[instructions provided in the documentation](https://mrtrix.readthedocs.io/en/latest/), 
and that your main _MRtrix3_ installation resides in the `~/mrtrix3` folder (other locations
are possible, please edit the instructions below to match your installation).

```
git clone https://github.com/MRtrix3/MRtrix3_demo_code.git
cd MRtrix3_demo_code
ln -s ~/mrtrix3/build
./build
```

at which point you should be able to invoke both the Python and C++ commands as:
```
bin/demo_binary
bin/demo_script
```
