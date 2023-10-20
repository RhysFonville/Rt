#include "rbutton.h"

RButton::RButton(RWindow &parent_window, Position position, Size size,
	const std::string &button_text, HMENU menu, long style, long extended_style,
	void* lpParam)
	: RWindowContentItem(parent_window, "Button", button_text.c_str(), position, size, menu, style,
	extended_style, WS_CHILD | WS_VISIBLE, lpParam) { }

void RButton::click() {
	SendMessageA(*content_window, BM_CLICK, NULL, NULL);
}

void RButton::is_highlighted(bool highlight) {
	SendMessageA(*content_window, BM_SETSTATE, highlight, NULL);
}

void RButton::highlight() {
	is_highlighted(true);
}

void RButton::unhighlight() {
	is_highlighted(false);
}
