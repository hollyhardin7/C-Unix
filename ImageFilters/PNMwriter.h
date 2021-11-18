#include <stdio.h>
#include <image.h>
#include <sink.h>

class PNMwriter : public Sink
{
    public:
	// Method for writing image
	void Write(const char *f_out);

	// Method for getting Source name
	virtual const char *SinkName()		{ return "PNMwriter"; };
};
