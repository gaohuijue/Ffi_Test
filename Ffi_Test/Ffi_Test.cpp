#include "stdafx.h"
#include "Ffi_Test.h"
#include <string>
#include <stdio.h>
#include <sstream>
#include <windows.h>
using namespace std;

wchar_t * say_hello()
{
	return (wchar_t*)u8"Hello world你好，世界！";
}

static Listener listeners[16];
static unsigned cursor=0;

void register_listener(Listener listener) {
	if (cursor >= sizeof(listeners)/sizeof(*listeners)) {
		stringstream ss;
		ss << u8"最多注册"<< sizeof(listeners) / sizeof(*listeners) << u8"个监听器";
		throw ss.str();
	}
	listeners[cursor] = listener;
	cursor++;
}

void notify(Listener l) {
	l((char*)u8"张三", (char*)"12342134x");
}

void fire() {
	for (unsigned i = 0; i < cursor; i++) {
		notify(listeners[i]);
	}
}

void CALLBACK TimerProc(HWND, UINT, UINT, DWORD);

//TODO 定时器要另开一个线程，否则卡死

int count_mem = 20;
void start_timer() {
	UINT id;
	MSG msg;

	id = SetTimer(NULL, 0, 300, (TIMERPROC)TimerProc);

	while (count_mem>0)
	{
		GetMessage(&msg, NULL, 0, 0);
		DispatchMessage(&msg);
	}

	KillTimer(NULL, id);
}

void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	for (unsigned i = 0; i < cursor; i++) {
		notify(listeners[i]);
	}
	count_mem--;
}
