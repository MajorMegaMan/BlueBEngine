#pragma once
#include "Graphics.h"

namespace BBB
{
	class Texture2D
	{
		int width;
		int height;
		int nrChannels;

		GLuint textureHandle;

		void GenerateTexture();

	public:
		void LoadImage(const char* fileName);

		void Bind();

		void Bind(int textureUnit);

		void DeleteTexture();

		static void SetActiveTexture(int textureUnit);

		static void SetImageFlipVertical(bool value);
	};
}