#ifndef _ECKERT_CUI_MAIN_
#define _ECKERT_CUI_MAIN_

#if defined(_WIN32) || defined(WIN64)
const char *CLEAR_SCREEN = "cls";
#elif defined(__linux__) || defined(__CYGWIN__)
const char *CLEAR_SCREEN = "clear";
#else
const char *CLEAR_SCREEN = nullptr;
#endif // defined(_WIN32) || defined(WIN64)

#endif // ifndef _ECKERT_CUI_MAIN_
