////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - UNSIGNED INTEGER
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_UINTEGER_H_
#define _ECKERT_UINTEGER_H_

#include "Element.h"

namespace engine {

class UInteger : public Element {
	public:
		virtual unsigned int getType() const {
			return UINTEGER;
		}
	private:
		uinteger_t _data;
	public:
		UInteger() = delete;
		UInteger(const uinteger_t &num);
		virtual SpElement clone() const;
		uinteger_t get() const {
			return _data;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_UINTEGER_H_
