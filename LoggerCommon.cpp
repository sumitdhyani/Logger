#include"LoggerCommon.h"
#include <algorithm>

LoggingLevel strToEnumLoggingLevel(std::string loggingLevel)
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

std::string enumToStrLoggingLevel(LoggingLevel loggingLvl)
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
	}
}