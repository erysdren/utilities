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

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* bitswap */
#include "bitswap.h"

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/* bit swap int16_t */
int16_t bitswap_int16(int16_t *val)
{
	*val = (*val << 8) | ((*val >> 8) & 0xFF);

	return *val;
}

/* bit swap uint16_t */
uint16_t bitswap_uint16(uint16_t *val)
{
	*val = (*val << 8) | (*val >> 8);

	return *val;
}

/* bit swap int32_t */
int32_t bitswap_int32(int32_t *val)
{
	int32_t out;

	out = ((*val << 8) & 0xFF00FF00) | ((*val >> 8) & 0xFF00FF);
	*val = (out << 16) | ((out >> 16) & 0xFFFF);

	return *val;
}

/* bit swap uint32_t */
uint32_t bitswap_uint32(uint32_t *val)
{
	uint32_t out;

	out = ((*val << 8) & 0xFF00FF00) | ((*val >> 8) & 0xFF00FF);
	*val = (out << 16) | (out >> 16);

	return *val;
}

/* bit swap int64_t */
int64_t bitswap_int64(int64_t *val)
{
	int64_t out;

	out = ((*val << 8) & 0xFF00FF00FF00FF00ULL) | ((*val >> 8) & 0x00FF00FF00FF00FFULL);
	out = ((out << 16) & 0xFFFF0000FFFF0000ULL) | ((out >> 16) & 0x0000FFFF0000FFFFULL);
	*val = (out << 32) | ((out >> 32) & 0xFFFFFFFF);

	return *val;
}

/* bit swap uint64_t */
uint64_t bitswap_uint64(uint64_t *val)
{
	uint64_t out;

	out = ((*val << 8) & 0xFF00FF00FF00FF00ULL) | ((*val >> 8) & 0x00FF00FF00FF00FFULL);
	out = ((out << 16) & 0xFFFF0000FFFF0000ULL) | ((out >> 16) & 0x0000FFFF0000FFFFULL);
	*val = (out << 32) | (out >> 32);

	return *val;
}
