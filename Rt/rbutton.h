#ifndef RBUTTON_H
#define RBUTTON_H

#include <utility>
#include "rwindowcontentitem.h"

class RButton : public RWindowContentItem {
public:
	enum class Notification {
		Clicked = BN_CLICKED,
		DoubleClicked = BN_DBLCLK,
		Disabled = BN_DISABLE,
		Highlighted = BN_HILITE,
		Unhighlighed = BN_UNHILITE,
		Focused = BN_SETFOCUS,
		FocusLost = BN_KILLFOCUS,
	};

	enum class Style {
		HorizontalCenteredText = BS_CENTER,
		FlatLook = BS_FLAT,
		LeftJustifiedText = BS_LEFT,
		RightJustifiedText = BS_RIGHT,
		TextAtLeft = BS_LEFTTEXT,
		TExtAtTop = BS_TOP,
		TextAtBottom = BS_BOTTOM,
		MultilineText = BS_MULTILINE,
		VerticalLeftText = BS_VCENTER
	};

	RButton(RWindow &parent_window, Position position = Position(5, 5),
		Size size = Size(200, 24), const std::string &button_text = "Button",
		HMENU menu = NULL, long style = WS_BORDER | WS_TABSTOP | BS_TEXT | BS_PUSHBUTTON,
		long extended_style = WS_EX_WINDOWEDGE, void* lpParam = NULL);

	void click();
	
	void is_highlighted(bool highlight);
	void highlight();
	void unhighlight();
};

#endif
