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

/* guards */
#pragma once
#ifndef __RGB_H__
#define __RGB_H__
#ifdef __cplusplus
extern "C" {
#endif

/*
 * headers
 */

#include <stdint.h>

/*
 * rgb packing macros
 */

#define RGBA8888(r, g, b, a) ((((uint32_t)(r)) << 24) | \
	(((uint32_t)(g)) << 16) | (((uint32_t)(b)) << 8) | ((uint32_t)(a)))

#define ARGB8888(r, g, b, a) ((((uint32_t)(a)) << 24) | \
	(((uint32_t)(r)) << 16) | (((uint32_t)(g)) << 8) | ((uint32_t)(b)))

#define ABGR8888(r, g, b, a) ((((uint32_t)(a)) << 24) | \
	(((uint32_t)(b)) << 16) | (((uint32_t)(g)) << 8) | ((uint32_t)(r)))

#define RGB565(r, g, b) ((((((uint16_t)(r)) >> 3) & 0x1f) << 11) | \
	(((((uint16_t)(g)) >> 2) & 0x3f) << 5) | ((((uint16_t)(b)) >> 3) & 0x1f))

/* guards */
#ifdef __cplusplus
}
#endif
#endif /* __RGB_H__ */
