#include <stdio.h>
#include <source.h>
#include <string.h>

class PNMreader : public Source
{
    public:
	// Constructor and Destructor
	PNMreader(const char *f);
	~PNMreader()			  { delete [] filename; };

	// Method for getting Source name
	const char *SourceName()	  { return "PNMreader"; };

	// Method for reading image
	void Execute();

	// Variables
	char *filename;
	char magicNum[128];
	int width, height;
	char maxval[128];
};
