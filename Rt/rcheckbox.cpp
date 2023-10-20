#include "rcheckbox.h"

RCheckbox::RCheckbox(RWindow &parent_window, Position position, Size size,
	const std::string &checkbox_text, HMENU menu, Type type, long style, long extended_style, void* lpParam)
	: RButton(parent_window, position, size, checkbox_text.c_str(), menu, style | (long)type | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | BS_TEXT, extended_style, lpParam),
	checked(State::Checked) {

	std::function<void(PROCEDURE_PARAMS)> func = [](PROCEDURE_PARAMS) {
		static_cast<RCheckbox*>(additional_info[0])->toggle_check();
	};

	parent_window.get_procedures().push_back(
		Procedure(func, menu, (int)RButton::Notification::Clicked, { this })
	);
}

void RCheckbox::toggle_check() {
	if (checked == State::Checked) {
		uncheck();
		checked = State::Unchecked;
	} else if (checked == State::Unchecked) {
		check();
		checked = State::Checked;
	}
}

void RCheckbox::check(State new_state) {
	switch (new_state) {
		case State::Checked:
			check();
			break;
		case State::Unchecked:
			uncheck();
			break;
		case State::Indeterminate:
			check_indeterminate();
			break;
	}
}

void RCheckbox::check() {
	Button_SetCheck(*content_window, BST_CHECKED);
	checked = State::Checked;
}

void RCheckbox::uncheck() {
	Button_SetCheck(*content_window, BST_UNCHECKED);
	checked = State::Unchecked;
}

void RCheckbox::check_indeterminate() {
	Button_SetCheck(*content_window, BST_INDETERMINATE);
	checked = State::Indeterminate;
}

RCheckbox::State RCheckbox::is_checked() {
	return checked;
}
