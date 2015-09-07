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
#include "AudioNodeInput.hpp"
#include "AudioListener.h"


using namespace dinahmoe;
using namespace audioengine;

struct Synth {
  void init(AudioContext* context){
    // *** Nodes creation ***
    // create an AudioBufferSourceNode, with the optional playback speed
    vco = context->createAudioBufferSourceNode(0.5);
    
    // set the buffer
    vco->setBuffer(mNoteBuffer);
    // create a filter
    vcf = context->createBiquadFilterNode(DspBasics::BiquadFilterType::LOWPASS, 2000, 3 , 1.0F);
    
    // *** Set the properties ***
    // connect VCO to VCF
    vco->connect(vcf.get());
    
    // connect VCF to Reverb via the public input
    //vcf->connect(rvb->m_input.get());
    
    //create a stereopanner
    panner = context->createPannerNode(&listener,0,0,0);
    vcf->connect(panner.get());
    // connect Reverb the main bus
    panner->connect(context->masterGainNode());
  }
  
  void playNote(AudioContext* context, float playbackSpeed, float filterFrequency, float x, float y, float z) {
    //vco->m_inputs[0]->setValueImmediate(playbackSpeed, context->getCurrentTime());
    //vcf->m_inputs[1]->setValueImmediate(filterFrequency, context->getCurrentTime());

    panner->m_inputs[1]->setValueImmediate(x, context->getCurrentTime());
    panner->m_inputs[2]->setValueImmediate(y, context->getCurrentTime());
    panner->m_inputs[3]->setValueImmediate(z, context->getCurrentTime());
    
    // *** Call noteOn  ***
    vco->noteOn(context->getCurrentTime() + 0.1);
  }
  
  void setListener(float lx, float ly, float lz, float ox, float oy, float oz, float oxu, float oyu, float ozu){
    listener.setPosition(lx, ly, lz);
    listener.setOrientation(ox, oy, oz, oxu, oyu, ozu);
  }
  AudioListener listener;
  RefCounted<AudioBufferSourceNode> vco;
  RefCounted<BiquadFilterNode> vcf;
  RefCounted<PannerNode> panner;
  ReverbNode* rvb;
  InMemoryBuffer* mNoteBuffer;
};


#endif
