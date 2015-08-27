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

using namespace dinahmoe;
using namespace audioengine;

class AllpassNode {
    public:
      AllpassNode(AudioContext* context,float delay,float gain);
      ~AllpassNode();
      RefCounted<AudioGainNode> m_input;
      RefCounted<AudioGainNode> m_output;
    private:
      RefCounted<AudioGainNode>* m_gains;
      RefCounted<DelayNode> m_delay;
      RefCounted<SummingNode>* m_sums;
};

#endif /* defined(__Nodal__AllpassNode__) */
