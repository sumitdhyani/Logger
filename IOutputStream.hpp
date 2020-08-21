#pragma once
#include "LoggerCommon.hpp"
class IOutputStream;

class IOutputStream
{
public:
	virtual IOutputStream& operator <<(std::string str) = 0;
	virtual IOutputStream& operator <<(const char* str) = 0;
	virtual IOutputStream& operator <<(int n) = 0;
	virtual IOutputStream& operator <<(long n) = 0;

	virtual ~IOutputStream() {}
};
DEFINE_PTR(IOutputStream)



class NullOutputStream : public IOutputStream
{
public:
	virtual IOutputStream& operator <<(std::string str)
	{
		return *this;
	}

	virtual IOutputStream& operator <<(const char* str)
	{
		return *this;
	}

	virtual IOutputStream& operator <<(int n)
	{
		return *this;
	}

	virtual IOutputStream& operator <<(long n)
	{
		return *this;
	}
};

