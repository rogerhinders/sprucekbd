#ifndef _KEYBOARD_H
#define _KEYBOARD_H

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

#endif /* _KEYBOARD_H */
