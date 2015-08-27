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


AllpassNode::AllpassNode(AudioContext* context,float delay,float gain){

  
  m_input =context->createGainNode();
  m_output =context->createGainNode();
  
  m_sums[0] = context->createSummingNode();
  m_sums[1] = context->createSummingNode();

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
}

AllpassNode::~AllpassNode(){}
