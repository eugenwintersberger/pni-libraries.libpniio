//
// (c) Copyright 2018 DESY
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Jan 5, 2018
//
#pragma once

#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
#include<queue>

template<typename ValueType>
class IOQueue
{
  private:
    std::mutex              _mutex;
    std::queue<ValueType>   _queue;
    std::condition_variable _data_ready;
  public:
    using value_type = ValueType;
    void push(const value_type &value);

    //--------------------------------------------------------------------
    void blocking_pop(value_type &value);
};

template<typename ValueType>
void IOQueue<ValueType>::push(const value_type &value)
 {
   std::lock_guard<std::mutex> guard(_mutex);
   _queue.push(value);
   _data_ready.notify_one();
 }

 template<typename ValueType>
 void IOQueue<ValueType>::blocking_pop(value_type &value)
 {
   std::unique_lock<std::mutex> lock(_mutex);
   _data_ready.wait(lock,[this]{ return !_queue.empty(); });
   value = _queue.front();
   _queue.pop();
 }
