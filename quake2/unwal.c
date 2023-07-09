/* ****************************************************************************
 *
 * ANTI-CAPITALIST SOFTWARE LICENSE (v 1.4)
 *
 * Copyright © 2023 erysdren (it/they/she)
 *
 * This is anti-capitalist software, released for free use by individuals
 * and organizations that do not operate by capitalist principles.
 *
 * Permission is hereby granted, free of charge, to any person or
 * organization (the "User") obtaining a copy of this software and
 * associated documentation files (the "Software"), to use, copy, modify,
 * merge, distribute, and/or sell copies of the Software, subject to the
 * following conditions:
 *
 *   1. The above copyright notice and this permission notice shall be
 *   included in all copies or modified versions of the Software.
 *
 *   2. The User is one of the following:
 *     a. An individual person, laboring for themselves
 *     b. A non-profit organization
 *     c. An educational institution
 *     d. An organization that seeks shared profit for all of its members,
 *     and allows non-members to set the cost of their labor
 *
 *   3. If the User is an organization with owners, then all owners are
 *   workers and all workers are owners with equal equity and/or equal vote.
 *
 *   4. If the User is an organization, then the User is not law enforcement
 *   or military, or working for or under either.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT EXPRESS OR IMPLIED WARRANTY OF
 * ANY KIND, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ************************************************************************* */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "palette.h"

typedef struct
{
	char name[32];
	int32_t width;
	int32_t height;
	int32_t mipmap_offsets[4];
	char next_name[32];
	uint32_t flags;
	uint32_t contents;
	uint32_t value;
} wal_t;

bool strext(char *str, char *ext)
{
	char *ptr = str + strlen(str) - strlen(ext);
	return strcmp(ptr, ext) == 0 ? true : false;
}

void changeext(char *str, char *ext)
{
	char *ptr = str + strlen(str) - strlen(ext);
	strcpy(ptr, ext);
}

int main(int argc, char *argv[])
{
	int i, p;
	uint8_t c;
	wal_t wal;
	FILE *file;
	uint8_t *pixels;

	if (argc < 2)
	{
		printf("useage: unwal file.wal\n");
		return 0;
	}

	for (i = 1; i < argc; i++)
	{
		// talk to you
		printf("processing %s\n", argv[i]);

		// check ext
		if (!strext(argv[i], ".wal") && !strext(argv[1], ".WAL"))
		{
			printf("%s has no WAL extension, will not try!\n", argv[i]);
			continue;
		}

		// open file
		file = fopen(argv[i], "rb");
		if (!file)
		{
			printf("failed to open %s!\n", argv[i]);
			continue;
		}

		// read wad header
		fread(&wal, sizeof(wal_t), 1, file);

		// alloc pixel buffer
		pixels = malloc(wal.width * wal.height * 3);

		// seek to mip 0
		fseek(file, wal.mipmap_offsets[0], SEEK_SET);

		// convert to rgba
		for (p = 0; p < wal.width * wal.height; p++)
		{
			c = fgetc(file);
			pixels[p * 3] = palette_data[c * 3];
			pixels[(p * 3) + 1] = palette_data[(c * 3) + 1];
			pixels[(p * 3) + 2] = palette_data[(c * 3) + 2];
		}

		// change output filename
		changeext(argv[i], ".png");

		// write png
		stbi_write_png(argv[i], wal.width, wal.height, 3, pixels, wal.width * 3);

		// talk to you
		printf("saved %s\n", argv[i]);

		// free memory
		free(pixels);
		fclose(file);
	}

	return 0;
}
