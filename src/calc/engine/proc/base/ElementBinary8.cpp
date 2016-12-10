#include "ElementBinary8.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY8 / Constructor
// [ description ]
// Constructor using uint8_t.
// [ Update ]
// Nov 13, 208
//====--------------------------------------------------------------------==////
Binary8::Binary8(const uint8_t &num) {
	_data = num;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY8 / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 208
//====--------------------------------------------------------------------==////
SpElement Binary8::clone() const {
	return SpElement(new Binary8(_data));
}

} // namespace engine
