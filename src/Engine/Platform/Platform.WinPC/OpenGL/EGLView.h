#pragma once

#include "../WindowsCommon.h"

namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			namespace Graphics
			{
				class EGLView
				{
				public:
					EGLView(const HWND& windowHWnd);
					virtual ~EGLView();

				public:
					void SwapBuffers();

				private:
				};
			}
		}
	}
}

