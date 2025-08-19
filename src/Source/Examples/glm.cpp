#include <cstddef>
#include <cstdio>
#include <string>
#define GLM_ENABLE_EXPERIMENTAL
#include "Examples/glm.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <vector>

namespace
{
    void PrintMatrix(const glm::mat4& matrix, const std::string& name)
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
        std::cout << '\n';
    }

    void PrintVec3(const glm::vec3& vec, const std::string& name)
    {
        printf("%s: [%7.3f, %7.3f, %7.3f]\n", name.c_str(), vec.x, vec.y, vec.z);
    }

} // namespace

namespace Twiz
{
    void ShowGlm()
    {
        std::cout << "\n=== GLM MATHEMATICS SHOWCASE ===" << '\n';
        std::cout << "OpenGL Mathematics Library for graphics programming" << '\n';
        std::cout << "Perfect for 3D graphics, transformations, and linear algebra\n" << '\n';
    }

    void MatrixTransformationsDemo()
    {
        std::cout << "\n--- Matrix Transformations Demo ---" << '\n';

        auto const identity = glm::mat4(1.0f);
        PrintMatrix(identity, "Identity Matrix");

        glm::vec3 const translation(5.0f, 3.0f, -2.0f);
        glm::mat4 const translateMatrix = glm::translate(identity, translation);
        PrintMatrix(translateMatrix, "Translation Matrix");

        float const angle = glm::radians(45.0f);
        glm::vec3 const rotationAxis(0.0f, 1.0f, 0.0f);
        glm::mat4 const rotationMatrix = glm::rotate(identity, angle, rotationAxis);
        PrintMatrix(rotationMatrix, "Rotation Matrix (45° around Y)");

        glm::vec3 const scaleFactors(2.0f, 1.5f, 0.8f);
        glm::mat4 const scaleMatrix = glm::scale(identity, scaleFactors);
        PrintMatrix(scaleMatrix, "Scale Matrix");

        glm::mat4 const combined = translateMatrix * rotationMatrix * scaleMatrix;
        PrintMatrix(combined, "Combined Transformation (T * R * S)");

        glm::vec3 const testPoint(1.0f, 0.0f, 0.0f);
        glm::vec4 const transformed = combined * glm::vec4(testPoint, 1.0f);
        PrintVec3(glm::vec3(transformed), "Transformed Point");
    }

    void VectorMathOperationsDemo()
    {
        std::cout << "\n--- Vector Math Operations Demo ---" << '\n';

        glm::vec3 const pointa(3.0f, 4.0f, 0.0f);
        glm::vec3 const pointb(1.0f, 2.0f, 5.0f);

        PrintVec3(pointa, "Vector A");
        PrintVec3(pointb, "Vector B");

        glm::vec3 const sum = pointa + pointb;
        PrintVec3(sum, "A + B");

        glm::vec3 const difference = pointa - pointb;
        PrintVec3(difference, "A - B");

        float const dotProduct = glm::dot(pointa, pointb);
        std::cout << "Dot Product (A · B): " << dotProduct << '\n';

        glm::vec3 const crossProduct = glm::cross(pointa, pointb);
        PrintVec3(crossProduct, "Cross Product (A × B)");

        float const lengthA = glm::length(pointa);
        float const lengthB = glm::length(pointb);
        std::cout << "Length of A: " << lengthA << '\n';
        std::cout << "Length of B: " << lengthB << '\n';

        glm::vec3 const normalizedA = glm::normalize(pointa);
        glm::vec3 const normalizedB = glm::normalize(pointb);
        PrintVec3(normalizedA, "Normalized A");
        PrintVec3(normalizedB, "Normalized B");

        float const distance = glm::distance(pointa, pointb);
        std::cout << "Distance between A and B: " << distance << '\n';

        float const angle = glm::acos(glm::dot(normalizedA, normalizedB));
        std::cout << "Angle between A and B: " << glm::degrees(angle) << "°" << '\n';

        glm::vec3 const lerpResult = glm::mix(pointa, pointb, 0.5f);
        PrintVec3(lerpResult, "Linear Interpolation (50%)");
    }

    void QuaternionRotationsDemo()
    {
        std::cout << "\n--- Quaternion Rotations Demo ---" << '\n';

        glm::quat const identityQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        std::cout << "Identity Quaternion: [w:" << identityQuat.w << ", x:" << identityQuat.x << ", y:" << identityQuat.y << ", z:" << identityQuat.z << "]" << '\n';

        float const pitch = glm::radians(30.0f);
        float const yaw = glm::radians(45.0f);
        float const roll = glm::radians(15.0f);

        glm::quat const pitchQuat = glm::angleAxis(pitch, glm::vec3(1, 0, 0));
        glm::quat const yawQuat = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
        glm::quat const rollQuat = glm::angleAxis(roll, glm::vec3(0, 0, 1));

        glm::quat const combinedRotation = yawQuat * pitchQuat * rollQuat;
        std::cout << "Combined Rotation Quaternion: [w:" << combinedRotation.w << ", x:" << combinedRotation.x << ", y:" << combinedRotation.y << ", z:" << combinedRotation.z << "]" << '\n';

        glm::mat4 const rotationMatrix = glm::mat4_cast(combinedRotation);
        PrintMatrix(rotationMatrix, "Quaternion to Matrix Conversion");

        glm::vec3 const eulerAngles = glm::eulerAngles(combinedRotation);
        std::cout << "Euler Angles (radians): [" << eulerAngles.x << ", " << eulerAngles.y << ", " << eulerAngles.z << "]" << '\n';
        std::cout << "Euler Angles (degrees): [" << glm::degrees(eulerAngles.x) << ", " << glm::degrees(eulerAngles.y) << ", " << glm::degrees(eulerAngles.z) << "]" << '\n';

        glm::vec3 const forward(0.0f, 0.0f, -1.0f);
        glm::vec3 const rotatedForward = combinedRotation * forward;
        PrintVec3(rotatedForward, "Rotated Forward Vector");

        glm::quat const q1 = glm::angleAxis(glm::radians(0.0f), glm::vec3(0, 1, 0));
        glm::quat const q2 = glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0));

        for (size_t i = 0; i <= 4; ++i)
        {
            float const t = i * 0.25f;
            glm::quat const interpolated = glm::slerp(q1, q2, t);
            glm::vec3 const interpolatedAngles = glm::eulerAngles(interpolated);
            std::cout << "SLERP t=" << t << ": Y rotation = " << glm::degrees(interpolatedAngles.y) << "°" << '\n';
        }
    }

    void ProjectionMatricesDemo()
    {
        std::cout << "\n--- Projection Matrices Demo ---" << '\n';

        float const fov = glm::radians(75.0f);
        float const aspectRatio = 16.0f / 9.0f;
        float const nearPlane = 0.1f;
        float const farPlane = 100.0f;

        glm::mat4 const perspectiveMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
        PrintMatrix(perspectiveMatrix, "Perspective Projection Matrix");

        const float left = -10.0f, right = 10.0f;
        const float bottom = -10.0f, top = 10.0f;
        const float orthonear = 0.1f, orthofar = 100.0f;

        glm::mat4 const orthographicMatrix = glm::ortho(left, right, bottom, top, orthonear, orthofar);
        PrintMatrix(orthographicMatrix, "Orthographic Projection Matrix");

        glm::vec3 const eye(0.0f, 5.0f, 10.0f);
        glm::vec3 const center(0.0f, 0.0f, 0.0f);
        glm::vec3 const up(0.0f, 1.0f, 0.0f);

        glm::mat4 const viewMatrix = glm::lookAt(eye, center, up);
        PrintMatrix(viewMatrix, "View Matrix (LookAt)");

        glm::mat4 const modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, -3.0f));
        glm::mat4 const mvpMatrix = perspectiveMatrix * viewMatrix * modelMatrix;
        PrintMatrix(mvpMatrix, "Model-View-Projection Matrix");

        glm::vec3 const worldPoint(1.0f, 1.0f, 1.0f);
        glm::vec4 const clipSpace = mvpMatrix * glm::vec4(worldPoint, 1.0f);

        if (clipSpace.w != 0.0f)
        {
            glm::vec3 const ndc = glm::vec3(clipSpace) / clipSpace.w;
            PrintVec3(ndc, "Normalized Device Coordinates");

            float const viewportWidth = 1920.0f;
            float const viewportHeight = 1080.0f;
            glm::vec2 const screenCoords((ndc.x + 1.0f) * 0.5f * viewportWidth, (1.0f - ndc.y) * 0.5f * viewportHeight);
            std::cout << "Screen Coordinates: [" << screenCoords.x << ", " << screenCoords.y << "]" << '\n';
        }
    }

    void GeometricCalculationsDemo()
    {
        std::cout << "\n--- Geometric Calculations Demo ---" << '\n';

        glm::vec3 const p1(0.0f, 0.0f, 0.0f);
        glm::vec3 const p2(3.0f, 4.0f, 0.0f);
        glm::vec3 const p3(0.0f, 4.0f, 0.0f);

        PrintVec3(p1, "Point 1");
        PrintVec3(p2, "Point 2");
        PrintVec3(p3, "Point 3");

        glm::vec3 const v1 = p2 - p1;
        glm::vec3 const v2 = p3 - p1;

        glm::vec3 const triangleNormal = glm::normalize(glm::cross(v1, v2));
        PrintVec3(triangleNormal, "Triangle Normal");

        float const triangleArea = 0.5f * glm::length(glm::cross(v1, v2));
        std::cout << "Triangle Area: " << triangleArea << '\n';

        glm::vec3 const centroid = (p1 + p2 + p3) / 3.0f;
        PrintVec3(centroid, "Triangle Centroid");

        glm::vec3 const rayOrigin(1.0f, 1.0f, 5.0f);
        glm::vec3 const rayDirection = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));

        PrintVec3(rayOrigin, "Ray Origin");
        PrintVec3(rayDirection, "Ray Direction");

        glm::vec3 const planePoint(0.0f, 0.0f, 0.0f);
        glm::vec3 const planeNormal(0.0f, 0.0f, 1.0f);

        float const denom = glm::dot(planeNormal, rayDirection);
        if (std::abs(denom) > 1e-6)
        {
            float const t = glm::dot(planePoint - rayOrigin, planeNormal) / denom;
            if (t >= 0)
            {
                glm::vec3 const intersection = rayOrigin + t * rayDirection;
                PrintVec3(intersection, "Ray-Plane Intersection");
                std::cout << "Intersection Distance: " << t << '\n';
            }
        }

        glm::vec3 const sphereCenter(0.0f, 0.0f, 0.0f);
        float const sphereRadius = 2.0f;

        glm::vec3 const oc = rayOrigin - sphereCenter;
        float const a = glm::dot(rayDirection, rayDirection);
        float const b = 2.0f * glm::dot(oc, rayDirection);
        float const c = glm::dot(oc, oc) - (sphereRadius * sphereRadius);

        float const discriminant = (b * b) - (4 * a * c);
        if (discriminant >= 0)
        {
            float const t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
            float const t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);

            std::cout << "Ray-Sphere Intersections:" << '\n';
            std::cout << "  t1: " << t1 << ", t2: " << t2 << '\n';

            if (t1 >= 0)
            {
                glm::vec3 const hiT1 = rayOrigin + t1 * rayDirection;
                PrintVec3(hiT1, "  First Hit Point");
            }
            if (t2 >= 0)
            {
                glm::vec3 const hiT2 = rayOrigin + t2 * rayDirection;
                PrintVec3(hiT2, "  Second Hit Point");
            }
        }
    }

    void GraphicsPipeline3dDemo()
    {
        std::cout << "\n--- 3D Graphics Pipeline Demo ---" << '\n';

        std::vector<glm::vec3> cubeVertices = {// Front face
                                               {-1.0f, -1.0f, 1.0f},
                                               {1.0f, -1.0f, 1.0f},
                                               {1.0f, 1.0f, 1.0f},
                                               {-1.0f, 1.0f, 1.0f},
                                               // Back face
                                               {-1.0f, -1.0f, -1.0f},
                                               {-1.0f, 1.0f, -1.0f},
                                               {1.0f, 1.0f, -1.0f},
                                               {1.0f, -1.0f, -1.0f}};

        std::cout << "Original Cube Vertices:" << '\n';
        for (size_t i = 0; i < cubeVertices.size(); ++i)
        {
            PrintVec3(cubeVertices[i], "  Vertex " + std::to_string(i));
        }

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 1.5f, 1.0f));

        glm::mat4 const view = glm::lookAt(glm::vec3(4.0f, 3.0f, 5.0f), // Camera position
                                           glm::vec3(0.0f, 0.0f, 0.0f), // Look at origin
                                           glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
        );

        glm::mat4 const projection = glm::perspective(glm::radians(60.0f), // FOV
                                                      16.0f / 9.0f,        // Aspect ratio
                                                      0.1f,                // Near plane
                                                      100.0f               // Far plane
        );

        glm::mat4 const mvp = projection * view * model;

        std::cout << "\nTransformed Vertices (Clip Space):" << '\n';
        std::vector<glm::vec4> clipVertices;

        for (size_t i = 0; i < cubeVertices.size(); ++i)
        {
            glm::vec4 const clipVertex = mvp * glm::vec4(cubeVertices[i], 1.0f);
            clipVertices.push_back(clipVertex);

            std::cout << "  Vertex " << i << " Clip: [" << clipVertex.x << ", " << clipVertex.y << ", " << clipVertex.z << ", " << clipVertex.w << "]" << '\n';
        }

        std::cout << "\nNormalized Device Coordinates:" << '\n';
        std::vector<glm::vec3> ndcVertices;

        for (size_t i = 0; i < clipVertices.size(); ++i)
        {
            if (clipVertices[i].w != 0.0f)
            {
                glm::vec3 const ndc = glm::vec3(clipVertices[i]) / clipVertices[i].w;
                ndcVertices.push_back(ndc);
                PrintVec3(ndc, "  Vertex " + std::to_string(i) + " NDC");
            }
        }

        float const viewportWidth = 1920.0f;
        float const viewportHeight = 1080.0f;

        std::cout << "\nScreen Coordinates (1920x1080):" << '\n';
        for (size_t i = 0; i < ndcVertices.size(); ++i)
        {
            glm::vec2 const screenCoords((ndcVertices[i].x + 1.0f) * 0.5f * viewportWidth, (1.0f - ndcVertices[i].y) * 0.5f * viewportHeight);

            std::cout << "  Vertex " << i << " Screen: [" << screenCoords.x << ", " << screenCoords.y << "]" << '\n';
        }

        std::cout << "\nDepth Values (Z-buffer):" << '\n';
        for (size_t i = 0; i < ndcVertices.size(); ++i)
        {
            float const depth = (ndcVertices[i].z + 1.0f) * 0.5f;
            std::cout << "  Vertex " << i << " Depth: " << depth << '\n';
        }
    }

    void RunGlmMathSuite()
    {
        ShowGlm();
        VectorMathOperationsDemo();
        MatrixTransformationsDemo();
        QuaternionRotationsDemo();
        ProjectionMatricesDemo();
        GeometricCalculationsDemo();
        GraphicsPipeline3dDemo();

        std::cout << "\n=== GLM MATHEMATICS DEMO COMPLETE ===" << '\n';
    }

} // namespace Twiz
