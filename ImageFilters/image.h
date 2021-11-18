#ifndef IMAGE_H
#define IMAGE_H

#include <string.h>

class Source;

struct Pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class Image
{
    public:
	// Constructor and Destructor
	Image();
	~Image()                                   { delete [] Pixmap; };

	// Setters
	void SetWidth(int w)                       { width = w; };
	void SetHeight(int h)                      { height = h; };
	void SetPixmap(Pixel *pxl);
	void SetSource(Source *s)                  { source = s; };

	// Getters
	int GetWidth() const                       { return width; };
	int GetHeight() const                      { return height; };
	Pixel GetPixel(int w, int h) const         { return Pixmap[h*width + w]; };
	Pixel *GetPixmap() const                   { return Pixmap; };
	Source *GetSource() const	           { return source; };

	// Method for resetting the size of image
	void Reset(int w, int h);

	// Method for updating source pointer
	void Update() const;

    private:
	// Variables
	int width, height;
	Pixel *Pixmap;
	Source *source;
};

#endif
