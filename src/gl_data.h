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

#ifndef VISIONTOOLS_GL_DATA_H
#define VISIONTOOLS_GL_DATA_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Eigen/Core>
#include <Eigen/StdVector>

namespace VisionTools
{
using namespace Eigen;
using namespace std;
struct GlPoint4f
{
  GlPoint4f(){}

  GlPoint4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) :
    x(x), y(y), z(z), w(w)
  {
  }

  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat w;
};

struct GlPoint3f
{
  GlPoint3f(){}

  GlPoint3f(const Vector3d & vec) :
    x(vec[0]), y(vec[1]), z(vec[2])
  {}

  GlPoint3f(GLfloat x, GLfloat y, GLfloat z) :
    x(x), y(y), z(z)
  {
  }

  GLfloat x;
  GLfloat y;
  GLfloat z;
};

struct GlPoint2f
{
  GlPoint2f(){}

  //In the image space, the center of the first pixel is denoted by (0,0)
  //whereas the position of the top left corner
  //of the first pixel is actually (-0.5,-0.5).

  GlPoint2f(const Vector2d & vec) :
    x(vec[0]+0.5f), y(vec[1]+0.5f), z(0)
  {}


  GlPoint2f(GLfloat x, GLfloat y) :
    x(x+0.5f), y(y+0.5f), z(0)
  {
  }

  GLfloat x;
  GLfloat y;
  GLfloat z;
};

inline void glColor(const Vector4f & c)
{
  glColor4f(c[0],c[1],c[2],c[3]);
}
}

#endif
