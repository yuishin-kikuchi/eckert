#include "ElementFloating.h"
#include <cmath>

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - FLOATING / Constructor
// [ description ]
// Constructor using floating_t.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Floating::Floating(const floating_t &num) {
	_data = num;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - FLOATING / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Floating::clone() const {
	return SpElement(new Floating(_data));
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - FLOATING / Is error
// [ description ]
// Judge error.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
bool Floating::hasError() const {
	return (std::isinf(_data) || std::isnan(_data));
}

} // namespace engine
