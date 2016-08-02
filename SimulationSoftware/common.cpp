
#include "stdafx.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



//void InitCISCorrectionTable() {
//	for (int side = 0; side < CIS_COUNT; side++) {
//		for (int color = 0; color < COLOR_COUNT; color++) {
//			for (int x = 0; x < CIS_IMAGE_WIDTH; x++) {
//				for (int level = 0; level < 256; level++) {
//					cisTalble.data[side][color][x][level] = level;
//				}
//			}
//		}
//	}
//}

CString GetExPath()
{
	TCHAR szPath[MAX_PATH];
	::GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strPath = szPath;
	int index = strPath.ReverseFind(_T('\\'));
	strPath = strPath.Left(index + 1);

	return strPath;
}