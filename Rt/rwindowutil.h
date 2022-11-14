#pragma once
#ifndef RWINDOWUTIL_H
#define RWINDOWUTIL_H

#include <windows.h>

static bool has_style(HWND hwnd, long style) noexcept {
	return (GetWindowLongA(hwnd, GWL_STYLE) & style);
}

#endif
