#pragma once

#include <EGL/egl.h>

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
					EGLDisplay m_eglDisplay;
					EGLSurface m_eglSurface;
					EGLContext m_eglContext;
				};
			}
		}
	}
}

