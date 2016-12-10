#include "ElementRational.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - RATIONAL / Constructor using 2 integer_t
// [ description ]
// Constructor using 2 integer_t.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Rational::Rational(const integer_t &num, const integer_t &den)
 : _data(num, den)
{
	_data.simplify();
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - RATIONAL / Constructor using rational_t
// [ description ]
// Constructor using rational_t.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Rational::Rational(const rational_t &num)
 : _data(num)
{
	_data.simplify();
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - RATIONAL / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Rational::clone() const {
	return SpElement(new Rational(_data));
}

} // namespace engine
