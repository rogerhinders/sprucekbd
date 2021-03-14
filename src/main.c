#include <xcb/xcb.h>
#include <xcb/xcb_icccm.h>
#include <xcb/xcb_keysyms.h>
#include "general.h"
#include "xserver.h"
#include "layout.h"
#include "keyboard.h"


int main() {
	int32_t ret = EXIT_SUCCESS;
	uint32_t v_mask;
	uint32_t v_list[2];

	if(!xserver_init()) {
		ret = EXIT_FAILURE;
		goto _main_cleanup;
	}

	if(!layout_init(LAYOUT_TYPE_DEFAULT)) {
		ret = EXIT_FAILURE;
		goto _main_cleanup;
	}


	struct window *k_wnd = window_create(
			xcb_generate_id(xserver_get_conn()));

	if(!keyboard_init(k_wnd)) {
		ret = EXIT_FAILURE;
		goto _main_cleanup;
	}

	window_setsize(k_wnd, xserver_get_root_wnd()->w/2, 800);

	v_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	v_list[0] = xserver_screen_get_white();
	v_list[1] = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_EXPOSURE;

	xcb_create_window(
			xserver_get_conn(),
			xserver_screen_get_depth(),
			k_wnd->handle,
			xserver_get_root_wnd()->handle,
			k_wnd->x,
			k_wnd->y,
			k_wnd->w,
			k_wnd->h,
			1,
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			xserver_screen_get_visual(),
			v_mask,
			v_list);

	xserver_map_window(k_wnd);

	xcb_icccm_wm_hints_t wm_hints;
	xcb_icccm_wm_hints_set_none(&wm_hints);
	xcb_icccm_wm_hints_set_input(&wm_hints, 0);
	xcb_icccm_set_wm_hints(
			xserver_get_conn(),
			k_wnd->handle,
			&wm_hints);
	xserver_flush_conn();


	xcb_generic_event_t *ev;
	xcb_button_press_event_t *bev;

	while((ev = xcb_wait_for_event(xserver_get_conn()))) {
		switch(ev->response_type) {
		case XCB_EXPOSE:
			printf("expose!\n");
			keyboard_draw();
			break;
		case XCB_BUTTON_PRESS:
			bev = (xcb_button_press_event_t *)ev;
			printf("presss\n");

			if(k_wnd != NULL && bev->event == k_wnd->handle)
				keyboard_onclick(bev->event_x, bev->event_y);

			break;
		default:
			break;
		}
	}

_main_cleanup:
	keyboard_cleanup();
	return ret;
}
