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
#include "draw2d.h"

#include <iostream>
#include <Eigen/Eigenvalues>


namespace VisionTools
{

void Draw2d::
activate(const cv::Size & size_in_pixel)
{
  glShadeModel(GL_FLAT);
  glEnable (GL_LINE_SMOOTH);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glLineWidth (1);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  ::glOrtho (0, size_in_pixel.width, size_in_pixel.height, 0, 0, 1);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
}

void Draw2d::
points(const vector<GlPoint2f> & point_vec,
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

void Draw2d::
circle(const Vector2d & p,
       double inner_radius,
       double outer_radius,
       GLUquadric * quad,
       int slices
       )
{
  Vector2d v = pixel2opengl(p);
  glPushMatrix();
  glTranslatef(v[0],v[1],0);
  gluDisk(quad, inner_radius, outer_radius, slices, 2 );


  glPopMatrix();

  assert(checkForGlError());
}

Vector2d Draw2d::
pixel2opengl(const Vector2d & v)
{
  //In the image space, the center of the first pixel is denoted by (0,0)
  //whereas the position of the top left corner
  //of the first pixel is actually (-0.5,-0.5).

  return Vector2d(v[0]+0.5,v[1]+0.5);
}

void Draw2d::
text(const std::string & str,
     const Vector2i & p)
{
  glPushMatrix();
  const char * c;
  glRasterPos2i(p[0], p[1]);

  for (c=str.c_str(); *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
  }

  glPopMatrix();

  assert(checkForGlError());
}

//TODO: rewrite
void Draw2d::
gauss(const Vector2d & mu,
      const Matrix2d & Sigma,
      GLUquadric * quad,
      double number_of_sigma,
      double ring_thickness)
{

  Vector2d v = pixel2opengl(mu);

  assert(false);

  assert(checkForGlError());
}

void Draw2d::
line(const Vector2d & p1,
     const Vector2d & p2)
{
  Vector2d v1 = pixel2opengl(p1);
  Vector2d v2 = pixel2opengl(p2);

  glLineWidth(1);
  glBegin(GL_LINES);
  glVertex2f(v1[0], v1[1]);
  glVertex2f(v2[0], v2[1]);
  glEnd();
  assert(checkForGlError());
}

void Draw2d::
box(const cv::Rect_<double> & r)
{
  Vector2d v1 = pixel2opengl(Vector2d(r.x,r.y));
  Vector2d v2 = pixel2opengl(Vector2d(r.x+r.width,r.y+r.height));

  glBegin(GL_LINE_LOOP);
  glVertex2f(v1[0], v1[1]);
  glVertex2f(v1[0], v2[1]);
  glVertex2f(v2[0], v2[1]);
  glVertex2f(v2[0], v1[1]);
  glEnd();
  assert(checkForGlError());
}

//TODO: method too long
void Draw2d::
texture(const cv::Mat & img, const Vector2i top_left)
{
  glEnable(GL_TEXTURE_2D);
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  if (img.type()==CV_8UC1)
  {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_LUMINANCE,
                 img.size().width,
                 img.size().height,
                 0,
                 GL_LUMINANCE,
                 GL_UNSIGNED_BYTE,
                 img.data);
  }
  else if (img.type()==CV_16S)
  {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_LUMINANCE,
                 img.size().width,
                 img.size().height,
                 0,
                 GL_LUMINANCE,
                 GL_UNSIGNED_SHORT,
                 img.data);
  }
  else if (img.type()==CV_8UC3)
  {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB8,
                 img.size().width,
                 img.size().height,
                 0,
                 GL_BGR,
                 GL_UNSIGNED_BYTE,
                 img.data);
  }
  else if (img.type()==CV_8UC4)
  {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB8,
                 img.size().width,
                 img.size().height,
                 0,
                 GL_BGRA,
                 GL_UNSIGNED_BYTE,
                 img.data);
  }
  else if (img.type()==CV_16UC1 || img.type()==CV_8UC2)
  {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_LUMINANCE,
                 img.size().width,
                 img.size().height,
                 0,
                 GL_LUMINANCE,
                 GL_UNSIGNED_SHORT,
                 img.data);
  }
  else if (img.type()==CV_32FC1)
  {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_LUMINANCE,
                 img.size().width,
                 img.size().height,
                 0,
                 GL_LUMINANCE,
                 GL_FLOAT,
                 img.data);
  }
  else if (img.type()==CV_32FC3)
  {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB8,
                 img.size().width,
                 img.size().height,
                 0,
                 GL_BGR,
                 GL_FLOAT,
                 img.data);
  }
  else if (img.type()==CV_32FC4)
  {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA8,
                 img.size().width,
                 img.size().height,
                 0,
                 GL_RGBA,
                 GL_FLOAT,
                 img.data);
  }
  else
  {
    cerr << "Unknown texture type" << img.type() << endl;
    assert(false);
  }
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, texture);

  int x = top_left[0];
  int y  = top_left[1];
  int w = img.size().width;
  int h  = img.size().height;

  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex2i(x, y);
  glTexCoord2f(0.0f, 1.0f); glVertex2i(x, y+h);
  glTexCoord2f(1.0f, 1.0f); glVertex2i(x+w, y+h);
  glTexCoord2f(1.0f, 0.0f); glVertex2i(x+w, y);
  glEnd();

  glDeleteTextures(1,&texture);
  glDisable(GL_TEXTURE_2D);
}

//TODO: remove redundant code with Draw3d
bool Draw2d::checkForGlError()
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
