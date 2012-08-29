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

#ifndef VISIONTOOLS_DRAW3D_H
#define VISIONTOOLS_DRAW3D_H

#include "gl_data.h"
#include "linear_camera.h"

namespace Sophus
{
class SE3;
class Sim3;
}

namespace VisionTools
{
using namespace Sophus;

struct Draw3d
{
  static void
  activate                   (const LinearCamera & cam,
                              const SE3 & T_cw);
  static void
  ball                       (const Vector3d & p1,
                              double radius,
                              GLUquadric * quad);
  static void
  points                     (const vector<GlPoint3f> & xyz_here,
                              const SE3 & T_world_from_here,
                              double pixel_size);
  static void
  points                     (const vector<GlPoint3f> & point_vec,
                              double pixel_size);
  static void
  coloredPoints              (const vector<GlPoint3f> & xyz_here,
                              const vector<GlPoint4f> & color_vec,
                              const SE3 & T_world_from_here,
                              double pixel_size);
  static void
  coloredPoints              (const vector<GlPoint3f> & point_vec,
                              const vector<GlPoint4f> & color_vec,
                              double pixel_size);
  static void
  point                      (const GlPoint3f & point,
                              double pixel_size);
  static void
  pose                       (const SE3 & T_world_from_cam, double size = 0.1);

  static void
  pose                       (const Sim3 & T_world_from_cam, double size = 0.1);

  static void
  line                       (const Vector3d & p1, const Vector3d & p2);
  static void
  gauss                      (const Vector3d & trans,
                              const Matrix3d & pose_unc,
                              double number_of_sigma,
                              GLUquadric* quad);
  static bool
  checkForGlError            ();
};

}

#endif
