#include <PNMwriter.h>

void PNMwriter::Write(const char *f)
{
	// Open file
	FILE *f_out = fopen(f, "wb");

	// Get image's dimensions
	const int width = image->GetWidth();
	const int height = image->GetHeight();

	// Write header values and pixel map
	fprintf(f_out, "P6\n%d %d\n255\n", width, height);
	fwrite(image->GetPixmap(), 1, 3 * width * height, f_out);

	// Close file
	fclose(f_out);
};
