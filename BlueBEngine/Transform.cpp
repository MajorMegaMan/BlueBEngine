#include "Transform.h"

namespace BBB
{
	Transform::Transform()
	{
		m_rotation = glm::identity<glm::quat>();
	}

	glm::vec3 Transform::GetPosition() const
	{
		return m_position;
	}

	void Transform::SetPosition(glm::vec3 position)
	{
		m_position = position;
	}

	void Transform::Translate(glm::vec3 translation)
	{
		m_position += translation;
	}

	void Transform::Rotate(float angle, glm::vec3 axis)
	{
		m_rotation = glm::angleAxis(glm::radians(angle), axis) * m_rotation;
	}

	void Transform::Scale(glm::vec3 scale)
	{
		m_scale += scale;
	}

	glm::mat4x4 Transform::CalcMatrix()
	{
		glm::mat4x4 transform = glm::identity<glm::mat4x4>();
		transform = glm::translate(transform, m_position);
		transform = transform * glm::mat4_cast(m_rotation);
		transform = glm::scale(transform, m_scale);

		return transform;
	}

	glm::vec3* Transform::GetPositionPtr()
	{
		return &m_position;
	}

	const glm::vec3* Transform::GetConstPositionPtr() const
	{
		return &m_position;
	}
}
