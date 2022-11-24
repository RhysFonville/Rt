#include "rlistbox.h"

static std::function<void(PROCEDURE_PARAMS)> set_selecion_var() {
	return [](PROCEDURE_PARAMS) {
		RListBox *list_box = static_cast<RListBox *>(additional_info[0]);
		list_box->selection_index = SendMessageA(*list_box->get_window(), LB_GETCURSEL, NULL, NULL);
		SendMessageA(*list_box->get_window(), LB_GETTEXT, (LPARAM)list_box->selection_index, (WPARAM)list_box->selection.c_str());
	};
}

RListBox::RListBox(RWindow &parent_window, Position position, Size size,
	HMENU menu, long style, long extended_style, void* lpParam)
	: RWindowContentItem(parent_window, "ListBox", NULL_STR, position, size, menu, style, extended_style, WS_CHILD | WS_VISIBLE | LBS_NOTIFY, lpParam) {
	
	parent_window.get_procedures().push_back(Procedure(set_selecion_var(), WPROCMESSAGE::CMD, MAKEWPARAM((WPARAM)menu, LBN_SELCHANGE), (LPARAM)*content_window, std::vector<void*>({ this })));
}

void RListBox::operator=(const RListBox &list) noexcept {
	content_window = list.content_window;
	parent_window = list.parent_window;
	position = list.position;
	size = list.size;
	menu = list.menu;
	style = list.style;
	extended_style = list.extended_style;
	lpParam = list.lpParam;
	//_can_drag = list._can_drag;
	_is_multi_select = list._is_multi_select;
	selection = list.selection;
	selection_index = list.selection_index;
}

void RListBox::add(const std::string &str) const noexcept {
	SendMessageA(*content_window, LB_ADDSTRING, NULL, (LPARAM)str.c_str());
}

void RListBox::remove(size_t index) const noexcept {
	SendMessageA(*content_window, LB_DELETESTRING, index, NULL);
}

void RListBox::is_multi_select(bool multi_select) noexcept {
	if (multi_select) {
		style |= LBS_MULTIPLESEL;
		create_window(true);
	} else {
		style &= LBS_MULTIPLESEL;
		create_window(true);
	}
}

bool RListBox::is_multi_select() const noexcept {
	return _is_multi_select;
}

//void RListBox::can_drag(bool can) noexcept {
//	_can_drag = can;
//
//	if (!_can_drag) {
//		RListBox new_list = RListBox(parent_window, position, size, menu,
//			style, extended_style, lpParam);
//
//		MakeDragList(*new_list.get_window());
//	}
//}
//
//bool RListBox::can_drag() const noexcept {
//	return _can_drag;
//}

size_t RListBox::list_size() const noexcept {
	return SendMessageA(*content_window, LB_GETCOUNT, NULL, NULL);
}

std::string RListBox::get_selection() const noexcept {
	return selection;
}

size_t RListBox::get_selection_index() const noexcept {
	return selection_index;
}

//std::vector<std::string> RListBox::get_selections() const noexcept {
//	size_t buffer_size = size();
//	std::vector<std::string> buffer(buffer_size);
//	SendMessageA(*content_window, LB_GETSELITEMS, buffer_size, (LPARAM)buffer.data());
//	return buffer;
//}
