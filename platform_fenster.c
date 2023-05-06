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

/*
 * headers
 */

/* std */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* fenster */
#include "fenster.h"

/* platform */
#include "platform.h"

/*
 * globals
 */

struct fenster f;
int running;

/*
 * platform_init
 */

int platform_init(int w, int h, int bpp, const char *title)
{
	/* title */
	f.title = calloc(strlen(title) + 1, sizeof(char));
	memcpy(f.title, title, strlen(title) * sizeof(char));

	/* pixels */
	f.buf = calloc(w * h, sizeof(uint32_t));

	/* open */
	fenster_open(&f);

	/* return success */
	return 1;
}

/*
 * platform_quit
 */

void platform_quit()
{
	free(f.buf);
	free(f.title);
	fenster_close(&f);
}

/*
 * platform_frame_start
 */

void platform_frame_start()
{
	if (fenster_loop(&f) == 0)
		running = 1;
	else
		running = 0;
}

/*
 * platform_frame_end
 */

void platform_frame_end()
{

}

/*
 * platform_frame
 */

int platform_frame()
{
	/* run end of last frame */
	platform_frame_end();

	/* run start of this frame */
	platform_frame_start();

	/* return run status */
	return context.running;
}

/*
 * platform_screen_clear
 */

void platform_screen_clear(uint32_t c)
{
	int i;
	for (i = 0; i < f.width * f.height; i++)
		f.buf[i] = c;
}

/*
 * platform_key
 */

int platform_key(int sc)
{
	return f.keys[sc];
}

/*
 * platform_draw_pixel
 */

void platform_draw_pixel(uint16_t x, uint16_t y, uint32_t c)
{
	fenster_pixel(&f, x, y) = c;
}

/*
 * platform_mouse
 */

void platform_mouse(int *x, int *y, int *dx, int *dy)
{
	/* set ptrs */
	if (x) *x = f.x;
	if (y) *y = f.y;
}

/*
 * platform_error
 */

void platform_error(const char *s, ...)
{
	va_list ap;

	platform_quit();

	va_start(ap, s);
	vfprintf(stderr, s, ap);
	va_end(ap);

	exit(1);
}

/*
 * platform_mouse_capture
 */

void platform_mouse_capture()
{

}

/*
 * platform_mouse_release
 */

void platform_mouse_release()
{

}
