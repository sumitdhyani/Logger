#pragma once
#include "IOutputStream.h"
#include "ConsoleOutputStreamDecorator.h"
#include "FileOutputStreamDecorator.h"
#include <boost/date_time.hpp>


class IOutputStreamFactory
{
public:
	virtual IOutputStream_SPtr getOutputStream(bool consoleLogging, bool fileLogging, LoggingLevel configuredLoggingLevel, LoggingLevel loggingLevel,  std::string title) = 0;
	virtual ~IOutputStreamFactory() {}
};
DEFINE_PTR(IOutputStreamFactory)

class DefaultutputStreamFactory : public IOutputStreamFactory
{
	std::function<std::string()> m_timestampfetcher;
public:
	DefaultutputStreamFactory(std::function<std::string()> timestampfetcher = []() {
																					boost::posix_time::ptime timeLocal = boost::posix_time::microsec_clock::local_time();
																					std::stringstream stream;
																					boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
																					facet->format("%Y%m%d:%H.%M.%S%F");
																					stream.imbue(std::locale(std::locale::classic(), facet));
																					stream << timeLocal;
																					return stream.str();
																					}
							 ) :
		m_timestampfetcher(timestampfetcher)
	{
	}

	virtual IOutputStream_SPtr getOutputStream(bool consoleLogging, bool fileLogging, LoggingLevel configuredLoggingLevel, LoggingLevel loggingLevel, std::string title)
	{
		IOutputStream_SPtr retVal(new NullOutputStream);
		if (loggingLevel >= configuredLoggingLevel)
		{
			if (consoleLogging)
				retVal = IOutputStream_SPtr(new ConsoleOutputStreamDecorator(retVal, loggingLevel, m_timestampfetcher, title));

			if (fileLogging)
				retVal = IOutputStream_SPtr(new FileOutputStreamDecorator(retVal, loggingLevel, m_timestampfetcher, title));
		}

		return retVal;
	}
};