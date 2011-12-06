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

#include "performance_monitor.h"

namespace VisionTools
{
using namespace std;

PerformanceMonitor
::PerformanceMonitor()/*:
  ringbuffer_(30)*/
{
}

void PerformanceMonitor
::setup(pangolin::DataLog * log)
{
  fps_ = 0;
  timers_.size();
  frame_timer_.start();
  for (std::list<pair<string, StopWatch> >::iterator iter = timers_.begin();
       iter!=timers_.end(); ++iter)
  {
    names_.push_back(iter->first);
  }
  log->SetLabels(names_);
}

void PerformanceMonitor
::add(const string & str)
{
  timers_.push_back(make_pair(str, StopWatch()));
}

void PerformanceMonitor
::new_frame()
{
  static int count_frames = 0;
  ++count_frames;
  for (list<pair<string, StopWatch> >::iterator iter = timers_.begin();
       iter!=timers_.end(); ++iter)
  {
    iter->second.reset();
  }
  if(count_frames>=1)
  {
    frame_timer_.stop();
    static RingBuffer<double> ring_buf(20);
    ring_buf.push_back(frame_timer_.get_stopped_time());
    int size = ring_buf.size();
    double sum = 0;
    for (int i=0;i<size; ++i)
    {
      sum += ring_buf.get(i);
    }
    fps_ = size/sum;
    frame_timer_.start();
  }
}

list<pair<string, StopWatch> >::iterator PerformanceMonitor
::find_timer(const string & str)
{
  for (list<pair<string, StopWatch> >::iterator it=timers_.begin();
       it!=timers_.end(); ++it)
  {
    if (it->first == str){
      return it;
    }
  }
  return timers_.end();
}

void PerformanceMonitor
::start(const std::string & str)
{
  list<pair<string, StopWatch> >::iterator iter = find_timer(str);
  if(iter!=timers_.end()){
    iter->second.start();
  }
  else
  {
    throw std::runtime_error("PerMon: Unknown type!");
  }
}

void PerformanceMonitor
::stop(const std::string & str)
{
  list<pair<string, StopWatch> >::iterator iter = find_timer(str);
  if(iter!=timers_.end()){
    iter->second.stop();
  }
  else
  {
    throw std::runtime_error("PerMon: Unknown type!");
  }
}

void PerformanceMonitor
::plot(pangolin::DataLog * plot)
{
  double cost_cur_frame=0;
  vector<float> time(timers_.size());
  int i = 0;
  for (list<pair<string, StopWatch> >::iterator iter=timers_.begin();
       iter!=timers_.end(); ++iter)
  {
    double stopped_time = iter->second.get_stopped_time();
    cost_cur_frame+=stopped_time ;
    time[i] = stopped_time ;
    ++i;
  }
  plot->Log(time);
}

}
