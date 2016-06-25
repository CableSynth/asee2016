#ifndef RINGS_H
#define RINGS_H
#include <Arduino.h>
#include <Servo.h>

namespace rings {

	// handles moving arm and dropping rings
    void dropRings();

	// starts a ring drop  	
  	void dropRing();

  	// stops ring motor after one revolution
  	void stopRing();

}

#endif
