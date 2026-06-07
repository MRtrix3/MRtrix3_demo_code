
#include "algo/geometric_mean.h"

namespace MR::Algo {

void GeometricMean::operator() (Image<float>& in, Image<float>& out) {
  // grab voxel intensities across volumes as a vector
  values = in.row(3);
  // compute the geometric mean if possible, set to invalid value if not
  out.value() = values.minCoeff() > 0.0
              ? std::exp(values.array().log().mean())
              : invalid;
}

} // namespace MR::Algo
