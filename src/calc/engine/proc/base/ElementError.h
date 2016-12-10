////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - ERROR
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_ERROR_H_
#define _ECKERT_ERROR_H_

#include "Element.h"
#include <string>

namespace engine {

class Error : public Element {
	public:
		virtual unsigned int getType() const {
			return ERROR;
		}
	private:
		std::string _str;
	public:
		Error() = delete;
		Error(const std::string &str);
		virtual SpElement clone() const;
		std::string get() const {
			return _str;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_ERROR_H_
