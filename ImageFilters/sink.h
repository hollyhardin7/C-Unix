#ifndef SINK_H
#define SINK_H

#include <image.h>
#include <stdio.h>
#include <stdlib.h>

class Sink
{
    public:
	// Constructor
	Sink();

	// Methods to set input of images
	void SetInput(Image* img);
	void SetInput2(Image* img);

	// Method for getting sink name
	virtual const char *SinkName() = 0;

    protected:
	// Variables
	const Image *image;
	const Image *image2;
};

#endif
