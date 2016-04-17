#include "motorController.h"
#include "EdisonHal.h"

int running = 0;
static int iopin;

void
sig_handler(int signo)
{
    if (signo == SIGINT) {
        printf("closing IO%d nicely\n", iopin);
        running = -1;
    }
}

int blink()
{
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
}

int sweep()
{
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
    //! [Interesting]
    return 0;
}

int read()
{
    mraa_aio_context adc_a0;
    uint16_t adc_value = 0;
    float adc_value_float = 0.0;

    adc_a0 = mraa_aio_init(0);
    if (adc_a0 == NULL) {
        edison::edout<<"boo\n";
        return 1;
    }

    mraa_init();
    //! [Interesting]
    mraa_pwm_context pwm;
    pwm = mraa_pwm_init(ENA);
    if (pwm == NULL) {
        edison::edout<<"cow\n";
        return 1;
    }
    mraa_pwm_period_us(pwm, 200);
    mraa_pwm_enable(pwm, 1);

    float value = 0.0f;

    while (1 == 1) {
        adc_value = mraa_aio_read(adc_a0);
        adc_value_float = mraa_aio_read_float(adc_a0);
        value = adc_value_float;
        mraa_pwm_write(pwm, value);

        //fprintf(stdout, "ADC A0 read %X - %d\n", adc_value, adc_value);
        //fprintf(stdout, "ADC A0 read float - %.5f\n", adc_value_float);
    }

    mraa_aio_close(adc_a0);

    return MRAA_SUCCESS;
}