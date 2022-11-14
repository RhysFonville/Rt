#pragma once
#ifndef RCHECKBOX_H
#define RCHECKBOX_H

#include "rwindowcontentitem.h"

enum class CheckboxCheckState {
	Checked,
	Unchecked,
	Indeterminate
};

class RCheckbox : RWindowContentItem {
public:
	RCheckbox(RWindow &parent_window, Position position = Position(5, 5),
		Size size = Size(200, 24), const std::string &checkbox_text = "Checkbox",
		HMENU menu = NULL, long style = WS_BORDER | WS_TABSTOP,
		long extended_style = WS_EX_WINDOWEDGE, void* lpParam = NULL);

	void toggle_check();
	void check();
	void check(CheckboxCheckState new_state);
	void uncheck();
	void check_indeterminate();

	CheckboxCheckState is_checked();

private:
	CheckboxCheckState checked;
};

#endif
