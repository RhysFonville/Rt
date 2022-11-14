#include "rtextbox.h"

RTextBox::RTextBox(RWindow &parent_window, Position position, Size size,
	const std::string &starting_text, HMENU menu, long style, long extended_style,
	void* lpParam)
	: RWindowContentItem(parent_window, position, size, menu, style, extended_style, lpParam) {

	content_window = std::make_shared<HWND>(
		CreateWindowExA(extended_style, "Edit", starting_text.c_str(),
		WS_CHILD | WS_VISIBLE | style, position.x, position.y, size.width, size.height,
		*parent_window.get_window(), menu, parent_window.get_hInstance(), lpParam)
	);
}

std::string RTextBox::get_text() {
	wchar_t text[100];
	GetWindowTextW(*content_window, text, 100);
	std::wstring s(text);
	return wstring_to_string(s);
}
