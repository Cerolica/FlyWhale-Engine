#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace FlyWhale 
{

    typedef glm::vec2 Vector2;
    typedef glm::vec3 Vector3;
    typedef glm::vec4 Vector4;

    typedef glm::mat2 Matrix2;
    typedef glm::mat3 Matrix3;
    typedef glm::mat4 Matrix4;

    typedef glm::quat Quarternion;


    namespace Math
    {
        // Constants and base utilities
        // ----------------------------
        constexpr float PI = 3.14159265359f;
        constexpr float EPSILON = 0.00001f;
        
        inline float Radians(float angleDegrees)
        {
            return glm::radians(angleDegrees);
        }

        inline float Degrees(float angleRadians)
        {
            return glm::degrees(angleRadians);
        }

        // Vector Math
        // -----------

        inline float Length(const Vector2& v) 
        {
            return glm::length(v);
        }

        inline float Length(const Vector3& v) 
        {
            return glm::length(v);
        }

        inline float Distance(const Vector2& a, const Vector2 b)
        {
            return glm::distance(a, b);
        }

        inline float Distance(const Vector3& a, const Vector3 b)
        {
            return glm::distance(a, b);
        }

        inline Vector2 Normalize(const Vector2& v)
        {
            return glm::normalize(v);
        }

        inline Vector3 Normalize(const Vector3& v)
        {
            return glm::normalize(v);
        }

        inline float Dot(const Vector2& a, const Vector2& b)
        {
            return glm::dot(a, b);
        }

        inline float Dot(const Vector3& a, const Vector3& b)
        {
            return glm::dot(a, b);
        }

        inline Vector3 Cross(const Vector3& a, const Vector3& b)
        {
            return glm::cross(a, b);
        }

        // ---Matrix & Camera Operations---
        // --------------------------------

        inline Matrix4 Inverse(const Matrix4& matrix)
        {
            return glm::inverse(matrix);
        }

        inline Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
        {
            return glm::lookAt(eye, center, up);
        }

        inline Matrix4 Orthographic(float left, float right, float bottom, float top, float zNear, float zFar) {
            return glm::ortho(left, right, bottom, top, zNear, zFar);
        }

        // ---Others---
        // ------------

        inline Matrix4 Translate(const Matrix4& matrix, const Vector3& translation)
        {
            return glm::translate(matrix, translation);
        }

        inline Matrix4 Rotate(const Matrix4& matrix, float angleRadians, const Vector3& axis)
        {
            return glm::rotate(matrix, angleRadians, axis);
        }

        inline Matrix4 Scale(const Matrix4& matrix, const Vector3& scale)
        {
            return glm::scale(matrix, scale);
        }

    }
}