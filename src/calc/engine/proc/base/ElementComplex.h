////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - COMPLEX
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_COMPLEX_H_
#define _ECKERT_COMPLEX_H_

#include "Element.h"

namespace engine {

class Complex : public Element {
	public:
		virtual unsigned int getType() const {
			return COMPLEX;
		}
	private:
		SpElement _re;
		SpElement _im;
		bool _error;
	public:
		Complex() = delete;
		Complex(const SpElement &re, const SpElement &im);
		virtual SpElement clone() const;
		bool hasError() const {
			return _error;
		}
		SpElement getRe() const {
			return _re;
		}
		SpElement getIm() const {
			return _im;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_COMPLEX_H_
