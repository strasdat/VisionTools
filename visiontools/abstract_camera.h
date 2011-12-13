// This file is part of VisionTools.
//
// Copyright 2011 Hauke Strasdat (Imperial College London)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights  to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#ifndef VISIONTOOLS_ABSTRACT_CAMERA_H
#define VISIONTOOLS_ABSTRACT_CAMERA_H

#include <Eigen/Core>
#include <Eigen/StdVector>

#include <opencv2/core/core.hpp>

namespace VisionTools
{
using namespace std;
using namespace Eigen;

class AbstractCamera
{
public:
  virtual const cv::Size &
  image_size                 () const = 0;
  virtual const Vector2d&
  principal_point            () const = 0;
  virtual const double &
  focal_length               () const = 0;
  virtual const Matrix3d &
  intrinsics                 () const = 0;
  virtual const Matrix3d &
  intrinsics_inv             () const = 0;
  virtual Vector2d           //applies camera intrinsics including distortion
  map                        (const Vector2d& camframe) const = 0;
  virtual Vector2d           //undo camera intrinsics including undistortion
  unmap                      (const Vector2d& imframe) const = 0;
  virtual Matrix2d
  jacobian                   (const Vector2d& camframe) const = 0;

  double width() const
  {
    return image_size().width;
  }

  double height() const
  {
    return image_size().height;
  }

  inline bool isInFrame(const Vector2i & obs, int boundry=0) const
  {
    if(obs[0]>=boundry && obs[0]<image_size().width-boundry
        && obs[1]>=boundry && obs[1]<image_size().height-boundry)
      return true;
    return false;
  }
};

}

#endif
