

/**
 */

#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "hardwareHeader.h"


#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>


	//#include "mraa.h"

namespace edison
{
#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 8
	
#define ENA 3
#define ENB 6
	
	int blink();
	
	int sweep();
	
	int read();
	
	class motorController {
	private:
		int pin1;
		int pin2;
 	int enable;
		
 	mraa_gpio_context gpioPin1;
		mraa_gpio_context gpioPin2;
		mraa_pwm_context pwmEnable;
		float _power;
	public:
		motorController();
		int initializeController(int PIN1, int PIN2, int ENABLE);
		int close();
		void setMotor(float powerLevel);
		void stopMotor();
		float power() const {return _power;}
	};
	
	class joyStick {
	private:
		int xPin;
		int yPin;
		mraa_aio_context xAIO;
		mraa_aio_context yAIO;
		
	public:
		joyStick();
		int initalizeJoyStick(int XPIN, int YPIN);
		float getX();
		float getY();
	};
	
	class robot {
	private:
		int L1;
		int L2;
		int LE;
		
		int R1;
		int R2;
		int RE;
		
		motorController LeftMotor;
		motorController RightMotor;
		
	public:
		robot();

		os::spinLock robotMutex;
		
		void demoForward(float factor);
		void demoBackward(float factor);
		void demoLeft(float factor);
		void demoRight(float factor);
		
		void demoDrive(float forwardFactor, float rightFactor);

		motorController& rightWheel(){return RightMotor;}
		motorController& leftWheel(){return LeftMotor;}
	};
}

#endif