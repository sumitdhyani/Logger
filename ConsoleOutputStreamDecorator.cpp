#include <iostream>
#include <thread>
#include "ConsoleOutputStreamDecorator.h"

ConsoleOutputStreamDecorator::ConsoleOutputStreamDecorator(IOutputStream_SPtr parent, LoggingLevel loggingLvl, std::function<std::string()> timestampFetcher, std::string title):
	m_parent(parent),
	m_loggingLvl(loggingLvl),
	m_timestampfetcher(timestampFetcher),
	m_title(title)
{
}
IOutputStream& ConsoleOutputStreamDecorator::operator <<(std::string str)
{
	*m_parent << str;
	m_stream << str;
	return *this;
}

IOutputStream& ConsoleOutputStreamDecorator::operator <<(const char* str)
{
	*m_parent << str;
	m_stream << str;
	return *this;
}

IOutputStream& ConsoleOutputStreamDecorator::operator <<(int n)
{
	*m_parent << n;
	m_stream << n;
	return *this;
}

IOutputStream& ConsoleOutputStreamDecorator::operator <<(long n)
{
	*m_parent << n;
	m_stream << n;
	return *this;
}
ConsoleOutputStreamDecorator::~ConsoleOutputStreamDecorator()
{
	try
	{
		std::string logString = m_stream.str();
		if (0 < logString.length())
		{
			std::ostringstream prefixStream;
			prefixStream << m_timestampfetcher() << "|" << m_title << "(" << std::this_thread::get_id() << ")|" << enumToStrLoggingLevel(m_loggingLvl) << "|";
			std::cout << prefixStream.str() << logString << std::endl;
		}
	}
	catch (...)
	{
	}
}


