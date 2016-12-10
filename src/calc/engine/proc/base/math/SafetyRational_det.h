#ifndef _SAFETY_RATIONAL_DET_H_
#define _SAFETY_RATIONAL_DET_H_

#include "SafetyRational.h"
#include "SafetyIntegerCalculator.h"

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL CONSTRUCTOR
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>::SafetyRational()
: _num(0), _den(0) {
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL CONSTRUCTOR
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>::SafetyRational(
	const IntegerType &num,
	const IntegerType &den)
: _num(num), _den(den) {
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL CONSTRUCTOR
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>::SafetyRational(const SafetyRational &obj)
: _num(obj._num), _den(obj._den) {
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL SIMPLIFY
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
void SafetyRational<IntegerType, FloatingType>::simplify() {
	if (0 == _num) {
		_den = 1;
	}
	else if (0 == _den) {
		_num = 0;
		_den = 0;
	}
	else {
		IntegerType divisor;
		divisor = SafetyIntegerCalculator::gcd(_num, _den);
		_num /= divisor;
		_den /= divisor;
	}
	return;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL IS ERROR
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
bool SafetyRational<IntegerType, FloatingType>::isError() const {
	return (0 == _den);
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL IS ZERO
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
bool SafetyRational<IntegerType, FloatingType>::isZero() const {
	return ((0 == _num) && (0 != _den));
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL IS INTEGER
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
bool SafetyRational<IntegerType, FloatingType>::isInteger() const {
	if (0 == _den) {
		return false;
	}
	else {
		return (0 == _num % _den);
	}
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL GET NUMERATOR
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
IntegerType SafetyRational<IntegerType, FloatingType>::getNum() const {
	return _num;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL GET DENOMINATOR
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
IntegerType SafetyRational<IntegerType, FloatingType>::getDen() const {
	return _den;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL GET DOUBLE
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
FloatingType SafetyRational<IntegerType, FloatingType>::getFloating() const {
	return (static_cast<FloatingType>(_num) / static_cast<FloatingType>(_den));
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL SET ERROR
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
void SafetyRational<IntegerType, FloatingType>::setError() {
	_num = 0;
	_den = 0;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL SET NUMERATOR
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
void SafetyRational<IntegerType, FloatingType>::setNum(const IntegerType &num) {
	_num = num;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL SET NUMERATOR
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
void SafetyRational<IntegerType, FloatingType>::setDen(const IntegerType &den) {
	_den = den;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL INVERT
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>
SafetyRational<IntegerType, FloatingType>::inv() const {
	if (_den < 0) {
		return SafetyRational();
	}
	else if (_num < 0) {
		return SafetyRational<IntegerType, FloatingType>
			(SafetyIntegerCalculator::neg(_den), SafetyIntegerCalculator::neg(_num));
	}
	else {
		return SafetyRational<IntegerType, FloatingType>(_den, _num);
	}
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL OPERATOR =
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>&
SafetyRational<IntegerType, FloatingType>::operator = (const SafetyRational &rhs)
{
	_num = rhs._num;
	_den = rhs._den;
	return *this;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL OPERATOR +
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>
SafetyRational<IntegerType, FloatingType>::operator + () const {
	return *this;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL OPERATOR -
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>
SafetyRational<IntegerType, FloatingType>::operator - () const {
	if (_den != 0) {
		return SafetyRational<IntegerType, FloatingType>
			(SafetyIntegerCalculator::neg(_num), _den);
	}
	else {
		return SafetyRational<IntegerType, FloatingType>();
	}
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL OPERATOR +=
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>&
SafetyRational<IntegerType, FloatingType>
::operator += (const SafetyRational<IntegerType, FloatingType> &rhs)
{
	IntegerType den = SafetyIntegerCalculator::lcm(_den, rhs._den);
	IntegerType lhs_num = den / _den;
	IntegerType rhs_num = den / rhs._den;
	_den = den;
	lhs_num = SafetyIntegerCalculator::mul(lhs_num, _num);
	rhs_num = SafetyIntegerCalculator::mul(rhs_num, rhs._num);
	_num = SafetyIntegerCalculator::add(lhs_num, rhs_num);
	simplify();
	return *this;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL OPERATOR -=
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>&
SafetyRational<IntegerType, FloatingType>
::operator -= (const SafetyRational<IntegerType, FloatingType> &rhs)
{
	IntegerType den = SafetyIntegerCalculator::lcm(_den, rhs._den);
	IntegerType lhs_num = den / _den;
	IntegerType rhs_num = den / rhs._den;
	_den = den;
	lhs_num = SafetyIntegerCalculator::mul(lhs_num, _num);
	rhs_num = SafetyIntegerCalculator::mul(rhs_num, rhs._num);
	_num = SafetyIntegerCalculator::sub(lhs_num, rhs_num);
	simplify();
	return *this;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL OPERATOR *=
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>&
SafetyRational<IntegerType, FloatingType>
::operator *= (const SafetyRational<IntegerType, FloatingType> &rhs)
{
	IntegerType lhs_num = _num;
	IntegerType lhs_den = _den;
	IntegerType rhs_num = rhs._num;
	IntegerType rhs_den = rhs._den;
	bool is_minus = false;
	if (isZero() || rhs.isZero()) {
		_num = 0;
		_den = 1;
		return *this;
	}
	if (lhs_num < 0) {
		lhs_num = SafetyIntegerCalculator::neg(lhs_num);
		is_minus = true;
	}
	if (rhs_num < 0) {
		rhs_num = SafetyIntegerCalculator::neg(rhs_num);
		is_minus ^= true;
	}
	IntegerType gcd_ln_rd = SafetyIntegerCalculator::gcd(lhs_num, rhs_den);
	IntegerType gcd_ld_rn = SafetyIntegerCalculator::gcd(lhs_den, rhs_num);
	lhs_num /= gcd_ln_rd;
	lhs_den /= gcd_ld_rn;
	rhs_num /= gcd_ld_rn;
	rhs_den /= gcd_ln_rd;
	_num = SafetyIntegerCalculator::mul(lhs_num, rhs_num);
	_den = SafetyIntegerCalculator::mul(lhs_den, rhs_den);
	if (is_minus) {
		_num = SafetyIntegerCalculator::neg(_num);
	}
	return *this;
}

////==--------------------------------------------------------------------====//
// SAFETY RATIONAL OPERATOR /=
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType>&
SafetyRational<IntegerType, FloatingType>
::operator /= (const SafetyRational<IntegerType, FloatingType> &rhs)
{
	IntegerType lhs_num = _num;
	IntegerType lhs_den = _den;
	IntegerType rhs_num = rhs._num;
	IntegerType rhs_den = rhs._den;
	bool is_minus = false;
	if (0 == lhs_num) {
		_num = 0;
		_den = 1;
		return *this;
	}
	if (0 == rhs_num) {
		throw OverflowException("division by zero");
	}
	if (lhs_num < 0) {
		lhs_num = SafetyIntegerCalculator::neg(lhs_num);
		is_minus = true;
	}
	if (rhs_num < 0) {
		rhs_num = SafetyIntegerCalculator::neg(rhs_num);
		is_minus ^= true;
	}
	IntegerType gcd_ln_rn = SafetyIntegerCalculator::gcd(lhs_num, rhs_num);
	IntegerType gcd_ld_rd = SafetyIntegerCalculator::gcd(lhs_den, rhs_den);
	lhs_num /= gcd_ln_rn;
	lhs_den /= gcd_ld_rd;
	rhs_num /= gcd_ln_rn;
	rhs_den /= gcd_ld_rd;
	_num = SafetyIntegerCalculator::mul(lhs_num, rhs_den);
	_den = SafetyIntegerCalculator::mul(lhs_den, rhs_num);
	if (is_minus) {
		_num = SafetyIntegerCalculator::neg(_num);
	}
	return *this;
}

////==--------------------------------------------------------------------====//
// OPERATOR +
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator + (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp += rhs);
}

////==--------------------------------------------------------------------====//
// OPERATOR -
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator - (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp -= rhs);
}

////==--------------------------------------------------------------------====//
// OPERATOR *
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator * (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp *= rhs);
}

////==--------------------------------------------------------------------====//
// OPERATOR /
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator / (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp /= rhs);
}

////==--------------------------------------------------------------------====//
// OPERATOR +
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator + (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const IntegerType &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp += SafetyRational<IntegerType, FloatingType>(rhs));
}

////==--------------------------------------------------------------------====//
// OPERATOR -
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator - (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const IntegerType &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp -= SafetyRational<IntegerType, FloatingType>(rhs));
}

////==--------------------------------------------------------------------====//
// OPERATOR *
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator * (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const IntegerType &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp *= SafetyRational<IntegerType, FloatingType>(rhs));
}

////==--------------------------------------------------------------------====//
// OPERATOR /
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator / (
	const SafetyRational<IntegerType, FloatingType> &lhs,
	const IntegerType &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp /= SafetyRational<IntegerType, FloatingType>(rhs));
}

////==--------------------------------------------------------------------====//
// OPERATOR +
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator + (
	const IntegerType &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp += rhs);
}

////==--------------------------------------------------------------------====//
// OPERATOR -
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator - (
	const IntegerType &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp -= rhs);
}

////==--------------------------------------------------------------------====//
// OPERATOR *
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator * (
	const IntegerType &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp *= rhs);
}

////==--------------------------------------------------------------------====//
// OPERATOR /
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
SafetyRational<IntegerType, FloatingType> operator / (
	const IntegerType &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs)
{
	SafetyRational<IntegerType, FloatingType> temp(lhs);
	return (temp /= rhs);
}

////==--------------------------------------------------------------------====//
// OPERATOR <<
//====--------------------------------------------------------------------==////
template <typename IntegerType, typename FloatingType>
std::ostream& operator << (
	std::ostream &lhs,
	const SafetyRational<IntegerType, FloatingType> &rhs)
{
	if (rhs.isError()) {
		lhs << "ERROR";
	}
	else if (rhs.isInteger()) {
		lhs << rhs.getNum();
	}
	else {
		lhs << rhs.getNum() << '/' << rhs.getDen();
	}
	return lhs;
}

#endif // _SAFETY_RATIONAL_DET_H_
