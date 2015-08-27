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


ReverbNode::ReverbNode(AudioContext* context){

  m_sum = context->createSummingNode();
  m_gains = new RefCounted<AudioGainNode>[4];
  m_plain = new PlainReverbNode*[4];
  m_allPass = new AllpassNode*[2];

  
  m_gains[0] = context->createGainNode(0.9);
  m_gains[1] = context->createGainNode(0.8);
  m_gains[2] = context->createGainNode(0.7);
  m_gains[3] = context->createGainNode(0.6);

  float samplerate = context->getSampleRate();
  m_plain[0] = new PlainReverbNode(context,0.02,0.65);
  m_plain[1] = new PlainReverbNode(context,0.03,0.65);
  m_plain[2] = new PlainReverbNode(context,0.04,0.65);
  m_plain[3] = new PlainReverbNode(context,0.05,0.65);

  m_allPass[0] = new AllpassNode(context,0.02,0.65);
  m_allPass[1] = new AllpassNode(context,0.03,0.65);
  
  m_input = context->createGainNode();
  m_output = context->createGainNode();
  
  m_input->connect(m_plain[0]->m_input.get());
  m_input->connect(m_plain[1]->m_input.get());
  m_input->connect(m_plain[2]->m_input.get());
  m_input->connect(m_plain[3]->m_input.get());

  m_plain[0]->m_output.get()->connect(m_gains[0].get());
  m_plain[1]->m_output.get()->connect(m_gains[1].get());
  m_plain[2]->m_output.get()->connect(m_gains[2].get());
  m_plain[3]->m_output.get()->connect(m_gains[3].get());

  m_gains[0]->connect(m_sum.get());
  m_gains[1]->connect(m_sum.get());
  m_gains[2]->connect(m_sum.get());
  m_gains[3]->connect(m_sum.get());

  m_sum->connect(m_allPass[0]->m_input.get());
  m_allPass[0]->m_output.get()->connect(m_allPass[1]->m_input.get());
  m_allPass[1]->m_output.get()->connect(m_output.get());
  
}

ReverbNode::~ReverbNode(){
  delete [] m_allPass;
  delete [] m_plain;
}

