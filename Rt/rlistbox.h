#pragma once
#ifndef RLISTBOX_H
#define RLISTBOX_H

#include "rwindowcontentitem.h"

class RListBox : public RWindowContentItem {
public:
	RListBox(RWindow &parent_window, Position position = Position(5, 5),
		Size size = Size(200, 250), HMENU menu = NULL, long style = WS_BORDER | WS_TABSTOP,
		long extended_style = WS_EX_WINDOWEDGE, void* lpParam = NULL);

	void operator=(const RListBox &list) noexcept;

	void add(const std::string &str) const noexcept;
	void remove(size_t index) const noexcept;

	void is_multi_select(bool multi_select) noexcept;
	bool is_multi_select() const noexcept;

	//void can_drag(bool can) noexcept;
	//bool can_drag() const noexcept;

	size_t list_size() const noexcept;

	//std::vector<std::string> get_selections() const noexcept;
	std::string get_selection() const noexcept;
	size_t get_selection_index() const noexcept;

	friend std::function<void(PROCEDURE_PARAMS)> set_selecion_var();
private:
	size_t selection_index;
	std::string selection;

	bool _is_multi_select;
	//bool _can_drag;
};

#endif
