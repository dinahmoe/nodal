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
//  AllpassNode.cpp
//  Nodal
//
//  Created by Thoren Horstmann on 26.08.15.
//
//


/*
   input -> sum ---> ---> gain(-g) -> sum -> output
             ^         |               ^
             |         V               |
          gain(g) <- delay(d) ---> --->
 */

#include "AllpassNode.h"

AllpassNode::AllpassNode(AudioContext* context,float delay,float gain){
  //create the nodes
  m_input =context->createGainNode();
  m_output =context->createGainNode();
  m_sums[0] = context->createGainNode();
  m_sums[1] = context->createGainNode();
  m_gains[0] = context->createGainNode(gain);
  m_gains[1] = context->createGainNode(-gain);
  m_delay = context->createDelayNode(delay);
  
  //connect the nodes
  m_input->connect(m_sums[0].get());
  m_sums[0]->connect(m_delay.get());
  m_sums[0]->connect(m_gains[1].get());
  m_delay->connect(m_gains[0].get());
  m_delay->connect(m_sums[1].get());
  m_gains[1]->connect(m_sums[0].get());
  m_gains[0]->connect(m_sums[1].get());
  m_sums[1]->connect(m_output.get());
}

AllpassNode::~AllpassNode(){}
