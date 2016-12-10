#ifndef _FLOAT_TO_RATIONAL_H_
#define _FLOAT_TO_RATIONAL_H_

////==--------------------------------------------------------------------====//
// APPROXIMATE RATIONAL BY FLOATING NUMBER
//====--------------------------------------------------------------------==////

#include "SafetyRational.h"
#include <vector>
#include <cmath>
#include <limits>

template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> approxRational(const FloatingType &num);
template <typename IntegerType, typename FloatingType>
bool floatToContFraction(std::vector<IntegerType> &vec, const FloatingType &num);

////==--------------------------------------------------------------------====//
// APPROXIMATE RATIONAL BY FLOATING NUMBER
// (Using continuing fraction)
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> approxRational(const FloatingType &num) {
	bool is_minus = false;
	FloatingType temp = num;
	if (num < 0.0) {
		is_minus = true;
		temp = -temp;
	}
	std::vector<IntegerType> vec;
	floatToContFraction(vec, temp);
	SafetyRational<IntegerType, FloatingType> r;
	if (!vec.empty()) {
		r = *(vec.rbegin());
		for (auto it = vec.rbegin() + 1; it != vec.rend(); ++it) {
			try{
				r = *it + r.inv();
			}
			catch (...) {
				r = *it;
			}
		}
		if (is_minus) {
			return -r;
		}
		else {
			return r;
		}
	}
	else {
		return SafetyRational<IntegerType, FloatingType>();
	}
}

////==--------------------------------------------------------------------====//
// FLOATING NUMBER TO CONTINUING FRACTION
// (negative number is fixed to positive)
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
bool floatToContFraction(std::vector<IntegerType> &vec, const FloatingType &num) {
	vec.clear();
	FloatingType temp = std::abs(num);
	for (int cnt = 0; cnt < std::numeric_limits<FloatingType>::digits10; ++cnt) {
		if (temp > std::sqrt(std::numeric_limits<IntegerType>::max())) {
			break;
		}
		IntegerType ipart = (IntegerType)temp;
		vec.push_back(ipart);
		temp -= ipart;
		if (0.0 != temp) {
			temp = 1 / temp;
		}
		else {
			break;
		}
	}
	return vec.empty();
}

#endif // _FLOAT_TO_RATIONAL_H_
