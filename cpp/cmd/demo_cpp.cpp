
#include "command.h" // key header for building an executable command against MRtrix3
#include "exception.h" // class to throw whenever an unrecoverable problem is detected
#include "header.h" // class that defines every property of an image except for its intensities
#include "image.h" // defines class for accessing image data
#include "algo/threaded_loop.h" // tools for multi-threaded looping over images

#include "algo/geometric_mean.h" // custom class provided as part of demo command

using namespace MR;
using namespace App;

// this function sets up the command-line interface for the command
void usage()
{
  // details that must be defined for all commands
  AUTHOR = "W. Heath Robinson (h.robinson@implausible.com)";
  SYNOPSIS = "Compute voxel-wise geometric mean across volumes";

  // these are compulsory command-line inputs that must always be provided by the user
  ARGUMENTS
    + Argument("input", "an input image").type_image_in()
    + Argument("output", "the output image").type_image_out();

  // these optional inputs can be either provided or omitted by the user
  OPTIONS
    + Option("invalid", "value if any intensity is non-positive (default = NaN)")
      // this option requires that a value be specified alongside it when used
      + Argument ("value").type_float();

  // demonstrative usage of the command
  EXAMPLES
    + Example("basic usage of the command", // <= synopsis
              "demo_cpp in.mif out.mif", // <= command-line usage
              "Typical usage of the command only requires specifying"         //
              " an input image and an output image;"                          // <= verbose description
              " the input image must be 4D and the output image will be 3D"); //

  // example citation for the command docs
  REFERENCES
    + "Robinson, W.H. A treatise on geometric averaging. Contrived Science Weekly, 2019.";

  // manually set the copyright notice if the default is inappropriate
  COPYRIGHT = "Copyright (c) 2019 Heath Robinson Labs.";
}

// this function contains the primary operation of the command
void run () {
  // access the input image and check validity
  auto in = Image<float>::open(argument[0]);
  if (in.ndim() != 4)
    throw Exception("expected 4D input image");

  // copy the input image's header, and modify to suit
  Header header = in;
  header.ndim() = 3; // <= remove 4th dimension
  header.datatype() = DataType::Float32; // <= use floating-point output

  // create the output image, using the modified header as a template
  auto out = Image<float>::create(argument[1], header);

  // create an instance of the functor with the value optionally provided by the user
  MR::Algo::GeometricMean functor(get_option_value("invalid", NaNF));
  // performs the operation using multiple threads while displaying a progress bar
  // only loop over spatial axes; the functor itself loops over volumes within each voxel
  ThreadedLoop("computing geometric mean", in, 0, 3).run(functor, in, out);
  // output image write to disk is finalised automatically when it goes out of scope
}

