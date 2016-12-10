#include "ElementComplex.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - COMPLEX / Constructor
// [ description ]
// Constructor using 2 shared pointers.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Complex::Complex(
	const SpElement &re,
	const SpElement &im)
{
	if (!re || !im) {
		// if any null pointers, set error flag
		_error = true;
	}
	else if (re->isKindOf(Element::SCALAR_TYPE) && im->isKindOf(Element::SCALAR_TYPE)) {
		// if the both are scalar, set
		_error = false;
		_re = re;
		_im = im;
	}
	else {
		_error = true;
	}
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - COMPLEX / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Complex::clone() const {
	if (!_error) {
		return SpElement(new Complex(_re->clone(), _im->clone()));
	}
	else {
		// if error, return nullptr
		return SpElement(nullptr);
	}
}

} // namespace engine
