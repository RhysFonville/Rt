#include "rwindowcontentitem.h"

RWindowContentItem::RWindowContentItem(RWindow &parent_window, const Position &position,
	const Size &size, HMENU menu, long style, long extended_style, void* lpParam) :
	parent_window(parent_window), position(position), size(size), menu(menu), style(style),
	extended_style(extended_style), lpParam(lpParam) { }

const std::shared_ptr<HWND> & RWindowContentItem::get_window() {
	return content_window;
}

RWindow & RWindowContentItem::get_parent_window() {
	return parent_window;
}

void RWindowContentItem::set_parent_window(RWindow &window) {
	parent_window = window;
}

Position RWindowContentItem::get_position() const noexcept {
	return position;
}

void RWindowContentItem::set_position(const Position &position) noexcept {
	SetWindowPos(*content_window, NULL, position.x, position.y, NULL, NULL, SWP_NOSIZE);
}

Size RWindowContentItem::get_size() const noexcept {
	return size;
}

void RWindowContentItem::set_size(const Size &size) noexcept {
	SetWindowPos(*content_window, NULL, NULL, NULL, size.width, size.height, SWP_NOREPOSITION);
}

HMENU RWindowContentItem::get_menu() const noexcept {
	return menu;
}

void RWindowContentItem::set_menu(HMENU menu) noexcept {
	SetMenu(*content_window, menu);
}

long RWindowContentItem::get_style() const noexcept {
	return style;
}

void RWindowContentItem::set_style(long style) noexcept {
	SetWindowLongA(*content_window, GWL_STYLE, style);
}

long RWindowContentItem::get_extended_style() const noexcept {
	return extended_style;
}

void RWindowContentItem::set_extended_style(long extended_style) noexcept {
	SetWindowLongA(*content_window, GWL_EXSTYLE, style);
}

void* RWindowContentItem::get_lpParam() const noexcept {
	return lpParam;
}

void RWindowContentItem::set_lpParam(void* lpParam) noexcept {
	this->lpParam = lpParam;
}

