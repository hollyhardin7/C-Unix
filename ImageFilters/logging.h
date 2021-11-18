#ifndef  LOGGING_H
#define  LOGGING_H

#include <exception>
#include <stdio.h>

using std::exception;

class DataFlowException : public exception
{
    public:
	// Methods for data flow execeptions
	DataFlowException(const char *type, const char *error);
	virtual const char *what() const throw()	 	 { return msg; };

    protected:
	//Variable
	char msg[1024];
};

class Logger
{
    public:
	// Methods for logging data flow
	static void LogEvent(const char *event);
	static void LogException(const char *msg);
	static void LogImageUpdate(const char *source, int num);
	static void LogImageExecution(const char *source, int num);
	static void LogSourceUpdate(const char *source);
	static void LogSourceExecution(const char *source);
	static void Finalize();
	static void Initialize();

     private:
	// Variables
	static bool initialized;
	static FILE *logger;
};

#endif
