#pragma once
#include "Graphics.h"

namespace BBB
{
	class Texture
	{
		int width;
		int height;
		int nrChannels;

		GLuint textureHandle;

		void GenerateTexture();

	public:
		void LoadImage(const char* fileName);

		void Bind();

		void DeleteTexture();
	};
}