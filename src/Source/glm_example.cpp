#define GLM_ENABLE_EXPERIMENTAL
#include "glm_example.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <vector>

namespace twiz
{

void print_matrix(const glm::mat4& matrix, const std::string& name)
{
    std::cout << name << ":\n";
    for (int i = 0; i < 4; ++i)
    {
        std::cout << "  ";
        for (int j = 0; j < 4; ++j)
        {
            printf("%8.3f ", matrix[j][i]);
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void print_vec3(const glm::vec3& vec, const std::string& name)
{
    printf("%s: [%7.3f, %7.3f, %7.3f]\n", name.c_str(), vec.x, vec.y, vec.z);
}

void show_glm()
{
    std::cout << "\n=== GLM MATHEMATICS SHOWCASE ===" << std::endl;
    std::cout << "OpenGL Mathematics Library for graphics programming" << std::endl;
    std::cout << "Perfect for 3D graphics, transformations, and linear algebra\n" << std::endl;
}

void matrix_transformations_demo()
{
    std::cout << "\n--- Matrix Transformations Demo ---" << std::endl;

    glm::mat4 identity = glm::mat4(1.0f);
    print_matrix(identity, "Identity Matrix");

    glm::vec3 translation(5.0f, 3.0f, -2.0f);
    glm::mat4 translate_matrix = glm::translate(identity, translation);
    print_matrix(translate_matrix, "Translation Matrix");

    float angle = glm::radians(45.0f);
    glm::vec3 rotation_axis(0.0f, 1.0f, 0.0f);
    glm::mat4 rotation_matrix = glm::rotate(identity, angle, rotation_axis);
    print_matrix(rotation_matrix, "Rotation Matrix (45° around Y)");

    glm::vec3 scale_factors(2.0f, 1.5f, 0.8f);
    glm::mat4 scale_matrix = glm::scale(identity, scale_factors);
    print_matrix(scale_matrix, "Scale Matrix");

    glm::mat4 combined = translate_matrix * rotation_matrix * scale_matrix;
    print_matrix(combined, "Combined Transformation (T * R * S)");

    glm::vec3 test_point(1.0f, 0.0f, 0.0f);
    glm::vec4 transformed = combined * glm::vec4(test_point, 1.0f);
    print_vec3(glm::vec3(transformed), "Transformed Point");
}

void vector_math_operations_demo()
{
    std::cout << "\n--- Vector Math Operations Demo ---" << std::endl;

    glm::vec3 a(3.0f, 4.0f, 0.0f);
    glm::vec3 b(1.0f, 2.0f, 5.0f);

    print_vec3(a, "Vector A");
    print_vec3(b, "Vector B");

    glm::vec3 sum = a + b;
    print_vec3(sum, "A + B");

    glm::vec3 difference = a - b;
    print_vec3(difference, "A - B");

    float dot_product = glm::dot(a, b);
    std::cout << "Dot Product (A · B): " << dot_product << std::endl;

    glm::vec3 cross_product = glm::cross(a, b);
    print_vec3(cross_product, "Cross Product (A × B)");

    float length_a = glm::length(a);
    float length_b = glm::length(b);
    std::cout << "Length of A: " << length_a << std::endl;
    std::cout << "Length of B: " << length_b << std::endl;

    glm::vec3 normalized_a = glm::normalize(a);
    glm::vec3 normalized_b = glm::normalize(b);
    print_vec3(normalized_a, "Normalized A");
    print_vec3(normalized_b, "Normalized B");

    float distance = glm::distance(a, b);
    std::cout << "Distance between A and B: " << distance << std::endl;

    float angle = glm::acos(glm::dot(normalized_a, normalized_b));
    std::cout << "Angle between A and B: " << glm::degrees(angle) << "°" << std::endl;

    glm::vec3 lerp_result = glm::mix(a, b, 0.5f);
    print_vec3(lerp_result, "Linear Interpolation (50%)");
}

void quaternion_rotations_demo()
{
    std::cout << "\n--- Quaternion Rotations Demo ---" << std::endl;

    glm::quat identity_quat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    std::cout << "Identity Quaternion: [w:" << identity_quat.w << ", x:" << identity_quat.x
              << ", y:" << identity_quat.y << ", z:" << identity_quat.z << "]" << std::endl;

    float pitch = glm::radians(30.0f);
    float yaw = glm::radians(45.0f);
    float roll = glm::radians(15.0f);

    glm::quat pitch_quat = glm::angleAxis(pitch, glm::vec3(1, 0, 0));
    glm::quat yaw_quat = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
    glm::quat roll_quat = glm::angleAxis(roll, glm::vec3(0, 0, 1));

    glm::quat combined_rotation = yaw_quat * pitch_quat * roll_quat;
    std::cout << "Combined Rotation Quaternion: [w:" << combined_rotation.w
              << ", x:" << combined_rotation.x << ", y:" << combined_rotation.y
              << ", z:" << combined_rotation.z << "]" << std::endl;

    glm::mat4 rotation_matrix = glm::mat4_cast(combined_rotation);
    print_matrix(rotation_matrix, "Quaternion to Matrix Conversion");

    glm::vec3 euler_angles = glm::eulerAngles(combined_rotation);
    std::cout << "Euler Angles (radians): [" << euler_angles.x << ", " << euler_angles.y << ", "
              << euler_angles.z << "]" << std::endl;
    std::cout << "Euler Angles (degrees): [" << glm::degrees(euler_angles.x) << ", "
              << glm::degrees(euler_angles.y) << ", " << glm::degrees(euler_angles.z) << "]"
              << std::endl;

    glm::vec3 forward(0.0f, 0.0f, -1.0f);
    glm::vec3 rotated_forward = combined_rotation * forward;
    print_vec3(rotated_forward, "Rotated Forward Vector");

    glm::quat q1 = glm::angleAxis(glm::radians(0.0f), glm::vec3(0, 1, 0));
    glm::quat q2 = glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0));

    for (float t = 0.0f; t <= 1.0f; t += 0.25f)
    {
        glm::quat interpolated = glm::slerp(q1, q2, t);
        glm::vec3 interpolated_angles = glm::eulerAngles(interpolated);
        std::cout << "SLERP t=" << t << ": Y rotation = " << glm::degrees(interpolated_angles.y)
                  << "°" << std::endl;
    }
}

void projection_matrices_demo()
{
    std::cout << "\n--- Projection Matrices Demo ---" << std::endl;

    float fov = glm::radians(75.0f);
    float aspect_ratio = 16.0f / 9.0f;
    float near_plane = 0.1f;
    float far_plane = 100.0f;

    glm::mat4 perspective_matrix = glm::perspective(fov, aspect_ratio, near_plane, far_plane);
    print_matrix(perspective_matrix, "Perspective Projection Matrix");

    float left = -10.0f, right = 10.0f;
    float bottom = -10.0f, top = 10.0f;
    float ortho_near = 0.1f, ortho_far = 100.0f;

    glm::mat4 orthographic_matrix = glm::ortho(left, right, bottom, top, ortho_near, ortho_far);
    print_matrix(orthographic_matrix, "Orthographic Projection Matrix");

    glm::vec3 eye(0.0f, 5.0f, 10.0f);
    glm::vec3 center(0.0f, 0.0f, 0.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    glm::mat4 view_matrix = glm::lookAt(eye, center, up);
    print_matrix(view_matrix, "View Matrix (LookAt)");

    glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, -3.0f));
    glm::mat4 mvp_matrix = perspective_matrix * view_matrix * model_matrix;
    print_matrix(mvp_matrix, "Model-View-Projection Matrix");

    glm::vec3 world_point(1.0f, 1.0f, 1.0f);
    glm::vec4 clip_space = mvp_matrix * glm::vec4(world_point, 1.0f);

    if (clip_space.w != 0.0f)
    {
        glm::vec3 ndc = glm::vec3(clip_space) / clip_space.w;
        print_vec3(ndc, "Normalized Device Coordinates");

        float viewport_width = 1920.0f;
        float viewport_height = 1080.0f;
        glm::vec2 screen_coords((ndc.x + 1.0f) * 0.5f * viewport_width,
                                (1.0f - ndc.y) * 0.5f * viewport_height);
        std::cout << "Screen Coordinates: [" << screen_coords.x << ", " << screen_coords.y << "]"
                  << std::endl;
    }
}

void geometric_calculations_demo()
{
    std::cout << "\n--- Geometric Calculations Demo ---" << std::endl;

    glm::vec3 p1(0.0f, 0.0f, 0.0f);
    glm::vec3 p2(3.0f, 4.0f, 0.0f);
    glm::vec3 p3(0.0f, 4.0f, 0.0f);

    print_vec3(p1, "Point 1");
    print_vec3(p2, "Point 2");
    print_vec3(p3, "Point 3");

    glm::vec3 v1 = p2 - p1;
    glm::vec3 v2 = p3 - p1;

    glm::vec3 triangle_normal = glm::normalize(glm::cross(v1, v2));
    print_vec3(triangle_normal, "Triangle Normal");

    float triangle_area = 0.5f * glm::length(glm::cross(v1, v2));
    std::cout << "Triangle Area: " << triangle_area << std::endl;

    glm::vec3 centroid = (p1 + p2 + p3) / 3.0f;
    print_vec3(centroid, "Triangle Centroid");

    glm::vec3 ray_origin(1.0f, 1.0f, 5.0f);
    glm::vec3 ray_direction = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));

    print_vec3(ray_origin, "Ray Origin");
    print_vec3(ray_direction, "Ray Direction");

    glm::vec3 plane_point(0.0f, 0.0f, 0.0f);
    glm::vec3 plane_normal(0.0f, 0.0f, 1.0f);

    float denom = glm::dot(plane_normal, ray_direction);
    if (std::abs(denom) > 1e-6)
    {
        float t = glm::dot(plane_point - ray_origin, plane_normal) / denom;
        if (t >= 0)
        {
            glm::vec3 intersection = ray_origin + t * ray_direction;
            print_vec3(intersection, "Ray-Plane Intersection");
            std::cout << "Intersection Distance: " << t << std::endl;
        }
    }

    glm::vec3 sphere_center(0.0f, 0.0f, 0.0f);
    float sphere_radius = 2.0f;

    glm::vec3 oc = ray_origin - sphere_center;
    float a = glm::dot(ray_direction, ray_direction);
    float b = 2.0f * glm::dot(oc, ray_direction);
    float c = glm::dot(oc, oc) - sphere_radius * sphere_radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant >= 0)
    {
        float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

        std::cout << "Ray-Sphere Intersections:" << std::endl;
        std::cout << "  t1: " << t1 << ", t2: " << t2 << std::endl;

        if (t1 >= 0)
        {
            glm::vec3 hit1 = ray_origin + t1 * ray_direction;
            print_vec3(hit1, "  First Hit Point");
        }
        if (t2 >= 0)
        {
            glm::vec3 hit2 = ray_origin + t2 * ray_direction;
            print_vec3(hit2, "  Second Hit Point");
        }
    }
}

void graphics_pipeline_3d_demo()
{
    std::cout << "\n--- 3D Graphics Pipeline Demo ---" << std::endl;

    std::vector<glm::vec3> cube_vertices = {// Front face
                                            {-1.0f, -1.0f, 1.0f},
                                            {1.0f, -1.0f, 1.0f},
                                            {1.0f, 1.0f, 1.0f},
                                            {-1.0f, 1.0f, 1.0f},
                                            // Back face
                                            {-1.0f, -1.0f, -1.0f},
                                            {-1.0f, 1.0f, -1.0f},
                                            {1.0f, 1.0f, -1.0f},
                                            {1.0f, -1.0f, -1.0f}};

    std::cout << "Original Cube Vertices:" << std::endl;
    for (size_t i = 0; i < cube_vertices.size(); ++i)
    {
        print_vec3(cube_vertices[i], "  Vertex " + std::to_string(i));
    }

    glm::mat4 model =
        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.0f, 1.5f, 1.0f));

    glm::mat4 view = glm::lookAt(glm::vec3(4.0f, 3.0f, 5.0f), // Camera position
                                 glm::vec3(0.0f, 0.0f, 0.0f), // Look at origin
                                 glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
    );

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), // FOV
                                            16.0f / 9.0f,        // Aspect ratio
                                            0.1f,                // Near plane
                                            100.0f               // Far plane
    );

    glm::mat4 mvp = projection * view * model;

    std::cout << "\nTransformed Vertices (Clip Space):" << std::endl;
    std::vector<glm::vec4> clip_vertices;

    for (size_t i = 0; i < cube_vertices.size(); ++i)
    {
        glm::vec4 clip_vertex = mvp * glm::vec4(cube_vertices[i], 1.0f);
        clip_vertices.push_back(clip_vertex);

        std::cout << "  Vertex " << i << " Clip: [" << clip_vertex.x << ", " << clip_vertex.y
                  << ", " << clip_vertex.z << ", " << clip_vertex.w << "]" << std::endl;
    }

    std::cout << "\nNormalized Device Coordinates:" << std::endl;
    std::vector<glm::vec3> ndc_vertices;

    for (size_t i = 0; i < clip_vertices.size(); ++i)
    {
        if (clip_vertices[i].w != 0.0f)
        {
            glm::vec3 ndc = glm::vec3(clip_vertices[i]) / clip_vertices[i].w;
            ndc_vertices.push_back(ndc);
            print_vec3(ndc, "  Vertex " + std::to_string(i) + " NDC");
        }
    }

    float viewport_width = 1920.0f;
    float viewport_height = 1080.0f;

    std::cout << "\nScreen Coordinates (1920x1080):" << std::endl;
    for (size_t i = 0; i < ndc_vertices.size(); ++i)
    {
        glm::vec2 screen_coords((ndc_vertices[i].x + 1.0f) * 0.5f * viewport_width,
                                (1.0f - ndc_vertices[i].y) * 0.5f * viewport_height);

        std::cout << "  Vertex " << i << " Screen: [" << screen_coords.x << ", " << screen_coords.y
                  << "]" << std::endl;
    }

    std::cout << "\nDepth Values (Z-buffer):" << std::endl;
    for (size_t i = 0; i < ndc_vertices.size(); ++i)
    {
        float depth = (ndc_vertices[i].z + 1.0f) * 0.5f;
        std::cout << "  Vertex " << i << " Depth: " << depth << std::endl;
    }
}

void run_glm_math_suite()
{
    show_glm();
    vector_math_operations_demo();
    matrix_transformations_demo();
    quaternion_rotations_demo();
    projection_matrices_demo();
    geometric_calculations_demo();
    graphics_pipeline_3d_demo();

    std::cout << "\n=== GLM MATHEMATICS DEMO COMPLETE ===" << std::endl;
}

} // namespace twiz
