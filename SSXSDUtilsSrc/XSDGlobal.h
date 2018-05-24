#pragma once

#ifdef _EXPORTING_SSXSDUtils
#define _EXPORTING
#define SSXSDUtils_API_DECLSPEC __declspec(dllexport)
#else
#define _IMPORTING
#define SSXSDUtils_API_DECLSPEC __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib, "SSXSDUtilsd.lib")
#else
#pragma comment(lib, "SSXSDUtils.lib")
#endif
#endif
