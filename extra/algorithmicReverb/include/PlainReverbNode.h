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

namespace dinahmoe {
  namespace audioengine {
    
    class PlainReverbNode : public AudioNode {
    public:
      PlainReverbNode(AudioContext* context,float delay,float gain);
      ~PlainReverbNode();
      inline const char* getType() { return "PlainReverbNode"; }
      void processInternal(int numSamples, int outputRequesting);
      RefCounted<AudioGainNode> m_input;
      RefCounted<AudioGainNode> m_output;
    private:
      RefCounted<AudioGainNode> m_gain;
      RefCounted<DelayNode> m_delay;
      RefCounted<SummingNode> m_sum;
    };
    
  } // AUDIOENGINE
} // DMAF

#endif /* defined(__Nodal__PlainReverbNode__) */
