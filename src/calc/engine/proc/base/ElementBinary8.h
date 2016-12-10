////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY8
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_BINARY8_H_
#define _ECKERT_BINARY8_H_

#include "Element.h"
#include <stdint.h>

namespace engine {
	
class Binary8 : public Element {
	public:
		virtual unsigned int getType() const {
			return BINARY8;
		}
	private:
		uint8_t _data;
	public:
		Binary8() = delete;
		Binary8(const uint8_t &num);
		virtual SpElement clone() const;
		uint8_t get() const {
			return _data;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_BINARY8_H_
