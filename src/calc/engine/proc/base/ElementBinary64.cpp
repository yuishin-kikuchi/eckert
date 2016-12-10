#include "ElementBinary64.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY64 / Constructor
// [ description ]
// Constructor using uint64_t.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Binary64::Binary64(const uint64_t &num) {
	_data = num;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY64 / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Binary64::clone() const {
	return SpElement(new Binary64(_data));
}

} // namespace engine
