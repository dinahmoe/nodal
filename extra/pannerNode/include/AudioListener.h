//
//  AudioListener.h
//  Nodal
//
//  Created by Thoren Horstmann on 04.09.15.
//
//

#ifndef Nodal_AudioListener_h
#define Nodal_AudioListener_h

class AudioListener{
public:
  AudioListener(float dopplerFactor = 1.F, float speedOfSound = 343.3F) :
  m_Position(0,0,0),
  m_OrientationUp(0,1,0),
  m_OrientationFront(0,0,-1),
  m_Velocity(),
  m_dopplerFactor(dopplerFactor),
  m_speedOfSound(speedOfSound){}
  void setPosition(float x, float y, float z){
    m_Position.setXYZ(x,y,z);
  }
  void setOrientation(float x, float y, float z , float xUp, float yUp, float zUp){
    m_OrientationFront.setXYZ(x,y,z);
    m_OrientationUp.setXYZ(xUp,yUp,zUp);
  }
  void setVelocity(float x, float y, float z){
    m_Velocity.setXYZ(x,y,z);
  }
  void setDopplerFactor(float df){
    m_dopplerFactor = df;
  }
  void setSpeedOfSound(float sos){
    m_speedOfSound = sos;
  }
  Vec3<float> m_Position;
  Vec3<float> m_OrientationUp;
  Vec3<float> m_OrientationFront;
  Vec3<float> m_Velocity;

private:
  float m_dopplerFactor;
  float m_speedOfSound;
};

#endif
