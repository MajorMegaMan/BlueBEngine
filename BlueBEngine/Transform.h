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

		void Translate(glm::vec3 translation);

		// angle is in degrees
		void Rotate(float angle, glm::vec3 axis);

		void Scale(glm::vec3 scale);

		glm::mat4x4 CalcMatrix();
	};
}