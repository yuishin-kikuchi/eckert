#ifndef _OVERFLOW_EXCEPTION_H_
#define _OVERFLOW_EXCEPTION_H_

#include <exception>

////==--------------------------------------------------------------------====//
// OVERFLOW EXCEPTION
//====--------------------------------------------------------------------==////

class OverflowException : public std::exception {
	private:
		const char *_str;
	public:
		OverflowException() {}
		OverflowException(const char *str) : _str(str) {}
		OverflowException(const OverflowException &obj) : _str(obj._str) {}
		virtual const char* what() const noexcept {
			return _str;
		}
};

#endif // _OVERFLOW_EXCEPTION_H_
