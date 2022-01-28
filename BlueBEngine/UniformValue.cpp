#include "UniformValue.h"
#include <cstring>

namespace BBB
{
	UniformValue::UniformValue(size_t byteSize)
	{
		Init(byteSize);
	}

	UniformValue::UniformValue(const UniformValue& other)
	{
		if (other.valueBuffer != nullptr)
		{
			SetValue(other.valueBuffer, other.m_bufferByteSize);
		}
	}

	UniformValue& UniformValue::operator=(const UniformValue& other)
	{
		if (valueBuffer != nullptr)
		{
			delete[] valueBuffer;
			valueBuffer = nullptr;
		}

		if (other.valueBuffer != nullptr)
		{
			SetValue(other.valueBuffer, other.m_bufferByteSize);
		}

		return *this;
	}

	UniformValue::~UniformValue()
	{
		if (valueBuffer != nullptr)
		{
			delete[] valueBuffer;
			valueBuffer = nullptr;
		}
	}

	void UniformValue::Init(size_t byteSize)
	{
		if (valueBuffer != nullptr)
		{
			delete[] valueBuffer;
		}
		m_bufferByteSize = byteSize;
		valueBuffer = new char[byteSize];
		memset(valueBuffer, 0, m_bufferByteSize);
	}

	void UniformValue::SetValue(void* data, size_t byteSize)
	{
		if (valueBuffer != nullptr)
		{
			delete[] valueBuffer;
		}
		m_bufferByteSize = byteSize;
		valueBuffer = new char[byteSize];
		memcpy(valueBuffer, data, m_bufferByteSize);
	}

	void UniformValue::ModifyValue(void* data)
	{
		memcpy(valueBuffer, data, m_bufferByteSize);
	}

	void UniformValue::ApplyValue(GLHandles::ShaderProgram& shader, UniformVar& uniformVar)
	{
		uniformVar.ApplyUniform(shader, valueBuffer);
	}

	template<class T>
	inline T* UniformValue::GetValue()
	{
		return (T*)valueBuffer;
	}
}
