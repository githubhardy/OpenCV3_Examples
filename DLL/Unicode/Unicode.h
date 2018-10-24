#pragma once
#include <iostream>
#include <string>
#include <tchar.h>
#include <afx.h>    

#ifndef TSTRING
#define TSTRING
namespace std
{
#ifdef _UNICODE
	typedef wstring tstring;
#define tcout wcout
#else
	typedef string tstring;
#define tcout cout
#endif
}
#endif // !TSTRING

/*
9.
建立一个基于Unicode的项目(exe类型)，实现以下功能
1).char* 到 wchar_t*的转换；wchar_t * 到 char *的转换；
2).CString 到 TCHAR*的转换；TCHAR* 到CString的转换；
3).std::string/ std::wstring 到 TCHAR*的转换；
4).TCHAR* 到std::string/ std::wstring的转换；
5).CStringA 到 CString的转换；CString 到 CStringA的转换；
*/

class  CommonTool {
public:
	CommonTool();
	virtual ~CommonTool();


	wchar_t* Towchar(wchar_t* chDes, const char* chSrc);
	TCHAR* charToTCHAR(TCHAR* pTchDest, const char* chSrc);

	//(1)char* ---- wchar_t*
	char* Tochar(char* chDes, const wchar_t* wchSrc);
	wchar_t* charTowchar(wchar_t* pWchDest, const char* wchSrc);
	wchar_t* Towchar_t(wchar_t* wchDes, const wchar_t* wchSrc, size_t srcSize);
	char* wcharTochar(char* pChDest, const wchar_t* wchSrc);

	//(2)CString ---- TCHAR*
	char* CStringTochar(char* pch, CString& cs);
	CString charToCString(const char* chSrc);
	wchar_t* CStringTowchar(wchar_t* pwch, CString& cs);
	CString wcharToCString(const wchar_t* wchSrc);
	wchar_t* TCHARTtowchar(wchar_t* pWchDest, const TCHAR* twchSrc);

	TCHAR* CStringToTCHAR(TCHAR* PTCHAR, CString& cs);
	CString TCHARToCString(const TCHAR* PTCHARSrc);

	//3 std::string/ std::wstring 到 TCHAR*的转换
	TCHAR* stringToTCHAR(const std::string& str);
	TCHAR* wtringToTCHAR(const std::wstring& str);

	//4 TCHAR* 到std::string/ std::wstring的转换；
	std::string TCHARTostring(const TCHAR* PTCHARSrc);
	std::wstring TCHARTowstring(const TCHAR* PTCHARSrc);

	//(5)  CString --- CStringA
	CStringA CStringToCStringA(const CString& cstr) const;
	CString CStringAToCString(const CStringA& cstrA) const;

	char* m_pchChar;
	wchar_t* m_pwchWchar;
private:
	const int INIT_SIZE = 255;

};