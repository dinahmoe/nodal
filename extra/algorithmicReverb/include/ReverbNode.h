//
//  ReverbNode.h
//
//  Created by Thoren Horstmann on 26.08.15.
//
//

#ifndef __ReverbNode__
#define __ReverbNode__

#include "AudioNode.hpp"
#include "PlainReverbNode.h"
#include "AllpassNode.h"
#include "AudioContext.hpp"
#include <array>


#define NR_PLAIN 4
#define NR_ALLPASS 2

using namespace dinahmoe;
using namespace audioengine;


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
  std::array<RefCounted<BiquadFilterNode>,NR_ALLPASS> m_filter;
  std::array<RefCounted<AudioGainNode>,NR_PLAIN> m_gains;
  RefCounted<AudioGainNode> m_sum;
};

#endif /* defined(__ReverbNode__) */
