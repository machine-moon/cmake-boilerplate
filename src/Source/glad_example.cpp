#include "glad_example.h"
#include <glad/gl.h>
#include <stdio.h>

namespace twiz_examples
{
void show_glad()
{
    printf("Glad loaded: %d\n", GL_TRUE);
}

void show_gl_version()
{
    printf("GL Version: %s\n", glGetString(GL_VERSION));
}

void show_gl_renderer()
{
    printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
}

void show_gl_vendor()
{
    printf("GL Vendor: %s\n", glGetString(GL_VENDOR));
}

void show_gl_shading_language_version()
{
    printf("GL Shading Language Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}
} // namespace twiz_examples
