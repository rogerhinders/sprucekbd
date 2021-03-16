#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include "general.h"
#include "layout.h"
#include "button.h"
#include "window.h"
#include "linked_list.h"

bool keyboard_init(struct window *parent);
void keyboard_draw();
void keyboard_cleanup();
uint32_t keyboard_unit_to_px(float unit);
uint32_t keyboard_get_key_height();
void keyboard_onclick(uint32_t x, uint32_t y);
void keyboard_enable_dock_mode();
uint32_t keyboard_get_height();

#endif /* _KEYBOARD_H */
