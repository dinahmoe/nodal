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
//  ReverbNode.h
//
//  Created by Thoren Horstmann on 26.08.15.
//
//

#ifndef __ReverbNode__
#define __ReverbNode__

#include "PlainReverbNode.h"
#include "AllpassNode.h"
#include "AudioContext.hpp"
#include <array>


#define NR_PLAIN 4
#define NR_ALLPASS 2

using namespace dinahmoe;
using namespace audioengine;

//a basic Schroeder's reverb
class ReverbNode{
public:
  ReverbNode(AudioContext* context);
  ~ReverbNode();

  RefCounted<AudioGainNode> m_input;
  RefCounted<AudioGainNode> m_output;
private:
  AudioContext* m_context;
  std::array<PlainReverbNode*,NR_PLAIN> m_plain;
  std::array<AllpassNode*,NR_ALLPASS> m_allPass;
  std::array<RefCounted<AudioGainNode>,NR_PLAIN> m_gains;
  RefCounted<AudioGainNode> m_sum;
};

#endif /* defined(__ReverbNode__) */
