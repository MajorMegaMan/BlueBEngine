#pragma once
#include "UniformVar.h"

namespace BBB
{
	// This is a typeless buffer of sorts to help send data to the shader.
	class UniformValue
	{
		char* valueBuffer = nullptr;
		size_t m_bufferByteSize = 0;

	public:
		UniformValue() {}

		UniformValue(size_t byteSize);

		UniformValue(const UniformValue& other);

		UniformValue& operator=(const UniformValue& other);

		~UniformValue();

		// Set only the size of the buffer
		void Init(size_t byteSize);

		// Set the value and size of the buffer
		void SetValue(void* data, size_t byteSize);

		// change the value of the value buffer as it is expected that the user has already set the bufferSize
		// THIS IS UNSAFE, if the user has not set the buffer size, memory stomping may occur.
		void ModifyValue(void* data);

		// Get the uniform value as the specified type
		template <class T>
		T* GetValue();

		void ApplyValue(GLHandles::ShaderProgram& shader, UniformVar& uniformVar);
	};
}