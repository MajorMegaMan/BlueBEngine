#include "ShaderProgram.h"
#include "File.h"
#include "Debug.h"

namespace BBB
{
	ShaderProgram::ShaderProgram(const char* vertFileName, const char* fragFileName)
	{
		LoadShaderProgram(vertFileName, fragFileName);
	}

	ShaderProgram::~ShaderProgram()
	{
		if (m_isLoaded)
		{
			glDeleteProgram(m_shaderProgram);
		}
	}

	void ShaderProgram::UseShaderProgram()
	{
		glUseProgram(m_shaderProgram);
	}

	int ShaderProgram::GetUniformLocation(const char* uniformName)
	{
		return glGetUniformLocation(m_shaderProgram, uniformName);
	}

	void ShaderProgram::SetUniform4f(const char* uniformName, float* vec4)
	{
		UseShaderProgram();
		SetUniform4f(GetUniformLocation(uniformName), vec4);
	}

	void ShaderProgram::SetUniform1i(const char* uniformName, int value)
	{
		UseShaderProgram();
		SetUniform1i(GetUniformLocation(uniformName), value);
	}

	void ShaderProgram::SetUniformMatrix4f(const char* uniformName, float* mat4)
	{
		UseShaderProgram();
		SetUniformMatrix4f(GetUniformLocation(uniformName), mat4);
	}

	void ShaderProgram::SetUniform4f(int location, float* vec4)
	{
		glUniform4f(location, vec4[0], vec4[1], vec4[2], vec4[3]);
	}

	void ShaderProgram::SetUniform1i(int location, int value)
	{
		glUniform1i(location, value);
	}

	void ShaderProgram::SetUniformMatrix4f(int location, float* mat4)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, mat4);
	}

	void ShaderProgram::LoadShaderProgram(const char* vertFileName, const char* fragFileName)
	{
		GLuint vertexShader;
		GLuint fragmentShader;

		LoadShader(vertexShader, GL_VERTEX_SHADER, vertFileName);
		LogShader(vertexShader, "Vertex Shader", vertFileName);

		LoadShader(fragmentShader, GL_FRAGMENT_SHADER, fragFileName);
		LogShader(fragmentShader, "Fragment Shader", fragFileName);

		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, vertexShader);
		glAttachShader(m_shaderProgram, fragmentShader);
		glLinkProgram(m_shaderProgram);
		LogProgram(m_shaderProgram, vertFileName, fragFileName);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		m_isLoaded = true;
	}

	void ShaderProgram::CreateShaderProgram(const char* vertShaderSource, const char* fragShaderSource)
	{
		GLuint vertexShader;
		GLuint fragmentShader;

		CreateShader(vertexShader, GL_VERTEX_SHADER, vertShaderSource);
		LogShader(vertexShader, "Vertex Shader", "vertex source");

		CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragShaderSource);
		LogShader(fragmentShader, "Fragment Shader", "fragment source");

		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, vertexShader);
		glAttachShader(m_shaderProgram, fragmentShader);
		glLinkProgram(m_shaderProgram);
		LogProgram(m_shaderProgram, "vertex source", "fragment source");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		m_isLoaded = true;
	}

	void ShaderProgram::LoadShader(GLuint& shaderHandle, int shaderType, const char* fileSource)
	{
		std::string source = LoadFileAsString(fileSource);
		const char* sourceC = source.c_str();

		CreateShader(shaderHandle, shaderType, sourceC);
	}

	void ShaderProgram::CreateShader(GLuint& shaderHandle, int shaderType, const char* shaderSource)
	{
		shaderHandle = glCreateShader(shaderType);
		glShaderSource(shaderHandle, 1, &shaderSource, nullptr);
		glCompileShader(shaderHandle);
	}

	int ShaderProgram::CheckShaderCompileStatus(GLuint shader)
	{
		GLint success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		return success;
	}

	void ShaderProgram::LogShader(GLuint shader, const char* shaderName, const char* fileName)
	{
		GLchar errorLog[512];
		GLint success = CheckShaderCompileStatus(shader);
		if (!success)
		{
			//Something failed with the vertex shader compilation
			glGetShaderInfoLog(shader, 512, nullptr, errorLog);

			Debug_Print(shaderName);
			Debug_Print(fileName);
			Debug_Print(" failed with error:");
			Debug_PrintLine(errorLog);
		}
		else
		{
			Debug_Print("\"");
			Debug_Print(fileName);
			Debug_PrintLine("\" compiled successfully.");
		}
	}

	int ShaderProgram::CheckProgramCompileStatus(GLuint shaderProgram)
	{
		GLint success = 0;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		return success;
	}
	void ShaderProgram::LogProgram(GLuint shaderProgram, const char* vertexFileName, const char* fragmentFileName)
	{
		GLchar errorLog[512];
		GLint success = CheckProgramCompileStatus(shaderProgram);
		if (success == GL_FALSE)
		{
			glGetProgramInfoLog(shaderProgram, 512, nullptr, errorLog);

			Debug_Print("Error linking shaders \"");
			Debug_Print(vertexFileName);
			Debug_Print("\" and \"");
			Debug_Print(fragmentFileName);
			Debug_PrintLine("\"");
			Debug_PrintLine(errorLog);
		}
	}
}
