#pragma once
#ifndef RWINDOWCONTENTITEM_H
#define RWINDOWCONTENTITEM_H

#include <Windows.h>
#include <memory>
#include "rwindow.h"

#define NULL_STR "\0"

class RWindowContentItem {
public:
	RWindowContentItem(RWindow &parent_window, const std::string &class_name, const std::string &window_name, const Position &position,
		const Size &size, HMENU menu, long style, long extended_style, long default_style, void* lpParam);

	void create_window(bool show_window = false);

	const std::shared_ptr<HWND> & get_window();
	RWindow & get_parent_window();

	void set_parent_window(RWindow &window);

	Position get_position() const noexcept;
	void set_position(const Position &position) noexcept;

	Size get_size() const noexcept;
	void set_size(const Size &size) noexcept;

	HMENU get_menu() const noexcept;
	void set_menu(HMENU menu) noexcept;

	long get_style() const noexcept;
	void set_style(long style) noexcept;

	long get_extended_style() const noexcept;
	void set_extended_style(long extended_style) noexcept;

	void* get_lpParam() const noexcept;
	void set_lpParam(void* lpParam) noexcept;

protected:
	std::shared_ptr<HWND> content_window;
	RWindow &parent_window;

	std::string class_name;
	std::string window_name;
	Position position;
	Size size;
	HMENU menu; 
	long style;
	long extended_style;
	long default_style;
	void* lpParam;
};

#endif
