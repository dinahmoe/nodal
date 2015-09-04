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
//  ReverbNode.cpp
//
//  Created by Thoren Horstmann on 26.08.15.
//
//
/*
       -> plain(g_0,d_0) -> gain(g_4) -|
       |                               |
 input -> plain(g_1,d_1) -> gain(g_5) ---> sum -> allpass(g__9,d_5) -> allpass(g_10,d_6) -> output
       |                               |
       -> plain(g_2,d_2) -> gain(g_6) --
       |                               |
       -> plain(g_3,d_3) -> gain(g_7) --
 */
#include "ReverbNode.h"
#include "AudioBufferSourceNode.hpp"
#include "AudioNodeInput.hpp"


ReverbNode::ReverbNode(AudioContext* context){
  //initial values for the plain and allpass reverbs
  //tune the reverb here
  static const float initialValuesPlain[3][NR_PLAIN] {
    {0.1,0.2,0.3,0.4},  //init m_gains
    {0.01,0.02,0.03,0.04}, //init m_plain delay
    {0.5,0.5,0.5,0.5} //init m_plain gain
  };
  static const float initialValuesAllpass[2][NR_ALLPASS] {
    {0.05,0.05}, //init m_allpass delay
    {0.4,0.4} //init m_allpass gain
  };
  
  //create the nodes
  m_input = context->createGainNode();
  m_output = context->createGainNode();
  m_sum = context->createGainNode();
  
  for(int i = 0; i < NR_PLAIN;++i){
    m_gains[i] = context->createGainNode(initialValuesPlain[0][i]);
    m_plain[i] = new PlainReverbNode(context,initialValuesPlain[1][i],initialValuesPlain[2][i]);
    //connect the four plainreverbs
    m_input->connect(m_plain[i]->m_input.get());
    m_plain[i]->m_output.get()->connect(m_gains[i].get());
    m_gains[i]->connect(m_sum.get());
  }
  
  for (int i = 0; i < NR_ALLPASS; ++i) {
    m_allPass[i] = new AllpassNode(context,initialValuesAllpass[0][i],initialValuesAllpass[1][i]);
  }
  //connect the nodes
  m_sum->connect(m_allPass[0]->m_input.get());
  m_allPass[0]->m_output.get()->connect(m_allPass[1]->m_input.get());
  m_allPass[1]->m_output.get()->connect(m_output.get());
}

ReverbNode::~ReverbNode(){}

