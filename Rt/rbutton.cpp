#include "rbutton.h"

RButton::RButton(RWindow &parent_window, Position position, Size size,
	const std::string &button_text, HMENU menu, long style, long extended_style,
	void* lpParam)
	: RWindowContentItem(parent_window, position, size, menu, style, extended_style, lpParam) {

	content_window = std::make_shared<HWND>(
		CreateWindowExA(extended_style, "Button", button_text.c_str(),
			WS_CHILD | WS_VISIBLE | style, position.x, position.y, size.width, size.height,
			*parent_window.get_window(), menu, parent_window.get_hInstance(), lpParam)
	);
}