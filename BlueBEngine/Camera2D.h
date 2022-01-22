#pragma once
#include "Transform.h"
#include "Graphics.h"

namespace BBB
{
	class Camera2D : public Transform
	{
	public:
		float aspectRatio = 800.0f / 600.0f;

		Camera2D();

		glm::mat4x4 FindOrthoMatrix();

		glm::vec2 GetCamPosition() const;
		void SetCamPosition(glm::vec2 position);

		float GetCamHeight() const;
		void SetCamHeight(float height);
	};
}