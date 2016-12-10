#ifndef _SAFETY_RATIONAL_H_
#define _SAFETY_RATIONAL_H_

#include <iostream>

template <typename IntegerType, typename FloatingType>
class SafetyRational {
	private:
		IntegerType _num;
		IntegerType _den;
	public:
		SafetyRational();
		SafetyRational(const IntegerType &num, const IntegerType &den = IntegerType(1));
		SafetyRational(const SafetyRational &obj);
		void simplify();
		bool isError() const;
		bool isZero() const;
		bool isInteger() const;
		IntegerType getNum() const;
		IntegerType getDen() const;
		FloatingType getFloating() const;
		void setError();
		void setNum(const IntegerType &num);
		void setDen(const IntegerType &den);
		SafetyRational inv() const;
		SafetyRational& operator = (const SafetyRational &rhs);
		SafetyRational operator + () const;
		SafetyRational operator - () const;
		SafetyRational& operator += (const SafetyRational &rhs);
		SafetyRational& operator -= (const SafetyRational &rhs);
		SafetyRational& operator *= (const SafetyRational &rhs);
		SafetyRational& operator /= (const SafetyRational &rhs);
		SafetyRational& operator += (const IntegerType &rhs);
		SafetyRational& operator -= (const IntegerType &rhs);
		SafetyRational& operator *= (const IntegerType &rhs);
		SafetyRational& operator /= (const IntegerType &rhs);
};

template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator + (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator - (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator * (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator / (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator + (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const IntegerType &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator - (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const IntegerType &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator * (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const IntegerType &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator / (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const IntegerType &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator + (
	const IntegerType &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator - (
	const IntegerType &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator * (
	const IntegerType &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs);
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator / (
	const IntegerType &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs);
template <typename IntegerType, typename FloatingType>
std::ostream& operator << (std::ostream &lhs, const SafetyRational<IntegerType, FloatingType> &rhs);

#include "SafetyRational_det.h"

#endif // _SAFETY_RATIONAL_H_
