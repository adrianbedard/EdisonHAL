/**
 */

#ifndef HARDWARE_ENTRY_CPP
#define HARDWARE_ENTRY_CPP

#include "EdisonHal.h"

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
	
	return 1;
}

#endif

#endif
