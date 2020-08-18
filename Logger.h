#pragma once
#include "ILogger.h"
#include "IOutputStream.h"
#include "IOutputStreamFactory.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", LoggingLevel)
inline void initLogging(LoggingLevel loggingLvl, int maxLogSizeInMb, std::string filenameFormat)
{
	// Create a text file sink
	boost::shared_ptr< file_sink > sink(new file_sink(
		keywords::file_name = filenameFormat,  /*< the resulting file name pattern >*/
		keywords::rotation_size = maxLogSizeInMb * 1024 * 1024,                 /*< rotation size, in characters >*/
		keywords::auto_flush = true
	));

	boost::shared_ptr< logging::core > core = logging::core::get();
	// Add the sink to the core
	core->add_sink(sink);

	//Add filter to the logs
	core->set_filter(severity >= loggingLvl);
}

class DefaultLogger : public ILogger
{
protected:
	LoggingLevel m_loggingLvl;
	bool m_consoleLogging;
	bool m_fileLogging;
	IOutputStreamFactory_SPtr m_outputStreamFactory;

public:
	DefaultLogger(LoggingLevel loggingLevel, bool consoleLogging, bool fileLogging, IOutputStreamFactory_SPtr outputStreamFactory):
		m_loggingLvl(loggingLevel),
		m_consoleLogging(consoleLogging),
		m_fileLogging(fileLogging),
		m_outputStreamFactory(outputStreamFactory)
	{
		if (m_outputStreamFactory == nullptr)
			m_outputStreamFactory = IOutputStreamFactory_SPtr(new DefaultutputStreamFactory);
	}

	virtual IOutputStream_SPtr operator ()(LoggingLevel loggingLevel, std::string title)
	{
		return m_outputStreamFactory->getOutputStream(m_consoleLogging, m_fileLogging, m_loggingLvl,loggingLevel, title);
	}

	~DefaultLogger() {}
};

#define LOG(logger, level)\
*((*logger)(level, ""))

#define LOG_WITH_TITLE(logger, level, title)\
*((*logger)(level, title))
