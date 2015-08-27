//
//  PlainReverbNode.h
//  Nodal
//
//  Created by Thoren Horstmann on 26.08.15.
//
//

#ifndef __Nodal__PlainReverbNode__
#define __Nodal__PlainReverbNode__

#include "AudioNode.hpp"
#include "AudioGainNode.hpp"
#include "DelayNode.hpp"
#include "AudioContext.hpp"

using namespace dinahmoe;
using namespace audioengine;

class PlainReverbNode{
public:
  PlainReverbNode(AudioContext* context,float delay,float gain);
  ~PlainReverbNode();

  RefCounted<AudioGainNode> m_input;
  RefCounted<AudioGainNode> m_output;
private:
  AudioContext* m_context;
  RefCounted<AudioGainNode> m_gain;
  RefCounted<DelayNode> m_delay;
  RefCounted<AudioGainNode> m_sum;
};

#endif /* defined(__Nodal__PlainReverbNode__) */
