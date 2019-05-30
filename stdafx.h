// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//Warnings disabled:
//1. " assignment operator could not be generated "
#pragma warning(disable:4512)
//2. "nonstandard extension used : nameless struct/union @ mmsystem.h
#pragma warning(disable:4201)
//3. Engine@tree3Dobject, controllemanager,...: unreferred formal paramater
#pragma warning(disable:4100)
//4. expatpp.h conditional expression is constant
#pragma warning(disable:4127)
//5. FMOD_ErrorString : unreferenced local function been removed
#pragma warning(disable:4505)
//6. Het gebruik van de functie localtime - fopen - asctime "unsave"?
#pragma warning(disable:4996)
//7. ergens een rare release build warning.. "/GS can not protect parameters & local vars from local buffer overrun because optimizations are disabled in function"
#pragma warning(disable:4748)
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define NOMINMAX




// TODO: reference additional headers your program requires here
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <tchar.h>


using namespace std;
#ifdef _UNICODE	// extra unicode defines
	#define tstring wstring
	#define tcin wcin
	#define tcout wcout
	#define tstringstream wstringstream
	#define tofstream wofstream
	#define tifstream wifstream
	#define tfstream wfstream
	#define tstrtod	wcstod
#else
	#define tstring string
	#define tcin cin
	#define tcout cout
	#define tstringstream stringstream
	#define tofstream ofstream
	#define tifstream ifstream
	#define tfstream fstream
	#define	tstrtod strtod
#endif

// ASSERT macro

#ifndef NDEBUG
#define ASSERT \
	if ( false ) {} \
else \
struct LocalAssert { \
	int mLine; \
	LocalAssert(int line=__LINE__) : mLine(line) {} \
	LocalAssert(bool isOK, const TCHAR* message=_T("")) { \
	if ( !isOK ) { \
	tstringstream buffer; \
	buffer << _T("ERROR!! Assert failed on line ") << LocalAssert().mLine << _T(" in file '") << __FILE__ << _T("'\nBoodschap: \"") << message << _T("\"\n"); \
	OutputDebugString(buffer.str().c_str()); \
	__asm { int 3 } \
	} \
} \
} myAsserter = LocalAssert
#else
#define ASSERT \
	if ( true ) {} else \
struct NoAssert { \
	NoAssert(bool isOK, const TCHAR* message=_T("")) {} \
} myAsserter = NoAssert
#endif


//===============================================================
// Clean up

#define ReleaseCOM(x) { if(x){ x->Release();x = 0; } }
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)  { if(p!=0) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p!=0) { (p)->Release(); (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif  

//===============================================================
// Debug

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                      \
	{                                                  \
		HRESULT hr = x;                                \
		if(FAILED(hr))                                 \
		{                                              \
			DXTrace(__FILE__, __LINE__, hr, _T(#x), TRUE); \
		}                                              \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) x;
	#endif
#endif 

#define DLLEXPORT __declspec(dllexport)