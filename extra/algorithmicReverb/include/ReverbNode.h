//
//  ReverbNode.h
//  Dmaf OSC Utilities
//
//  Created by Thoren Horstmann on 26.08.15.
//
//

#ifndef __Dmaf_OSC_Utilities__ReverbNode__
#define __Dmaf_OSC_Utilities__ReverbNode__

#include "AudioNode.hpp"
#include "PlainReverbNode.h"
#include "AllpassNode.h"
#include "AudioContext.hpp"

using namespace dinahmoe;
using namespace audioengine;
    
class ReverbNode{
    public:
      ReverbNode(AudioContext* context);
      ~ReverbNode();

      RefCounted<AudioGainNode> m_input;
      RefCounted<AudioGainNode> m_output;
    private:
      PlainReverbNode** m_plain;
      AllpassNode** m_allPass;
      RefCounted<AudioGainNode>* m_gains;
      RefCounted<SummingNode> m_sum;
};

#endif /* defined(__Dmaf_OSC_Utilities__ReverbNode__) */
