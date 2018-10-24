// Unicode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Unicode.h"
using namespace std;



CommonTool::CommonTool()
{
	m_pchChar = new char[INIT_SIZE];
	m_pwchWchar = new(std::nothrow) wchar_t[INIT_SIZE];
}

CommonTool::~CommonTool()
{
	if (nullptr != m_pchChar)
	{
		delete[] m_pchChar;
		m_pchChar = nullptr;
	}
	if (nullptr != m_pwchWchar)
	{
		delete[] m_pwchWchar;
		m_pwchWchar = nullptr;
	}
}

wchar_t* CommonTool::Towchar(wchar_t* chDes, const char* chSrc)
{
	setlocale(LC_ALL, "chs");
	size_t nDestSize;
	mbstowcs_s(&nDestSize, nullptr, 0, chSrc, 0);
	wchar_t* pDes;
	pDes = m_pwchWchar;
	size_t nTempSize;
	mbstowcs_s(&nTempSize, pDes, nDestSize, chSrc, nDestSize);
	setlocale(LC_ALL, "C");
	return pDes;
}


//char -- wchar (Towchar)
wchar_t* CommonTool::charTowchar(wchar_t* pWchDest, const char* wchSrc)
{
	return Towchar(pWchDest, wchSrc);
}

char* CommonTool::Tochar(char* chDes, const wchar_t* wchSrc)
{
	setlocale(LC_ALL, "chs");
	size_t nDestSize;
	//一定要记得第一个参数时 size_t类型，若果用int类型是不行的
	wcstombs_s(&nDestSize, nullptr, 0, wchSrc, 0);  //这个主要是超过255调用MEMRENew的时候做判断的，
													//主要是为了获取src的Size而已
	char* pDes;
	size_t nTempSize = 0;
	if (nullptr == chDes)
	{
		pDes = m_pchChar;//m_pchChar 是255字节的
	}
	else
	{
		pDes = chDes;
	}
	wcstombs_s(&nTempSize, pDes, nDestSize, wchSrc, nDestSize);
	setlocale(LC_ALL, "C");
	return pDes;
}
// wchar_t---- char(tochar)
char* CommonTool::wcharTochar(char* pChDest, const wchar_t* wchSrc)
{
	return Tochar(pChDest, wchSrc);
}

TCHAR* CommonTool::charToTCHAR(TCHAR* pTchDest, const char* chSrc)
{
#ifdef _UNICODE  //wchar
	wchar_t* pWcharDest = pTchDest;
	return Towchar(pWcharDest, chSrc);
#else //char
	return const_cast<char *> (chSrc);
#endif
}

wchar_t* CommonTool::TCHARTtowchar(wchar_t* pWchDest, const TCHAR* twchSrc)
{
#ifdef _UNICODE
	const wchar_t* _wchartemp = twchSrc;
	return const_cast<wchar_t *> (_wchartemp);
#else
	return charTowchar(pWchDest, twchSrc);
#endif // _UNICODE

}

//////
wchar_t* CommonTool::Towchar_t(wchar_t* wchDes, const wchar_t* wchSrc, size_t srcSize)
{
	wchar_t* pDes;
	if (nullptr == wchDes)
	{
		pDes = m_pwchWchar;
	}
	else
	{
		pDes = wchDes;
	}
	wcscpy_s(pDes, srcSize + 1, wchSrc);
	return pDes;
}

wchar_t* CommonTool::CStringTowchar(wchar_t* pwch, CString& cs)
{
#ifdef _UNICODE
	return Towchar_t(pwch, cs.GetBuffer(), cs.GetLength());
#else
	return charTowchar(pwch, cs.GetBuffer());
#endif
}

CString CommonTool::wcharToCString(const wchar_t* wchSrc)
{
#ifdef _UNICODE
	CString cs(wchSrc);
	return cs;
#else
	CString cs(wcharTochar(nullptr, wchSrc));
	return cs;
#endif
}

char* CommonTool::CStringTochar(char* pch, CString& cs)
{
#ifdef _UNICODE
	return wcharTochar(pch, cs.GetBuffer());
#else
	return Tochar(pch, cs.GetBuffer(), cs.GetLength());
#endif
}

CString CommonTool::charToCString(const char* chSrc)
{
#ifdef _UNICODE
	CString cs(charTowchar(nullptr, chSrc));
	return cs;
#else
	CString cs(chSrc);
	return cs;
#endif
}


// 3 std::string/ std::wstring 到 TCHAR*的转换；
TCHAR* CommonTool::stringToTCHAR(const std::string& str) 
{
#ifdef _UNICODE  //wchar_*

	return charTowchar(nullptr, str.c_str());
#else 
	return const_cast<char *>(str.c_str());
#endif
}

TCHAR* CommonTool::wtringToTCHAR(const std::wstring& str)
{
#ifdef _UNICODE  //wchar_t*
	return const_cast<wchar_t *>(str.c_str());
#else  //char
	return wcharTochar(nullptr, str.c_str());
#endif
}

//4 TCHAR* 到std::string/ std::wstring的转换；
string CommonTool::TCHARTostring(const TCHAR* PTCHARSrc) 
{
#ifdef _UNICODE  //wchar_t* -- char* --string
	std::string temp(wcharTochar(nullptr, PTCHARSrc));
	return temp;
#else  //char --string 
	std::string temp(PTCHARSrc);
	return temp;
#endif
}
wstring CommonTool::TCHARTowstring(const TCHAR* PTCHARSrc) 
{
#ifdef _UNICODE  //wchar_t* -- wstring
	std::wstring temp(PTCHARSrc);
	return temp;

#else  //char - wchar_t* -- wstring 
	std::wstring temp(chartowchar(nullptr, PTCHARSrc););
	return temp;
#endif
}

//(5)CString ----CStringA
CStringA CommonTool::CStringToCStringA(const CString& cstr) const
{
#ifdef _UNICODE
	CStringA cstrA(cstr);
	return cstrA;
#else
	return cstr;
#endif
}

CString CommonTool::CStringAToCString(const CStringA& cstrA) const
{
#ifdef _UNICODE
	CString cstr(cstrA);
	return cstr;
#else
	return cstrA;
#endif
}



TCHAR* CommonTool::CStringToTCHAR(TCHAR* pTCHAR, CString& cs)
{
#ifdef _UNICODE
	return CStringTowchar(pTCHAR, cs);
#else
	return CStringTochar(pTCHAR, cs);
#endif
}

CString CommonTool::TCHARToCString(const TCHAR* PTCHARSrc)
{
#ifdef _UNICODE
	return wcharToCString(PTCHARSrc);
#else
	return charToCString(PTCHARSrc);
#endif
}


/*
9.
建立一个基于Unicode的项目(exe类型)，实现以下功能
1).char* 到 wchar_t*的转换；wchar_t * 到 char *的转换；
2).CString 到 TCHAR*的转换；TCHAR* 到CString的转换；
3).std::string/ std::wstring 到 TCHAR*的转换；
4).TCHAR* 到std::string/ std::wstring的转换；
5).CStringA 到 CString的转换；CString 到 CStringA的转换；
*/



int main()
{
	//支持中文
	std::locale loc = std::locale("");
	std::locale::global(loc);
	wcout.imbue(locale(locale(), "", LC_CTYPE));
	CommonTool tool;

	//1   char* --- wchar_t*
	wchar_t *wch1 = tool.charTowchar(nullptr, "（1）测试 char* to wchar*");
	char * ch2 = tool.wcharTochar(nullptr, L"测试 wchar* to char*");
	wcout << wch1 << endl;
	cout << ch2 << endl;

	//2   CString ---- TCHAR*
	CString cstr81(tool.TCHARToCString(_T("（2）测试  TCHAR* to CString")));
	tcout << cstr81.GetString() << endl;
	CString s1 = _T("测试 CString to TCHAR*");
	TCHAR* ch82 = tool.CStringToTCHAR(nullptr, s1);
	tcout << ch82 << endl;
	
	//3 std::string/ std::wstring --- TCHAR*
	string str22 = ("（3）测试 string to TCHAR*");
	tcout << tool.stringToTCHAR(str22) << endl;
	wstring wstr22 = _T("测试 wstring to TCHAR*");
	tcout << tool.wtringToTCHAR(wstr22)<<endl;
	

	//4 TCHAR* 到std::string/ std::wstring的转换；
	TCHAR* test1 = _T("（4）测试 TCHAR* TO string");
	TCHAR* test2 = _T("测试 TCHAR* TO wstring");
	std::string str11 = tool.TCHARTostring(test1);
	cout << str11 << endl;
	std::wstring str12 = tool.TCHARTowstring(test2);
	wcout << str12 << endl;


	//5  CStringA --- CString
	CString cstr1 = _T("（5）测试 CStringToCStringA 测试1");
	CStringA& cstrA1 = tool.CStringToCStringA(cstr1);
	cout << cstrA1.GetString() << endl;

	CStringA cstrA2 = "测试 CStringAToCString 测试2";
	CString& cstr2 = tool.CStringAToCString(cstrA2);
	wcout << cstr2.GetString() << endl;

	system("pause");
    return 0;
}

