#ifndef _ECKERT_GENERAL_PROCESSOR_H_
#define _ECKERT_GENERAL_PROCESSOR_H_

#include "EckertProcessor.h"
#include "ElementMacros.h"
#include "except/Exceptions.h"

////==--------------------------------------------------------------------====//
// ECKERT GENERAL PROCESSOR
// [ Update ]
// Dec 21, 2016
//====--------------------------------------------------------------------==////

namespace engine {

class GeneralProcessor : public EckertProcessor {
	public:
		//==  Constants  ==//
		static const floating_t PI;
		static const floating_t NAPIER;
		static const floating_t EGAMMA;
		static const int NEGATIVE;
		static const int POSITIVE;
		static const int ZERO;
		//==  Flag  ==//
		enum : unsigned int {
			ERROR_FLAG   = 1u << 0,
			INT_OVERFLOW  = 1u << 1,
			FLT_OVERFLOW = 1u << 2,
			RAT_OVERFLOW = 1u << 3,
		};
		//==  Quadrant  ==//
		enum class Quadrant : int {
			FIRST = 0,
			SECOND = 1,
			THIRD = 2,
			FORTH = 3,
		};
	private:
		//==  EInfinity arithmetic functions  ==//
		SpElement addInfinity(const SpElement &p_ey, const SpElement &p_ex);
		SpElement subInfinity(const SpElement &p_ey, const SpElement &p_ex);
		SpElement mulInfinity(const SpElement &p_ey, const SpElement &p_ex);
		SpElement divInfinity(const SpElement &p_ey, const SpElement &p_ex);
		SpElement powInfinity(const SpElement &p_ey, const SpElement &p_ex);
		//==  Complex arithmetic functions  ==//
		SpElement addComplex(const SpElement &p_ey, const SpElement &p_ex);
		SpElement subComplex(const SpElement &p_ey, const SpElement &p_ex);
		SpElement mulComplex(const SpElement &p_ey, const SpElement &p_ex);
		SpElement divComplex(const SpElement &p_ey, const SpElement &p_ex);
		SpElement powComplex(const SpElement &p_ey, const SpElement &p_ex);
		//==  Scalar arithmetic functions  ==//
		SpElement addScalar(const SpElement &p_ey, const SpElement &p_ex);
		SpElement subScalar(const SpElement &p_ey, const SpElement &p_ex);
		SpElement mulScalar(const SpElement &p_ey, const SpElement &p_ex);
		SpElement divScalar(const SpElement &p_ey, const SpElement &p_ex);
		SpElement powScalar(const SpElement &p_ey, const SpElement &p_ex);
		//==  Binary arithmetic functions  ==//
		SpElement addBinary(const SpElement &p_ey, const SpElement &p_ex);
		SpElement subBinary(const SpElement &p_ey, const SpElement &p_ex);
		SpElement mulBinary(const SpElement &p_ey, const SpElement &p_ex);
		SpElement divBinary(const SpElement &p_ey, const SpElement &p_ex);
		//==  ETuple and Matrix arithmetic functions  ==//
		SpElement addSet(const SpElement &p_ey, const SpElement &p_ex);
		SpElement subSet(const SpElement &p_ey, const SpElement &p_ex);
		SpElement mulSet(const SpElement &p_ey, const SpElement &p_ex);
		SpElement divSet(const SpElement &p_ey, const SpElement &p_ex);
		SpElement negSet(const SpElement &p_ex);
		SpElement invMatrix(const SpElement &p_ex);
	public:
		GeneralProcessor() : EckertProcessor() {}
		//==  Value setter  ==//
		void setError(SpElement &rp_set, const char *str);
		void setInteger(SpElement &rp_set, const integer_t &num);
		void setFloating(SpElement &rp_set, const floating_t &num);
		void setRational(SpElement &rp_set, const rational_t &num);
		void setRational(SpElement &rp_set, const integer_t &numer, const integer_t &denom);
		void setInfinity(SpElement &rp_set, const int &sign);
		void setComplex(SpElement &rp_set, const SpElement &re, const SpElement &im);
		//==  Value checker  ==//
		bool isZero(const SpElement &p_ex);
		bool isPositiveZero(const SpElement &p_ex);
		bool isNegativeZero(const SpElement &p_ex);
		bool isPositive(const SpElement &p_ex);
		bool isNegative(const SpElement &p_ex);
		bool isInEpsilonInverse(const SpElement &p_ex);
		//==  Constants  ==//
		SpElement pi();
		SpElement pi_2();
		//==  Converion functions  ==//
		SpElement toInteger(const SpElement &p_ex);
		SpElement toFloating(const SpElement &p_ex);
		SpElement toRational(const SpElement &p_ex);
		SpElement toBoolean(const SpElement &p_ex);
		SpElement toByte(const SpElement &p_ex);
		SpElement toWord(const SpElement &p_ex);
		SpElement toDword(const SpElement &p_ex);
		SpElement toQword(const SpElement &p_ex);
		//==  Standard functions  ==//
		SpElement inc(const SpElement &p_ex);
		SpElement dec(const SpElement &p_ex);
		SpElement add(const SpElement &p_ey, const SpElement &p_ex);
		SpElement sub(const SpElement &p_ey, const SpElement &p_ex);
		SpElement mul(const SpElement &p_ey, const SpElement &p_ex);
		SpElement div(const SpElement &p_ey, const SpElement &p_ex);
		SpElement neg(const SpElement &p_ex);
		SpElement inv(const SpElement &p_ex);
		SpElement abs(const SpElement &p_ex);
		//==  N-th functions  ==//
		SpElement square(const SpElement &p_ex);
		SpElement nthPow(const SpElement &p_ey, const SpElement &p_ex);
		SpElement nthRoot(const SpElement &p_ey, const SpElement &p_ex);
		//==  Mod functions  ==//
		SpElement mod(const SpElement &p_ey, const SpElement &p_ex);
		SpElement quot(const SpElement &p_ey, const SpElement &p_ex);
		//==  Mod functions  ==//
		SpElement floor(const SpElement &p_ex);
		SpElement ceil(const SpElement &p_ex);
		SpElement round(const SpElement &p_ex);
		//==  Operations for integers  ==//
		SpElement gcd(const SpElement &p_ey, const SpElement &p_ex);
		SpElement lcm(const SpElement &p_ey, const SpElement &p_ex);
		SpElement fact(const SpElement &p_ex);
		SpElement perm(const SpElement &p_ey, const SpElement &p_ex);
		SpElement comb(const SpElement &p_ey, const SpElement &p_ex);
		//==  Exponent and Logarithm ==//
		SpElement sqrt(const SpElement &p_ex);
		SpElement cbrt(const SpElement &p_ex);
		SpElement pow(const SpElement &p_ey, const SpElement &p_ex);
		SpElement exp(const SpElement &p_ex);
		SpElement pow2(const SpElement &p_ex);
		SpElement pow10(const SpElement &p_ex);
		SpElement loge(const SpElement &p_ex);
		SpElement log10(const SpElement &p_ex);
		SpElement log2(const SpElement &p_ex);
		SpElement hypot(const SpElement &p_ey, const SpElement &p_ex);
		//==  Angle conversions  ==//
		SpElement radianToDegree(const SpElement &p_ex);
		SpElement radianToGrade(const SpElement &p_ex);
		SpElement degreeToRadian(const SpElement &p_ex);
		SpElement degreeToGrade(const SpElement &p_ex);
		SpElement gradeToRadian(const SpElement &p_ex);
		SpElement gradeToDegree(const SpElement &p_ex);
		//==  Trigonometric functions (rad)  ==//
		SpElement sinRadian(const SpElement &p_ex);
		SpElement cosRadian(const SpElement &p_ex);
		SpElement tanRadian(const SpElement &p_ex);
		SpElement asinRadian(const SpElement &p_ex);
		SpElement acosRadian(const SpElement &p_ex);
		SpElement atanRadian(const SpElement &p_ex);
		//==  Trigonometric functions (deg)  ==//
		SpElement sinDegree(const SpElement &p_ex);
		SpElement cosDegree(const SpElement &p_ex);
		SpElement tanDegree(const SpElement &p_ex);
		SpElement asinDegree(const SpElement &p_ex);
		SpElement acosDegree(const SpElement &p_ex);
		SpElement atanDegree(const SpElement &p_ex);
		//==  Trigonometric functions (grad)  ==//
		SpElement sinGrade(const SpElement &p_ex);
		SpElement cosGrade(const SpElement &p_ex);
		SpElement tanGrade(const SpElement &p_ex);
		SpElement asinGrade(const SpElement &p_ex);
		SpElement acosGrade(const SpElement &p_ex);
		SpElement atanGrade(const SpElement &p_ex);
		//==  Hyperbolic functions  ==//
		SpElement sinh(const SpElement &p_ex);
		SpElement cosh(const SpElement &p_ex);
		SpElement tanh(const SpElement &p_ex);
		SpElement asinh(const SpElement &p_ex);
		SpElement acosh(const SpElement &p_ex);
		SpElement atanh(const SpElement &p_ex);
		//==  Gamma function and Error function  ==//
		SpElement trueGamma(const SpElement &p_ex);
		SpElement lnGamma(const SpElement &p_ex);
		SpElement erf(const SpElement &p_ex);
		SpElement erfc(const SpElement &p_ex);
		//==  Complex functions  ==//
		SpElement re(const SpElement &p_ex);
		SpElement im(const SpElement &p_ex);
		SpElement argRadian(const SpElement &p_ex);
		SpElement argDegree(const SpElement &p_ex);
		SpElement argGrade(const SpElement &p_ex);
		SpElement conj(const SpElement &p_ex);
		//==  Binary function  ==//
		SpElement bitwiseNot(const SpElement &p_ex);
		SpElement bitwiseOr(const SpElement &p_ey, const SpElement &p_ex);
		SpElement bitwiseAnd(const SpElement &p_ey, const SpElement &p_ex);
		SpElement bitwiseXor(const SpElement &p_ey, const SpElement &p_ex);
		SpElement bitwiseNor(const SpElement &p_ey, const SpElement &p_ex);
		SpElement bitwiseNand(const SpElement &p_ey, const SpElement &p_ex);
		SpElement shiftLeft(const SpElement &p_ex);
		SpElement shiftRight(const SpElement &p_ex);
		SpElement shiftArithmeticRight(const SpElement &p_ex);
		SpElement shiftByteLeft(const SpElement &p_ex);
		SpElement shiftByteRight(const SpElement &p_ex);
		SpElement shiftNibbleLeft(const SpElement &p_ex);
		SpElement shiftNibbleRight(const SpElement &p_ex);
		SpElement rotateLeft(const SpElement &p_ex);
		SpElement rotateRight(const SpElement &p_ex);
		//==  Tuple and matrix  ==//
		SpElement transpose(const SpElement &p_ex);
		SpElement hermitianTranspose(const SpElement &p_ex);
		SpElement innerProduct(const SpElement &p_ey, const SpElement &p_ex);
		SpElement outerProduct(const SpElement &p_ey, const SpElement &p_ex);
		SpElement determinant(const SpElement &p_ex);
		SpElement trace(const SpElement &p_ex);
		SpElement norm(const SpElement &p_ex);
		SpElement normSq(const SpElement &p_ex);
		SpElement lpNorm(const SpElement &p_ey, const SpElement &p_ex);
		SpElement maxNorm(const SpElement &p_ex);
};

} // namespace engine

#endif // _ECKERT_GENERAL_PROCESSOR_H_
