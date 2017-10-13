#ifndef _STRING_ENGINE_H_
#define _STRING_ENGINE_H_

#include "FloatingDisplayConfig.h"
#include "proc/ElementMacros.h"
#include <string>

////==--------------------------------------------------------------------====//
// ECKERT ENGINE - STRING ENGINE
// [ Update ]
// Jul 10, 2017
//====--------------------------------------------------------------------==////

namespace engine {

class CalculationConfig;

class StringEngine {
	public:
		enum : int {
			CONSOLE_DOTS = 3,
			LONG_TYPE_WIDTH = 10,
			SHORT_TYPE_WIDTH = 5,
		};
		enum class TypeDisplayMode : int {
			NO_DISPLAY,
			LONG,
			SHORT,
		};
		enum class DecimalDisplayMode : int {
			AUTO_DECIMAL,
			FORCE_DECIMAL,
			FORCE_FRACTIONAL,
		};
		enum class FractionalDisplayMode : int {
			PROVISIONAL,
			MIXED,
		};
		enum class NumberBaseMode : int {
			BINARY,
			OCTAL,
			SIGNED_DECIMAL,
			UNSIGNED_DECIMAL,
			HEXADECIMAL,
		};
	private:
		TypeDisplayMode _tdisp;
		DecimalDisplayMode _ddisp;
		FractionalDisplayMode _frdisp;
		NumberBaseMode _nbase;
		FloatingDisplayConfig _fcfg;
		mutable bool _euler;
		bool _piRad;
		std::string complexArgumentToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string errorToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string estringToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string integerToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string floatingToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string rationalToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string einfinityToString(const CalculationConfig &cfg,const SpElement &elm) const;
		std::string complexToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string complexToReImString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string complexToEulerString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string booleanToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string binary8ToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string binary16ToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string binary32ToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string binary64ToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string etupleToString(const CalculationConfig &cfg, const SpElement &elm) const;
		std::string matrixToString(const CalculationConfig &cfg, const SpElement &elm) const;
	public:
		StringEngine();
		void init();
		static std::string floatToStandardString(const floating_t &val, const int &p);
		static std::string floatToFixedString(const floating_t &val, const int &p);
		static std::string floatToScientificString(const floating_t &val, const int &p);
		static std::string floatToEngineeringString(const floating_t &val, const int &p);
		std::string typeToString(const CalculationConfig &cfg, const SpElement &elm) const;
		static std::string typeToShortString(const SpElement &elm);
		static std::string typeToLongString(const SpElement &elm);
		std::string elementToString(const CalculationConfig &cfg, const SpElement &elm, const int &len) const;
		std::string elementToString(const CalculationConfig &cfg, const SpElement &elm) const;
		// setter and getter
		TypeDisplayMode getTypeDisplayMode() const {
			return _tdisp;
		}
		NumberBaseMode getNumberBaseMode() const {
			return _nbase;
		}
		DecimalDisplayMode getDecimalDisplayMode() const {
			return _ddisp;
		}
		FractionalDisplayMode getFractionalDisplayMode() const {
			return _frdisp;
		}
		FloatingDisplayConfig getFloatingDisplayConfig() const {
			return _fcfg;
		}
		void setTypeDisplayMode(const TypeDisplayMode &mode) {
			_tdisp = mode;
		}
		void setDecimalDisplayMode(const DecimalDisplayMode &mode) {
			_ddisp = mode;
		}
		void setFractionalDisplayMode(const FractionalDisplayMode &mode) {
			_frdisp = mode;
		}
		void setNumberBaseMode(const NumberBaseMode &mode) {
			_nbase = mode;
		}
		void setFloatingDisplayConfig(const FloatingDisplayConfig &cfg) {
			_fcfg = cfg;
		}
		FloatingDisplayConfig& refFloatingDisplayConfig() {
			return _fcfg;
		}
		const FloatingDisplayConfig& refFloatingDisplayConfig() const {
			return _fcfg;
		}
		void setEulerFlag(const bool &flag) {
			_euler = flag;
		}
		bool getEulerFlag() const {
			return _euler;
		}
		void setPiRadianFlag(const bool &flag) {
			_piRad = flag;
		}
		bool getPiRadianFlag() const {
			return _piRad;
		}
};

} // namespace engine

#endif // _STRING_ENGINE_H_
