#include "ElementBinary32.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY32 / Constructor
// [ description ]
// Constructor using uint32_t.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Binary32::Binary32(const uint32_t &num) {
	_data = num;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY32 / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Binary32::clone() const {
	return SpElement(new Binary32(_data));
}

} // namespace engine
