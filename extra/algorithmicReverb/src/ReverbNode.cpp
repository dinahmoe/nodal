//
//  ReverbNode.cpp
//  Dmaf OSC Utilities
//
//  Created by Thoren Horstmann on 26.08.15.
//
//

#include "ReverbNode.h"
#include "AudioBufferSourceNode.hpp"
#include "AudioNodeInput.hpp"


dinahmoe::audioengine::ReverbNode::ReverbNode(AudioContext* context) : AudioNode(context){
  addInput("Audio Input", TYPE_AUDIO);
  /*addInput("Delay control", TYPE_HYBRID);
  m_inputs[1]->setInitialValue(delay);
  
  addInput("Gain control", TYPE_HYBRID);
  m_inputs[2]->setInitialValue(gain);*/
  
  m_sum = context->createSummingNode();
  m_gains = new RefCounted<AudioGainNode>[4];
  m_plain = new PlainReverbNode*[4];
  m_allPass = new AllpassNode*[2];

  
  m_gains[0] = context->createGainNode(1);
  m_gains[1] = context->createGainNode(0.9);
  m_gains[2] = context->createGainNode(0.8);
  m_gains[3] = context->createGainNode(0.7);

  float samplerate = context->getSampleRate();
  m_plain[0] = new PlainReverbNode(context,29/samplerate,0.75);
  m_plain[1] = new PlainReverbNode(context,37/samplerate,0.75);
  m_plain[2] = new PlainReverbNode(context,44/samplerate,0.75);
  m_plain[3] = new PlainReverbNode(context,50/samplerate,0.75);

  m_allPass[0] = new AllpassNode(context,27/samplerate,0.75);
  m_allPass[1] = new AllpassNode(context,31/samplerate,0.75);
  
  m_input = context->createGainNode();
  m_output = context->createGainNode();
  
  m_input->connect(m_plain[0]);
  m_input->connect(m_plain[1]);
  m_input->connect(m_plain[2]);
  m_input->connect(m_plain[3]);

  m_plain[0]->connect(m_gains[0].get());
  m_plain[1]->connect(m_gains[1].get());
  m_plain[2]->connect(m_gains[2].get());
  m_plain[3]->connect(m_gains[3].get());

  m_gains[0]->connect(m_sum.get());
  m_gains[1]->connect(m_sum.get());
  m_gains[2]->connect(m_sum.get());
  m_gains[3]->connect(m_sum.get());

  m_sum->connect(m_allPass[0]);
  m_allPass[0]->connect(m_allPass[1]);
  m_allPass[1]->connect(m_output.get());
  
  addOutput(1);
}

dinahmoe::audioengine::ReverbNode::~ReverbNode(){}

void dinahmoe::audioengine::ReverbNode::processInternal(int numSamples, int outputRequesting){

}

