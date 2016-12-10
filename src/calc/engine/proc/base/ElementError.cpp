#include "ElementError.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - ERROR / Constructor using std::string
// [ description ]
// Constructor using std::string.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Error::Error(const std::string &str) {
	_str = str;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - ERROR / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Error::clone() const {
	return SpElement(new Error(_str));
}

} // namespace engine
