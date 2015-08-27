//
//  AllpassNode.h
//  Nodal
//
//  Created by Thoren Horstmann on 26.08.15.
//
//

#ifndef __Nodal__AllpassNode__
#define __Nodal__AllpassNode__


#include "AudioNode.hpp"
#include "AudioGainNode.hpp"
#include "DelayNode.hpp"
#include "AudioContext.hpp"
#include <array>

using namespace dinahmoe;
using namespace audioengine;

class AllpassNode {
public:
  AllpassNode(AudioContext* context,float delay,float gain);
  ~AllpassNode();
  RefCounted<AudioGainNode> m_input;
  RefCounted<AudioGainNode> m_output;
private:
  AudioContext* m_context;
  std::array<RefCounted<AudioGainNode>,2> m_gains;
  RefCounted<DelayNode> m_delay;
  std::array<RefCounted<AudioGainNode>,2> m_sums;
};

#endif /* defined(__Nodal__AllpassNode__) */
