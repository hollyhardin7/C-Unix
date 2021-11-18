#include <stdio.h>
#include <source.h>
#include <sink.h>

class Color : public Source
{
    public:
	// Constructor
	Color(int w, int h, unsigned char r, unsigned char g, unsigned char b);

	// Method for getting source name
	const char *SourceName()		{ return "Color"; };

	// Method for creating a colored image
	void Execute();

    protected:
	int height, width;
	unsigned char red, blue, green;
};

class CheckSum : public Sink
{
    public:
	// Method for getting sink name
	const char *SinkName()			{ return "CheckSum"; };

	// Method for summing the total value of the colors
	void OutputCheckSum(const char *f);
};

class Filter : public Source, public Sink
{
    public:
	// Filter
	Filter();

	// Method for updating image pointer 
	virtual void Update();

	// Method for getting filter name
	virtual const char *FilterName() = 0;
	const char *SourceName()		{ return FilterName(); };
	const char *SinkName()			{ return FilterName(); };

	// Variable for updating the image
	bool updating;
};

class Mirror : public Filter
{
    public:
	// Method for mirroring image
	void Execute();

	// Method for getting Source name
	virtual const char *FilterName()	{ return "Mirror"; };
};

class Rotate : public Filter
{
    public:
	// Method for rotating image 90 degrees
	void Execute();

	// Method for getting Source name
	virtual const char *FilterName()	{ return "Rotate"; };
};

class Subtract : public Filter
{
    public:
	// Method for finding the difference between two images
	void Execute();

	// Method for getting Source name
	virtual const char *FilterName()	{ return "Subtract"; };
};

class Grayscale : public Filter
{
    public:
	// Method for removing the color from an image
	void Execute();

	// Method for getting Source name
	virtual const char *FilterName()	{ return "Grayscale"; };
};

class Blur : public Filter
{
    public:
	// Method for blurring an image
	void Execute();

	// Method for getting Source name
	virtual const char *FilterName()	{ return "Blur"; };
};

class Shrinker : public Filter
{
    public:
	// Method for shrinking image
	void Execute();

	// Method for getting Source name
	virtual const char *FilterName()	{ return "Shrinker"; };
};


class LRCombine : public Filter
{
    public:
	// Method for combining left and right images
	void Execute();

	// Method for getting Source name
	virtual const char *FilterName()	{ return "LRConcat"; };
};

class TBCombine : public Filter
{
    public:
	// Method for combining top and bottom images
	void Execute();

	// Method for getting Source name
	virtual const char *FilterName()	{ return "TBConcat"; };
};

class Blender : public Filter
{
    public:
	// Methods for blending image
	void SetFactor(double f)		{ factor = f; };
	void Execute();

	// Method for getting Source name
	virtual const char *FilterName()	{ return "Blender"; };

	// Variables
	double factor;
	double remaining;
};
