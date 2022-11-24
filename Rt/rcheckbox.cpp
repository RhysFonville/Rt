#include "rcheckbox.h"

RCheckbox::RCheckbox(RWindow &parent_window, Position position, Size size,
	const std::string &checkbox_text, HMENU menu, long style, long extended_style,
	void* lpParam)
	: RWindowContentItem(parent_window, "Button", checkbox_text.c_str(), position, size, menu, style, extended_style, BS_CHECKBOX | WS_CHILD | WS_VISIBLE, lpParam),
	checked(CheckboxCheckState::Checked) {
	check();

	std::function<void(PROCEDURE_PARAMS)> func = [](PROCEDURE_PARAMS) {
		static_cast<RCheckbox *>(additional_info[0])->toggle_check();
	};

	parent_window.get_procedures().push_back(
		Procedure(func, WPROCMESSAGE::CMD, (WPARAM)menu, (LPARAM)*content_window, { this }));
}

void RCheckbox::toggle_check() {
	if (checked == CheckboxCheckState::Checked) {
		uncheck();
		checked = CheckboxCheckState::Unchecked;
	} else if (checked == CheckboxCheckState::Unchecked) {
		check();
		checked = CheckboxCheckState::Checked;
	}
}

void RCheckbox::check() {
	CheckDlgButton(*parent_window.get_window(), (int)GetMenu(*content_window), BST_CHECKED);
	checked = CheckboxCheckState::Checked;
}

void RCheckbox::check(CheckboxCheckState new_state) {
	switch (new_state) {
		case CheckboxCheckState::Checked:
			check();
			break;
		case CheckboxCheckState::Unchecked:
			uncheck();
			break;
		case CheckboxCheckState::Indeterminate:
			check_indeterminate();
			break;
	}
}

void RCheckbox::uncheck() {
	CheckDlgButton(*parent_window.get_window(), *(int*)GetMenu(*content_window), BST_UNCHECKED);
	checked = CheckboxCheckState::Unchecked;
}

void RCheckbox::check_indeterminate() {
	CheckDlgButton(*parent_window.get_window(), *(int*)GetMenu(*content_window), BST_INDETERMINATE);
	checked = CheckboxCheckState::Indeterminate;
}

CheckboxCheckState RCheckbox::is_checked() {
	return checked;
}
