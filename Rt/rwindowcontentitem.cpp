#include "rwindowcontentitem.h"

RWindowContentItem::RWindowContentItem(RWindow &parent_window, const std::string &class_name, const std::string &window_name, const Position &position,
	const Size &size, HMENU menu, long style, long extended_style, long default_style, void* lpParam) :
	parent_window(parent_window), class_name(class_name), window_name(window_name), position(position), size(size), menu(menu), style(style),
	extended_style(extended_style), default_style(default_style), lpParam(lpParam) {

	create_window();
}

void RWindowContentItem::create_window(bool show_window) {
	content_window = std::make_shared<HWND>(
	CreateWindowExA(extended_style, class_name.c_str(), window_name.c_str(),
		default_style | style, position.x, position.y, size.x, size.y,
		*parent_window.get_window(), menu, parent_window.get_hInstance(), lpParam)
	);
	if (show_window)
		ShowWindow(*content_window, SW_SHOW);
}

const std::shared_ptr<HWND> & RWindowContentItem::get_window() {
	return content_window;
}

RWindow & RWindowContentItem::get_parent_window() {
	return parent_window;
}

void RWindowContentItem::set_parent_window(RWindow &window) {
	parent_window = window;
	SetParent(*content_window, *window.get_window());
}

Position RWindowContentItem::get_position() const noexcept {
	return position;
}

void RWindowContentItem::set_position(const Position &position) noexcept {
	SetWindowPos(*content_window, NULL, position.x, position.y, NULL, NULL, SWP_NOSIZE);
	this->position = position;
}

Size RWindowContentItem::get_size() const noexcept {
	return size;
}

void RWindowContentItem::set_size(const Size &size) noexcept {
	SetWindowPos(*content_window, NULL, NULL, NULL, size.x, size.y, SWP_NOREPOSITION);
	this->size = size;
}

HMENU RWindowContentItem::get_menu() const noexcept {
	return menu;
}

void RWindowContentItem::set_menu(HMENU menu) noexcept {
	SetMenu(*content_window, menu);
	this->menu = menu;
}

long RWindowContentItem::get_style() const noexcept {
	return style;
}

void RWindowContentItem::set_style(long style) noexcept {
	LONG_PTR style_ptr = SetWindowLongPtrW(*content_window, GWL_STYLE, style);
	SetWindowPos(*content_window, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_SHOWWINDOW);
	this->style = style;
}

long RWindowContentItem::get_extended_style() const noexcept {
	return extended_style;
}

void RWindowContentItem::set_extended_style(long extended_style) noexcept {
	LONG_PTR style_ptr = SetWindowLongPtrW(*content_window, GWL_EXSTYLE, style);
	SetWindowPos(*content_window, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_SHOWWINDOW);
	this->extended_style = extended_style;
}

void* RWindowContentItem::get_lpParam() const noexcept {
	return lpParam;
}

void RWindowContentItem::set_lpParam(void* lpParam) noexcept {
	this->lpParam = lpParam;
}

