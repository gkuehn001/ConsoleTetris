#pragma once
class CDebug
{
public:
	CDebug();
	~CDebug();

	static void Render();
	static void Output();
	static void SetDebugOutput(const char* szFormat, ...);

	static char szBuff[1024];
};

