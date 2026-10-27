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
        
        inline Matrix4 Translate(const Matrix4& matrix, const Vector3& translation)
        {
            return glm::translate(matrix, translation);
        }

        inline Matrix4 Rotation(const Matrix4& matrix, float angleRadians, const Vector3& axis)
        {
            return glm::rotate(matrix, angleRadians, axis);
        }

        inline Matrix4 Scale(const Matrix4& matrix, const Vector3& scale)
        {
            return glm::scale(matrix, scale);
        }

        inline Matrix4 Inverse(const Matrix4& matrix)
        {
            return glm::inverse(matrix);
        }
    }
}