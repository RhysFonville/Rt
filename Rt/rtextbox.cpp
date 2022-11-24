#include "rtextbox.h"

RTextBox::RTextBox(RWindow &parent_window, Position position, Size size,
	const std::string &starting_text, HMENU menu, long style, long extended_style,
	void* lpParam)
	: RWindowContentItem(parent_window, "Edit", starting_text.c_str(), position, size, menu, style, extended_style, WS_CHILD | WS_VISIBLE, lpParam) { }

std::string RTextBox::get_text() {
	char text[100];
	GetWindowTextA(*content_window, text, 100);
	std::string s(text);
	return s;
}
