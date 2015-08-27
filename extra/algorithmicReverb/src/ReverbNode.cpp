//
//  ReverbNode.cpp
//
//  Created by Thoren Horstmann on 26.08.15.
//
//
/*
       -> plain(g_0,d_0) -> gain(g_4) -|
       |                               |
 input -> plain(g_1,d_1) -> gain(g_5) ---> sum -> allpass(g__9,d_5) -> allpass(g_10,d_6) -> output
       |                               |
       -> plain(g_2,d_2) -> gain(g_6) --
       |                               |
       -> plain(g_3,d_3) -> gain(g_7) --
 */
#include "ReverbNode.h"
#include "AudioBufferSourceNode.hpp"
#include "AudioNodeInput.hpp"


ReverbNode::ReverbNode(AudioContext* context){
  //initial values for the plain and allpass reverbs
  //tune the reverb here
  static const float initialValuesPlain[3][NR_PLAIN] {
    {0.1,0.2,0.3,0.4},  //init m_gains
    {0.01,0.02,0.03,0.04}, //init m_plain delay
    {0.5,0.5,0.5,0.5} //init m_plain gain
  };
  static const float initialValuesAllpass[2][NR_ALLPASS] {
    {0.05,0.05}, //init m_allpass delay
    {0.4,0.4} //init m_allpass gain
  };
  
  //create the nodes
  m_input = context->createGainNode();
  m_output = context->createGainNode();
  m_sum = context->createGainNode();
  
  for(int i = 0; i < NR_PLAIN;++i){
    m_gains[i] = context->createGainNode(initialValuesPlain[0][i]);
    m_plain[i] = new PlainReverbNode(context,initialValuesPlain[1][i],initialValuesPlain[2][i]);
    //connect the four plainreverbs
    m_input->connect(m_plain[i]->m_input.get());
    m_plain[i]->m_output.get()->connect(m_gains[i].get());
    m_gains[i]->connect(m_sum.get());
  }
  
  for (int i = 0; i < NR_ALLPASS; ++i) {
    m_allPass[i] = new AllpassNode(context,initialValuesAllpass[0][i],initialValuesAllpass[1][i]);
  }
  //connect the nodes
  m_sum->connect(m_allPass[0]->m_input.get());
  m_allPass[0]->m_output.get()->connect(m_allPass[1]->m_input.get());
  m_allPass[1]->m_output.get()->connect(m_output.get());
}

ReverbNode::~ReverbNode(){}

