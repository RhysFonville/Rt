#pragma once
#ifndef RWINDOWCONTENTS_H
#define RWINDOWCONTENTS_H

#include <Windows.h>
#include <string>
#include "rwindow.h"
#include "rwindowcontentitem.h"
#include "rconversion.h"

class RTextBox : public RWindowContentItem {
public:
	RTextBox(RWindow &parent_window, Position position = Position(5, 5),
		Size size = Size(200, 24), const std::string &starting_text = "Textbox",
		HMENU menu = NULL, long style = WS_BORDER | WS_TABSTOP | ES_AUTOVSCROLL,
		long extended_style = NULL, void* lpParam = NULL);

	std::string get_text();
};

#endif
