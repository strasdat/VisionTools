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

#ifndef VISIONTOOLS_DRAW2D_H
#define VISIONTOOLS_DRAW2D_H

#include <opencv2/core/core.hpp>

#include "gl_data.h"

namespace VisionTools
{
struct Draw2d
{
  static void
  activate                   (const cv::Size & size_in_pixel);
  static void
  points                     (const vector<GlPoint2f> & point_vec,
                              double pixel_size);
  static void
  circle                     (const Vector2d & p,
                              double inner_radius,
                              double outer_radius,
                              GLUquadric * quad,
                              int slices=20);
  static void
  text                       (const std::string & str,
                              const Vector2i & p);
  static void
  gauss                      (const Vector2d & mu,
                              const Matrix2d& Sigma,
                              GLUquadric * quad,
                              double number_of_sigma=3,
                              double ring_thickness=1 );
  static void
  line                       (const Vector2d & p1,
                              const Vector2d & p2);
  static void
  box                        (const cv::Rect_<double> & r);

  static void
  texture                    (const cv::Mat & img,
                              const Vector2i top_left = Vector2i(0.,0.));
  static bool
  checkForGlError();
private:
  static Vector2d
  pixel2opengl               (const Vector2d & v);

};
}

#endif
