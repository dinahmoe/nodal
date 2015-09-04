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

//  StereoPannerNode.cpp
//  Nodal
//
//  Created by Thoren Horstmann on 02.09.15.


#include "StereoPannerNode.h"
#include "AudioNode.hpp"
#include "AudioNodeInput.hpp"

namespace dinahmoe {
  namespace audioengine {
    
    StereoPannerNode::StereoPannerNode(AudioContext* context, float pan) : AudioNode(context), m_pModel(EQUALPOWER) {
      addInput("Input 1", TYPE_AUDIO);
      addInput("Input 2", TYPE_HYBRID);
      m_inputs[1]->setInitialValue(pan);
      addOutput(1);
    }
    
    StereoPannerNode::~StereoPannerNode() {
      
    }
    void StereoPannerNode::setPanningModel(PanningModel pModel){
      m_pModel = pModel;
    }

    void StereoPannerNode::processInternal(int numSamples, int outputRequesting) {
      bool isInput1SampleAccurate = m_inputs[1]->isSampleAccurate();
      bool isSilent = true;
      float gainL = 0;
      float gainR = 0;
      bool isMono = false;
      float x = 0;
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
      float *panData;
      float panValue;
      if (isInput1SampleAccurate) {
        panData = m_inputBuffers[1]->data[0];
      }else{
        panValue = m_inputs[1]->getValue();
        x = computeX(panValue, isMono);
        gainL = cosf(x * M_PI / 2);
        gainR = sinf(x * M_PI / 2);
      }
      for(int currentSample = 0; currentSample < numSamples; ++currentSample){
        if(isInput1SampleAccurate){
          panValue = panData[currentSample];
          x = computeX(panValue, isMono);
          gainL = cosf(x * M_PI / 2);
          gainR = sinf(x * M_PI / 2);
        }
        if(isMono){
          out->data[0][currentSample] = in->data[0][currentSample] * gainL;
          out->data[1][currentSample] = in->data[0][currentSample] * gainR;
        } else {
          if(panValue <= 0){
            out->data[0][currentSample] = in->data[0][currentSample] + in->data[1][currentSample] * gainL;
            out->data[1][currentSample] = in->data[1][currentSample] * gainR;
          } else {
            out->data[0][currentSample] = in->data[0][currentSample] * gainL;
            out->data[1][currentSample] = in->data[1][currentSample] + in->data[0][currentSample] * gainR;
          }
        }
      }

    }
  float StereoPannerNode::computeX(float pan, bool isMono){
      pan = fmax(-1,pan);
      pan = fmin(1,pan);
      if(isMono){
        return (pan +1) / 2;
      } else {
        if(pan <= 0){
          return pan +1;
        } else {
          return pan;
        }
    }
  }

  } // audioengine
} // dinahmoe