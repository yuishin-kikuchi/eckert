#ifndef _SAFETY_INTEGER_CALCULATOR_H_
#define _SAFETY_INTEGER_CALCULATOR_H_

class SafetyIntegerCalculator {
	public:
		template <typename T>
		static bool checkAdd(const T &lhs, const T &rhs);
		template <typename T>
		static bool checkSub(const T &lhs, const T &rhs);
		template <typename T>
		static bool checkMul(const T &lhs, const T &rhs);
		template <typename T>
		static bool checkDiv(const T &lhs, const T &rhs);
		template <typename T>
		static bool checkNeg(const T &rhs);
		template <typename T, typename SrcType>
		static bool checkRange(const SrcType &rhs);
		template <typename T>
		static T neg(const T &rhs);
		template <typename T>
		static T add(const T &lhs, const T &rhs);
		template <typename T>
		static T sub(const T &lhs, const T &rhs);
		template <typename T>
		static T mul(const T &lhs, const T &rhs);
		template <typename T>
		static T div(const T &lhs, const T &rhs);
		template <typename T>
		static T mod(const T &lhs, const T &rhs);
		template <typename T>
		static T gcd(const T &lhs, const T &rhs);
		template <typename T>
		static T lcm(const T &lhs, const T &rhs);
};

#include "SafetyIntegerCalculator_det.h"

#endif // ifndef _SAFETY_INTEGER_CALCULATOR_H_
