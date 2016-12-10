#include "ElementUInteger.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - UINTEGER / Constructor
// [ description ]
// Constructor using uinteger_t.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
UInteger::UInteger(const uinteger_t &num) {
	_data = num;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - UINTEGER / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement UInteger::clone() const {
	return SpElement(new UInteger(_data));
}

} // namespace engine
