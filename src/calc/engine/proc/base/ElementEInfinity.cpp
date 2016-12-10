#include "ElementEInfinity.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - EINFINITY / Constructor using int
// [ description ]
// Constructor using int.
// [ Update ]
// Jan 25, 2016
//====--------------------------------------------------------------------==////
EInfinity::EInfinity(const int &sign) {
	_sign = sign;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - EINFINITY / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Jan 25, 2016
//====--------------------------------------------------------------------==////
SpElement EInfinity::clone() const {
	return SpElement(new EInfinity(_sign));
}

} // namespace engine
