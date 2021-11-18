#include <PNMreader.h>

#include <iostream>
#include <new>
#include <exception>

PNMreader::PNMreader(const char *f)
{    
	// Save file name
	filename = new char[strlen(f)+1];
	strcpy(filename, f);
}

void PNMreader::Execute()
{
	// Open file
	FILE *f_in = fopen(filename, "rb");

	if (f_in)
	{
		// Read header values and pixel map
		fscanf(f_in, "%s\n%d %d\n%s\n", magicNum, &width, &height, maxval);
		Pixel *Pixmap = new Pixel[width * height];
		fread(Pixmap, 1, 3*width*height, f_in);

		// Update source's image
		GetOutput()->Reset(width, height);
		GetOutput()->SetPixmap(Pixmap);

		// Delete pixel map
		delete [] Pixmap;

		// Close file
		fclose(f_in);
     }
    else
    {
		char msg[1024];
		sprintf(msg, "Invalid filename for PNMreader: %s", filename);
		DataFlowException e(SourceName(), msg);
		throw e;
    }
}
