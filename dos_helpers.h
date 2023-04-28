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
#ifndef __DOS_H__
#define __DOS_H__
#ifdef __cplusplus
extern "C" {
#endif

/*
 * this file is special. we need to trigger a failure
 * if its not being compiled by a supported dos compiler
 */
#if !defined(__DJGPP__) && !defined(__WATCOMC__)
#error i can only be compiled with watcom or djgpp!
#endif

/* *************************************
 *
 * the headers
 *
 * ********************************** */

/* std */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* shared dos headers */
#if defined(__DJGPP__) || defined(__WATCOMC__)

/* standard dos headers */
#include <dos.h>
#include <io.h>
#include <conio.h>

#endif

/* watcom headers */
#ifdef __WATCOMC__

#include <i86.h>
#include <graph.h>

#endif

/* djgpp headers */
#ifdef __DJGPP__

#include <dpmi.h>
#include <go32.h>
#include <sys/nearptr.h>
#include <sys/farptr.h>

#endif

/* *************************************
 *
 * the text macros
 *
 * ********************************** */

/*
 * standard video modes supported by all vga cards
 */

#define DOS_MODE_0 0x0				/* 40×25, text, 16 colors */
#define DOS_MODE_1 0x1				/* 40×25, text, 16 colors */
#define DOS_MODE_2 0x2				/* 80×25, text, 16 colors */
#define DOS_MODE_3 0x3				/* 80×25, text, 16 colors */
#define DOS_MODE_4 0x4				/* 320x200, graphics, 4 colors */
#define DOS_MODE_5 0x5				/* 320x200, graphics, 4 colors */
#define DOS_MODE_6 0x6				/* 640x200, graphics, 2 colors */
#define DOS_MODE_7 0x7				/* 80×25, text, monochrome */
#define DOS_MODE_D 0xD				/* 320x200, graphics, 16 colors */
#define DOS_MODE_E 0xE				/* 640x200, graphics, 16 colors */
#define DOS_MODE_F 0xF				/* 640x350, graphics, monochrome */
#define DOS_MODE_10 0x10			/* 640x350, graphics, 16 colors */
#define DOS_MODE_11 0x11			/* 640x480, graphics, 2 colors */
#define DOS_MODE_12 0x12			/* 640x480, graphics, 16 colors */
#define DOS_MODE_13 0x13			/* 320x200, graphics, 256 colors */

/*
 * cursor shapes available in text mode
 */

#define DOS_CURSOR_NONE 0x2000		/* no cursor */
#define DOS_CURSOR_BLOCK 0x0007		/* solid block cursor */
#define DOS_CURSOR_LINE 0x0607		/* default underline cursor */

/*
 * mouse button masks
 */

#define DOS_MOUSE_LMB 0x1
#define DOS_MOUSE_RMB 0x2

/* *************************************
 *
 * the types
 *
 * ********************************** */

/* pointers to memory locations */
#ifdef __DJGPP__
#define DOS_GRAPHICS_MEMORY (0xA0000 + __djgpp_conventional_base)
#define DOS_TEXT_MEMORY (0xB8000 + __djgpp_conventional_base)
#else
#define DOS_GRAPHICS_MEMORY (0xA0000L)
#define DOS_TEXT_MEMORY (0xB8000L)
#endif

/* *************************************
 *
 * the forward declarations
 *
 * ********************************** */

/* mode-agnostic functions */
static void dos_set_mode(uint16_t mode);
static int dos_get_mode();
static void dos_clear_screen();

/* graphics mode functions */
static void dos_graphics_clear_screen();
static void dos_graphics_putb(uint8_t *s, size_t n);
static void dos_set_palette_color(uint8_t i, uint8_t r, uint8_t g, uint8_t b);

/* text mode functions */
static void dos_text_set_cursor_shape(uint16_t shape);
static void dos_text_set_cursor_pos(uint16_t x, uint16_t y);
static void dos_text_get_cursor_pos(uint16_t *x, uint16_t *y);
static void dos_text_clear_screen();
static int dos_text_get_screen_columns();
static int dos_text_get_screen_rows();
static void dos_text_get_screen_size(int *w, int *h);
static int dos_text_get_attributes();
static void dos_text_putb(uint16_t x, uint16_t y, uint16_t *s, size_t n);
static void dos_text_puts(uint16_t x, uint16_t y, const char *s);
static void dos_text_putc(uint16_t x, uint16_t y, char c);

/* microsoft mouse */
static void dos_mouse_enable();
static void dos_mouse_show();
static void dos_mouse_hide();
static void dos_mouse_get(int16_t *x, int16_t *y, int16_t *b);
static void dos_mouse_set(int16_t x, int16_t y, int16_t b);

/* *************************************
 *
 * the functions
 *
 * ********************************** */

/*
 * mode-agnostic functions
 */

/* set mode of vga adapter */
static void dos_set_mode(uint16_t mode)
{
	union REGS r;
	r.w.ax = mode;
	int386(0x10, &r, &r);
}

/* get mode of vga adapter */
static int dos_get_mode()
{
	union REGS r;
	r.h.ah = 0x0f;
	int386(0x10, &r, &r);
	return r.h.al;
}

/* clear both video mode and text mode screen memory */
static void dos_clear_screen()
{
	dos_graphics_clear_screen();
	dos_text_clear_screen();
}

/*
 * graphics mode functions
 */

/* clear vga screen buffer */
static void dos_graphics_clear_screen()
{
	memset((void *)DOS_GRAPHICS_MEMORY, 0, 64000);
	dos_text_set_cursor_pos(0, 0);
}

/* place n 1-byte segments from pointer s to the graphics memory */
static void dos_graphics_putb(uint8_t *s, size_t n)
{
	/* sanity check */
	if (n > 64000) return;
	memcpy((void *)DOS_GRAPHICS_MEMORY, (void *)s, n * sizeof(uint8_t));
}

/* set a color in the palette */
void dos_set_palette_color(uint8_t i, uint8_t r, uint8_t g, uint8_t b)
{
	outp(0x3c8, i);
	outp(0x3c9, (r * 63) / 255);
	outp(0x3c9, (g * 63) / 255);
	outp(0x3c9, (b * 63) / 255);
}

/*
 * text mode functions
 */

/* set the shape of the cursor */
static void dos_text_set_cursor_shape(uint16_t shape)
{
	union REGS r;
	r.h.ah = 1;
	r.w.cx = shape;
	int386(0x10, &r, &r);
}

/* set text cursor position */
static void dos_text_set_cursor_pos(uint16_t x, uint16_t y)
{
	union REGS r;
	r.h.ah = 2;
	r.h.bh = 0;
	r.h.dh = y;
	r.h.dl = x;
	int386(0x10, &r, &r);
}

/* get text cursor position */
static void dos_text_get_cursor_pos(uint16_t *x, uint16_t *y)
{
	union REGS r;
	r.h.ah = 3;
	r.h.bh = 0;
	int386(0x10, &r, &r);
	if (x) *x = r.h.dl;
	if (y) *y = r.h.dh;
}

/* clear text screen buffer */
static void dos_text_clear_screen()
{
	/* variables */
	size_t s;
	uint16_t c;
	uint16_t *vidmem;

	/* calculate screen size */
	s = dos_text_get_screen_rows() * dos_text_get_screen_columns();

	/* text value we're putting in */
	c = ' ' | (dos_text_get_attributes() << 8);

	/* set memory */
	vidmem = (uint16_t *)DOS_TEXT_MEMORY;
	while (s--) *vidmem++ = c;

	/* reset cursor pos */
	dos_text_set_cursor_pos(0, 0);
}

/* get text screen columns */
static int dos_text_get_screen_columns()
{
	#ifdef __DJGPP__
	return _farpeekb(_dos_ds, 0x44a);
	#else
	return *(char *)0x44a;
	#endif
}

/* get text screen rows */
static int dos_text_get_screen_rows()
{
	#ifdef __DJGPP__
	return _farpeekb(_dos_ds, 0x484) + 1;
	#else
	return *(char *)0x484 + 1;
	#endif
}

/* get text screen size */
static void dos_text_get_screen_size(int *rows, int *columns)
{
	if (rows) *rows = dos_text_get_screen_rows();
	if (columns) *columns = dos_text_get_screen_columns();
}

/* retrieve current text attributes */
static int dos_text_get_attributes()
{
	union REGS r;
	r.h.ah = 0x08;
	r.h.bh = 0;
	int386(0x10, &r, &r);

	return r.h.ah;
}

/* place n 2-byte segments from pointer s to the text memory */
static void dos_text_putb(uint16_t x, uint16_t y, uint16_t *s, size_t n)
{
	/* variables */
	size_t max, rows, cols, ofs;

	/* set variables */
	rows = dos_text_get_screen_rows();
	cols = dos_text_get_screen_columns();
	max = rows * cols;
	ofs = (y * cols + x) * sizeof(uint16_t);

	/* sanity checks */
	if (n > max) return;

	/* do copy */
	memcpy((void *)(DOS_TEXT_MEMORY + ofs), (void *)s, n * sizeof(uint16_t));
}

/* place char sequence s at column x, row y */
static void dos_text_puts(uint16_t x, uint16_t y, const char *s)
{
	/* variables */
	int i;

	/* perform put loop */
	for (i = 0; i < strlen(s); i++)
		dos_text_putc(x + i, y, s[i]);
}

/* place char c at column x, row y */
static void dos_text_putc(uint16_t x, uint16_t y, char c)
{
	((uint16_t *)DOS_TEXT_MEMORY)[y * dos_text_get_screen_columns() + x] = 
		c | (dos_text_get_attributes() << 8);
}

/*
 * microsoft mouse
 */

/* enable mouse driver */
static void dos_mouse_enable()
{
	union REGS r;
	r.w.ax = 0x00;
	int386(0x33, &r, &r);
}

/* show mouse cursor */
static void dos_mouse_show()
{
	union REGS r;
	r.w.ax = 0x01;
	int386(0x33, &r, &r);
}

/* hide mouse cursor */
static void dos_mouse_hide()
{
	union REGS r;
	r.w.ax = 0x02;
	int386(0x33, &r, &r);
}

/* get mouse values */
static void dos_mouse_get(int16_t *x, int16_t *y, int16_t *b)
{
	union REGS r;
	r.w.ax = 0x03;
	int386(0x33, &r, &r);
	if (b) *b = r.w.bx;
	if (x) *x = r.w.cx;
	if (y) *y = r.w.dx;
}

/* set mouse values */
static void dos_mouse_set(int16_t x, int16_t y, int16_t b)
{
	union REGS r;
	r.w.ax = 0x04;
	r.w.bx = b;
	r.w.cx = x;
	r.w.dx = y;
	int386(0x33, &r, &r);
}

/* guards */
#ifdef __cplusplus
}
#endif
#endif /* __DOS_H__ */
