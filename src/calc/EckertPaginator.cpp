#include "EckertPaginator.h"

////==--------------------------------------------------------------------====//
// PAGINATOR / STATIC MEMBERS
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
const std::size_t EckertPaginator::LEAST_DISPLAY_LINE = 4;
const int EckertPaginator::LEAST_DISPLAY_WIDTH = 60;

////==--------------------------------------------------------------------====//
// PAGINATOR / CONSTRUCTOR
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
EckertPaginator::EckertPaginator() {
	_displayLine = LEAST_DISPLAY_LINE;
	_displayWidth = LEAST_DISPLAY_WIDTH;
	init();
}

////==--------------------------------------------------------------------====//
// PAGINATOR / INITIALIZER
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertPaginator::init() {
	_stackOffset = 0;
	_registerOffset = 0;
	_registerDisplayFlag = false;
}

////==--------------------------------------------------------------------====//
// PAGINATOR / CALCULATE STACK LINE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
std::size_t EckertPaginator::calcStackLine(const std::size_t &registerSize) const {
	if (_registerDisplayFlag) {
		return (_displayLine - calcRegisterLine(registerSize));
	}
	else {
		return _displayLine;
	}
}

////==--------------------------------------------------------------------====//
// PAGINATOR / CALCULATE REGISTER LINE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
std::size_t EckertPaginator::calcRegisterLine(const std::size_t &registerSize) const {
	return ((_displayLine / 2 <= registerSize) ? (_displayLine / 2) : registerSize);
}

////==--------------------------------------------------------------------====//
// PAGINATOR / STACK NEXT PAGE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
bool EckertPaginator::stackNext(const std::size_t &stackItems, const std::size_t &registerSize) {
	std::size_t to_move = _displayLine;
	if (_registerDisplayFlag) {
		to_move -= calcRegisterLine(registerSize);
	}
	if (_stackOffset + to_move < stackItems) {
		_stackOffset += to_move;
	}
	else {
		return true;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// PAGINATOR / STACK PREVIOUS PAGE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
bool EckertPaginator::stackPrev(const std::size_t &stackItems, const std::size_t &registerSize) {
	std::size_t to_move = _displayLine;
	if (_registerDisplayFlag) {
		to_move -= calcRegisterLine(registerSize);
	}
	if (0 == _stackOffset) {
		return true;
	}
	if (_stackOffset > to_move) {
		_stackOffset -= to_move;
	}
	else {
		_stackOffset = 0;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// PAGINATOR / STACK FIRST PAGE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
bool EckertPaginator::stackFirst(const std::size_t &stackItems, const std::size_t &registerSize) {
	_stackOffset = 0;
	return false;
}

////==--------------------------------------------------------------------====//
// PAGINATOR / REGISTER NEXT PAGE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
bool EckertPaginator::registerNext(const std::size_t &registerSize) {
	std::size_t to_move = calcRegisterLine(registerSize);
	if (_registerOffset + to_move < registerSize) {
		_registerOffset += to_move;
	}
	else {
		return true;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// PAGINATOR / REGISTER PREVIOUS PAGE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
bool EckertPaginator::registerPrev(const std::size_t &registerSize) {
	std::size_t to_move = calcRegisterLine(registerSize);
	if (0 == _registerOffset) {
		return true;
	}
	if (_registerOffset > to_move) {
		_registerOffset -= to_move;
	}
	else {
		_registerOffset = 0;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// PAGINATOR / REGISTER FIRST PAGE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
bool EckertPaginator::registerFirst(const std::size_t &registerSize) {
	_registerOffset = 0;
	return false;
}
