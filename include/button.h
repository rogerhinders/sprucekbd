#ifndef _BUTTON_H
#define _BUTTON_H

/* define to enable x11 keycodes from ksymdef */
#define XK_MISCELLANY

#include <pthread.h>
#include <unistd.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xtest.h>
#include <xcb/xcb_keysyms.h>
#include <X11/keysymdef.h>
#include "general.h"
#include "xserver.h"
#include "layout.h"
#include "window.h"
#include "keyboard.h"

struct button {
	struct window *parent;
	struct layout_key *key;
	void (*click_handler)();
	uint32_t x, y, w, h;
	bool pressed;
};

struct button *button_create(
		struct window *parent, struct layout_key *key, void (*click_handler)(),
		uint32_t x, uint32_t y);
void button_draw(struct button *btn);
void button_onclick(struct button *btn);
#endif /* _BUTTON_H */
