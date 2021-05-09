#include "WinPCGLException.h"


namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			namespace Graphics
			{
				EGLViewCreateFailException::EGLViewCreateFailException(EGLViewCreateErrorType error, EGLint eglError)
					: std::exception("Failed to create EGL View")
					, error(error)
					, eglError(eglError)
				{
				}
			}
		}
	}
}
