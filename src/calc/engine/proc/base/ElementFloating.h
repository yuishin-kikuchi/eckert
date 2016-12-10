////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - FLOATING
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_FLOATING_H_
#define _ECKERT_FLOATING_H_

#include "Element.h"

namespace engine {

class Floating : public Element {
	public:
		virtual unsigned int getType() const {
			return FLOATING;
		}
	private:
		floating_t _data;
	public:
		Floating() = delete;
		Floating(const floating_t &num);
		virtual SpElement clone() const;
		virtual bool hasError() const;
		floating_t get() const {
			return _data;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_FLOATING_H_
