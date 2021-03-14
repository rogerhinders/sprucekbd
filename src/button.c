#include "button.h"

static void *reset_button(void *arg) {
	struct button *btn = (struct button *)arg;
	usleep(200000);

	btn->pressed = false;
	button_draw(btn);
	xserver_flush_conn();

	return NULL;
}

static void send_fake_keysym(xcb_keysym_t keysym) {
	xcb_test_fake_input(
			xserver_get_conn(),
			XCB_KEY_PRESS,
			*xcb_key_symbols_get_keycode(
				xserver_get_key_symbols(), keysym), 
			XCB_CURRENT_TIME,
			xserver_get_root_wnd()->handle,
			0,0,0);

	xcb_test_fake_input(
			xserver_get_conn(),
			XCB_KEY_RELEASE,
			*xcb_key_symbols_get_keycode(
				xserver_get_key_symbols(), keysym), 
			XCB_CURRENT_TIME,
			xserver_get_root_wnd()->handle,
			0,0,0);
}

static void send_fake_key_event(struct button *btn) {
	xcb_keysym_t key = XK_VoidSymbol;

	switch(btn->key->type) {
	case LAYOUT_KEY_TYPE_NULL:
		return;
	case LAYOUT_KEY_TYPE_SYM:
		key = btn->key->label[0];
		break;
	case LAYOUT_KEY_TYPE_ESC:
		key = XK_Escape;
		break;
	case LAYOUT_KEY_TYPE_CTRL:
		key = XK_Control_L;
		break;
	case LAYOUT_KEY_TYPE_ALT:
		key = XK_Alt_L;
		break;
	case LAYOUT_KEY_TYPE_DELETE:
		key = XK_Delete;
		break;
	case LAYOUT_KEY_TYPE_BKSPACE:
		key = XK_BackSpace;
		break;
	case LAYOUT_KEY_TYPE_MOD:
		key = XK_Super_L;
		break;
	case LAYOUT_KEY_TYPE_TAB:
		key = XK_Tab;
		break;
	case LAYOUT_KEY_TYPE_ENTER:
		key = XK_Return;
		break;
	case LAYOUT_KEY_TYPE_SHIFT:
		key = XK_Shift_L;
		break;
	}

	send_fake_keysym(key);
}

struct button *button_create(
		struct window *parent, struct layout_key *key, void (*click_handler)(),
		uint32_t x, uint32_t y){

	struct button *btn = malloc(sizeof(struct button));

	if(btn == NULL)
		return NULL;

	btn->parent = parent;
	btn->click_handler = click_handler;
	btn->key = key;

	btn->w = keyboard_unit_to_px(btn->key->units);
	btn->h = keyboard_get_key_height();
	btn->x = x;
	btn->y = y;
	btn->pressed = false;

	return btn;
}

void button_draw(struct button *btn) {
	xcb_gcontext_t gc = xserver_create_drawable_gc(
			xserver_screen_get_white(),
			xserver_screen_get_black(),
			xserver_get_root_wnd());

	xcb_gcontext_t gcp = xserver_create_drawable_gc(
			xserver_screen_get_black(),
			xserver_screen_get_white(),
			xserver_get_root_wnd());

	xcb_gcontext_t fgc = xserver_create_font_gc(
			xserver_screen_get_white(),
			xserver_screen_get_black(),
			"-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-15",
			btn->parent);

	xcb_gcontext_t fgcp = xserver_create_font_gc(
			xserver_screen_get_black(),
			xserver_screen_get_white(),
			"-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-15",
			btn->parent);

	uint32_t t_len = strlen(btn->key->label);

	/* draw border */
	xcb_rectangle_t rect = {
		btn->x, btn->y,
		btn->w, btn->h
	};

	xcb_poly_fill_rectangle(
			xserver_get_conn(),
			btn->parent->handle,
			btn->pressed ? gc : gcp,
			1,
			&rect);

	if(!btn->pressed)
		xcb_poly_rectangle(
				xserver_get_conn(),
				btn->parent->handle,
				gc,
				1,
				&rect);

	/* draw label */
	if(t_len > 0) {
		/* add padding */
		uint32_t tx = btn->x + btn->w / 2 - t_len * 10 / 2;
		uint32_t ty = btn->y + btn->h / 2 + 20 / 2;

		xcb_image_text_8(
				xserver_get_conn(),
				t_len,
				btn->parent->handle,
				btn->pressed ? fgcp : fgc,
				tx, ty,
				btn->key->label);
	}

	/* cleanup */
	xcb_free_gc(xserver_get_conn(), gc);
	xcb_free_gc(xserver_get_conn(), fgc);
	xcb_free_gc(xserver_get_conn(), fgcp);
	xcb_free_gc(xserver_get_conn(), gcp);
}

void button_onclick(struct button *btn) {
	pthread_t t_reset;

	printf("PRESS %s\n", btn->key->label);
	btn->pressed = true;

	send_fake_key_event(btn);
	button_draw(btn);

	pthread_create(&t_reset, NULL, reset_button, btn);
	xserver_flush_conn();
}
