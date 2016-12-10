#include "ElementInteger.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - INTEGER / Constructor
// [ description ]
// Constructor using integer_t.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Integer::Integer(const integer_t &num) {
	_data = num;
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - INTEGER / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Integer::clone() const {
	return SpElement(new Integer(_data));
}

} // namespace engine
