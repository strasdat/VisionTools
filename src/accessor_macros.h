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

#ifndef VISIONTOOLS_ACCESSOR_MACROS_H
#define VISIONTOOLS_ACCESSOR_MACROS_H

#include <cassert>
#include <map>
#include <set>
#include <vector>

#include <tr1/memory>
#include <tr1/unordered_map>
#include <tr1/unordered_set>

#include <Eigen/Core>

#include <opencv2/opencv.hpp>

namespace VisionTools
{

using namespace std;
using namespace Eigen;

template<class KEY, class VAL, class H, class P, class A>
void  ADD_TO_MAP_ELEM(const KEY & key, const VAL & val,
                      tr1::unordered_map<KEY,VAL,H,P,A> * m)
{
  typename tr1::unordered_map<KEY,VAL,H,P,A>::iterator it
      = m->find(key);
  if(it!=m->end())
  {
    it->second += val;
  }
  else
  {
    m->insert(make_pair(key,val));
  }
}

template<class KEY, class VAL, class C, class A>
void  ADD_TO_MAP_ELEM(const KEY & key, const VAL & val,
                      map<KEY,VAL,C,A> * m)
{
  typename map<KEY,VAL,C,A>::iterator it
      = m->find(key);
  if(it!=m->end())
  {
    it->second += val;
  }
  else
  {
    m->insert(make_pair(key,val));
  }
}

template<class KEY, class VAL, class H, class P, class A>
const VAL &
GET_MAP_ELEM(const KEY & key,
             const tr1::unordered_map<KEY,tr1::shared_ptr<VAL>,H,P,A> & m)
{
  typename tr1::unordered_map<KEY,tr1::shared_ptr<VAL>,H,P,A>::const_iterator it
      = m.find(key);
  assert(it!=m.end());
  return *(it->second);
}

template<class KEY, class VAL, class H, class P, class A>
const VAL &  GET_MAP_ELEM(const KEY & key,
                          const tr1::unordered_map<KEY,VAL,H,P,A> & m)
{
  typename tr1::unordered_map<KEY,VAL,H,P,A>::const_iterator it
      = m.find(key);
  assert(it!=m.end());
  return it->second;
}

template<class KEY, class VAL, class C, class A>
const VAL &  GET_MAP_ELEM(const KEY & key,
                          const map<KEY,tr1::shared_ptr<VAL>,C,A> & m)
{
  typename map<KEY,tr1::shared_ptr<VAL>,C,A>::const_iterator it = m.find(key);
  assert(it!=m.end());
  return *(it->second);
}

template<class KEY, class VAL, class C, class A>
const VAL &  GET_MAP_ELEM(const KEY & key,
                          const map<KEY,VAL,C,A> & m)
{
  typename map<KEY,VAL,C,A>::const_iterator it = m.find(key);
  assert(it!=m.end());
  return it->second;
}

template<class KEY, class VAL, class H, class P, class A>
VAL &
GET_MAP_ELEM_REF(const KEY & key,
                 tr1::unordered_map<KEY,tr1::shared_ptr<VAL>,H,P,A> * m)
{
  typename tr1::unordered_map<KEY,tr1::shared_ptr<VAL>,H,P,A>::iterator it
      = m->find(key);
  assert(it!=m->end());
  return *(it->second);
}

template<class KEY, class VAL, class H, class P, class A>
VAL &  GET_MAP_ELEM_REF(const KEY & key,
                        tr1::unordered_map<KEY,VAL,H,P,A> * m)

{
  typename tr1::unordered_map<KEY,VAL,H,P,A>::iterator it
      = m->find(key);
  assert(it!=m->end());
  return it->second;
}

template<class KEY, class VAL, class C, class A>
VAL & GET_MAP_ELEM_REF(const KEY & key,
                       map<KEY,tr1::shared_ptr<VAL>,C,A> * m)
{
  typename map<KEY,tr1::shared_ptr<VAL>,C,A>::iterator it = m->find(key);
  assert(it!=m->end());
  return *(it->second);
}

template<class KEY, class VAL, class C, class A>
VAL &  GET_MAP_ELEM_REF(const KEY & key,
                        map<KEY,VAL,C,A> * m)
{
  typename map<KEY,VAL,C,A>::iterator it = m->find(key);
  assert(it!=m->end());
  return it->second;
}


template<class KEY, class VAL, class H, class P, class A>
bool IS_IN_SET(const KEY & key,
               const tr1::unordered_map<KEY,VAL,H,P,A> & m)
{
  typename tr1::unordered_map<KEY,VAL,H,P,A>::const_iterator it
      = m.find(key);
  return it!=m.end();
}

template<class KEY, class H, class P, class A>
bool IS_IN_SET(const KEY & key,
               const tr1::unordered_set<KEY,H,P,A> & m)
{
  typename tr1::unordered_set<KEY,H,P,A>::const_iterator it
      = m.find(key);
  return it!=m.end();
}

template<class KEY, class C, class A>
bool IS_IN_SET(const KEY & key,
               const set<KEY,C,A> & m)
{
  typename set<KEY,C,A>::const_iterator it = m.find(key);
  return it!=m.end();
}

template<class KEY, class VAL, class C, class A>
bool IS_IN_SET(const KEY & key,
               const map<KEY,VAL,C,A> & m)
{
  typename map<KEY,VAL,C,A>::const_iterator it = m.find(key);
  return it!=m.end();
}

template <class TYPE, class A>
const TYPE & GET_VEC_VAL(size_t i, const vector<TYPE,A> & vec)
{
  assert(i>=0 && i<vec.size());
  return vec[i];
}

template <class TYPE, class A>
TYPE & GET_VEC_VAL_REF(size_t i, vector<TYPE,A> * vec)
{
  assert(i>=0 && i<vec->size());
  return (*vec)[i];
}

inline double pyrFromZero_d(double x, int level)
{
  return x/(1<<level);
}

inline int zeroFromPyr_i(int x, int level)
{
  return (x<<level);
}

inline int pyrFromZero_i(int x, int level)
{
  return (x>>level);
}

inline double zeroFromPyr_d(double x, int level)
{
  return x*(1<<level);
}

inline Vector2d pyrFromZero_2d(const Vector2d & uv_0, int level)
{
  return Vector2d(pyrFromZero_d(uv_0.x(), level),
                  pyrFromZero_d(uv_0.y(), level));
}

inline Vector2i pyrFromZero_2d(const Vector2i & uv_0, int level)
{
  return Vector2i(pyrFromZero_i(uv_0.x(), level),
                  pyrFromZero_i(uv_0.y(), level));
}

inline Vector2d zeroFromPyr_2d(const Vector2d & uv_pyr, int level)
{
  return Vector2d(zeroFromPyr_d(uv_pyr.x(), level),
                  zeroFromPyr_d(uv_pyr.y(), level));
}

inline Vector2i zeroFromPyr_2i(const Vector2i & uv_pyr, int level)
{
  return Vector2i(zeroFromPyr_i(uv_pyr.x(), level),
                  zeroFromPyr_i(uv_pyr.y(), level));
}


inline Vector3d pyrFromZero_3d(const Vector3d & uvu_0, int level)
{
  return Vector3d(pyrFromZero_d(uvu_0.x(), level),
                  pyrFromZero_d(uvu_0.y(), level),
                  pyrFromZero_d(uvu_0.z(), level));
}


inline Vector3d zeroFromPyr_3d(const Vector3d & uvu_pyr, int level)
{
  return Vector3d(zeroFromPyr_d(uvu_pyr.x(), level),
                  zeroFromPyr_d(uvu_pyr.y(), level),
                  zeroFromPyr_d(uvu_pyr.z(), level));
}


inline Vector3i zeroFromPyr_3d(const Vector3i & uvu_pyr, int level)
{
  return Vector3i(zeroFromPyr_i(uvu_pyr.x(), level),
                  zeroFromPyr_i(uvu_pyr.y(), level),
                  zeroFromPyr_i(uvu_pyr.z(), level));
}

}

#endif // ACCESSOR_MACROS_H
