#include "layout.h"

static struct layout_keys *keys = NULL;

static struct layout_key create_key(
		const char *symbol, enum layout_key_type type, float units) {
	struct layout_key key = { .type = type, .units = units };

	strncpy(key.label, symbol, 7);

	return key;
}
		
static struct layout_key create_sym_key_1u(const char *symbol) {
	return create_key(symbol, LAYOUT_KEY_TYPE_SYM, 1.0f);
}

static struct layout_key *get_row(uint32_t row) {
	return keys->keys + keys->cols * row;
}

static bool load_layout_default() {
	keys = malloc(sizeof(struct layout_keys));

	if(keys == NULL)
		return false;

	keys->rows = 5;
	keys->cols = 12;

	keys->keys = malloc(sizeof(struct layout_key) * keys->cols * keys->rows);

	if(keys->keys == NULL) {
		free(keys);
		return false;
	}

	struct layout_key *key = get_row(0);

	*key++ = create_key("Esc", LAYOUT_KEY_TYPE_ESC, 1.0f);
	*key++ = create_sym_key_1u("1");
	*key++ = create_sym_key_1u("2");
	*key++ = create_sym_key_1u("3");
	*key++ = create_sym_key_1u("4");
	*key++ = create_sym_key_1u("5");
	*key++ = create_sym_key_1u("6");
	*key++ = create_sym_key_1u("7");
	*key++ = create_sym_key_1u("8");
	*key++ = create_sym_key_1u("9");
	*key++ = create_sym_key_1u("0");
	*key++ = create_key("<-", LAYOUT_KEY_TYPE_BKSPACE, 1.0f);

	key = get_row(1);

	*key++ = create_key("Tab", LAYOUT_KEY_TYPE_TAB, 1.50f);
	*key++ = create_sym_key_1u("Q");
	*key++ = create_sym_key_1u("W");
	*key++ = create_sym_key_1u("E");
	*key++ = create_sym_key_1u("R");
	*key++ = create_sym_key_1u("T");
	*key++ = create_sym_key_1u("Y");
	*key++ = create_sym_key_1u("U");
	*key++ = create_sym_key_1u("I");
	*key++ = create_sym_key_1u("O");
	*key++ = create_sym_key_1u("P");
	*key++ = create_key("", LAYOUT_KEY_TYPE_NULL, 1.0f);

	key = get_row(2);

	*key++ = create_key("Control", LAYOUT_KEY_TYPE_CTRL, 1.75f);
	*key++ = create_sym_key_1u("A");
	*key++ = create_sym_key_1u("S");
	*key++ = create_sym_key_1u("D");
	*key++ = create_sym_key_1u("F");
	*key++ = create_sym_key_1u("G");
	*key++ = create_sym_key_1u("H");
	*key++ = create_sym_key_1u("J");
	*key++ = create_sym_key_1u("K");
	*key++ = create_sym_key_1u("L");
	*key++ = create_sym_key_1u("\"");
	*key++ = create_key("", LAYOUT_KEY_TYPE_NULL, 1.0f);

	key = get_row(3);

	*key++ = create_key("Shift", LAYOUT_KEY_TYPE_SHIFT, 2.0f);
	*key++ = create_sym_key_1u("Z");
	*key++ = create_sym_key_1u("X");
	*key++ = create_sym_key_1u("C");
	*key++ = create_sym_key_1u("V");
	*key++ = create_sym_key_1u("B");
	*key++ = create_sym_key_1u("N");
	*key++ = create_sym_key_1u("M");
	*key++ = create_sym_key_1u(".");
	*key++ = create_sym_key_1u(",");
	*key++ = create_sym_key_1u("/");
	*key++ = create_key("", LAYOUT_KEY_TYPE_NULL, 1.0f);

	key = get_row(4);

	*key++ = create_key("", LAYOUT_KEY_TYPE_NULL, 0.5f);
	*key++ = create_key("Alt", LAYOUT_KEY_TYPE_ALT, 1.0f);
	*key++ = create_key("Mod", LAYOUT_KEY_TYPE_MOD, 1.0f);
	*key++ = create_sym_key_1u("@");
	*key++ = create_key("", LAYOUT_KEY_TYPE_BKSPACE, 5.0f);
	*key++ = create_sym_key_1u(":");
	*key++ = create_sym_key_1u(";");
	*key++ = create_sym_key_1u("SW");
	*key++ = create_key("", LAYOUT_KEY_TYPE_NULL, 0.5f);

	return true;
}

bool layout_init(enum layout_type layout) {
	switch(layout) {
	case LAYOUT_TYPE_DEFAULT:
		if(!load_layout_default())
			return false;
		break;
	default:
		return false;
	}

	return true;
}

struct layout_keys *layout_get_keys() {
	return keys;
}
