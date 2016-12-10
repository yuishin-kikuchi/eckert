#ifndef _OPERATORS_ANGLE_CONVERSION_H_
#define _OPERATORS_ANGLE_CONVERSION_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class RadianToDegreeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_RTOD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.radianToDegree(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class RadianToGradeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_RTOG");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.radianToGrade(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class DegreeToRadianOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_DTOR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.degreeToRadian(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class DegreeToGradeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_DTOG");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.degreeToGrade(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class GradeToRadianOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_GTOR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.gradeToRadian(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class GradeToDegreeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_GTOD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.gradeToDegree(p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class ComplementaryAngleRadian : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_CAGR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.sub(proc.pi_2(), p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class ComplementaryAngleDegree : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_CAGD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.sub(GEN_INTEGER(90), p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class ComplementaryAngleGrade : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_CAGG");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.sub(GEN_INTEGER(100), p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class SupplementaryAngleRadian : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_SAGR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.sub(proc.pi(), p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class SupplementaryAngleDegree : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_SAGD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.sub(GEN_INTEGER(180), p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

class SupplementaryAngleGrade : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_SAGG");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.sub(GEN_INTEGER(200), p_ex);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(1);
				stack.push(p_etemp);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 1;
		}
};

} // namespace engine

#endif // _OPERATORS_ANGLE_CONVERSION_H_
