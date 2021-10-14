#pragma once
#include "ILogger.hpp"
#include <iostream>
#include <thread>
#include <sstream>

class ConsoleOutputStreamDecorator : public IOutputStream, public std::enable_shared_from_this<ConsoleOutputStreamDecorator>
{
	IOutputStream_SPtr m_parent;
	LoggingLevel m_loggingLvl;
	std::ostringstream m_stream;
	std::function<std::string()> m_timestampfetcher;
	std::string m_title;

public:
	ConsoleOutputStreamDecorator(IOutputStream_SPtr parent, LoggingLevel loggingLvl, std::function<std::string()> timestampFetcher, std::string title) :
		m_parent(parent),
		m_loggingLvl(loggingLvl),
		m_timestampfetcher(timestampFetcher),
		m_title(title)
	{
	}
	IOutputStream& operator <<(std::string str)
	{
		*m_parent << str;
		m_stream << str;
		return *this;
	}

	IOutputStream& operator <<(const char* str)
	{
		*m_parent << str;
		m_stream << str;
		return *this;
	}

	IOutputStream& operator <<(int n)
	{
		*m_parent << n;
		m_stream << n;
		return *this;
	}

	IOutputStream& operator <<(long n)
	{
		*m_parent << n;
		m_stream << n;
		return *this;
	}

	~ConsoleOutputStreamDecorator()
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
};

