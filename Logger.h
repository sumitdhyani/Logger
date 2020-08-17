#pragma once
#include "ILogger.h"
#include "IOutputStream.h"
#include "IOutputStreamFactory.h"

void initLogging(LoggingLevel loggingLvl, int maxLogSizeInMb, std::string filenameFormat);

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
