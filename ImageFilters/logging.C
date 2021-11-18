#include <logging.h>
#include <string.h>

bool Logger::initialized = false;
FILE *Logger::logger;

DataFlowException::DataFlowException(const char *type, const char *error)
{
	// Save type and error in msg
	int i;
	strcpy(msg, "(");
	strcat(msg, type);
	strcat(msg, "): ");
	strcat(msg, error);

	// Log event
	Logger::LogException(msg);
}

void Logger::Initialize()
{
	// Open file
	logger = fopen("logger", "w");
	initialized = true;
}

void Logger::LogEvent(const char *event)
{
	if (!initialized)
		Initialize();

	fprintf(logger, "%s\n", event);
}

void Logger::LogException(const char *msg)
{
	// Print the message for logging an exception
	fprintf(logger, "Throwing exception: ");
	LogEvent(msg);
}

void Logger::LogImageUpdate(const char *source, int num)
{
	if (!initialized)
		Initialize();

	// Print the message before updating an image
	fprintf(logger, "%s: about to update input%d\n", source, num);
}

void Logger::LogImageExecution(const char *source, int num)
{
	if (!initialized)
		Initialize();

	// Print the message after updating an image
	fprintf(logger, "%s: done updating input%d\n", source, num);
}

void Logger::LogSourceUpdate(const char *source)
{
	if (!initialized)
		Initialize();

	// Print the message before executing a source
	fprintf(logger, "%s: about to execute\n", source);
}

void Logger::LogSourceExecution(const char *source)
{
	if (!initialized)
		Initialize();

	// Print the message after executing a source
	fprintf(logger, "%s: done executing\n", source);
}

void Logger::Finalize()
{
	// Close file
	fclose(logger);    
}
