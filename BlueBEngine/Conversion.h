#pragma once

template <class T>
T* ConvertTo(void* data)
{
	return (T*)data;
}

template <class T>
const T* ConstConvertTo(const void* data)
{
	return (T*)data;
}