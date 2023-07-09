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

//
//
// headers
//
//

// std
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// mdl
#include "mdl.h"

//
//
// globals
//
//

const char mdl_magic_quake[4] = "IDPO";
const char mdl_magic_quake2[4] = "IDP2";

//
//
// functions
//
//

//
// mdl_load
//

mdl_t *mdl_load(char *filename)
{
	// variables
	int i, num_pixels;
	mdl_t *mdl;
	FILE *file;

	// open file
	file = fopen(filename, "rb");
	if (file == NULL)
	{
		printf("error: couldn't load %s\n", filename);
		return NULL;
	}

	// allocate memory
	mdl = calloc(1, sizeof(mdl_t));

	// read header 
	fread(&mdl->header, sizeof(mdl_header_t), 1, file);

	// check file signature
	if (!memcmp(mdl->header.magic, mdl_magic_quake2, 4) != 0)
	{
		printf("error: %s is a Quake 2 model file, which is currently not supported.\n", filename);
		return NULL;
	}

	// check file signature
	if (memcmp(mdl->header.magic, mdl_magic_quake, 4) != 0)
	{
		printf("error: %s has an unrecognized file signature %x.\n", filename, mdl->header.magic);
		return NULL;
	}

	// check file version
	if (mdl->header.version == MDL_VERSION_QTEST)
	{
		printf("error: %s is a QTest model file, which is currently not supported.\n", filename);
		return NULL;
	}
	else if (mdl->header.version == MDL_VERSION_QUAKE2)
	{
		printf("error: %s is a Quake 2 model file, which is currently not supported.\n", filename);
		return NULL;
	}
	else if (mdl->header.version != MDL_VERSION_QUAKE)
	{
		printf("error: %s has an unrecognized file version.\n", filename);
		return NULL;
	}

	// calculate number of pixels 
	num_pixels = mdl->header.skin_width * mdl->header.skin_height;

	// allocate more memory
	mdl->skins = calloc(mdl->header.num_skins, sizeof(mdl_skin_t));
	mdl->texcoords = calloc(mdl->header.num_vertices, sizeof(mdl_texcoord_t));
	mdl->faces = calloc(mdl->header.num_faces, sizeof(mdl_face_t));
	mdl->frames = calloc(mdl->header.num_frames, sizeof(mdl_frame_t));

	// read skins
	for (i = 0; i < mdl->header.num_skins; i++)
	{
		fread(&mdl->skins[i].skin_type, sizeof(uint32_t), 1, file);

		if (mdl->skins[i].skin_type != 0)
		{
			fclose(file);
			printf("error: %s skin %d has an unsupported type.\n", i);
			return NULL;
		}

		mdl->skins[i].skin_pixels = calloc(num_pixels, sizeof(uint8_t));
		fread(mdl->skins[i].skin_pixels, sizeof(uint8_t), num_pixels, file);
	}

	// read texcoords
	fread(mdl->texcoords, sizeof(mdl_texcoord_t), mdl->header.num_vertices, file);

	// read faces
	fread(mdl->faces, sizeof(mdl_face_t), mdl->header.num_faces, file);

	// read frames
	for (i = 0; i < mdl->header.num_frames; i++)
	{
		fread(&mdl->frames[i].frame_type, sizeof(uint32_t), 1, file);
		fread(&mdl->frames[i].min, sizeof(mdl_vertex_t), 1, file);
		fread(&mdl->frames[i].max, sizeof(mdl_vertex_t), 1, file);
		fread(&mdl->frames[i].name, sizeof(uint8_t), 16, file);

		if (mdl->frames[i].frame_type != 0)
		{
			fclose(file);
			printf("error: %s frame %d has an unsupported type.\n", i);
			return NULL;
		}

		mdl->frames[i].vertices = calloc(mdl->header.num_vertices, sizeof(mdl_vertex_t));
		fread(mdl->frames[i].vertices, sizeof(mdl_vertex_t), mdl->header.num_vertices, file);
	}

	// close file pointer
	fclose(file);

	// return pointer to mdl container
	return mdl;
}


//
// mdl_free
//

void mdl_free(mdl_t *mdl)
{
	int i;

	if (mdl)
	{
		if (mdl->skins)
		{
			for (i = 0; i < mdl->header.num_skins; i++)
				if (mdl->skins[i].skin_pixels)
					free(mdl->skins[i].skin_pixels);

			free(mdl->skins);
		}

		if (mdl->texcoords)
			free(mdl->texcoords);

		if (mdl->faces)
			free(mdl->faces);

		if (mdl->frames)
		{
			for (i = 0; i < mdl->header.num_frames; i++)
				if (mdl->frames[i].vertices)
					free(mdl->frames[i].vertices);

			free(mdl->frames);
		}

		free(mdl);
	}
}
