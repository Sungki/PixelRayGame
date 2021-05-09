#pragma once

#include <exception>

#include <EGL/egl.h>

namespace PixelRay
{
	namespace Platform
	{
		namespace Windows
		{
			namespace Graphics
			{
				enum class EGLViewCreateErrorType
				{
					kSuccess = 0,

					kNoEGLDisplay = 1,
					kDisplayInitializeFail = 2,

					kEGLVersionNotSupport = 11,
					kEGLConfigNotExists = 12,

					kSurfaceCreateFail = 21,
					kContextCreateFail = 22,

					kCurrentMakeFail = 31,
				};


				class EGLViewCreateFailException : public std::exception
				{
				public:
					EGLViewCreateFailException(EGLViewCreateErrorType error, EGLint eglError);
					virtual ~EGLViewCreateFailException() throw() { }

				public:
					EGLViewCreateErrorType	error;
					EGLint					eglError;
				};
			}
		}
	}
}
