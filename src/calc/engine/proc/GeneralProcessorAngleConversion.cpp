#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / RADIAN TO DEGREE
// [ description ]
// Convert radian to degree
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::radianToDegree(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	// X * 180 / PI
	return mul(p_ex, div(GEN_INTEGER(180), pi()));
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / RADIAN TO GRADE
// [ description ]
// Convert radian to grade
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::radianToGrade(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	// X * 200 / PI
	return mul(p_ex, div(GEN_INTEGER(200), pi()));
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / DEGREE TO RADIAN
// [ description ]
// Convert degree to radian
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::degreeToRadian(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	// X * PI / 180
	return mul(p_ex, divScalar(pi(), GEN_INTEGER(180)));
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / DEGREE TO GRADE
// [ description ]
// Convert degree to grade
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::degreeToGrade(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	// X * 10 / 9
	return mul(p_ex, GEN_RATIONAL2(10, 9));
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / GRADE TO RADIAN
// [ description ]
// Convert grade to radian
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::gradeToRadian(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	// X * PI / 200
	return mul(p_ex, divScalar(pi(), GEN_INTEGER(200)));
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / GRADE TO DEGREE
// [ description ]
// Convert grade to degree
// [ Update ]
// Jan 28, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::gradeToDegree(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	// X * 9 / 10
	return mul(p_ex, GEN_RATIONAL2(9, 10));
}

} // namespace engine
