#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MIN(a,b)	((a)<(b) ? (a):(b))
#define MAX(a,b)	((a)>(b) ? (a):(b))
#define CLAMP_RGB(v)	MIN(255, MAX(0, v))

const double R_SCALAR      = +1.402;
const double G_SCALAR_1    = -0.344136;
const double G_SCALAR_2    = -0.714136;
const double B_SCALAR      = +1.772;
const int    CHROMA_OFFSET = -128;

void yuy2_to_rgb(const uint8_t* yuy2, uint8_t* rgb, size_t n_pixels)
{
	size_t yuy2_offset        = 0;
	size_t rgb_offset         = 0;
	size_t n_pixels_converted = 0;

	while (n_pixels_converted < n_pixels)
	{
		// Get set of two pixels (Y1, Y2) and their chromas (U, V).
		int Y1 = yuy2[yuy2_offset + 0];
		int U  = yuy2[yuy2_offset + 1];
		int Y2 = yuy2[yuy2_offset + 2];
		int V  = yuy2[yuy2_offset + 3];


		// Convert both pixels to RGB format.
		V += CHROMA_OFFSET;
		U += CHROMA_OFFSET;

		int r1 = Y1 + R_SCALAR   * V;
		int g1 = Y1 + G_SCALAR_1 * U + G_SCALAR_2 * V;
		int b1 = Y1 + B_SCALAR   * U;

		int r2 = Y2 + R_SCALAR   * V;
		int g2 = Y2 + G_SCALAR_1 * U + G_SCALAR_2 * V;
		int b2 = Y2 + B_SCALAR   * U;


		// Write both RGB pixels.
		rgb[rgb_offset + 0] = CLAMP_RGB(r1);
		rgb[rgb_offset + 1] = CLAMP_RGB(g1);
		rgb[rgb_offset + 2] = CLAMP_RGB(b1);
		rgb[rgb_offset + 3] = CLAMP_RGB(r2);
		rgb[rgb_offset + 4] = CLAMP_RGB(g2);
		rgb[rgb_offset + 5] = CLAMP_RGB(b2);

		yuy2_offset        += 4;
		rgb_offset         += 6;
		n_pixels_converted += 2;
	}
}

void convert(const char* infile, const char* outfile)
{
	uint8_t* indata = NULL;
	uint8_t* outdata = NULL;
	FILE* fp = NULL;
	int infilesize = 0;
	int outfilesize = 0;
	size_t n_read = 0;
	size_t n_written = 0;

	// Read input file into buffer.
	fp = fopen(infile, "rb");
	if (!fp)
	{
		fprintf(stderr, "Failed to open '%s'\n", infile);
		goto done;
	}

	fseek(fp, 0L, SEEK_END);
	infilesize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	printf("%s is %d bytes\n", infile, infilesize);

	indata = (uint8_t*)malloc(infilesize);
	n_read = fread(indata, 1, infilesize, fp);
	if (n_read != infilesize)
	{
		fprintf(stderr, "Failed to read whole file\n");
		goto done;
	}
	fclose(fp);
	fp = NULL;

	// Convert YUY2 data to RGB and write to file.
	outfilesize = (infilesize / 2) * 3;
	printf("%s will be %d bytes\n", outfile, outfilesize);
	outdata = (uint8_t*)malloc(outfilesize);

	yuy2_to_rgb(indata, outdata, outfilesize / 3);

	fp = fopen(outfile, "wb");
        if (!fp)
        {
                fprintf(stderr, "Failed to open '%s'\n", outfile);
                goto done;
        }
	n_written = fwrite(outdata, 1, outfilesize, fp);
	if (n_written != outfilesize)
	{
		fprintf(stderr, "Failed to write whole file\n");
		goto done;
	}
	fclose(fp);
	fp = NULL;

done:
	if (fp)
		fclose(fp);
	if (indata)
		free(indata);
	if (outdata)
		free(outdata);
	return;
}

int main(int argc, char* argv[])
{
	convert(argv[1], argv[2]);
	return 0;
}
