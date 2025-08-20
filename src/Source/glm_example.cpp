#include "glm_example.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace twiz_examples {
void show_glm() {
    glm::vec3 v(1.0f, 2.0f, 3.0f);
    std::cout << "GLM vec3: " << v.x << ", " << v.y << ", " << v.z << std::endl;

    glm::vec3 u(4.0f, 5.0f, 6.0f);
    glm::vec3 sum = v + u;
    std::cout << "Sum: " << sum.x << ", " << sum.y << ", " << sum.z << std::endl;

    glm::vec3 cross = glm::cross(v, u);
    std::cout << "Cross product: " << cross.x << ", " << cross.y << ", " << cross.z << std::endl;

    float dot = glm::dot(v, u);
    std::cout << "Dot product: " << dot << std::endl;

    glm::mat4 mat = glm::mat4(1.0f);
    glm::mat4 trans = glm::translate(mat, glm::vec3(10.0f, 0.0f, 0.0f));
    std::cout << "Translated matrix[3]: " << trans[3].x << ", " << trans[3].y << ", " << trans[3].z << std::endl;

    glm::vec3 normalized = glm::normalize(v);
    std::cout << "Normalized v: " << normalized.x << ", " << normalized.y << ", " << normalized.z << std::endl;
}
}
