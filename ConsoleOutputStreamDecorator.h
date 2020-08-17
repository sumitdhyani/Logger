#pragma once
#include "ILogger.h"
#include <sstream>
class ConsoleOutputStreamDecorator : public IOutputStream, public std::enable_shared_from_this<ConsoleOutputStreamDecorator>
{
	IOutputStream_SPtr m_parent;
	LoggingLevel m_loggingLvl;
	std::ostringstream m_stream;
	std::function<std::string()> m_timestampfetcher;
	std::string m_title;

public:
	ConsoleOutputStreamDecorator(IOutputStream_SPtr parent, LoggingLevel loggingLvl, std::function<std::string()> timestampFetcher, std::string title);

	virtual IOutputStream& operator <<(std::string str);

	virtual IOutputStream& operator <<(const char* str);

	virtual IOutputStream& operator <<(int n);

	virtual IOutputStream& operator <<(long n);

	~ConsoleOutputStreamDecorator();
};

