#ifndef MOTOR_CONTROLLER_CPP
#define MOTOR_CONTROLLER_CPP

#include "motorController.h"
#include "EdisonHal.h"

using namespace edison;

int running = 0;
static int iopin;

void sig_handler(int signo)
{
#ifdef EDISON
	if (signo == SIGINT) {
		printf("closing IO%d nicely\n", iopin);
		running = -1;
	}
#endif
}

int blink()
{
#ifdef EDISON
	mraa_result_t r = MRAA_SUCCESS;
	iopin = IN1;
	
	
	mraa_init();
	fprintf(stdout, "MRAA Version: %s\nStarting Blinking on IO%d\n", mraa_get_version(), iopin);
	
	mraa_gpio_context gpio;
	gpio = mraa_gpio_init(iopin);
	if (gpio == NULL) {
		fprintf(stderr, "Are you sure that pin%d you requested is valid on your platform?", iopin);
		exit(1);
	}
	printf("Initialised pin%d\n", iopin);
	
		// set direction to OUT
	r = mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
	if (r != MRAA_SUCCESS) {
		mraa_result_print(r);
	}
	
	signal(SIGINT, sig_handler);
	
	while (running < 5) {
		r = mraa_gpio_write(gpio, 0);
		if (r != MRAA_SUCCESS) {
			mraa_result_print(r);
		} else {
			printf("off\n");
		}
		
		sleep(1);
		
		r = mraa_gpio_write(gpio, 1);
		if (r != MRAA_SUCCESS) {
			mraa_result_print(r);
		} else {
			printf("on\n");
		}
		
		sleep(1);
		
		running++;
	}
	
	r = mraa_gpio_close(gpio);
	if (r != MRAA_SUCCESS) {
		mraa_result_print(r);
	}
	
	return r;
#else
	return 1;
#endif
}

int sweep()
{
#ifdef EDISON
	mraa_init();
		//! [Interesting]
	mraa_pwm_context pwm;
	pwm = mraa_pwm_init(ENA);
	if (pwm == NULL) {
		return 1;
	}
	mraa_pwm_period_us(pwm, 200);
	mraa_pwm_enable(pwm, 1);
	
	float value = 0.0f;
	
	while (1) {
		value = value + 0.01f;
		mraa_pwm_write(pwm, value);
		usleep(5000);
		if (value >= 1.0f) {
			value = 0.0f;
		}
		float output = mraa_pwm_read(pwm);
	}
#endif
	return 0;
}

int read()
{
		#ifdef EDISON
	mraa_aio_context adc_a0;
	uint16_t adc_value = 0;
	float adc_value_float = 0.0;
	adc_a0 = mraa_aio_init(0);
	if (adc_a0 == NULL) {
		return 1;
	}
	for (;;) {
		adc_value = mraa_aio_read(adc_a0);
		adc_value_float = mraa_aio_read_float(adc_a0);
		fprintf(stdout, "ADC A0 read %X - %d\n", adc_value, adc_value);
		fprintf(stdout, "ADC A0 read float - %.5f\n", adc_value_float);
	}
	mraa_aio_close(adc_a0);
	return MRAA_SUCCESS;
#else
	return 1;
#endif
}


motorController::motorController()
{
	#ifdef EDISON
	pin1 = -1;
	pin2 = -1;
	enable = -1;
#endif
	_power=0;
}

int motorController::initializeController(int PIN1, int PIN2, int ENABLE)
{
	#ifdef EDISON
	pin1 = PIN1;
	pin2 = PIN2;
	enable = ENABLE;
	
	mraa_result_t r = MRAA_SUCCESS;
	
	
	mraa_init();
		//fprintf(stdout, "MRAA Version: %s\nStarting Blinking on IO%d\n", mraa_get_version(), iopin);
	
	
	
	gpioPin1 = mraa_gpio_init(pin1);
	if (gpioPin1 == NULL) {
		fprintf(stderr, "Are you sure that pin%d you requested is valid on your platform?", pin1);
		exit(1);
	}
	printf("Initialised pin%d\n", pin1);
	
	gpioPin2 = mraa_gpio_init(pin2);
	if (gpioPin2 == NULL) {
		fprintf(stderr, "Are you sure that pin%d you requested is valid on your platform?", pin2);
		exit(1);
	}
	printf("Initialised pin%d\n", pin2);
	
	
		// set direction to OUT
	r = mraa_gpio_dir(gpioPin1, MRAA_GPIO_OUT);
	if (r != MRAA_SUCCESS) {
		mraa_result_print(r);
	}
	
	r = mraa_gpio_dir(gpioPin2, MRAA_GPIO_OUT);
	if (r != MRAA_SUCCESS) {
		mraa_result_print(r);
	}
	
	signal(SIGINT, sig_handler);
	
	
	pwmEnable = mraa_pwm_init(enable);
	if (pwmEnable == NULL) {
		return 1;
	}
	mraa_pwm_period_us(pwmEnable, 200);
	mraa_pwm_enable(pwmEnable, 1);
	
		//mraa_aio_context adc_a0;
	
	return 0;
#else
	return 1;
#endif
	
}


int motorController::close()
{
	_power=0;
	#ifdef EDISON
	mraa_result_t r = MRAA_SUCCESS;
	
	r = mraa_gpio_close(gpioPin1);
	if (r != MRAA_SUCCESS) {
		mraa_result_print(r);
	}
	
	r = mraa_gpio_close(gpioPin2);
	if (r != MRAA_SUCCESS) {
		mraa_result_print(r);
	}
	
	return r;
#else
	return 1;
#endif
}

void motorController::setMotor(float powerLevel)
{
	if(powerLevel>1) powerLevel=1;
	else if(powerLevel<-1) powerLevel=-1;

	_power=powerLevel;
	#ifdef EDISON
	mraa_result_t r = MRAA_SUCCESS;
	if(powerLevel > 0)
		{
		r = mraa_gpio_write(gpioPin1, 0);
		r = mraa_gpio_write(gpioPin2, 1);
		mraa_pwm_write(pwmEnable, powerLevel);
		
		}
	else
		{
		r = mraa_gpio_write(gpioPin1, 1);
		r = mraa_gpio_write(gpioPin2, 0);
		mraa_pwm_write(pwmEnable, -1.0f * powerLevel);
		}
	return;
#endif
}

void motorController::stopMotor()
{
	#ifdef EDISON
	mraa_result_t r = MRAA_SUCCESS;
	r = mraa_gpio_write(gpioPin1, 1);
	r = mraa_gpio_write(gpioPin2, 1);
	mraa_pwm_write(pwmEnable, 0);
	
	return;
	#endif
}

joyStick::joyStick()
{
	#ifdef EDISON
	xPin = -1;
	yPin = -1;
	#endif
}

int joyStick::initalizeJoyStick(int XPIN, int YPIN)
{
	#ifdef EDISON
	xPin = XPIN;
	yPin = YPIN;
	
	mraa_result_t r = MRAA_SUCCESS;
	
	mraa_init();
	
	xAIO = mraa_aio_init(xPin);
	yAIO = mraa_aio_init(yPin);
	
	if (xAIO == NULL) {
		return 1;
	}
	
	if (yAIO == NULL) {
		return 1;
	}
#else
	return 0;
	#endif
	
	
}

float joyStick::getX()
{
	#ifdef EDISON
	return mraa_aio_read_float(xAIO);
#else
	return 0.5f;
	#endif
	
}

float joyStick::getY()
{
	#ifdef EDISON
	return mraa_aio_read_float(yAIO);
#else
	return 0.5f;
	#endif
}


robot::robot()
{
	#ifdef EDISON
	
	L1 = 7;
	L2 = 5;
	LE = 6;
	
	R1 = 4;
	R2 = 2;
	RE = 3;
	
	LeftMotor.initializeController(L1, L2, LE);
	RightMotor.initializeController(R1, R2, RE);
	#endif
}

void robot::demoForward(float factor) {
	#ifdef EDISON
	LeftMotor.setMotor(factor * 2);
	RightMotor.setMotor(factor * 2);
	#endif
}

void robot::demoBackward(float factor) {
	#ifdef EDISON
	LeftMotor.setMotor(factor * -2);
	RightMotor.setMotor(factor * -2);
	#endif
}

void robot::demoLeft(float factor) {
	#ifdef EDISON
	LeftMotor.setMotor(factor * -2);
	RightMotor.setMotor(factor * 2);
	#endif
}

void robot::demoRight(float factor) {
	#ifdef EDISON
	LeftMotor.setMotor(factor * 2);
	RightMotor.setMotor(factor * -2);
	#endif
}

void robot::demoDrive(float forwardFactor, float rightFactor) {
	#ifdef EDISON
	float functionalLeft = ((forwardFactor + rightFactor) - 1.0f) * 2;
	float functionalRight = ((forwardFactor - rightFactor)) * 2;
	
		//fprintf(stdout, "%f       %f\n", functionalLeft, functionalRight);
	
	LeftMotor.setMotor(functionalLeft);
	RightMotor.setMotor(functionalRight);
	#endif
}


#endif

