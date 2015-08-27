//
//  ReverbNode.cpp
//
//  Created by Thoren Horstmann on 26.08.15.
//
//

#include "ReverbNode.h"
#include "AudioBufferSourceNode.hpp"
#include "AudioNodeInput.hpp"


ReverbNode::ReverbNode(AudioContext* context){
  static const float initialValuesPlain[3][NR_PLAIN] {
    {0.1,0.2,0.3,0.4},  //init m_gains
    {0.01,0.02,0.03,0.04}, //init m_plain delay
    {0.5,0.5,0.5,0.5} //init m_plain gain
  };
  static const float initialValuesAllpass[2][NR_ALLPASS] {
    {0.05,0.05}, //init m_allpass delay
    {0.4,0.4} //init m_allpass gain
  };
  
  m_input = context->createGainNode();
  m_output = context->createGainNode();
  m_sum = context->createGainNode();
  
  for(int i = 0; i < NR_PLAIN;++i){
    m_gains[i] = context->createGainNode(initialValuesPlain[0][i]);
    m_plain[i] = new PlainReverbNode(context,initialValuesPlain[1][i],initialValuesPlain[2][i]);
    
    m_input->connect(m_plain[i]->m_input.get());
    m_plain[i]->m_output.get()->connect(m_gains[i].get());
    m_gains[i]->connect(m_sum.get());
  }
  
  for (int i = 0; i < NR_ALLPASS; ++i) {
    m_allPass[i] = new AllpassNode(context,initialValuesAllpass[0][i],initialValuesAllpass[1][i]);
    m_filter[i] = context->createBiquadFilterNode(DspBasics::BiquadFilterType::ALLPASS, 1, 3, 1.0F);
  }

  /*m_sum->connect(m_allPass[0]->m_input.get());
  m_allPass[0]->m_output.get()->connect(m_allPass[1]->m_input.get());
  m_allPass[1]->m_output.get()->connect(m_output.get());*/
  m_sum->connect(m_filter[0].get());
  m_filter[0].get()->connect(m_filter[1].get());
  m_filter[1].get()->connect(m_output.get());
}

ReverbNode::~ReverbNode(){}

