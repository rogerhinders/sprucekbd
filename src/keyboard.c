#include "keyboard.h"

static struct window *p_wnd = NULL;
static struct linked_list *l_btn = NULL;

bool keyboard_init(struct window *parent) {
	if(parent == NULL)
		return false;

	p_wnd = parent;
	l_btn = linked_list_create();
	return true;
}

void keyboard_draw() {
	struct layout_keys *keys = layout_get_keys();
	uint32_t off_x = 0;
	uint32_t off_y = 0;

	//for(int row = 0; row < keys->rows; row++) {
	for(int row = 0; row < keys->rows; row++) {
		for(int col = 0; col < keys->cols; col++) {
			//printf("%s ", keys->keys[row * keys->cols + col].label);
			struct button *btn = button_create(
					p_wnd, &keys->keys[row * keys->cols + col], NULL,
					off_x, off_y);

			linked_list_add(l_btn, btn);

			button_draw(btn);
			off_x += keyboard_unit_to_px(btn->key->units);
		}
		off_x = 0;
		off_y += keyboard_get_key_height();
		//printf("\n");
	}

	xserver_flush_conn();
}

void keyboard_cleanup() {
	struct button *btn;

	linked_list_rewind(l_btn);

	while((btn = linked_list_next(l_btn)) != NULL) {
		free(btn);
	}

	linked_list_destroy(l_btn);
}

uint32_t keyboard_unit_to_px(float unit) {
	uint32_t u1 = (xserver_get_root_wnd()->w / 2) / layout_get_keys()->cols;
	return u1 * unit;
}

uint32_t keyboard_get_key_height() {
	return keyboard_unit_to_px(1.0f);
}

void keyboard_onclick(uint32_t x, uint32_t y) {
	struct button *btn;
	linked_list_rewind(l_btn);

	while((btn = linked_list_next(l_btn)) != NULL) {
		if(x > btn->x && x < btn->x + btn->w && 
				y > btn->y && y < btn->y + btn->h)
			button_onclick(btn);
	}
}
