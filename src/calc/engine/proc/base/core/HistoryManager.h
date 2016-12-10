#ifndef _HISTORY_MANAGER_H_
#define _HISTORY_MANAGER_H_

#include "BaseElement.h"
#include <vector>
#include <list>

////==--------------------------------------------------------------------====//
// STACK ENGINE HISTORY MANAGER
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////

namespace engine {

class StackEngine;

class HistoryManager {
	public:
		static const std::size_t DEFAULT_HISTORY_SIZE;
	private:
		struct Item {
			Item(std::vector<SpElement> stk, std::vector<SpElement> reg)
				: stackVector(stk), registerVector(reg) {}
			std::vector<SpElement> stackVector;
			std::vector<SpElement> registerVector;
		};
		std::list<Item> _history;
		std::size_t _maxSize;
		std::size_t _currentPos;
	public:
		HistoryManager();
		HistoryManager(StackEngine &stackEngine);
		void init(StackEngine &stackEngine);
		bool undo(StackEngine &stackEngine);
		bool redo(StackEngine &stackEngine);
		void manage(StackEngine &stackEngine);
		void setMaxSize(const std::size_t &size) {
			_maxSize = size;
		}
		std::size_t getMaxSize() const {
			return _maxSize;
		}
		std::size_t getCurrentSize() const {
			return (_history.size() - 1);
		}
		std::size_t getCurrentPos() const {
			return _currentPos;
		}
};

} // namespace engine

#endif // _HISTORY_MANAGER_H_
