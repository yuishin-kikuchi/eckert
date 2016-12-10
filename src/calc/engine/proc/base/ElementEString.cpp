#include "ElementEString.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - ESTRING / Constructor using std::string
// [ description ]
// Constructor using std::string.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
EString::EString(const std::string &str) {
	_str = str;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - ESTRING / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement EString::clone() const {
	return SpElement(new EString(_str));
}

} // namespace engine
