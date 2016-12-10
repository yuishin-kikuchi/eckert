////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - EINFINITY
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_EINFINITY_H_
#define _ECKERT_EINFINITY_H_

#include "Element.h"

namespace engine {

class EInfinity : public Element {
	public:
		virtual unsigned int getType() const {
			return EINFINITY;
		}
	private:
		int _sign;
	public:
		EInfinity() = delete;
		EInfinity(const int &sign);
		virtual SpElement clone() const;
		int get() const {
			return _sign;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_EINFINITY_H_
