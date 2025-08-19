#include "Examples/opengl.h"
#include <GL/gl.h>
#include <iostream>
namespace Twiz
{
    void OpenglDemo()
    {
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
    }
} // namespace Twiz
