#include "stdafx.h"
#include "Debug.h"
#include "Windows.h"
#include <curses.h>

char CDebug::szBuff[1024];

CDebug::CDebug()
{
}


CDebug::~CDebug()
{
}

void CDebug::Render()
{
	mvaddstr(0, 0, szBuff);
}

void CDebug::Output()
{
	OutputDebugString(szBuff);
}

void CDebug::SetDebugOutput(const char * szFormat, ...)
{
	va_list arg;
	va_start(arg, szFormat);
	_vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
	va_end(arg);
}
