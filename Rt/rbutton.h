#ifndef RBUTTON_H
#define RBUTTON_H

#include "rwindowcontentitem.h"
#include <utility>

class RButton : public RWindowContentItem {
public:
	RButton(RWindow &parent_window, Position position = Position(5, 5),
		Size size = Size(200, 24), const std::string &button_text = "Button",
		HMENU menu = NULL, long style = WS_BORDER | WS_TABSTOP,
		long extended_style = WS_EX_WINDOWEDGE, void* lpParam = NULL);
};

#endif
