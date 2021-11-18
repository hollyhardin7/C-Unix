#include <filter.h>

Color::Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
	width = w;
	height = h;
	red = r;
	green = g;
	blue = b;
}

void Color::Execute()
{
	// Get pixel map
	Pixel *Pixmap = new Pixel[width * height];
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			Pixmap[i*width + j].r = red;
			Pixmap[i*width + j].g = green;
			Pixmap[i*width + j].b = blue;
		}

	// Update source's image
	GetOutput()->Reset(width, height);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}

void CheckSum::OutputCheckSum(const char *filename)
{
	// Check for and throw exception
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Open file
	FILE *f_out = fopen(filename, "wb");

	// Get image's dimensions
	int width, height;
	height = image->GetHeight();
	width = image->GetWidth();

	// Get values of the color channels
	unsigned char red_values = 0;
	unsigned char green_values = 0;
	unsigned char blue_values = 0; 
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			red_values += (image->GetPixel(j, i)).r; 
			green_values += (image->GetPixel(j, i)).g; 
			blue_values += (image->GetPixel(j, i)).b; 
		}

	// Write total value of the color channels
	fprintf(f_out, "CHECKSUM: %d, %d, %d\n", red_values, green_values, blue_values);

	// Close file
	fclose(f_out);
}

Filter::Filter()
{
	updating = false;
}

void Filter::Update()
{
	if (updating == true)
	{
		char msg[1024];
		sprintf(msg, "Still trying to update %s!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}       

	updating = true;

	// Update image pointer
	if (image != NULL)
	{
		Logger::LogImageUpdate(SourceName(), 1);
		image->Update();
		Logger::LogImageExecution(SourceName(), 1);
	}

	// Update image2 pointer
	if (image2 != NULL)
	{
		Logger::LogImageUpdate(SourceName(), 2);
		image2->Update();
		Logger::LogImageExecution(SourceName(), 2);
	}

	// Request source to do an update
	Logger::LogSourceUpdate(SourceName());
	Execute();
	updating = false;
	Logger::LogSourceExecution(SourceName());
}

void Mirror::Execute()
{
	// Check for and throw exceptions
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Get dimensions of image and resize
	int height, width;
	height = image->GetHeight();
	width = image->GetWidth();

	// Get pixel map
	Pixel *Pixmap = new Pixel[width * height];
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			Pixmap[i*width + j] = image->GetPixel(width - j - 1, i);

	// Update source's image
	GetOutput()->Reset(width, height);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}

void Rotate::Execute()
{
	// Check for and throw exceptions
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Get dimensions of image and resize
	int height, width;
	height = image->GetHeight();
	width = image->GetWidth();

	// Get pixel map
	Pixel *Pixmap = new Pixel[width * height];
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			Pixmap[j*height + (height - i - 1)] = image->GetPixel(j, i);

	// Update source's image
	GetOutput()->Reset(height, width);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}

void Subtract::Execute()
{
	// Check for and throw exceptions
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (image2 == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (image->GetHeight() != image2->GetHeight())
	{
		char msg[1024];
		sprintf(msg, "%s: heights must match: %d, %d", SinkName(), image->GetHeight(), image2->GetHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (image->GetWidth() != image2->GetWidth())
	{
		char msg[1024];
		sprintf(msg, "%s: widths must match: %d, %d", SinkName(), image->GetWidth(), image2->GetWidth());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Get dimensions of image and resize
	int height, width;
	height = image->GetHeight();
	width = image->GetWidth();

	// Get pixel map
	Pixel *Pixmap = new Pixel[width * height];
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if ((image->GetPixel(j, i)).r > (image2->GetPixel(j, i)).r)
				Pixmap[i*width + j].r =
					(image->GetPixel(j, i)).r - (image2->GetPixel(j, i)).r;
			else
				Pixmap[i*width + j].r = 0;

			if ((image->GetPixel(j, i)).g > (image2->GetPixel(j, i)).g)
				Pixmap[i*width + j].g =
					(image->GetPixel(j, i)).g - (image2->GetPixel(j, i)).g;
			else
				Pixmap[i*width + j].g = 0;

			if ((image->GetPixel(j, i)).b > (image2->GetPixel(j, i)).b)
				Pixmap[i*width + j].b =
					(image->GetPixel(j, i)).b - (image2->GetPixel(j, i)).b;
			else
				Pixmap[i*width + j].b = 0; 
		}

	// Update source's image
	GetOutput()->Reset(width, height);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}

void Grayscale::Execute()
{
	// Check for and throw exception
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Get dimensions of image and resize
	int height, width;
	height = image->GetHeight();
	width = image->GetWidth();

	// Get pixel map
	Pixel *Pixmap = new Pixel[width * height];
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)   
		{
			Pixmap[i*width + j].r =
				((image->GetPixel(j, i)).r / 5)
				+ ((image->GetPixel(j, i)).g / 2)
				+ ((image->GetPixel(j, i)).b / 4);
			Pixmap[i*width + j].g =
				((image->GetPixel(j, i)).r / 5)
				+ ((image->GetPixel(j, i)).g / 2)
				+ ((image->GetPixel(j, i)).b / 4);
			Pixmap[i*width + j].b =
				((image->GetPixel(j, i)).r / 5)
				+ ((image->GetPixel(j, i)).g / 2)
				+ ((image->GetPixel(j, i)).b / 4);
		}

	// Update source's image
	GetOutput()->Reset(width, height);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}

void Blur::Execute()
{
	// Check for and throw exception
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Get dimensions of image and resize
	int height, width;
	height = image->GetHeight();
	width = image->GetWidth();

	// Get pixel map
	Pixel *Pixmap = new Pixel[width * height];
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)   
		{
			if (i == 0 || j == 0 || i == (height - 1) || j == (width - 1))
				Pixmap[i*width + j] = image->GetPixel(j, i);
			else
			{
				Pixmap[i*width + j].r =
					(((image->GetPixel(j - 1, i - 1)).r / 8)
					+ ((image->GetPixel(j - 1, i)).r / 8)
					+ ((image->GetPixel(j - 1, i + 1)).r / 8)
					+ ((image->GetPixel(j, i - 1)).r / 8)
					+ ((image->GetPixel(j, i + 1)).r / 8)
					+ ((image->GetPixel(j + 1, i - 1)).r / 8)
					+ ((image->GetPixel(j + 1, i)).r / 8)
					+ ((image->GetPixel(j + 1, i + 1)).r / 8));
				Pixmap[i*width + j].g =
					(((image->GetPixel(j - 1, i - 1)).g / 8)
					+ ((image->GetPixel(j - 1, i)).g / 8)
					+ ((image->GetPixel(j - 1, i + 1)).g / 8)
					+ ((image->GetPixel(j, i - 1)).g / 8)
					+ ((image->GetPixel(j, i + 1)).g / 8)
					+ ((image->GetPixel(j + 1, i - 1)).g / 8)
					+ ((image->GetPixel(j + 1, i)).g / 8)
					+ ((image->GetPixel(j + 1, i + 1)).g / 8));
				Pixmap[i*width + j].b =
					(((image->GetPixel(j - 1, i - 1)).b / 8)
					+ ((image->GetPixel(j - 1, i)).b / 8)
					+ ((image->GetPixel(j - 1, i + 1)).b / 8)
					+ ((image->GetPixel(j, i - 1)).b / 8)
					+ ((image->GetPixel(j, i + 1)).b / 8)
					+ ((image->GetPixel(j + 1, i - 1)).b / 8)
					+ ((image->GetPixel(j + 1, i)).b / 8)
					+ ((image->GetPixel(j + 1, i + 1)).b / 8));
			}
		}

	// Update source's image
	GetOutput()->Reset(width, height);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}

void Shrinker::Execute()
{
	// Check for and throw exceptions
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Get dimensions of image and resize
	int height, width;
	height = image->GetHeight() / 2;
	width = image->GetWidth() / 2;

	if (image->GetHeight() == 3 && image->GetWidth() == 3)
	{
		height = (image->GetHeight() / 2) + 1;
		width = (image->GetWidth() / 2) + 1;
	}
	else if (image->GetHeight() == 3 && image->GetWidth() > 3)
		height = (image->GetHeight() / 2) + 1;
	else if (image->GetHeight() > 3 && image->GetWidth() == 3)
		width = (image->GetWidth() / 2) + 1;

	// Get pixel map
	Pixel *Pixmap = new Pixel[width * height];
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			Pixmap[i*width + j] = image->GetPixel(2*j, 2*i);

	// Update source's image
	GetOutput()->Reset(width, height);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}

void LRCombine::Execute()
{
	// Check for and throw exceptions
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (image2 == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (image->GetHeight() != image2->GetHeight())
	{
		char msg[1024];
		sprintf(msg, "%s: heights must match: %d, %d", SinkName(), image->GetHeight(), image2->GetHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Get dimensions of image
	int height, width, width2;
	height = image->GetHeight();
	width = image->GetWidth();
	width2 = image2->GetWidth();

	// Get pixel map
	Pixel *Pixmap = new Pixel[(width + width2) * height];
	int i, j, j2;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
			Pixmap[i*(width + width2) + j] = image->GetPixel(j, i);
		for (j2 = width; j2 < width + width2; j2++)
			Pixmap[i*(width + width2) + j2] = image2->GetPixel(j2 - width, i);
	}

	// Update source's image
	GetOutput()->Reset(width + width2, height);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}

void TBCombine::Execute()
{
	// Check for and throw exception
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (image2 == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (image->GetWidth() != image2->GetWidth())
	{
		char msg[1024];
		sprintf(msg, "%s: widths must match: %d, %d", SinkName(), image->GetHeight(), image2->GetHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Get dimensions of image
	int height, height2, width;
	height = image->GetHeight();
	height2 = image2->GetHeight();
	width = image->GetWidth();

	// Get pixel map
	Pixel *Pixmap = new Pixel[width * (height + height2)];
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			Pixmap[i*width + j] = image->GetPixel(j, i);
	for (i = height; i < height + height2; i++)
		for (j = 0; j < width; j++)
			Pixmap[i*width + j] = image2->GetPixel(j, i - height);

	// Update source's image
	GetOutput()->Reset(width, height + height2);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}

void Blender::Execute()
{
	// Check for and throw exception
	if (image == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (image2 == NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Check for and throw exception
	if (factor > 1.0)
	{
		char msg[1024];
		sprintf(msg, "Invalid factor for Blender: %f", factor);
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if (image->GetHeight() != image2->GetHeight())
	{
		char msg[1024];
		sprintf(msg, "Heights don't match");
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if (image->GetWidth() != image2->GetWidth())
	{
		char msg[1024];
		sprintf(msg, "Widths don't match");
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// Get dimensions of image
	int height, width;
	height = image->GetHeight();
	width = image->GetWidth();
	GetOutput()->Reset(width, height);

	// Get pixel map
	Pixel *Pixmap = new Pixel[width * height];
	remaining = 1.0 - factor;
	int i, j;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			Pixmap[i*width + j].r = factor*(image->GetPixel(j, i)).r + remaining*(image2->GetPixel(j, i)).r;
			Pixmap[i*width + j].g = factor*(image->GetPixel(j, i)).g + remaining*(image2->GetPixel(j, i)).g;
			Pixmap[i*width + j].b = factor*(image->GetPixel(j, i)).b + remaining*(image2->GetPixel(j, i)).b;
		}

	// Update source's image
	GetOutput()->Reset(width, height);
	GetOutput()->SetPixmap(Pixmap);

	// Delete pixel map
	delete [] Pixmap;
}
