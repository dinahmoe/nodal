//
//  Synth.hpp
//
//  Created by Alessandro Saccoia on 8/25/15.
//
//

#ifndef _Synth_hpp
#define _Synth_hpp

#include "AudioContext.hpp"
#include "AudioNodeInput.hpp"
#include "AudioListener.h"


using namespace dinahmoe;
using namespace audioengine;

struct Synth {
  void init(AudioContext* context){
    m_audioContext = context;
    // *** Nodes creation ***
    // create an AudioBufferSourceNode, with the optional playback speed
    vco = context->createAudioBufferSourceNode(0.5);
    
    // set the buffer
    vco->setBuffer(mNoteBuffer);
    
    //create a stereopanner
    panner = context->createPannerNode(&listener,0,0,0);
    
    // *** Set the properties ***
    
    vco->connect(panner.get());

    panner->connect(context->masterGainNode());
    
  }
  
  void playNote(AudioContext* context, float x, float y, float z) {
    
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

  AudioContext* m_audioContext;
  AudioListener listener;
  RefCounted<PannerNode> panner;
  RefCounted<AudioBufferSourceNode> vco;
  InMemoryBuffer* mNoteBuffer;
};


#endif
