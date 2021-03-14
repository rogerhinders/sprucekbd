#ifndef _LAYOUT_H
#define _LAYOUT_H

#include <string.h>
#include "general.h"
#include "xserver.h"

enum layout_type {
	LAYOUT_TYPE_DEFAULT
};

enum layout_key_type {
	LAYOUT_KEY_TYPE_NULL,
	LAYOUT_KEY_TYPE_SYM,
	LAYOUT_KEY_TYPE_ESC,
	LAYOUT_KEY_TYPE_CTRL,
	LAYOUT_KEY_TYPE_ALT,
	LAYOUT_KEY_TYPE_DELETE,
	LAYOUT_KEY_TYPE_BKSPACE,
	LAYOUT_KEY_TYPE_MOD,
	LAYOUT_KEY_TYPE_TAB,
	LAYOUT_KEY_TYPE_ENTER,
	LAYOUT_KEY_TYPE_SHIFT
};

struct layout_key {
	char label[8];
	enum layout_key_type type;
	float units;
};

struct layout_keys {
	struct layout_key *keys;
	uint32_t rows;
	uint32_t cols;
};

bool layout_init(enum layout_type layout);
struct layout_keys *layout_get_keys();

#endif /* _LAYOUT_H */
