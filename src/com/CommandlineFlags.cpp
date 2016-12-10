// COMMANDLINE FLAGS
// (C) 2015-2016 Yuishin Kikuchi

#include "CommandlineFlags.h"

////==--------------------------------------------------------------------====//
// COMMANDLINE FLAGS CONSTRUCTOR
// CommandlineFlags::CommandlineFlags()
//====--------------------------------------------------------------------==////
CommandlineFlags::CommandlineFlags() {
	init();
}

////==--------------------------------------------------------------------====//
// COMMANDLINE FLAGS CONSTRUCTOR
// CommandlineFlags::CommandlineFlags(char **argv)
//====--------------------------------------------------------------------==////
CommandlineFlags::CommandlineFlags(char **argv) {
	read_flags(argv);
}

////==--------------------------------------------------------------------====//
// COMMANDLINE FLAGS INITIALIZER
// CommandlineFlags::init()
//====--------------------------------------------------------------------==////
void CommandlineFlags::init() {
	for (auto &&x : _flags) {
		x = false;
	}
}

////==--------------------------------------------------------------------====//
// COMMANDLINE FLAGS READ FLAGS
// CommandlineFlags::read_flags(char **argv)
//====--------------------------------------------------------------------==////
void CommandlineFlags::read_flags(char **argv) {
	init();
	if (nullptr == argv) {
		return;
	}
	++argv; // skip program name
	while (nullptr != *argv) {
		const char *pos = *argv;
		if ('-' == *pos) {
			// debug flag string begin with '-'
			++pos;
			while ('\0' != *pos) {
				// set flags with chars
				_flags.at((std::size_t)(*pos)) = true;
				++pos;
			}
		}
		++argv;
	}
}

////==--------------------------------------------------------------------====//
// COMMANDLINE FLAGS SET FLAG
// CommandlineFlags::set_flag(const char **argv)
//====--------------------------------------------------------------------==////
void CommandlineFlags::set(const char &ch, const bool &flag) {
	_flags.at((std::size_t)ch) = flag;
}

////==--------------------------------------------------------------------====//
// COMMANDLINE FLAGS GET FLAG
// CommandlineFlags::get(const char &ch) const
//====--------------------------------------------------------------------==////
bool CommandlineFlags::get(const char &ch) const{
	return _flags.at((std::size_t)ch);
}
