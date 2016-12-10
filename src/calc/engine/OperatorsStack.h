#ifndef _OPERATORS_STACK_H_
#define _OPERATORS_STACK_H_

#include "GeneralOperator.h"
#include "proc/ElementMacros.h"

namespace engine {

class PushOperator : public GeneralOperator {
	private:
		SpElement _elm;
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_PUSH");
			stackEngine.setErrorMessage("NO_ERROR");
			auto &stack = stackEngine.refExStack();
			if (nullptr != _elm) {
				stack.push(_elm);
				return false;
			}
			else {
				stackEngine.setErrorMessage("NULLPTR");
				return true;
			}
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
		void setSpElement(const SpElement &elm) {
			_elm = elm;
		}
		SpElement getSpElement() const {
			return _elm;
		}
};

class DupOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_DUP");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.dup();
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

class SwapOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_SWAP");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.swap(0, 1);
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

class OverOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_OVER");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.pick(1);
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

class DropOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_DROP");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.drop(1);
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

class RotOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_SROT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.roll(2);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 3;
		}
};

class UnrotOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_SURT");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.rolld(2);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 3;
		}
};

class RollOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_ROLL");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t sel_pos = 0;
				if (!getSizetValue(sel_pos, p_ex)) {
					std::size_t items = stack.size();
					if (sel_pos > 0) {
						if (items < sel_pos + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							stack.drop(1);
							stack.roll(sel_pos - 1);
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
			return 3;
		}
};

class RolldOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_ROLD");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t sel_pos = 0;
				if (!getSizetValue(sel_pos, p_ex)) {
					std::size_t items = stack.size();
					if (sel_pos > 0) {
						if (items < sel_pos + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							stack.drop(1);
							stack.rolld(sel_pos - 1);
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
			return 3;
		}
};

class PickOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_PICK");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t sel_pos = 0;
				if (!getSizetValue(sel_pos, p_ex)) {
					std::size_t items = stack.size();
					if (sel_pos > 0) {
						if (items < sel_pos + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							stack.drop(1);
							stack.pick(sel_pos - 1);
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
			return 3;
		}
};

class UnpickOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_UPIK");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t sel_pos = 0;
				if (!getSizetValue(sel_pos, p_ex)) {
					std::size_t items = stack.size();
					if (sel_pos > 0) {
						if (items < sel_pos + 2) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							stack.drop(1);
							stack.unpick(sel_pos);
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
			return 3;
		}
};

class Pick3Operator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_PIK3");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.pick(2);
			}
			else {
				return true;
			}
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 3;
		}
};

class StackDepthOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_DPTH");
			stackEngine.setErrorMessage("NO_ERROR");
			auto &stack = stackEngine.refExStack();
			stack.push(GEN_INTEGER((integer_t)stack.size()));
			return false;
		}
		virtual std::size_t getRequiredCount() const {
			return 0;
		}
};

class Dup2Operator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_DUP2");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.dupn(2);
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

class DupnOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_DUPN");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t dup_items = 0;
				if (!getSizetValue(dup_items, p_ex)) {
					std::size_t items = stack.size();
					if (dup_items > 0) {
						if (items < dup_items + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							stack.drop(1);
							stack.dupn(dup_items);
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

class Drop2Operator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_DRP2");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.drop(2);
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

class DropnOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_DRPN");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t drop_items = 0;
				if (!getSizetValue(drop_items, p_ex)) {
					std::size_t items = stack.size();
					if (drop_items > 0) {
						if (items < drop_items + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							stack.drop(drop_items + 1);
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

class DupDupOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_DDUP");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.dup(2);
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

class NipOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_NIP");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				stack.nipn(1);
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

class NipnOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_NIPN");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t sel_pos = 0;
				if (!getSizetValue(sel_pos, p_ex)) {
					std::size_t items = stack.size();
					if (sel_pos > 0) {
						if (items < sel_pos + 1) {
							stackEngine.setErrorMessage("BAD_CNT");
							return true;
						}
						else {
							stack.drop(1);
							stack.nipn(sel_pos - 1);
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

class NdupnOperator : public GeneralOperator {
	public:
		virtual bool operate(StackEngine &stackEngine) const {
			stackEngine.setCommandMessage("OP_NDPN");
			stackEngine.setErrorMessage("NO_ERROR");
			if (hasEnoughItems(stackEngine)) {
				auto &stack = stackEngine.refExStack();
				SpElement p_ex = stack.fetch(0);
				std::size_t dup_cnt = 0;
				if (!getSizetValue(dup_cnt, p_ex)) {
					if (dup_cnt > 0) {
						stack.drop(1);
						stack.dup(dup_cnt - 1);
						stack.push(p_ex);
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

} // namespace engine

#endif // _OPERATORS_STACK_H_
