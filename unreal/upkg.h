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

/* guard */
#pragma once
#ifndef __UPKG_H__
#define __UPKG_H__
#ifdef __cplusplus
extern "C" {
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* std */
#include <stdio.h>
#include <stdint.h>

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* upkg generation */
typedef struct upkg_generation_t
{
	int32_t num_exports;
	int32_t num_names;
} upkg_generation_t;

/* upkg name */
typedef struct upkg_name_t
{
	uint8_t len_name;
	char *name;
	uint32_t flags;
} upkg_name_t;

/* upkg export */
typedef struct upkg_export_t
{
	int32_t class_index;		/* compact index */
	int32_t super_index;		/* compact index */
	int32_t package_index;
	int32_t object_name;		/* compact index */
	uint32_t object_flags;
	int32_t len_serial;		/* compact index */
	int32_t ofs_serial;		/* compact index */
} upkg_export_t;

/* upkg import */
typedef struct upkg_import_t
{
	int32_t class_package;	/* compact index */
	int32_t class_name;		/* compact index */
	int32_t package_index;
	int32_t object_name;		/* compact index */
} upkg_import_t;

/* upkg */
typedef struct upkg_t
{
	uint32_t tag;
	uint16_t format_version;
	uint16_t licensee_version;
	uint32_t package_flags;
	int32_t num_names;
	int32_t ofs_names;
	int32_t num_exports;
	int32_t ofs_exports;
	int32_t num_imports;
	int32_t ofs_imports;
	uint32_t guid[4];
	int32_t num_generations;
	upkg_generation_t *generations;
	upkg_name_t *names;
	upkg_export_t *exports;
	upkg_import_t *imports;
	FILE *handle;
} upkg_t;

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* opening and closing upackages */
upkg_t *upkg_open(const char *filename);
void upkg_close(upkg_t *upkg);

/* utility functions */
int32_t upkg_read_compact_index(FILE *stream);
void upkg_print_members(upkg_t *upkg, FILE *stream);

/* guard */
#ifdef __cplusplus
}
#endif
#endif /* __UPKG_H__ */
