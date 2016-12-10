// COMMANDLINE FLAGS
// (C) 2015-2016 Yuishin Kikuchi

#ifndef _CLASS_COMMANDLINE_FLAGS_H_
#define _CLASS_COMMANDLINE_FLAGS_H_

#include <array>

class CommandlineFlags {
	private:
		std::array<bool, 256> _flags;
	public:
		CommandlineFlags();
		CommandlineFlags(char **argv);
		void init();
		void read_flags(char **argv);
		void set(const char &ch, const bool &flag);
		bool get(const char &ch) const;
};

#endif // _CLASS_COMMANDLINE_FLAGS_H_
