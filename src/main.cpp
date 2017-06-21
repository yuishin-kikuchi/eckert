////==--------------------------------------------------------------------====//
//============================================================================//
//           Engineering Calculator with KEyboard and Refined Tools
//                                 - ECKERT -
//                      (C) 2014-2017   Yuishin Kikuchi
//============================================================================//
//====--------------------------------------------------------------------==////

#include "main.h"
#include "calc/EckertCui.h"
#include "com/CommandlineFlags.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

static const unsigned int BREAK_LINES = 5;

int main(int argc, char **argv) {
	////==--------
	// Variable declarations
	//====--------
	CommandlineFlags clf(argv);  // debug flags
	bool to_clear = true;        // clear screen flag
	bool output_as_json = false; // json flag
	bool normal_end = false;     // normal end flag
	bool abnormal_end = false;   // abnormal end flag
	std::string input;           // keyboard input
	EckertCui eckertCui;         // core program
	////==--------
	// Initialize
	//====--------
	if (clf.get('D') || clf.get('d')) {
		// if both flag 'D' and 'd' are unset, rewrite console
		to_clear = false;
	}
	if (clf.get('j') || clf.get('J')) {
		// json flag
		output_as_json = true;
	}
	////==--------
	// Default display
	//====--------
	if (!output_as_json) {
		eckertCui.loadConfig();
		eckertCui.showConfig();
		// Default output
		for (;;) {
			// unconditional loop
			normal_end = eckertCui.isEnd();
			abnormal_end = eckertCui.isFatal();
			if (normal_end || abnormal_end) {
				// break if end flag or fatal flag is set
				break;
			}
			if (to_clear) {
				if (0 != std::system(CLEAR_SCREEN)) {
					for (unsigned ucnt = 0; ucnt < BREAK_LINES; ++ucnt) {
						std::cout << '\n';
					}
				}
			}
			eckertCui.display();
			std::cout << "> ";
			std::getline(std::cin, input);
			if (std::cin.good()) {
				eckertCui.operate(input);
			}
			else {
				abnormal_end = true;
				break;
			}
		}
	}
	////==--------
	// JSON output
	//====--------
	else {
		std::cout << "json" << std::endl;
		bool inst_exists = false;
		int inst_start_at = 0;
		for (int cnt = 0; cnt < argc; ++cnt) {
			if (!strncmp(argv[cnt], "--", 2)) {
				// `+ 1` means the next index of "--"
				inst_start_at = cnt + 1;
				if (inst_start_at < argc) {
					inst_exists = true;
					break;
				}
			}
		}
		if (inst_exists) {
			for (int cnt = inst_start_at; cnt < argc; ++cnt) {
				eckertCui.operate(argv[cnt]);
				if (eckertCui.isFatal()) {
					abnormal_end = true;
					goto EXIT;
				}
			}
		}
		else {
			abnormal_end = true;
			goto EXIT;
		}
		std::cerr << '\n';
		if (to_clear) {
			// -j option means json file output
			std::cerr << "JSON OUTPUT" << std::endl;
			if (eckertCui.outputJson()) {
				// if the return value is true, output failed
				std::cerr << "[!] OUTPUT FAILED" << std::endl;
				abnormal_end = true;
				goto EXIT;
			}
			else {
				// succeed to output file
				std::cerr
					<< "out: "
					<< eckertCui.getJsonFilename()
					<< std::endl;
			}
		}
		else {
			// -jd option means json output to standard error
			eckertCui.displayAsJson();
		}
		normal_end = true;
	}
	////==--------
	// End process
	//====--------
EXIT:
	if (normal_end) {
		return EXIT_SUCCESS;
	}
	else if (abnormal_end) {
		std::cerr << "ECKERT terminated by fatal error" << std::endl;
		getchar();
		return EXIT_FAILURE;
	}
	else {
		std::cerr << "ECKERT terminated" << std::endl;
		getchar();
		return EXIT_FAILURE;
	}
}
