

/**
*/

#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "hardwareHeader.h"


#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>


#include "mraa.h"

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
public:
	motorController();
	int initializeController(int PIN1, int PIN2, int ENABLE);
	int close();
	void setMotor(float powerLevel);
	void stopMotor();
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
}

#endif