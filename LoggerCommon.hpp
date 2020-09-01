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

enum LoggingLevel
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
		return trace;
	else if (loggingLevel == debugStr)
		return debug;
	else if (loggingLevel == infoStr)
		return info;
	else if (loggingLevel == warningStr)
		return warning;
	else if (loggingLevel == errorStr)
		return error;
	else if (loggingLevel == fatalStr)
		return fatal;
	else
		throw std::runtime_error("Invalid error level set");
}

inline std::string enumToStrLoggingLevel(LoggingLevel loggingLvl)
{
	switch (loggingLvl)
	{
	case trace:
		return traceStr;
	case debug:
		return debugStr;
	case info:
		return infoStr;
	case warning:
		return warningStr;
	case error:
		return errorStr;
	case fatal:
		return fatalStr;
	default:
		throw std::runtime_error("Invalid argument");
	}
}