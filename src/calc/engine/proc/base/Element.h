////==--------------------------------------------------------------------====//
// ECKERT ELEMENT
// [ Update ]
// Nov 18, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_ELEMENT_H_
#define _ECKERT_ELEMENT_H_

#include "EckertTypedef.h"
#include "core/BaseElement.h"

namespace engine {

class Element : public BaseElement {
	public:
		enum : unsigned int {
			// KIND
			SCALAR_TYPE  = 16,  // 0b 0001 0000
			NUMERIC_TYPE = 32,  // 0b 0010 0000
			BINARY_TYPE  = 64,  // 0b 0100 0000
			SET_TYPE     = 128, // 0b 1000 0000
			// TYPE
			ERROR        = 1,
			ESTRING      = 2,
			EINFINITY    = 3,
			UINTEGER     = 4,
			INTEGER      = NUMERIC_TYPE | SCALAR_TYPE | 1,
			FLOATING     = NUMERIC_TYPE | SCALAR_TYPE | 2,
			RATIONAL     = NUMERIC_TYPE | SCALAR_TYPE | 3,
			COMPLEX      = NUMERIC_TYPE | 1,
			BOOLEAN      = BINARY_TYPE  | 1,
			BINARY8      = BINARY_TYPE  | 2,
			BINARY16     = BINARY_TYPE  | 3,
			BINARY32     = BINARY_TYPE  | 4,
			BINARY64     = BINARY_TYPE  | 5,
			ETUPLE       = SET_TYPE     | 1,
			MATRIX       = SET_TYPE     | 2,
		};
	public:
		virtual unsigned int getType() const = 0;
		virtual SpElement clone() const = 0;
		virtual bool isType(const unsigned int &type) const {
			return ((type == this->getType()) ? true : false);
		}
		virtual bool isKindOf(const unsigned int &type) const {
			return ((type & this->getType()) ? true : false);
		}
		virtual bool hasError() const {
			return false;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_ELEMENT_H_
