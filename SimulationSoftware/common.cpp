
#include "stdafx.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString GetExPath()
{
	TCHAR szPath[MAX_PATH];
	::GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strPath = szPath;
	int index = strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index + 1);

	return strPath;
}