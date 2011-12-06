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

#ifndef VISIONTOOLS_PERFORMANCE_MONITOR_H
#define VISIONTOOLS_PERFORMANCE_MONITOR_H

#include <pangolin/pangolin.h>

#include "linear_camera.h"
#include "ringbuffer.h"
#include "stopwatch.h"

namespace VisionTools
{

class PerformanceMonitor
{
public:
  PerformanceMonitor();

  void
  add                        (const std::string & str);
  void
  new_frame                  ();
  void
  start                      (const std::string & str);
  void
  stop                       (const std::string & str);
  void
  plot                       (pangolin::DataLog * plot);
  void
  setup                      (pangolin::DataLog * log);

  const float & fps() const
  {
    return fps_;
  }

private:
  float fps_;
  std::list<std::pair<std::string, StopWatch> >::iterator
  find_timer                 (const std::string & str);
  std::list<std::pair<std::string, StopWatch> > timers_;
  //RingBuffer<std::vector<float> > ringbuffer_;
  std::vector<std::string> names_;
  //int num_timers_;
  StopWatch frame_timer_;
};
}

#endif
