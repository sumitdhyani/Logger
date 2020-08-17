#include <thread>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include "FileOutputStreamDecorator.h"

#include <boost/move/utility.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
src::severity_logger_mt<LoggingLevel> lg;

FileOutputStreamDecorator::FileOutputStreamDecorator(IOutputStream_SPtr parent, LoggingLevel loggingLvl, std::function<std::string()> timestampFetcher, std::string title) :
	m_parent(parent),
	m_loggingLvl(loggingLvl),
	m_timestampfetcher(timestampFetcher),
	m_title(title)
{
}
IOutputStream& FileOutputStreamDecorator::operator <<(std::string str)
{
	*m_parent << str;
	m_stream << str;
	return *this;
}

IOutputStream& FileOutputStreamDecorator::operator <<(const char* str)
{
	*m_parent << str;
	m_stream << str;
	return *this;
}

IOutputStream& FileOutputStreamDecorator::operator <<(int n)
{
	*m_parent << n;
	m_stream << n;
	return *this;
}

IOutputStream& FileOutputStreamDecorator::operator <<(long n)
{
	*m_parent << n;
	m_stream << n;
	return *this;
}

FileOutputStreamDecorator::~FileOutputStreamDecorator()
{
	try
	{
		std::string logString = m_stream.str();
		if (0 < logString.length())
		{
			std::ostringstream prefixStream;
			prefixStream << m_timestampfetcher() << "|" << m_title << "(" << std::this_thread::get_id() << ")|" << enumToStrLoggingLevel(m_loggingLvl) << "|";
			BOOST_LOG_SEV(lg, m_loggingLvl) << prefixStream.str() << logString;
		}
	}
	catch (...)
	{
	}
}




