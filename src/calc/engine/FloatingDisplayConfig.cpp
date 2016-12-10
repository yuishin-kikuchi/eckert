#include "FloatingDisplayConfig.h"
#include "proc/base/EckertTypedef.h"
#include <limits>

namespace engine {

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / STATIC MEMBERS
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
const int FloatingDisplayConfig::DEFAULT_STD_DIGITS = 9;
const int FloatingDisplayConfig::DEFAULT_FIX_DIGITS = 9;
const int FloatingDisplayConfig::DEFAULT_SCI_DIGITS = 9;
const int FloatingDisplayConfig::DEFAULT_ENG_DIGITS = 9;

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / CONSTRUCTOR
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
FloatingDisplayConfig::FloatingDisplayConfig() {
	init();
}

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / INITIALIZER
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
void FloatingDisplayConfig::init() {
	_mode = STANDARD;
	_stdDigits = DEFAULT_STD_DIGITS;
	_fixDigits = DEFAULT_FIX_DIGITS;
	_sciDigits = DEFAULT_SCI_DIGITS;
	_engDigits = DEFAULT_ENG_DIGITS;
}

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / GET MIN STANDARD DIGITS
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
int FloatingDisplayConfig::getStdMin() const {
	return 1;
}

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / GET MIN FIX DIGITS
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
int FloatingDisplayConfig::getFixMin() const {
	return 0;
}

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / GET MIN SCIENTIFIC DIGITS
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
int FloatingDisplayConfig::getSciMin() const {
	return 1;
}

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / GET MIN ENGINEERING DIGITS
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
int FloatingDisplayConfig::getEngMin() const {
	return 1;
}

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / GET MAX STANDARD DIGITS
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
int FloatingDisplayConfig::getStdMax() const {
	return std::numeric_limits<floating_t>::digits10;
}

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / GET MAX FIX DIGITS
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
int FloatingDisplayConfig::getFixMax() const {
	return std::numeric_limits<floating_t>::digits10;
}

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / GET MAX SCIENTIFIC DIGITS
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
int FloatingDisplayConfig::getSciMax() const {
	return std::numeric_limits<floating_t>::digits10;
}

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG / GET MAX ENGINEERING DIGITS
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
int FloatingDisplayConfig::getEngMax() const {
	return std::numeric_limits<floating_t>::digits10;
}

} // namespace engine
