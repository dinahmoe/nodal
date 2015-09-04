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
//
//  PannerNode.h
//  Nodal
//
//  Created by Thoren Horstmann on 02.09.15.
//
//

#ifndef __Nodal__PannerNode__
#define __Nodal__PannerNode__

#include "AudioNode.hpp"
#include "StereoPannerNode.h"
#include "Vec3.h"
#include "AudioListener.h"

namespace dinahmoe {
  namespace audioengine {
    
    enum DistanceModelType {
      LINEAR,
      INVERSE,
      EXPONENTIAL
    };
    
    class PannerNode : public AudioNode {
    public:
      PannerNode(AudioContext* context, float x = 0.F, float y = 0.F, float z = 0.F);
      ~PannerNode();
      void setPanningModel(PanningModel pModel);
      void setDistanceModel(DistanceModelType dModel);
      void setListener(AudioListener listener);
      void setPosition(float x = 0, float y = 0, float z = 0);
      void setOrientation(float x = 1, float y = 0, float z = 0);
      void setVelocity(float x = 0, float y = 0, float z = 0);

      inline const char* getType() { return "PannerNode"; }
      void processInternal(int numSamples, int outputRequesting);
    private:
      PanningModel m_pModel;
      DistanceModelType m_dModel;
      AudioListener m_Listener;
      float m_refDistance;
      float m_maxDistance;
      float m_rolloffFactor;
      float m_coneInnerAngle;
      float m_coneOuterAngle;
      float m_coneOuterGain;
      Vec3<float> m_Position;
      Vec3<float> m_Orientation;
      Vec3<float> m_Velocity;
      
      void computeAzimuthElevationDistance(float* azimuth, float* elevation, float* distance);
      float computeX(float azimuth, bool isMono);
      float computeDistanceGain(float distance);
    };
    
  } // audioengine
} // dinahmoe

#endif /* defined(__Nodal__PannerNode__) */