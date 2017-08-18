#pragma once
#include <cstring>

class AStr
{
public:
	AStr(const char* str,bool bUtf8);
	~AStr();

public:
	const char* toUtf8() const;
	const char* toAnsi() const;
	const wchar_t* toWchar() const;

private:
	char* _ansi;
	char* _utf8;
	wchar_t* _wchar;

private:
	AStr(const AStr&){};
	AStr(){};
};
