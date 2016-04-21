#ifndef HELLO_WORLD_MRAA_CPP
#define HELLO_WORLD_MRAA_CPP

#include "helloWorldMraa.h"

int hello()
{
	#ifdef EDISON
    const char* board_name = mraa_get_platform_name();
    fprintf(stdout, "hello mraa\n Version: %s\n Running on %s\n", mraa_get_version(), board_name);

    mraa_deinit();

    return MRAA_SUCCESS;
	#else
	return 1;
	#endif
}
//! [Interesting]
#endif