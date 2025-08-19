#include "Examples/glad.h"
#include <cstdio>
#include <glad/gl.h>

namespace Twiz
{
    void ShowGlad()
    {
        printf("Glad loaded: %d\n", GL_TRUE);
    }

    void ShowGlVersion()
    {
        printf("GL Version: %s\n", glGetString(GL_VERSION));
    }

    void ShowGlRenderer()
    {
        printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
    }

    void ShowGlVendor()
    {
        printf("GL Vendor: %s\n", glGetString(GL_VENDOR));
    }

    void ShowGlShadingLanguageVersion()
    {
        printf("GL Shading Language Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    }
} // namespace Twiz
