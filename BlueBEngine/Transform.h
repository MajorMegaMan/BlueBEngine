#pragma once
#include "Maths.h"

namespace BBB
{
	class Transform
	{
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		glm::quat m_rotation;
		glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

	public:
		Transform();

		glm::vec3 GetPosition() const;
		void SetPosition(glm::vec3 position);

		void Translate(glm::vec3 translation);

		// angle is in degrees
		void Rotate(float angle, glm::vec3 axis);

		void Scale(glm::vec3 scale);

		glm::mat4x4 CalcMatrix();

	protected:
		glm::vec3* GetPositionPtr();

		// used for type conversion getters
		// example use is in the camera2D class
		const glm::vec3* GetConstPositionPtr() const;
	};
}