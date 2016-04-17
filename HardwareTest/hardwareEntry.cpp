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
	hello();
	//blink();
	//sweep();
	read();
#endif
	
	return 1;
}

#endif

#endif
