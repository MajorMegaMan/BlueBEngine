#pragma once
#include "UniformVar.h"

namespace BBB
{
	class Texture2D : public UniformVar
	{
		int width;
		int height;
		int nrChannels;

		GLuint textureHandle;

		bool isLoaded = false;

		void GenerateTexture();

	public:
		Texture2D();
		~Texture2D();

		void LoadImage(const char* fileName);

		void Bind();

		void Bind(int textureUnit);

		void DeleteTexture();

		static void SetActiveTexture(int textureUnit);

		static void SetImageFlipVertical(bool value);

	protected:
		virtual void SetUniformFromLocation(int location, const void* data) override;
	};
}