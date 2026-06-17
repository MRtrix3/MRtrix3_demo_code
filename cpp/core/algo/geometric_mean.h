
#include "types.h"
#include <Eigen/Core>

#include "image.h"

namespace MR::Algo {

// this is the functor class defining the operation to be applied
class GeometricMean
{
  public:
    GeometricMean (const float value) : invalid (value) { }

    // the operation to be performed independently for each voxel
    void operator() (Image<float>& in, Image<float>& out);

    Eigen::VectorXd values;
    const float invalid;
};

} // namespace MR::Algo
