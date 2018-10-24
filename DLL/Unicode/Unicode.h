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
����һ������Unicode����Ŀ(exe����)��ʵ�����¹���
1).char* �� wchar_t*��ת����wchar_t * �� char *��ת����
2).CString �� TCHAR*��ת����TCHAR* ��CString��ת����
3).std::string/ std::wstring �� TCHAR*��ת����
4).TCHAR* ��std::string/ std::wstring��ת����
5).CStringA �� CString��ת����CString �� CStringA��ת����
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

	//3 std::string/ std::wstring �� TCHAR*��ת��
	TCHAR* stringToTCHAR(const std::string& str);
	TCHAR* wtringToTCHAR(const std::wstring& str);

	//4 TCHAR* ��std::string/ std::wstring��ת����
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