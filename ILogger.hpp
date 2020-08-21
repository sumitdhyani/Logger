#pragma once
#include <string>
#include "LoggerCommon.hpp"
#include "IOutputStream.hpp"


class ILogger;
DEFINE_PTR(ILogger)

class ILogger
{
public:
	virtual IOutputStream_SPtr operator ()(LoggingLevel loggingLevel, std::string title) = 0;

	virtual ~ILogger() {}
};

class NullLogger : public IOutputStream, public std::enable_shared_from_this<NullLogger>
{
public:
	virtual IOutputStream_SPtr operator ()(LoggingLevel loggingLevel, std::string title)
	{
		return std::make_shared<NullOutputStream>();
	}
};