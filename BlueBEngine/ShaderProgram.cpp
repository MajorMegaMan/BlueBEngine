#include "ShaderProgram.h"
#include "File.h"
#include "Debug.h"

#define TEST_VERT_FILE "basic.vert"
#define TEST_FRAG_FILE "basic.frag"

namespace BBB
{
	ShaderProgram::ShaderProgram()
	{
		CreateShaderProgram();
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_shaderProgram);
	}

	void ShaderProgram::UseShaderProgram()
	{
		glUseProgram(m_shaderProgram);
	}

	void ShaderProgram::CreateShaderProgram()
	{
		GLuint vertexShader;
		GLuint fragmentShader;

		CreateShader(vertexShader, GL_VERTEX_SHADER, TEST_VERT_FILE);
		LogShader(vertexShader, "Vertex Shader", TEST_VERT_FILE);

		CreateShader(fragmentShader, GL_FRAGMENT_SHADER, TEST_FRAG_FILE);
		LogShader(fragmentShader, "Fragment Shader", TEST_FRAG_FILE);

		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, vertexShader);
		glAttachShader(m_shaderProgram, fragmentShader);
		glLinkProgram(m_shaderProgram);
		LogProgram(m_shaderProgram, TEST_VERT_FILE, TEST_FRAG_FILE);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void ShaderProgram::CreateShader(GLuint& shaderHandle, int shaderType, const char* fileSource)
	{
		shaderHandle = glCreateShader(shaderType);
		std::string source = LoadFileAsString(fileSource);
		const char* sourceC = source.c_str();

		glShaderSource(shaderHandle, 1, &sourceC, nullptr);
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
