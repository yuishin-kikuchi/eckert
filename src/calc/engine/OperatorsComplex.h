#ifndef _OPERATORS_COMPLEX_H_
#define _OPERATORS_COMPLEX_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class MakeComplexReImOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MCMP");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				if (p_ey->isKindOf(Element::SCALAR_TYPE) && p_ex->isKindOf(Element::SCALAR_TYPE)) {
					SpElement p_etemp;
					proc.setComplex(p_etemp, p_ey, p_ex);
					stack.drop(2);
					stack.push(p_etemp);
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 2;
		}
};

class MakeComplexPolRadianOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MKER");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement magnitude = stack.fetch(1);
				SpElement argument = stack.fetch(0);
				if (magnitude->isKindOf(Element::SCALAR_TYPE) && argument->isKindOf(Element::SCALAR_TYPE)) {
					SpElement real;
					SpElement imag;
					try {
						real = proc.mul(magnitude, proc.cosRadian(argument));
						imag = proc.mul(magnitude, proc.sinRadian(argument));
					}
					catch (BadArgument &ba) {
						stackEngine.setErrorMessage(ba.what());
						return true;
					}
					if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
						stackEngine.setErrorMessage("TOO_LRGE");
						return true;
					}
					else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
						stackEngine.setErrorMessage("ERR_CALC");
						return true;
					}
					SpElement p_etemp;
					proc.setComplex(p_etemp, real, imag);
					stack.drop(2);
					stack.push(p_etemp);
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 2;
		}
};

class MakeComplexPolDegreeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MKED");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement magnitude = stack.fetch(1);
				SpElement argument = stack.fetch(0);
				if (magnitude->isKindOf(Element::SCALAR_TYPE) && argument->isKindOf(Element::SCALAR_TYPE)) {
					SpElement real;
					SpElement imag;
					try {
						real = proc.mul(magnitude, proc.cosDegree(argument));
						imag = proc.mul(magnitude, proc.sinDegree(argument));
					}
					catch (BadArgument &ba) {
						stackEngine.setErrorMessage(ba.what());
						return true;
					}
					if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
						stackEngine.setErrorMessage("TOO_LRGE");
						return true;
					}
					else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
						stackEngine.setErrorMessage("ERR_CALC");
						return true;
					}
					SpElement p_etemp;
					proc.setComplex(p_etemp, real, imag);
					stack.drop(2);
					stack.push(p_etemp);
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 2;
		}
};

class MakeComplexPolGradeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MKEG");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement magnitude = stack.fetch(1);
				SpElement argument = stack.fetch(0);
				if (magnitude->isKindOf(Element::SCALAR_TYPE) && argument->isKindOf(Element::SCALAR_TYPE)) {
					SpElement real;
					SpElement imag;
					try {
						real = proc.mul(magnitude, proc.cosGrade(argument));
						imag = proc.mul(magnitude, proc.sinGrade(argument));
					}
					catch (BadArgument &ba) {
						stackEngine.setErrorMessage(ba.what());
						return true;
					}
					if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
						stackEngine.setErrorMessage("TOO_LRGE");
						return true;
					}
					else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
						stackEngine.setErrorMessage("ERR_CALC");
						return true;
					}
					SpElement p_etemp;
					proc.setComplex(p_etemp, real, imag);
					stack.drop(2);
					stack.push(p_etemp);
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 2;
		}
};

class ReOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_RE");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.re(p_ex);
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

class ImOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_IM");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.im(p_ex);
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

class ConjOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_CONJ");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.conj(p_ex);
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

class ArgRadianOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_ARGR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.argRadian(p_ex);
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

class ArgDegreeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_ARGD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.argDegree(p_ex);
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

class ArgGradeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_ARGG");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.argGrade(p_ex);
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

class RealImagOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_REIM");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isType(Element::COMPLEX)) {
					SpElement real;
					SpElement imag;
					try {
						real = proc.re(p_ex);
						imag = proc.im(p_ex);
					}
					catch (BadArgument &ba) {
						stackEngine.setErrorMessage(ba.what());
						return true;
					}
					checkFlags(stackEngine);
					stack.drop(1);
					stack.push(real);
					stack.push(imag);
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
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

class MagArgRadianOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MAR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isType(Element::COMPLEX)) {
					SpElement mag;
					SpElement arg;
					try {
						mag = proc.abs(p_ex);
						arg = proc.argRadian(p_ex);
					}
					catch (BadArgument &ba) {
						stackEngine.setErrorMessage(ba.what());
						return true;
					}
					checkFlags(stackEngine);
					stack.drop(1);
					stack.push(mag);
					stack.push(arg);
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
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

class MagArgDegreeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MAD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isType(Element::COMPLEX)) {
					SpElement mag;
					SpElement arg;
					try {
						mag = proc.abs(p_ex);
						arg = proc.argDegree(p_ex);
					}
					catch (BadArgument &ba) {
						stackEngine.setErrorMessage(ba.what());
						return true;
					}
					checkFlags(stackEngine);
					stack.drop(1);
					stack.push(mag);
					stack.push(arg);
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
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

class MagArgGradeOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_MAG");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				if (p_ex->isType(Element::COMPLEX)) {
					SpElement mag;
					SpElement arg;
					try {
						mag = proc.abs(p_ex);
						arg = proc.argGrade(p_ex);
					}
					catch (BadArgument &ba) {
						stackEngine.setErrorMessage(ba.what());
						return true;
					}
					checkFlags(stackEngine);
					stack.drop(1);
					stack.push(mag);
					stack.push(arg);
				}
				else {
					stackEngine.setErrorMessage("BAD_TYPE");
					return true;
				}
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

#endif // _OPERATORS_COMPLEX_H_
