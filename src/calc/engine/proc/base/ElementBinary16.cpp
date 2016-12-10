#include "ElementBinary16.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY16 / Constructor
// [ description ]
// Constructor using uint16_t.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Binary16::Binary16(const uint16_t &num) {
	_data = num;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY16 / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Binary16::clone() const {
	return SpElement(new Binary16(_data));
}

} // namespace engine
