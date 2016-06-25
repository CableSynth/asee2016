#ifndef RINGS_H
#define RINGS_H
#include <Arduino.h>
#include <Servo.h>

namespace rings {
  const int RING_DROP_DELAY = 25; // in miliis
  
  
	// handles moving arm and dropping rings
    void dropRings();

	// starts a ring drop  	
  	void dropRing();
  
  // initializes drop sequence
  void initDrop(bool newInit);

  	// stops ring motor after one revolution
  	void stopRing();

}

#endif
