#ifndef _SAFETY_INTEGER_CALCULATOR_DET_H_
#define _SAFETY_INTEGER_CALCULATOR_DET_H_

#include "SafetyIntegerCalculator.h"
#include "OverflowException.h"
#include <cmath>
#include <limits>

////==--------------------------------------------------------------------====//
// CHECK ADD OVERFROW
//====--------------------------------------------------------------------==////
template <typename T>
bool SafetyIntegerCalculator::checkAdd(const T &lhs, const T &rhs) {
	const T IMAX = std::numeric_limits<T>::max();
	const T IMIN = std::numeric_limits<T>::min();
	if (((lhs > 0) && (rhs > 0) && (lhs > IMAX - rhs)) ||
	    ((lhs < 0) && (rhs < 0) && (lhs < IMIN - rhs))) {
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// CHECK SUB OVERFROW
//====--------------------------------------------------------------------==////
template<typename T>
bool SafetyIntegerCalculator::checkSub(const T &lhs, const T &rhs) {
	const T IMAX = std::numeric_limits<T>::max();
	const T IMIN = std::numeric_limits<T>::min();
	if (((lhs > 0) && (rhs < 0) && (lhs > IMAX + rhs)) ||
	    ((lhs < 0) && (rhs > 0) && (lhs < IMIN + rhs))) {
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// CHECK MUL OVERFROW
//====--------------------------------------------------------------------==////
template<typename T>
bool SafetyIntegerCalculator::checkMul(const T &lhs, const T &rhs) {
	const T IMAX = std::numeric_limits<T>::max();
	const T IMIN = std::numeric_limits<T>::min();
	if (lhs > 0) {
		if (rhs > 0) {
			if (lhs > (IMAX / rhs)) {
				return true;
			}
		}
		else {
			if (rhs < (IMIN / lhs)) {
				return true;
			}
		}
	}
	else {
		if (rhs > 0) {
			if (lhs < (IMIN / rhs)) {
				return true;
			}
		}
		else {
			if ((lhs != 0) && (rhs < (IMAX / lhs))) {
				return true;
			}
		}
	}
	return false;
}

////==--------------------------------------------------------------------====//
// CHECK DIV OVERFROW
//====--------------------------------------------------------------------==////
template <typename T>
bool SafetyIntegerCalculator::checkDiv(const T &lhs, const T &rhs) {
	const T IMIN = std::numeric_limits<T>::min();
	if ((rhs == 0) || ((lhs == IMIN) && (rhs == -1))) {
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// CAN NEGATE
//====--------------------------------------------------------------------==////
template<typename T>
bool SafetyIntegerCalculator::checkNeg(const T &rhs) {
	const T IMIN = std::numeric_limits<T>::min();
	return (rhs == IMIN);
}

////==--------------------------------------------------------------------====//
// CHECK RANGE
// --------------------------------------------------------------------------
// SrcType:double -> T:int64_t
//====--------------------------------------------------------------------==////
template<typename T, typename SrcType>
bool SafetyIntegerCalculator::checkRange(const SrcType &rhs) {
	T test = static_cast<T>(static_cast<SrcType>(rhs));
	if (std::abs(rhs - test) > 1.0) {
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// SAFE NEGATE
//====--------------------------------------------------------------------==////
template<typename T>
T SafetyIntegerCalculator::neg(const T &rhs) {
	if (checkNeg(rhs)) {
		throw OverflowException("Overflow: neg");
	}
	else {
		return -rhs;
	}
}

////==--------------------------------------------------------------------====//
// SAFE ADD
//====--------------------------------------------------------------------==////
template<typename T>
T SafetyIntegerCalculator::add(const T &lhs, const T &rhs) {
	if (checkAdd(lhs, rhs)) {
		throw OverflowException("Overflow: add");
	}
	else {
		return (lhs + rhs);
	}
}

////==--------------------------------------------------------------------====//
// SAFE SUB
//====--------------------------------------------------------------------==////
template<typename T>
T SafetyIntegerCalculator::sub(const T &lhs, const T &rhs) {
	if (checkSub(lhs, rhs)) {
		throw OverflowException("Overflow: sub");
	}
	else {
		return (lhs - rhs);
	}
}

////==--------------------------------------------------------------------====//
// SAFE MUL
//====--------------------------------------------------------------------==////
template<typename T>
T SafetyIntegerCalculator::mul(const T &lhs, const T &rhs) {
	if (checkMul(lhs, rhs)) {
		throw OverflowException("Overflow: mul");
	}
	else {
		return (lhs * rhs);
	}
}

////==--------------------------------------------------------------------====//
// SAFE DIV
//====--------------------------------------------------------------------==////
template<typename T>
T SafetyIntegerCalculator::div(const T &lhs, const T &rhs) {
	if (checkDiv(lhs, rhs)) {
		throw OverflowException("Overflow: div");
	}
	else {
		return (lhs / rhs);
	}
}

////==--------------------------------------------------------------------====//
// SAFE MOD
//====--------------------------------------------------------------------==////
template<typename T>
T SafetyIntegerCalculator::mod(const T &lhs, const T &rhs) {
	if (checkDiv(lhs, rhs)) {
		return 0;
	}
	else {
		return (lhs % rhs);
	}
}

////==--------------------------------------------------------------------====//
// SAFE GREATEST COMMON DIVISOR
//====--------------------------------------------------------------------==////
template<typename T>
T SafetyIntegerCalculator::gcd(const T &lhs, const T &rhs) {
	T m = lhs;
	T n = rhs;
	T temp;
	// if m or n is zero, error
	if ((0 == m) || (0 == n)) {
		throw OverflowException("Overflow: gcd");
	}
	// if m < 0, negate it
	if (m < 0) {
		m = neg(m);
	}
	// if n < 0, negate it
	if (n < 0) {
		n = neg(n);
	}
	if (n < m) {
		temp = m;
		m = n;
		n = temp;
	}
	while (n) {
		temp = n;
		n = m % n;
		m = temp;
	}
	return m;
}

////==--------------------------------------------------------------------====//
// SAFE LEAST COMMON MULTIPLE
//====--------------------------------------------------------------------==////
template<typename T>
T SafetyIntegerCalculator::lcm(const T &lhs, const T &rhs) {
	T m = lhs;
	T n = rhs;
	// if m or n is zero, error
	if ((0 == m) || (0 == n)) {
		throw OverflowException("Overflow: lcm");
	}
	// if m < 0, negate it
	if (m < 0) {
		m = neg(m);
	}
	// if n < 0, negate it
	if (n < 0) {
		m = neg(n);
	}
	return mul(m / gcd<T>(m, n), n);
}

#endif // _SAFETY_INTEGER_CALCULATOR_DET_H_
