#include "EGLView.h"

//#include "WinPCGLException.h"
//#include "WinPCGLThreadContext.h"


namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			namespace Graphics
			{
				EGLView::EGLView(const HWND& windowHWnd)
				{
					m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
				}

				//------------------------------------------------------------------------------
				EGLView::~EGLView()
				{
					eglTerminate(m_eglDisplay);
				}

				//------------------------------------------------------------------------------
				void EGLView::SwapBuffers()
				{
					eglSwapBuffers(m_eglDisplay, m_eglSurface);
				}
			}
		}
	}
}
