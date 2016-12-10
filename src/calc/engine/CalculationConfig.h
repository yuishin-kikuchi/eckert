#ifndef _CALCULATION_CONFIG_H_
#define _CALCULATION_CONFIG_H_

////==--------------------------------------------------------------------====//
// CALCULATION CONFIG
// [ Update ]
// Nov 16, 2016
//====--------------------------------------------------------------------==////

namespace engine {

class CalculationConfig {
	public:
		enum class AngleMode : int;
	private:
		AngleMode _angle;
	public:
		CalculationConfig();
		void init();
		void setAngleMode(const AngleMode &mode) {
			_angle = mode;
		}
		AngleMode getAngleMode() const {
			return _angle;
		}
};

enum class CalculationConfig::AngleMode : int {
	DEGREE,
	RADIAN,
	GRADE,
};

} // namespace engine

#endif // _CALCULATION_CONFIG_H_
