#ifndef _OPERATORS_STATS_H_
#define _OPERATORS_STATS_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class BetaOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_BETA");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ey = stack.fetch(1);
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					SpElement divisor = proc.trueGamma(proc.add(p_ey, p_ex));
					p_etemp = proc.mul(proc.trueGamma(p_ey), proc.trueGamma(p_ex));
					p_etemp = proc.div(p_etemp, divisor);
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.drop(2);
				stack.push(p_etemp);
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

class GammaOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_GAM");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.trueGamma(p_ex);
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

class LnGammaOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_LGAM");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.lnGamma(p_ex);
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

class ErrorFunctionOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_ERF");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.erf(p_ex);
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

class ComplementaryErrorFunctionOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_ERFC");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				SpElement p_etemp;
				try {
					p_etemp = proc.erfc(p_ex);
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

class SumOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_SUM");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.clear();
				stack.push(p_etemp);
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

class ProdOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PRD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.clear();
				stack.push(p_etemp);
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

class ArithmeticAverageOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_AVR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
					integer_t temp = (integer_t)stack.size();
					if (0 < temp) {
						p_etemp = proc.div(p_etemp, GEN_INTEGER(temp));
					}
					else {
						stackEngine.setErrorMessage("TOO_LRGE");
						return true;
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.clear();
				stack.push(p_etemp);
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

class GeometricAverageOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_GVR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.mul(p_etemp, stack.fetch(ucnt));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
					integer_t temp = (integer_t)stack.size();
					if (0 < temp) {
						p_etemp = proc.nthRoot(p_etemp, GEN_INTEGER(temp));
					}
					else {
						stackEngine.setErrorMessage("TOO_LRGE");
						return true;
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.clear();
				stack.push(p_etemp);
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

class HarmonicAverageOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_HVR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = proc.inv(stack.fetch(0));
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.add(p_etemp, proc.inv(stack.fetch(ucnt)));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
					integer_t temp = (integer_t)stack.size();
					if (0 < temp) {
						p_etemp = proc.mul(proc.inv(p_etemp), GEN_INTEGER(temp));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
					}
					else {
						stackEngine.setErrorMessage("TOO_LRGE");
						return true;
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.clear();
				stack.push(p_etemp);
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

class SumWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_SUMW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.push(p_etemp);
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

class ProdWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PRDW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.push(p_etemp);
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

class ArithmeticAverageWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_AVRW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
					integer_t temp = (integer_t)stack.size();
					if (0 < temp) {
						p_etemp = proc.div(p_etemp, GEN_INTEGER(temp));
					}
					else {
						stackEngine.setErrorMessage("TOO_LRGE");
						return true;
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.push(p_etemp);
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

class GeometricAverageWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_GVRW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.mul(p_etemp, stack.fetch(ucnt));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
					integer_t temp = (integer_t)stack.size();
					if (0 < temp) {
						p_etemp = proc.nthRoot(p_etemp, GEN_INTEGER(temp));
					}
					else {
						stackEngine.setErrorMessage("TOO_LRGE");
						return true;
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.push(p_etemp);
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

class HarmonicAverageWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_HVRW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = proc.inv(stack.fetch(0));
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.add(p_etemp, proc.inv(stack.fetch(ucnt)));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
						else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
							stackEngine.setErrorMessage("ERROR_CALC");
							return true;
						}
					}
					integer_t temp = (integer_t)stack.size();
					if (0 < temp) {
						p_etemp = proc.mul(proc.inv(p_etemp), GEN_INTEGER(temp));
						if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
							stackEngine.setErrorMessage("TOO_LRGE");
							return true;
						}
					}
					else {
						stackEngine.setErrorMessage("TOO_LRGE");
						return true;
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.push(p_etemp);
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

class PartialSumOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PSUM");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					if (arg_count > 0) {
						std::size_t items = stack.size();
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = stack.fetch(1);
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1 + arg_count);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class PartialProdOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PPRD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					if (arg_count > 0) {
						std::size_t items = stack.size();
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = stack.fetch(1);
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.mul(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1 + arg_count);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class PartialArithmeticAverageOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PAVR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					std::size_t items = stack.size();
					if (arg_count > 0) {
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = stack.fetch(1);
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
								p_etemp = proc.div(p_etemp, GEN_INTEGER((integer_t)arg_count));
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1 + arg_count);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class PartialGeometricAverageOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PGVR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					if (arg_count > 0) {
						std::size_t items = stack.size();
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = stack.fetch(1);
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.mul(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
								p_etemp = proc.nthRoot(p_etemp, GEN_INTEGER((integer_t)arg_count));
								if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
									stackEngine.setErrorMessage("TOO_LRGE");
									return true;
								}
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1 + arg_count);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class PartialHarmonicAverageOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PHVR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					if (arg_count > 0) {
						std::size_t items = stack.size();
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = proc.inv(stack.fetch(1));
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.mul(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
								p_etemp = proc.mul(proc.inv(p_etemp), GEN_INTEGER((integer_t)arg_count));
								if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
									stackEngine.setErrorMessage("TOO_LRGE");
									return true;
								}
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1 + arg_count);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class PartialSumWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PSUMW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					if (arg_count > 0) {
						std::size_t items = stack.size();
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = stack.fetch(1);
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class PartialProdWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PPRDW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					if (arg_count > 0) {
						std::size_t items = stack.size();
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = stack.fetch(1);
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.mul(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class PartialArithmeticAverageWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PAVRW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					if (arg_count > 0) {
						std::size_t items = stack.size();
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = stack.fetch(1);
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.add(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
								p_etemp = proc.div(p_etemp, GEN_INTEGER((integer_t)arg_count));
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class PartialGeometricAverageWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PGVRW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					if (arg_count > 0) {
						std::size_t items = stack.size();
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = stack.fetch(1);
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.mul(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
								p_etemp = proc.nthRoot(p_etemp, GEN_INTEGER((integer_t)arg_count));
								if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
									stackEngine.setErrorMessage("TOO_LRGE");
									return true;
								}
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class PartialHarmonicAverageWDOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_PHVRW");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t arg_count = 0;
				if (!getSizetValue(arg_count, p_ex)) {
					if (arg_count > 0) {
						std::size_t items = stack.size();
						if (items < arg_count + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							SpElement p_etemp;
							try {
								p_etemp = proc.inv(stack.fetch(1));
								for (std::size_t ucnt = 2; ucnt < arg_count + 1; ++ucnt) {
									p_etemp = proc.mul(p_etemp, stack.fetch(ucnt));
									if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
										stackEngine.setErrorMessage("TOO_LRGE");
										return true;
									}
									else if (proc.checkFlags(GeneralProcessor::ERROR_FLAG)) {
										stackEngine.setErrorMessage("ERROR_CALC");
										return true;
									}
								}
								p_etemp = proc.mul(proc.inv(p_etemp), GEN_INTEGER((integer_t)arg_count));
								if (proc.checkFlags(GeneralProcessor::FLT_OVERFLOW)) {
									stackEngine.setErrorMessage("TOO_LRGE");
									return true;
								}
							}
							catch (BadArgument &ba) {
								stackEngine.setErrorMessage(ba.what());
								return true;
							}
							checkFlags(stackEngine);
							stack.drop(1);
							stack.push(p_etemp);
						}
					}
					else {
						stackEngine.setErrorMessage("BAD_VAL");
						return true;
					}
				}
				else {
					stackEngine.setErrorMessage("NOT_PINT");
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

class AllAndOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_AAND");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.bitwiseAnd(p_etemp, stack.fetch(ucnt));
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.clear();
				stack.push(p_etemp);
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

class AllOrOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_AOR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.bitwiseOr(p_etemp, stack.fetch(ucnt));
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.clear();
				stack.push(p_etemp);
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

class AllXorOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			auto &proc = getGeneralProcessor();
			proc.resetFlags();
			stackEngine.setCommandMessage("OP_AXOR");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_etemp;
				try {
					p_etemp = stack.fetch(0);
					std::size_t items = stack.size();
					for (std::size_t ucnt = 1; ucnt < items; ++ucnt) {
						p_etemp = proc.bitwiseXor(p_etemp, stack.fetch(ucnt));
					}
				}
				catch (BadArgument &ba) {
					stackEngine.setErrorMessage(ba.what());
					return true;
				}
				checkFlags(stackEngine);
				stack.clear();
				stack.push(p_etemp);
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

} // namespace engine

#endif // _OPERATORS_STATS_H_
