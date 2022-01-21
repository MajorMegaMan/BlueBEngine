#include "Transform.h"

namespace BBB
{
	Transform::Transform()
	{
		m_rotation = glm::identity<glm::quat>();
	}

	void Transform::Translate(glm::vec3 translation)
	{
		m_position += translation;
		CalcMatrix();
	}

	void Transform::Rotate(float angle, glm::vec3 axis)
	{
		m_rotation = glm::angleAxis(glm::radians(angle), axis) * m_rotation;
		CalcMatrix();
	}

	void Transform::Scale(glm::vec3 scale)
	{
		m_scale += scale;
		CalcMatrix();
	}

	glm::mat4x4 Transform::CalcMatrix()
	{
		glm::mat4x4 transform = glm::identity<glm::mat4x4>();
		transform = glm::translate(transform, m_position);
		transform = transform * glm::mat4_cast(m_rotation);
		transform = glm::scale(transform, m_scale);

		return transform;
	}
}
