#ifndef _ECKERT_PROCESSOR_H_
#define _ECKERT_PROCESSOR_H_

#include <exception>

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////

namespace engine {

class EckertProcessor {
	private:
		unsigned int _errorFlags;
		unsigned int _exceptFlags;
	public:
		EckertProcessor() {
			resetFlags();
			resetExceptions();
		}
		class FlagException : public std::exception { };
		void setFlags(const unsigned int &flag) {
			_errorFlags |= flag;
			if (_errorFlags & _exceptFlags) {
				_exceptFlags = 0;
				throw FlagException();
			}
		}
		void setExceptions(const unsigned int &flag) {
			_exceptFlags |= flag;
		}
		//==  Flag controller  ==//
		bool checkFlags(const unsigned int &flag) {
			return ((_errorFlags & flag) ? true : false);
		}
		void resetFlags() {
			_errorFlags = 0;
		}
		void resetExceptions() {
			_exceptFlags = 0;
		}
};

} // namespace engine

#endif // _ECKERT_PROCESSOR_H_
