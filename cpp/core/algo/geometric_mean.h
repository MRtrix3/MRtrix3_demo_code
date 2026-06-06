
#include <Eigen/Core>

#include "image.h"

namespace MR::Algo {

// this is the functor class defining the operation to be applied
class GeometricMean
{
  public:
    GeometricMean (const float value) : invalid (value) { }

    // the operation to be performed independently for each voxel
    void operator() (Image<float>& in, Image<float>& out) {
      // grab voxel intensities across volumes as a vector
      values = in.row(3);
      // compute the geometric mean if possible, set to invalid value if not
      out.value() = values.minCoeff() > 0.0
                  ? std::exp(values.array().log().mean())
                  : invalid;
    }

    Eigen::VectorXd values;
    const float invalid;
};

} // namespace MR::Algo
