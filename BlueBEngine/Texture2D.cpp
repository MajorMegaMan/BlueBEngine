#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture2D.h"
#include "Debug.h"

namespace BBB
{
	void Texture2D::LoadImage(const char* fileName)
	{
		GenerateTexture();

		unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
		if (data)
		{
			if (nrChannels == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
				Debug_Print("Loaded texture RGB \"");
				Debug_Print(fileName);
				Debug_PrintLine("\"");
			}
			else if (nrChannels == 4)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				Debug_Print("Loaded texture RGBA \"");
				Debug_Print(fileName);
				Debug_PrintLine("\"");
			}
			else
			{
				Debug_Print("Failed to find correct Channels in texture \"");
				Debug_Print(fileName);
				Debug_PrintLine("\"");
				DeleteTexture();
			}
		}
		else
		{
			Debug_Print("Failed to load texture");
			Debug_Print(" \"");
			Debug_Print(fileName);
			Debug_PrintLine("\"");
			DeleteTexture();
		}

		stbi_image_free(data);
	}

	void Texture2D::GenerateTexture()
	{
		DeleteTexture();
		glGenTextures(1, &textureHandle);
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		isLoaded = true;
	}

	Texture2D::Texture2D()
	{
	}

	Texture2D::~Texture2D()
	{
		DeleteTexture();
	}

	void Texture2D::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, textureHandle);
	}

	void Texture2D::Bind(int textureUnit)
	{
		SetActiveTexture(textureUnit);
		Bind();
	}

	void Texture2D::DeleteTexture()
	{
		if (isLoaded)
		{
			glDeleteTextures(1, &textureHandle);
			isLoaded = false;
		}
	}

	void Texture2D::SetActiveTexture(int textureUnit)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
	}

	void Texture2D::SetImageFlipVertical(bool value)
	{
		stbi_set_flip_vertically_on_load(true);
	}

	void Texture2D::SetUniformFromLocation(int location, const void* data)
	{
		GLHandles::ShaderProgram::SetUniform1i(location, *(int*)data);
	}
}