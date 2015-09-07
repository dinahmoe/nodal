/*
 * Copyright (c) 2015, Dinahmoe. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
//  Vec3.h
//  Nodal
//
//  Created by Thoren Horstmann on 04.09.15.
//
//  Simple vector with 3 elements and basic operations

#ifndef __Nodal__Vec3__
#define __Nodal__Vec3__

#include <type_traits>

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vec3{
public:
  Vec3():m_x(0),m_y(0),m_z(0){}
  Vec3(T x, T y,T z):m_x(x),m_y(y),m_z(z){}

  void setXYZ(T x, T y, T z){
    m_x = x;
    m_y = y;
    m_z = z;
  }
  T getX(){return m_x;}
  T getY(){return m_y;}
  T getZ(){return m_z;}

  Vec3 operator+(Vec3 vec){
    return Vec3(m_x + vec.getX(), m_y + vec.getY(), m_z + vec.getZ());
  }
  Vec3 operator-(Vec3 vec){
    return Vec3(m_x - vec.getX(), m_y - vec.getY(), m_z - vec.getZ());
  }
  Vec3 operator*(T scalar){
    return Vec3(m_x * scalar, m_y * scalar, m_z * scalar);
  }
  Vec3 operator/(T scalar){
    return Vec3(m_x / scalar, m_y / scalar,m_z / scalar);
  }
  void operator=(Vec3 vec){
    m_x = vec.getX();
    m_y = vec.getY();
    m_z = vec.getZ();
  }
  Vec3 cross(Vec3 vec){
    return Vec3(m_y*vec.getZ() - m_z*vec.getY(),m_z*vec.getX() - m_x*vec.getZ(),m_x*vec.getY() - m_y*vec.getX());
  }
  T dot(Vec3 vec){
    return m_x*vec.getX() + m_y*vec.getY() + m_z*vec.getZ();
  }
  bool isZero(){
    return m_x == 0 && m_y == 0 && m_z == 0;
  }
  void normalize(){
    T magnitude = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    if(magnitude != 0){
      m_x /= magnitude;
      m_y /= magnitude;
      m_z /= magnitude;
    }
  }

private:
  T m_x;
  T m_y;
  T m_z;
};

#endif /* defined(__Nodal__Vec3__) */
