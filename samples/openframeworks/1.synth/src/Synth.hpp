//
//  Synth.hpp
//
//  Created by Alessandro Saccoia on 8/25/15.
//
//

#ifndef _Synth_hpp
#define _Synth_hpp

#include "AudioContext.hpp"
#include "ReverbNode.h"
#include "PlainReverbNode.h"


using namespace dinahmoe;
using namespace audioengine;

struct Synth {
  void playNote(AudioContext* context, float playbackSpeed, float filterFrequency) {
    // *** Nodes creation ***
    // create an AudioBufferSourceNode, with the optional playback speed
    RefCounted<AudioBufferSourceNode> vco = context->createAudioBufferSourceNode(playbackSpeed);
    // set the buffer
    vco->setBuffer(mNoteBuffer);
    // create a filter
    RefCounted<BiquadFilterNode> vcf = context->createBiquadFilterNode
      (DspBasics::BiquadFilterType::LOWPASS, filterFrequency, 3, 1.0F);
    
    // *** Set the properties ***
    // connect VCO to VCF
    vco->connect(vcf.get());
    
    // connect VCF to Reverb via the public input
    vcf->connect(rvb->m_input.get());
    
    // connect Reverb the main bus
    rvb->m_output->connect(context->masterGainNode());
    
    // *** Call noteOn  ***
    vco->noteOn(context->getCurrentTime() + 0.1);
  }
  
  ReverbNode* rvb;
  InMemoryBuffer* mNoteBuffer;
};


#endif
