/*-
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <tobias.rehbein@web.de> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.
 *                                                              Tobias Rehbein
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>
#include <wand/MagickWand.h>

void usage(void);

int
main(int argc, char **argv)
{
	MagickWandGenesis();

	char *infile = NULL, *outfile = NULL;
	int times = 1;

	int opt;
	while ((opt = getopt(argc, argv, "ht:i:o:")) != -1) {
		switch (opt) {
			case 't':
				times = strtol(optarg, (char **)NULL, 10);
				if (times <= 0)
					times = 1;
				break;
			case 'i':
				infile = strdup(optarg);
				break;
			case 'o':
				outfile = strdup(optarg);
				break;
			case 'h':
			default:
				usage();
		}
	}

	if (infile == NULL || outfile == NULL)
		usage();

	MagickWand *wand = NewMagickWand();
	if (MagickReadImage(wand, infile) == MagickFalse)
		err(EXIT_FAILURE, "could not read image: %s\n", infile);

	PixelIterator *iterator = NewPixelIterator(wand);
	if (iterator == NULL)
		err(EXIT_FAILURE, "could not create PixelIterator");

	size_t height = MagickGetImageHeight(wand);
	double dhue = 1.0 / height * times;
	double nhue = 0;

	for (size_t y = 0; y < height; y++) {
		size_t width;
		PixelWand **pixels = PixelGetNextIteratorRow(iterator, &width);
		if (pixels == NULL)
			err(EXIT_FAILURE, "could not PixelGetNextIteratorRow");;

		for (size_t x = 0; x < width; x++) {
			double hue, sat, lightness;

			PixelGetHSL(pixels[x], &hue, &sat, &lightness);
			PixelSetHSL(pixels[x], nhue, 1, lightness);
		}

		nhue += dhue;
		if (nhue >= 1)
			nhue = 0;

		PixelSyncIterator(iterator);
	}

	MagickWriteImages(wand, outfile , MagickTrue);

	DestroyPixelIterator(iterator);
	DestroyMagickWand(wand);
	MagickWandTerminus();

	return (EXIT_SUCCESS);
}

void usage(void)
{
	printf("usage: %s [-t times] -i <infile> -o <outfile>\n", getprogname());
	exit(1);
}
