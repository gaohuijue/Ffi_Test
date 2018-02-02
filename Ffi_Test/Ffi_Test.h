#pragma once

#ifdef FFITEST_EXPORTS
#define FFITEST_API __declspec(dllexport)
#else
#define FFITEST_API __declspec(dllimport)
#endif


typedef int(*Listener)(char* name, char* code);

extern "C" FFITEST_API wchar_t * say_hello();
extern "C" FFITEST_API void register_listener(Listener listener);
extern "C" FFITEST_API void fire();
