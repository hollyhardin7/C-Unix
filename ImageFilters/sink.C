#include <sink.h>
#include <iostream>
#include <logging.h>

using namespace std;

Sink::Sink()
{
	image = NULL;
	image2 = NULL;
}

void Sink::SetInput(Image *img)
{
	image = img;
}

void Sink::SetInput2(Image *img)
{
	image2 = img;
}
