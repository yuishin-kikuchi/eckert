////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY16
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_BINARY16_H_
#define _ECKERT_BINARY16_H_

#include "Element.h"

namespace engine {

class Binary16 : public Element {
	public:
		virtual unsigned int getType() const {
			return BINARY16;
		}
	private:
		uint16_t _data;
	public:
		Binary16() = delete;
		Binary16(const uint16_t &num);
		virtual SpElement clone() const;
		uint16_t get() const {
			return _data;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_BINARY16_H_
