#include "ElementBoolean.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BOOLEAN / Constructor
// [ description ]
// Constructor using bool.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Boolean::Boolean(const bool &flag) {
	_flag = flag;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BOOLEAN / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Boolean::clone() const {
	return SpElement(new Boolean(_flag));
}

} // namespace engine
