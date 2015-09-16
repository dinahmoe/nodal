#include "ofApp.h"

#define BUFFER_SIZE 512
#define SAMPLING_RATE 44100


//--------------------------------------------------------------
void ofApp::setup(){
  m_tempOutputBuffer = new float*[2];
  for (int ch = 0; ch < 2; ++ch) {
    m_tempOutputBuffer[ch] = new float[BUFFER_SIZE];
  }
  // create and start an audio context. it won't be pulled until soundstream is started
  mAudioContext = new AudioContext(SAMPLING_RATE, 2, BUFFER_SIZE, true);
  mAudioContext->start();
  
  // start audio
  ofSoundStreamSetup(2, 0, this, SAMPLING_RATE, BUFFER_SIZE, 4);
  //ofSoundStreamStart();
  
  // create a buffer from file. Note that this throws std::runtime_error
  // in case of errors
  mSynth.mNoteBuffer = mAudioContext->createInMemoryBuffer(ofToDataPath("sounds/SynthNote.aif"));
  mSynth.init(mAudioContext);
  mSynth.panner->setMaxDistance(1000);
  m_Box.set(50);
  m_BoxX = 0;
  m_BoxY = 0;
  m_BoxZ = 0;
  m_moveLeft = true;
  m_moveUp = true;
  m_moveBack = true;
  i = 0;
  //m_outerBox.set(500);
  m_outerBox.set(1000, 500, 500);
  m_outerBox.setPosition(m_BoxX, m_BoxY, m_BoxZ);
  m_listenerPosition.setPosition(m_BoxX, m_BoxY, m_BoxZ);
  ofVec3f op = m_outerBox.getPosition();
  ofVec3f size = m_outerBox.getSize();
  m_BoxX = 100;
}

//--------------------------------------------------------------
void ofApp::update(){
  
  if(m_BoxX <= -500){
    m_moveLeft = false;
  }
  if(m_BoxX >= 500){
    m_moveLeft = true;
  }
  if(m_BoxY <= -250){
    m_moveUp = false;
  }
  if(m_BoxY >= 250){
    m_moveUp = true;
  }
  if(m_BoxZ <= -250){
    m_moveBack = true;
  }
  if(m_BoxZ >= 250){
    m_moveBack = false;
  }
  
  if(m_moveLeft){
    --m_BoxX;
  }else{
    ++m_BoxX;
  }
  if(m_moveUp){
    --m_BoxY;
  }else{
    ++m_BoxY;
  }
  if(m_moveBack){
    ++m_BoxZ;
  }else{
    --m_BoxZ;
  }
  ofVec3f camPos = m_listenerPosition.getPosition();
  ofVec3f camof = m_listenerPosition.getLookAtDir();
  ofVec3f camUp = m_listenerPosition.getUpDir();
  
  mSynth.setListener(camPos[0],camPos[1],camPos[2], camof[0], camof[1], camof[2] , camUp[0], camUp[1], camUp[2]);
}

//--------------------------------------------------------------
void ofApp::draw(){
  m_listenerPosition.begin();
  
  m_outerBox.drawWireframe();
  m_Box.setPosition(m_BoxX, m_BoxY, m_BoxZ);
  m_Box.draw();

  if(i == 10){
    i = 0;
    mSynth.playNote(mAudioContext,m_BoxX,m_BoxY,m_BoxZ);
  }
  ++i;
  m_listenerPosition.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
  mAudioContext->audioCallback(NULL, 0, m_tempOutputBuffer, nChannels, bufferSize);
  float * outputSample = output;
  for (int i = 0; i < bufferSize; ++i) {
    for (int ch = 0; ch < nChannels; ++ch) {
      *outputSample = m_tempOutputBuffer[ch][i];
      ++outputSample;
    }
  }
}
