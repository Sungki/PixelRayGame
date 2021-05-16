#pragma once

//#include <Basic/LeggieroBasic.h>

#include "../WindowsCommon.h"

namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			class IWindowEventObserver
			{
			public:
				virtual ~IWindowEventObserver() { };

			public:
				virtual bool HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return false; }
				virtual void OnDestoryed(HWND hWnd) { }
			};
		}
	}
}