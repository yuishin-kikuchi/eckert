#include "HistoryManager.h"
#include "StackEngine.h"

namespace engine {

////==--------------------------------------------------------------------====//
// STACK ENGINE HISTORY MANAGER
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////
const std::size_t HistoryManager::DEFAULT_HISTORY_SIZE = 10;

////==--------------------------------------------------------------------====//
// STACK ENGINE HISTORY MANAGER
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////
HistoryManager::HistoryManager() {
	_maxSize = 0;
	_currentPos = 0;
}

////==--------------------------------------------------------------------====//
// STACK ENGINE HISTORY MANAGER
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////
HistoryManager::HistoryManager(StackEngine &stackEngine) {
	init(stackEngine);
}

////==--------------------------------------------------------------------====//
// STACK ENGINE HISTORY MANAGER
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////
void HistoryManager::init(StackEngine &stackEngine) {
	_maxSize = DEFAULT_HISTORY_SIZE;
	_currentPos = 0;
	_history.clear();
	_history.push_front(
		Item(stackEngine.refStack(), stackEngine.refRegister())
	);
}

////==--------------------------------------------------------------------====//
// STACK ENGINE HISTORY MANAGER
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////
bool HistoryManager::undo(StackEngine &stackEngine) {
	if (_currentPos + 1 == _history.size()) {
		return true;
	}
	else {
		auto itr = _history.begin();
		++_currentPos;
		for (std::size_t ucnt = 0; ucnt < _currentPos; ++ucnt) {
			++itr;
		}
		stackEngine.refStack() = itr->stackVector;
		stackEngine.refRegister() = itr->registerVector;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// STACK ENGINE HISTORY MANAGER
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////
bool HistoryManager::redo(StackEngine &stackEngine) {
	if (0 == _currentPos) {
		return true;
	}
	else {
		auto itr = _history.begin();
		--_currentPos;
		for (std::size_t ucnt = 0; ucnt < _currentPos; ++ucnt) {
			++itr;
		}
		stackEngine.refStack() = itr->stackVector;
		stackEngine.refRegister() = itr->registerVector;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// STACK ENGINE HISTORY MANAGER
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////
void HistoryManager::manage(StackEngine &stackEngine) {
	if (0 != _currentPos) {
		auto itr = _history.begin();
		for (std::size_t ucnt = 0; ucnt < _currentPos; ++ucnt) {
			++itr;
		}
		_history.erase(_history.begin(), itr);
	}
	_history.push_front(
		Item(stackEngine.refStack(), stackEngine.refRegister())
	);
	while (_history.size() > _maxSize + 1) {
		_history.pop_back();
	}
	_currentPos = 0;
}

} // namespace engine
