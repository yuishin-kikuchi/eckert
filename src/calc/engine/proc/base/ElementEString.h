////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - ESTRING
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_ESTRING_H_
#define _ECKERT_ESTRING_H_

#include "Element.h"

namespace engine {

class EString : public Element {
	public:
		virtual unsigned int getType() const {
			return ESTRING;
		}
	private:
		std::string _str;
	public:
		EString() = delete;
		EString(const std::string &str);
		virtual SpElement clone() const;
		std::string get() const {
			return _str;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_ESTRING_H_
