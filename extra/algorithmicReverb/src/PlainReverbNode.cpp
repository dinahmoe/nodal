//
//  PlainReverbNode.cpp
//  Nodal
//
//  Created by Thoren Horstmann on 26.08.15.
//
//

#include "PlainReverbNode.h"
#include "AudioBufferSourceNode.hpp"
#include "AudioNodeInput.hpp"


PlainReverbNode::PlainReverbNode(AudioContext* context,float delay,float gain){

  m_sum = context->createSummingNode();
  m_gain = context->createGainNode(gain);
  m_delay = context->createDelayNode(delay);
  
  m_input = context->createGainNode();
  m_output = context->createGainNode();

  m_input->connect(m_sum.get());
  m_sum->connect(m_delay.get());
  m_delay->connect(m_gain.get());
  m_gain->connect(m_sum.get());
  m_sum->connect(m_output.get());
}

PlainReverbNode::~PlainReverbNode(){}

