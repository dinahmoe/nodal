//
//  AllpassNode.cpp
//  Nodal
//
//  Created by Thoren Horstmann on 26.08.15.
//
//

#include "AllpassNode.h"
#include "AudioBufferSourceNode.hpp"
#include "AudioNodeInput.hpp"


dinahmoe::audioengine::AllpassNode::AllpassNode(AudioContext* context,float delay,float gain) : AudioNode(context){
  addInput("Audio Input", TYPE_AUDIO);
  addInput("Delay control", TYPE_HYBRID);
  m_inputs[1]->setInitialValue(delay);
  
  addInput("Gain control", TYPE_HYBRID);
  m_inputs[2]->setInitialValue(gain);
  
  m_input =context->createGainNode();
  m_output =context->createGainNode();
  
  
  m_sums = new RefCounted<SummingNode>[2];
  m_sums[0] = context->createSummingNode();
  m_sums[1] = context->createSummingNode();

  m_gains = new RefCounted<AudioGainNode>[2];
  m_gains[0] = context->createGainNode(gain);
  m_gains[1] = context->createGainNode(-gain);

  m_delay = context->createDelayNode(delay);
  
  m_input->connect(m_sums[0].get());
  m_sums[0]->connect(m_delay.get());
  m_sums[0]->connect(m_gains[1].get());
  m_delay->connect(m_gains[0].get());
  m_delay->connect(m_sums[1].get());
  m_gains[1]->connect(m_sums[0].get());
  m_gains[0]->connect(m_sums[1].get());
  m_sums[1]->connect(m_output.get());
  
  addOutput(1);
}

dinahmoe::audioengine::AllpassNode::~AllpassNode(){}

void dinahmoe::audioengine::AllpassNode::processInternal(int numSamples, int outputRequesting){
  //m_sums[0]->m_inputs = m_inputs;
  //m_outputs = m_sums[1]->m_outputs;
}