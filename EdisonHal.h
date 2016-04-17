/**
 */

#ifndef EDISON_HAL_H
#define EDISON_HAL_H

#include "Datastructures.h"
#include "osMechanics.h"
#include "hardwareHeader.h"

namespace edison
{
	/** @brief Standard out pointer for edison namespace
	 *
	 * This std::ostream is used as standard out
	 * for the edison namespace.  This pointer can be
	 * swapped out to programmatically redirect standard out for
	 * the edison namespace.
	 */
	extern os::smart_ptr<std::ostream> edout_ptr;
	/** @brief Standard error pointer for edison namespace
	 *
	 * This std::ostream is used as standard error
	 * for the edison namespace.  This pointer can be
	 * swapped out to programmatically redirect standard error for
	 * the edison namespace.
	 */
    extern os::smart_ptr<std::ostream> ederr_ptr;
	/** @brief Standard out object for edison namespace
	 *
	 * #define statements allow the user to call this
	 * function with "edison::edout."  Logging is achieved
	 * by using "edison::edout" as one would use "std::cout."
	 */
	std::ostream& edout_func();
	/** @brief Standard error object for edison namespace
	 *
	 * #define statements allow the user to call this
	 * function with "edison::ederr."  Logging is achieved
	 * by using "edison::ederr" as one would use "std::cerr."
	 */
	std::ostream& ederr_func();
};

#ifndef edout
#define edout edout_func()
#endif
#ifndef ederr
#define ederr ederr_func()
#endif

#endif
