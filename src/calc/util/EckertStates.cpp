#include "EckertStates.h"

////==--------------------------------------------------------------------====//
// ECKERT STATES / CONSTRUCTOR
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
EckertStates::EckertStates() {
	init();
}

////==--------------------------------------------------------------------====//
// ECKERT STATES / INITIALIZER
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
void EckertStates::init() {
	_waiting = WaitingState::NONE;
}

////==--------------------------------------------------------------------====//
// ECKERT STATES / RESET WAITING STATE
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
void EckertStates::resetWaitingState() {
	_waiting = WaitingState::NONE;
}

////==--------------------------------------------------------------------====//
// ECKERT STATES / RECORD START TIME
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
void EckertStates::startRec() {
	_endPoint
	 = _startPoint
	 = std::chrono::high_resolution_clock::now();
}

////==--------------------------------------------------------------------====//
// ECKERT STATES / RECORD STOP TIME
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
void EckertStates::stopRec() {
	_endPoint = std::chrono::high_resolution_clock::now();
}

////==--------------------------------------------------------------------====//
// ECKERT STATES / GET TIME DURATION
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
double EckertStates::getDuration() const {
	auto timeSpan
		= std::chrono::duration_cast<std::chrono::duration<double>>
		(_endPoint - _startPoint);
	return timeSpan.count();
}
