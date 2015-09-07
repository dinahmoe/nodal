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
//  PannerNode.cpp
//  Nodal
//
//  Created by Thoren Horstmann on 02.09.15.
//
//

#include "PannerNode.h"
#include "AudioNode.hpp"
#include "AudioNodeInput.hpp"
#include <iostream>

namespace dinahmoe {
  namespace audioengine {
    
    PannerNode::PannerNode(AudioContext* context, AudioListener* listener, float x, float y, float z) :
    AudioNode(context),
    m_pModel(EQUALPOWER),
    m_dModel(LINEAR),
    m_Listener(listener),
    m_refDistance(1),
    m_maxDistance(1000),
    m_rolloffFactor(1),
    m_coneInnerAngle(360),
    m_coneOuterAngle(360),
    m_coneOuterGain(0)
    {
      addInput("Input 1", TYPE_AUDIO);
      addInput("Input 2", TYPE_HYBRID);
      m_inputs[1]->setInitialValue(x);
      addInput("Input 2", TYPE_HYBRID);
      m_inputs[2]->setInitialValue(y);
      addInput("Input 2", TYPE_HYBRID);
      m_inputs[3]->setInitialValue(z);
      setPosition(x, y, z);
      setOrientation();
      setVelocity();
      addOutput(1);
    }
    
    PannerNode::~PannerNode() {
    }
    void PannerNode::setPosition(float x, float y, float z){
      m_Position.setXYZ(x,y,z);
    }
    void PannerNode::setOrientation(float x, float y, float z){
      m_Orientation.setXYZ(x,y,z);
    }
    void PannerNode::setVelocity(float x, float y, float z){
      m_Velocity.setXYZ(x,y,z);
    }
    void PannerNode::setPanningModel(PanningModel pModel){
      m_pModel = pModel;
    }
    void PannerNode::setDistanceModel(DistanceModelType dModel){
      m_dModel = dModel;
    }
    void PannerNode::setListener(AudioListener* listener){
      m_Listener = listener;
    }
    void PannerNode::setRefDistance(float refDistance){
      m_refDistance = refDistance;
    }
    void PannerNode::setMaxDistance(float maxDistance){
      m_maxDistance = maxDistance;
    }
    void PannerNode::setRollOffFactor(float rollOffFactor){
      m_rolloffFactor = rollOffFactor;
    }
    void PannerNode::setConeInnerAngle(float coneInnerAngle){
      m_coneInnerAngle = fmod(coneInnerAngle,360);
    }
    void PannerNode::setConeOuterAngle(float coneOuterAngle){
      m_coneOuterAngle = fmod(coneOuterAngle,360);
    }
    void PannerNode::setConeOuterGain(float coneOuterGain){
      m_coneOuterGain = coneOuterGain;
    }
    
    void PannerNode::processInternal(int numSamples, int outputRequesting) {
      bool isInput1SampleAccurateX = m_inputs[1]->isSampleAccurate();
      bool isInput1SampleAccurateY = m_inputs[2]->isSampleAccurate();
      bool isInput1SampleAccurateZ = m_inputs[3]->isSampleAccurate();

      bool isSilent = true;
      float gainL = 0;
      float gainR = 0;
      bool isMono = false;
      float x = 0;
      float *xData;
      float *yData;
      float *zData;
      float xValue;
      float yValue;
      float zValue;
      float azimuth;
      float elevation;
      float distanceGain;
      const AudioBuffer* in = m_inputBuffers[0];
      if (in->isSilent) {
        m_outputBuffers[0]->isSilent = true;
        return;
      } else {
        isSilent = false;
      }
      if(in->channels == 1){
        isMono = true;
      }
      AudioBuffer* out = m_outputBuffers[0];
      out->isSilent = false;

      if (isInput1SampleAccurateX && isInput1SampleAccurateY && isInput1SampleAccurateZ) {
        xData = m_inputBuffers[1]->data[0];
        yData = m_inputBuffers[2]->data[0];
        zData = m_inputBuffers[3]->data[0];

      }else{
        xValue = m_inputs[1]->getValue();
        yValue = m_inputs[2]->getValue();
        zValue = m_inputs[3]->getValue();
        setPosition(xValue,yValue,zValue);
        computeAzimuthElevationDistance(&azimuth,&elevation);
        x = computeX(azimuth, isMono);
        assert(x <= 90 && x >= -90);
        distanceGain = computeDistanceAndConeGain();
        std::cout << distanceGain << std::endl;
        gainL = cosf(x * M_PI / 2);
        gainR = sinf(x * M_PI / 2);

      }
      for(int currentSample = 0; currentSample < numSamples; ++currentSample){
        if(isInput1SampleAccurateX){
          xValue = xData[currentSample];
          yValue = yData[currentSample];
          zValue = zData[currentSample];
          setPosition(xValue,yValue,zValue);
          computeAzimuthElevationDistance(&azimuth,&elevation);
          x = computeX(azimuth, isMono);
          distanceGain = computeDistanceAndConeGain();

          gainL = cosf(x * M_PI / 2);
          gainR = sinf(x * M_PI / 2);

        }
        if(isMono){
          out->data[0][currentSample] = (in->data[0][currentSample] * gainL) * distanceGain;
          out->data[1][currentSample] = (in->data[0][currentSample] * gainR) * distanceGain;
        } else {
          if(azimuth <= 0){
            out->data[0][currentSample] = (in->data[0][currentSample] + in->data[1][currentSample] * gainL) * distanceGain;
            out->data[1][currentSample] = (in->data[1][currentSample] * gainR) * distanceGain;
          } else {
            out->data[0][currentSample] = (in->data[0][currentSample] * gainL) * distanceGain;
            out->data[1][currentSample] = (in->data[1][currentSample] + in->data[0][currentSample] * gainR) *distanceGain;
          }
        }
      }
      
    }
    void PannerNode::computeAzimuthElevationDistance(float* azimuth, float* elevation){
      Vec3<float> sourceListener = m_Position - m_Listener->m_Position;
      if(sourceListener.isZero()){
        *azimuth = 0;
        *elevation = 0;
        return;
      }
      sourceListener.normalize();
      // Align axes.
      Vec3<float> listenerFront = m_Listener->m_OrientationFront;
      Vec3<float> listenerUp = m_Listener->m_OrientationUp;
      Vec3<float> listenerRight = listenerFront.cross(listenerUp);
      listenerRight.normalize();
      
      Vec3<float> listenerFrontNorm = listenerFront;
      listenerFrontNorm.normalize();
      
      Vec3<float> up = listenerRight.cross(listenerFrontNorm);
      
      float upProjection = sourceListener.dot(up);
      
      Vec3<float> projectedSource = sourceListener -  up * upProjection;
      projectedSource.normalize();
      
      *azimuth = 180 * acos(projectedSource.dot(listenerRight)) / M_PI;
      
      // Source in front or behind the listener.
      float frontBack = projectedSource.dot(listenerFrontNorm);
      if (frontBack < 0)
        *azimuth = 360 - *azimuth;
      
      // Make azimuth relative to "front" and not "right" listener vector.
      if ((*azimuth >= 0) && (*azimuth <= 270))
        *azimuth = 90 - *azimuth;
      else
        *azimuth = 450 - *azimuth;
      
      *elevation = 90 - 180 * acos(sourceListener.dot(up)) / M_PI;
      
      if (*elevation > 90)
        *elevation = 180 - *elevation;
      else if (*elevation < -90)
        *elevation = -180 - *elevation;
    }
    float PannerNode::computeDistanceAndConeGain(){
      Vec3<float> sourceToListener = m_Listener->m_Position - m_Position;
      float distance = sqrt(sourceToListener.dot(sourceToListener));

      switch (m_dModel) {
        case LINEAR:
          distance =  1 - m_rolloffFactor * ((distance - m_refDistance) / (m_maxDistance - m_refDistance));
          break;
        case INVERSE:
          distance = m_refDistance / (m_refDistance + m_rolloffFactor * (distance - m_refDistance));
          break;
        case EXPONENTIAL:
          distance = pow((distance / m_refDistance), -m_rolloffFactor);
          break;
      }
      distance = fmax(0,distance);
      distance = fmin(1,distance);
      if (m_Orientation.isZero() || ((m_coneInnerAngle == 0) && (m_coneOuterAngle == 0)))
        return distance; // no cone specified - unity gain
      
      // Normalized source-listener vector
      sourceToListener.normalize();
      
      Vec3<float> normalizedSourceOrientation = m_Orientation;
      normalizedSourceOrientation.normalize();
      
      // Angle between the source orientation vector and the source-listener vector
      float dotProduct = sourceToListener.dot(normalizedSourceOrientation);
      float angle = 180 * acos(dotProduct) / M_PI;
      float absAngle = fabs(angle);
      
      // Divide by 2 here since API is entire angle (not half-angle)
      float absInnerAngle = fabs(m_coneInnerAngle) / 2;
      float absOuterAngle = fabs(m_coneOuterAngle) / 2;
      float gain = 1;
      
      if (absAngle <= absInnerAngle)
        // No attenuation
        gain = 1;
      else if (absAngle >= absOuterAngle)
        // Max attenuation
        gain = m_coneOuterGain;
      else {
        // Between inner and outer cones
        // inner -> outer, x goes from 0 -> 1
        float x = (absAngle - absInnerAngle) / (absOuterAngle - absInnerAngle);
        gain = (1 - x) + m_coneOuterGain * x;
      }
      
      return distance * gain;
    }
    
    float PannerNode::computeX(float azimuth, bool isMono){
      azimuth = fmax(-180,azimuth);
      azimuth = fmin(180,azimuth);
      
      if(azimuth < -90){
        azimuth = -180 - azimuth;
      } else if(azimuth > 90) {
        azimuth = 180 - azimuth;
      }
      if(isMono){
        return (azimuth + 90) / 180;
      } else {
        if(azimuth <= 0){
          return (azimuth + 90) / 90;
        } else {
          return azimuth / 90;
        }
      }
    }
    
  } // audioengine
} // dinahmoe