#pragma once
#include "UniformVar.h"
#include "Maths.h"

namespace BBB
{
	class UniformMat4x4Helper : public UniformVar
	{
		void SetUniformFromLocation(int location, const void* data) override
		{
			GLHandles::ShaderProgram::SetUniformMatrix4f(location, (float*)data);
		}
	};

	class UniformVec4Helper : public UniformVar
	{
		void SetUniformFromLocation(int location, const void* data) override
		{
			GLHandles::ShaderProgram::SetUniform4f(location, (float*)data);
		}
	};
}