////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY64
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_BINARY64_H_
#define _ECKERT_BINARY64_H_

#include "Element.h"

namespace engine {

class Binary64 : public Element {
	public:
		virtual unsigned int getType() const {
			return BINARY64;
		}
	private:
		uint64_t _data;
	public:
		Binary64() = delete;
		Binary64(const uint64_t &num);
		virtual SpElement clone() const;
		uint64_t get() const {
			return _data;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_BINARY64_H_
