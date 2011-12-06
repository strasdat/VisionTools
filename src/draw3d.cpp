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

#include <iostream>
#include <Eigen/Eigenvalues>

#include <se3.h>

#include "draw3d.h"


namespace VisionTools
{
inline void
glTranslate( const Vector3d & v)
{
  glTranslated(v[0], v[1], v[2]);
}

void Draw3d
::activate(const LinearCamera & cam,
         const SE3 & T_cw)
{
  glShadeModel(GL_FLAT);
  glMatrixMode(GL_PROJECTION);

  double f = cam.focal_length();
  double px = cam.principal_point()[0]+0.5;
  double py = cam.principal_point()[1]+0.5;

  glLoadIdentity();
  GLdouble left, right, bottom, top;
  double nr = 0.1;
  double fr = 1000;

  left = -nr * px / f;
  top = -nr * py / f;
  right = nr * ( cam.image_size().width - px ) / f;
  bottom = nr * ( cam.image_size().height - py ) / f;

  ::glFrustum( left, right, bottom, top, nr, fr );
  Vector3d aa = T_cw.so3().log();
  double angle = aa.norm();

  glScaled(1,1,-1);
  glTranslatef(T_cw.translation()[0],T_cw.translation()[1],
               T_cw.translation()[2]);
  glRotated(angle* 180.0 / M_PI, aa[0], aa[1], aa[2]);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
}

void Draw3d
::ball(const Vector3d & p1, double radius, GLUquadric * quad)
{
  glPushMatrix();
  glTranslate(p1);
  gluSphere(quad, radius, 4, 4);
  glPopMatrix();
  assert(checkForGlError());
}


void Draw3d
::points(const vector<GlPoint3f> & xyz_here,
       const SE3 & T_world_from_here,
       double pixel_size)
{
  glPushMatrix();
  Matrix<double,4,4,ColMajor> Topengl_world_from_here
      = T_world_from_here.matrix();
  glMultMatrixd(Topengl_world_from_here.data());
  points(xyz_here,pixel_size);
  glPopMatrix();
}

void Draw3d
::points(const vector<GlPoint3f> & point_vec,
                    double pixel_size)
{
  glEnable(GL_POINT_SMOOTH);
  glEnableClientState(GL_VERTEX_ARRAY);
  glPointSize(pixel_size);

  glVertexPointer(3, GL_FLOAT, 0, &(point_vec[0].x));

  glDrawArrays(GL_POINTS, 0, point_vec.size());
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_POINT_SMOOTH);
  assert(checkForGlError());
}

void Draw3d
::coloredPoints(const vector<GlPoint3f> & xyz_here,
              const vector<GlPoint4f> & color_vec,
              const SE3 & T_world_from_here,
              double pixel_size)
{
  glPushMatrix();
  Matrix<double,4,4,ColMajor> Topengl_world_from_here
      = T_world_from_here.matrix();
  glMultMatrixd(Topengl_world_from_here.data());
  coloredPoints(xyz_here,color_vec,pixel_size);
  glPopMatrix();
}

void Draw3d
::coloredPoints(const vector<GlPoint3f> & point_vec,
              const vector<GlPoint4f> & color_vec,
              double pixel_size)
{
  assert(point_vec.size() == color_vec.size());
  glEnable(GL_POINT_SMOOTH);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glPointSize(pixel_size);
  glVertexPointer(3, GL_FLOAT, 0, &(point_vec[0].x));
  glColorPointer(4,GL_FLOAT,0,&(color_vec[0].x));
  glDrawArrays(GL_POINTS, 0, point_vec.size());

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_POINT_SMOOTH);
  assert(checkForGlError());
}

void Draw3d
::point(const GlPoint3f & point,
      double pixel_size)
{
  glEnable(GL_POINT_SMOOTH);

  glPointSize(pixel_size);
  glBegin(GL_POINTS);
  glVertex3f(point.x, point.y, point.z);
  glEnd( );

  glDisable(GL_POINT_SMOOTH);

  assert(checkForGlError());
}

void Draw3d
::pose(const SE3 & T_world_from_cam, double size)
{
  glPushMatrix();
  const Vector3d & center = T_world_from_cam.translation();

  glTranslate(center);

  Vector3d axis_angle = T_world_from_cam.so3().log();
  double angle = axis_angle.norm();
  if(angle != 0.)
  {
    glRotatef(angle * 180.0 / M_PI,
               axis_angle[0], axis_angle[1], axis_angle[2]);
  }
  double half_size = size*0.5;
  line(Vector3d(0,0,0), Vector3d(size, 0, 0));
  line(Vector3d(0,0,0), Vector3d(0, size, 0));
  line(Vector3d(0,0,0), Vector3d(0, 0, size));
  line(Vector3d(half_size,half_size,0),
       Vector3d(-half_size, half_size, 0));
  line(Vector3d(-half_size,-half_size,0),
       Vector3d(-half_size, half_size, 0));
  line(Vector3d(-half_size,-half_size,0),
       Vector3d(half_size, -half_size, 0));
  line(Vector3d(half_size,half_size,0),
       Vector3d(half_size, -half_size, 0));
  glPopMatrix();

  assert(checkForGlError());
}

void Draw3d
::line(const Vector3d & p1, const Vector3d & p2)
{
  glBegin(GL_LINES);
  glVertex3f(p1[0], p1[1], p1[2]);
  glVertex3f(p2[0], p2[1], p2[2]);
  glEnd();
  assert(checkForGlError());
}


void Draw3d
::gauss(const Vector3d & trans, const Matrix3d & pose_unc,
        double number_of_sigma, GLUquadric* quad)
{
  assert(false);
  assert(checkForGlError());
}

bool Draw3d
::checkForGlError()
{
  int error_code = glGetError();
  if (error_code==GL_NO_ERROR)
  {
    return true;
  }
  if (error_code==GL_INVALID_ENUM)
  {
    cerr << "GL_INVALID_ENUM" << endl;
  }
  else if (error_code==GL_INVALID_VALUE)
  {
    cerr << "GL_INVALID_VALUE" << endl;
  }
  else if (error_code==GL_INVALID_OPERATION)
  {
    cerr << "GL_INVALID_OPERATION" << endl;
  }
  else if (error_code==GL_STACK_OVERFLOW)
  {
    cerr << "GL_STACK_OVERFLOW" << endl;
  }
  else if (error_code==GL_STACK_UNDERFLOW)
  {
    cerr << "GL_STACK_UNDERFLOW" << endl;
  }
  else if (error_code==GL_OUT_OF_MEMORY)
  {
    cerr << "GL_OUT_OF_MEMORY" << endl;
  }
  else
  {
    cerr << "unknown OpenGL error!" << endl;
  }
  return false;
}

}
