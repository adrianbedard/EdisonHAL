/** @brief Basic development program for testing mraa library
 *
 */

#ifndef HARDWARE_ENTRY_CPP
#define HARDWARE_ENTRY_CPP

#include "EdisonHAL/EdisonHal.h"

using namespace edison;

#ifndef MAIN
#define MAIN

int main(int argc,char** argv)
{
    //Primary set up
	srand(time(NULL));
    os::setLocalPath(argc,argv);
	
	//Log bind
    os::osout_ptr = os::logger.castNewTargetStream("osMechanics",false);
    os::oserr_ptr = os::logger.castNewTargetStream("osMechanics Error",true);

	edout_ptr = os::logger.castNewTargetStream("Edison",false);
    ederr_ptr = os::logger.castNewTargetStream("Edison Error",true);
	
	//No edison case
#ifndef EDISON
	ederr<<"Not running this program on an Edison"<<std::endl;
	ederr<<"Exiting pre-maturely"<<std::endl;

	//For testing sanity
	#ifdef _WIN32
	#if _DEBUG
	system("pause");
	#endif
	#endif

	//Edison case
#else
	edout<<"Edison hardware testing..."<<std::endl;

	mraa_aio_context adc_a0;
    //uint16_t adc_value = 0;
    float adc_value_float = 0.0;
    
    adc_a0 = mraa_aio_init(0);
    if (adc_a0 == NULL) {
        return 1;
    }
	//hello();
	//blink();
	//sweep();
	//read();
	motorController demoLeft;
	demoLeft.initializeController(IN1, IN2, ENA);

	joyStick demoStick;
	demoStick.initalizeJoyStick(0, 1);

	float value = 0.0f;
	int i = 0;

    while (i < 50000) {
        //value = value + 0.01f;
        

        //adc_value = mraa_aio_read(adc_a0);
        adc_value_float = mraa_aio_read_float(adc_a0);

        //demoLeft.setMotor((adc_value_float - 0.5f) * 2);
        value = adc_value_float;
        demoLeft.setMotor((value - 0.5f) * 2);
        //fprintf(stdout, "ADC A0 read %X - %d\n", adc_value, adc_value);
        //fprintf(stdout, "ADC A0 read float - %.5f\n", adc_value_float);

        //fprintf(stdout, "%f\n", adc_value_float);

        fprintf(stdout, "%f   %f\n", demoStick.getX(), 1.0f - demoStick.getY());

        usleep(50000);
        ++i;
        if (value >= 1.0f) {
            value = 0.0f;
            //++i;
        }
    demoLeft.stopMotor();
        //float output = mraa_pwm_read(pwm);
    //demoLeft.close();
    }
#endif
	
	return 1;
}

#endif

#endif
