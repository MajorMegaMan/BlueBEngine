#include "Camera2D.h"
#include "Conversion.h"

namespace BBB
{
	Camera2D::Camera2D()
	{
		SetCamHeight(10.0f);
	}

	glm::mat4x4 Camera2D::FindOrthoMatrix()
	{
		glm::vec3 pos = GetPosition();
		glm::vec2 cameraCentre = { pos.x, pos.y };
		float cameraHeight = pos.z;
		return glm::ortho(
			-aspectRatio * cameraHeight / 2.0f + cameraCentre.x,
			aspectRatio * cameraHeight / 2.0f + cameraCentre.x,
			-cameraHeight / 2.0f + cameraCentre.y,
			cameraHeight / 2.0f + cameraCentre.y,
			-1.0f, 1.0f);
	}

	float Camera2D::GetCamHeight() const
	{
		return GetPosition().z;
	}

	void Camera2D::SetCamHeight(float height)
	{
		float* floatBuffer = ConvertTo<float>(GetPositionPtr());
		floatBuffer[2] = height;
	}

	glm::vec2 Camera2D::GetCamPosition() const
	{
		return *ConstConvertTo<glm::vec2>(GetConstPositionPtr());
	}

	void Camera2D::SetCamPosition(glm::vec2 position)
	{
		glm::vec2* pos = ConvertTo<glm::vec2>(GetPositionPtr());
		pos[0] = position;
	}
}
