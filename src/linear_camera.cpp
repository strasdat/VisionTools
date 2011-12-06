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

#include "linear_camera.h"


namespace VisionTools
{
LinearCamera
::LinearCamera()
  : focal_length_(1.),
    principle_point_(Vector2d(0,0)),
    image_size_(-1,-1) ,
    intrinsics_(Matrix3d::Identity()),
    intrinsics_inv_(Matrix3d::Identity())
{
}

LinearCamera
::LinearCamera(const AbstractCamera& cam)
  : focal_length_(cam.focal_length()),
    principle_point_(cam.principal_point()),
    image_size_(cam.image_size()) ,
    intrinsics_(Matrix3d::Identity()),
    intrinsics_inv_(Matrix3d::Identity())
{
  initialise();
}

LinearCamera
::LinearCamera(const Matrix3d K,
               const cv::Size & size)
  : focal_length_( K(0,0)/K(2,2)),
    principle_point_( K(0,2)/K(2,2), K(1,2)/K(2,2) ),
    image_size_(size),
    intrinsics_(Matrix3d::Identity()),
    intrinsics_inv_(Matrix3d::Identity())
{
  initialise();
}

LinearCamera
::LinearCamera(const double & focal_length,
              const Vector2d & principle_point,
              const cv::Size & size)
  : focal_length_(focal_length),
    principle_point_(principle_point),
    image_size_(size) ,
    intrinsics_(Matrix3d::Identity()),
    intrinsics_inv_(Matrix3d::Identity())
{
  initialise();
}

void LinearCamera
::initialise()
{
  inv_focal_length_ = 1./focal_length_;
  intrinsics_(0,0) = focal_length_;
  intrinsics_(1,1) = focal_length_;
  intrinsics_(0,2) = principle_point_[0];
  intrinsics_(1,2) = principle_point_[1];
  intrinsics_inv_(0,0) = inv_focal_length_;
  intrinsics_inv_(1,1) = inv_focal_length_;
  intrinsics_inv_(0,2) = -principle_point_[0]*inv_focal_length_;
  intrinsics_inv_(1,2) = -principle_point_[1]*inv_focal_length_;
}

Vector2d LinearCamera
::map(const Vector2d& point) const
{
  return focal_length_*point + principle_point_;
}

Vector2d LinearCamera
::unmap(const Vector2d& dist_point) const
{
  return inv_focal_length_*(dist_point-principle_point_);
}

pangolin::OpenGlMatrixSpec LinearCamera
::getOpenGlMatrixSpec() const
{
  return pangolin::ProjectionMatrixRDF_TopLeft(image_size().width,
                                               image_size().height,
                                               focal_length(),
                                               focal_length(),
                                               principal_point()[0],
                                               principal_point()[1],
                                               0.00001,
                                               1000);
}

}
