#pragma once
#ifndef RCHECKBOX_H
#define RCHECKBOX_H

#include "rbutton.h"

class RCheckbox : RButton {
public:
	enum class State {
		Checked,
		Unchecked,
		Indeterminate
	};

	enum class Type {
		ThreeState = BS_3STATE,
		PushLike = BS_PUSHLIKE,
		Default = BS_CHECKBOX
	};

	RCheckbox(RWindow &parent_window, Position position = Position(5, 5),
		Size size = Size(200, 24), const std::string &checkbox_text = "Checkbox",
		HMENU menu = NULL, Type type = Type::Default, long style = WS_BORDER | WS_TABSTOP,
		long extended_style = WS_EX_WINDOWEDGE, void* lpParam = NULL);

	void toggle_check();
	void check();
	void check(State new_state);
	void uncheck();
	void check_indeterminate();

	State is_checked();

private:
	State checked;
};

#endif
