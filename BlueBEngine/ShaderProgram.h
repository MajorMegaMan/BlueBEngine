#pragma once
#include "Graphics.h"

namespace BBB
{
	class ShaderProgram
	{
		GLuint m_shaderProgram;

	public:
		ShaderProgram();
		~ShaderProgram();

		ShaderProgram(const ShaderProgram& other) = delete;
		ShaderProgram& operator= (const ShaderProgram& other) = delete;

		void UseShaderProgram();

	private:
		void CreateShaderProgram();

		void CreateShader(GLuint& shaderHandle, int shaderType, const char* fileSource);

		int CheckShaderCompileStatus(GLuint shader);

		void LogShader(GLuint shader, const char* shaderName, const char* fileName);

		int CheckProgramCompileStatus(GLuint shaderProgram);

		void LogProgram(GLuint shaderProgram, const char* shaderName, const char* fileName);
	};
}