////==--------------------------------------------------------------------====//
// ECKERT EXCEPTION
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_EXCEPTION_H_
#define _ECKERT_EXCEPTION_H_

#include <exception>

namespace engine {
	class EckertException : public std::exception {
		public:
			const char *_str;
			const char *_place;
		public:
			EckertException()
			 : _str("Unknown error"), _place("Unknown") {}
			EckertException(const char *str)
			 : _str(str), _place("Unknown") {}
			EckertException(const char *str, const char *place)
			 : _str(str), _place(place) {}
			EckertException(const EckertException &obj)
			: _str(obj._str), _place(obj._place) {}
			virtual const char* what() const throw() {
				return _str;
			}
			const char* where() const throw() {
				return _place;
			}
	};
} // namespace engine

#endif // ifndef _ECKERT_EXCEPTION_H_
