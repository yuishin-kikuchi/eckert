#ifndef _ENGINEERING_CALCULATOR_H_
#define _ENGINEERING_CALCULATOR_H_

#include "proc/base/core/StackCalculator.h"

////==--------------------------------------------------------------------====//
// ENGINEERING CALCULATOR
// [ Update ]
// Nov 23, 2016
//====--------------------------------------------------------------------==////

namespace engine {

class EngineeringCalculator : public engine::StackCalculator {
	public:
		EngineeringCalculator();
		void init();
		virtual bool operate(const std::string &str);
};

} // namespace engine

#endif // ifndef _ENGINEERING_CALCULATOR_H_
