#pragma once
#include "Graphics.h"

namespace BBB
{
	class ShaderProgram
	{
		GLuint m_shaderProgram;

	public:
		ShaderProgram(const char* vertFileName, const char* fragFileName);
		~ShaderProgram();

		ShaderProgram(const ShaderProgram& other) = delete;
		ShaderProgram& operator= (const ShaderProgram& other) = delete;

		void UseShaderProgram();

		int GetUniformLocation(const char* uniformName);

		// This will use this shader program and find the location before setting the uniform variable
		void SetUniform4f(const char* uniformName, float* vec4);
		void SetUniform1i(const char* uniformName, int value);

		// This only sets the target location uniform variable. It does not use any specific shader and will therefore apply to the last used shader
		static void SetUniform4f(int location, float* vec4);
		static void SetUniform1i(int location, int value);

	private:
		void CreateShaderProgram(const char* vertFileName, const char* fragFileName);

		void CreateShader(GLuint& shaderHandle, int shaderType, const char* fileSource);

		int CheckShaderCompileStatus(GLuint shader);

		void LogShader(GLuint shader, const char* shaderName, const char* fileName);

		int CheckProgramCompileStatus(GLuint shaderProgram);

		void LogProgram(GLuint shaderProgram, const char* shaderName, const char* fileName);
	};
}