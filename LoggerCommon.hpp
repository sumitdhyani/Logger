#pragma once
#include <CommonUtils/CommonDefs.hpp>
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
#include <algorithm>
namespace logging = boost::log;

enum class LoggingLevel
{
	trace,
	debug,
	info,
	warning,
	error,
	fatal
};

static const std::string traceStr = "trace";
static const std::string debugStr = "debug";
static const std::string infoStr = "info";
static const std::string warningStr = "warning";
static const std::string errorStr = "error";
static const std::string fatalStr = "fatal";

inline LoggingLevel strToEnumLoggingLevel(std::string loggingLevel)
{
	std::transform(loggingLevel.begin(), loggingLevel.end(), loggingLevel.begin(), ::tolower);
	if (loggingLevel == traceStr)
		return LoggingLevel::trace;
	else if (loggingLevel == debugStr)
		return LoggingLevel::debug;
	else if (loggingLevel == infoStr)
		return LoggingLevel::info;
	else if (loggingLevel == warningStr)
		return LoggingLevel::warning;
	else if (loggingLevel == errorStr)
		return LoggingLevel::error;
	else if (loggingLevel == fatalStr)
		return LoggingLevel::fatal;
	else
		throw std::runtime_error("Invalid error level set");
}

inline std::string enumToStrLoggingLevel(LoggingLevel loggingLvl)
{
	switch (loggingLvl)
	{
	case LoggingLevel::trace:
		return traceStr;
	case LoggingLevel::debug:
		return debugStr;
	case LoggingLevel::info:
		return infoStr;
	case LoggingLevel::warning:
		return warningStr;
	case LoggingLevel::error:
		return errorStr;
	case LoggingLevel::fatal:
		return fatalStr;
	default:
		throw std::runtime_error("Invalid argument");
	}
}