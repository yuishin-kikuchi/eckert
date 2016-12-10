#include "CalculationConfig.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ENGINE - CONFIG / CONSTRUCTOR
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
CalculationConfig::CalculationConfig() {
	init();
}

////==--------------------------------------------------------------------====//
// ECKERT ENGINE - CONFIG / INITIALIZER
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////
void CalculationConfig::init() {
	_angle = CalculationConfig::AngleMode::RADIAN;
}

} // namespace engine
