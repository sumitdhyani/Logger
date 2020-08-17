#pragma once
#include <CommonUtils/CommonDefs.h>
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

LoggingLevel strToEnumLoggingLevel(std::string loggingLevel);

std::string enumToStrLoggingLevel(LoggingLevel loggingLvl);