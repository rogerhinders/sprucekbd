#ifndef _WINDOW_H
#define _WINDOW_H

#include <xcb/xcb.h>
#include <string.h>
#include "general.h"

#define WINDOW_NAME_MAXLEN 255

struct window {
	xcb_window_t handle;
	uint32_t x, y, w, h;
	char name[WINDOW_NAME_MAXLEN];
};

struct window *window_create(xcb_window_t handle);
void window_destroy(struct window *wnd);
void window_setcoords(struct window *wnd, uint32_t x, uint32_t y);
void window_setsize(struct window *wnd, uint32_t w, uint32_t h);
void window_setname(struct window *wnd, const char *name);

#endif /* _WINDOW_H */
