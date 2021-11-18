#include <source.h>
#include <image.h>
#include <string.h>

Image::Image()
{
	// Initialize variables
	width = 0;
	height = 0;
	Pixmap = NULL;
	source = NULL;
}

void Image::SetPixmap(Pixel *pxl)
{
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			Pixmap[i*width + j].r = pxl[i*width + j].r;
			Pixmap[i*width + j].g = pxl[i*width + j].g;
			Pixmap[i*width + j].b = pxl[i*width + j].b;
		}
}

void Image::Reset(int w, int h)
{
	// Reset variables
	width = w;
	height = h;

	// Delete pixel info
	delete [] Pixmap;

	// Create new pixmap
	Pixmap = new Pixel[w*h];
}

void Image::Update() const 
{
	// Request the source pointer to do an update 
	if (source != NULL)
		source->Update();
};
