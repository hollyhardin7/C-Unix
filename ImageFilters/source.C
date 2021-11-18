#include <source.h>

Source::Source()
{
	// Save the derived class that called Source
	output_image.SetSource(this);    
}

void Source::Update()
{
	// Write data to string
	char msg[128];
	sprintf(msg, "%s: about to execute", SourceName());
 
	// Log event
	Logger::LogEvent(msg);

	// Execute
	Execute();

	// Write data to string
	sprintf(msg, "%s: done executing", SourceName());

	// Log event
	Logger::LogEvent(msg);
};
