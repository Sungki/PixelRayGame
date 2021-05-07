#pragma once


//#include <Basic/LeggieroBasic.h>

#include "../WindowsCommon.h"


namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			struct WindowCreateParam
			{
				HINSTANCE	hInstance;
				HWND		hWndParent;

				LPCTSTR		className;
				LPCTSTR		windowName;

				int			nCmdShow;

				LPCTSTR		menuName;
				HMENU		hMenu;

				UINT		classStyle;
				DWORD		windowStyle;

				int			x;
				int			y;
				int			width;
				int			height;
				bool		isSetContentsSize;

				HBRUSH		hbrBackground;
				HICON		hIcon;
				HICON		hIconSm;
				HCURSOR		hCursor;

				LPVOID		lpParam;

				WindowCreateParam()
					: hInstance(NULL)
					, hWndParent(NULL)
					, className(L"PixelRayGame")
					, windowName(L"")
					, nCmdShow(SW_SHOWNORMAL)
					, menuName(NULL), hMenu(NULL)
					, classStyle(0), windowStyle(WS_OVERLAPPEDWINDOW)
					, x(CW_USEDEFAULT), y(CW_USEDEFAULT)
					, width(CW_USEDEFAULT), height(CW_USEDEFAULT), isSetContentsSize(false)
					, hbrBackground(NULL)
					, hIcon(NULL), hIconSm(NULL)
					, hCursor(NULL)
					, lpParam(NULL)
				{
				}
			};
		}
	}
}