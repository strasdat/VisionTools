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

#ifndef VISIONTOOLS_LINEAR_CAMERA_H
#define VISIONTOOLS_LINEAR_CAMERA_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <pangolin/display.h>

#include "abstract_camera.h"


namespace VisionTools
{

class LinearCamera : public AbstractCamera
{
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  LinearCamera             ();
  LinearCamera             (const AbstractCamera& cam);
  LinearCamera             (const Matrix3d intrinsics,
                            const cv::Size & image_size);
  LinearCamera             (const double & focal_length,
                            const Vector2d & principle_point,
                            const cv::Size & image_size);
  Vector2d
  map                      (const Vector2d& camframe) const;
  Vector2d
  unmap                    (const Vector2d& imframe) const;
  pangolin::OpenGlMatrixSpec
  getOpenGlMatrixSpec      () const;

  const cv::Size & image_size() const
  {
    return image_size_;
  }
  const Vector2d& principal_point() const
  {
    return principle_point_;
  }
  const double & focal_length() const
  {
    return focal_length_;
  }
  const double & Finv() const
  {
    return inv_focal_length_;
  }
  const Matrix3d& intrinsics() const
  {
    return intrinsics_;
  }
  const Matrix3d& intrinsics_inv() const
  {
    return intrinsics_inv_;
  }

  Matrix2d
  jacobian(const Vector2d& camframe) const
  {
    return jacobian();
  }

  Matrix2d
  inv_jacobian(const Vector2d& imframe) const
  {
    return inv_jacobian();
  }

  Matrix2d
  jacobian() const
  {
    return intrinsics_.block(0,0,2,2);
  }

  Matrix2d
  inv_jacobian() const
  {
    return intrinsics_inv_.block(0,0,2,2);
  }

  static const int obs_dim = 2;
  static const int NUM_PARAMS = 4;

protected:
  void initialise();

  //Trick: Do computation once, and store ambiguous represenations
  double focal_length_;
  Vector2d principle_point_;
  cv::Size image_size_;
  Matrix3d intrinsics_;
  Matrix3d intrinsics_inv_;
  double inv_focal_length_;
};
}
#endif
