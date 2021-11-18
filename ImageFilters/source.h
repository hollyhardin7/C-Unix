#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <logging.h>
#include <image.h>

class Source
{
    public:
	// Constructor
	Source();

	// Method to get image
	Image *GetOutput()              	{ return &output_image; };

	// Method for updating source pointer
	virtual void Update();

	// Method for getting source name
	virtual const char *SourceName() = 0;

    protected:
	// Other
	virtual void Execute() = 0;

	// Image varaible
	Image output_image;
};

#endif
