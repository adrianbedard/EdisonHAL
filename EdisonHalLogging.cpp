/** @brief EdisonHal Logging objects
 *
 */
#ifndef EDISONHAL_CPP
#define EDISONHAL_CPP

#include "EdisonHal.h"

namespace edison
{
	//Log conversion functions
	std::ostream& edout_func() {return *edout_ptr;}
	std::ostream& ederr_func() {return *ederr_ptr;}

	//Global Streams
    os::smart_ptr<std::ostream> edout_ptr(&(std::cout));
    os::smart_ptr<std::ostream> ederr_ptr(&(std::cerr));
}

#endif
