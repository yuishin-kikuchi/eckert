////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - RATIONAL
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_RATIONAL_H_
#define _ECKERT_RATIONAL_H_

#include "Element.h"

namespace engine {

class Rational : public Element {
	public:
		virtual unsigned int getType() const {
			return RATIONAL;
		}
	private:
		rational_t _data;
	public:
		Rational() = delete;
		Rational(const rational_t &num);
		Rational(const integer_t &num, const integer_t &den);
		virtual SpElement clone() const;
		virtual bool hasError() const {
			return (0 == _data.getDen());
		}
		rational_t get() const {
			return _data;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_RATIONAL_H_
