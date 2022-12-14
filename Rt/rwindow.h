#pragma once
#ifndef RWINDOW_H
#define RWINDOW_H

#include <Windows.h>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "rconversion.h"

using Tab = std::vector<std::shared_ptr<HWND>>;

namespace WPROCMESSAGE {
	constexpr int CLOSE = WM_CLOSE;
	constexpr int PAINT = WM_PAINT;
	constexpr int CMD = WM_COMMAND;
}

struct Position {
	int x;
	int y;

	Position(int x, int y) : x(x), y(y) {  }
};

struct Size {
	int width;
	int height;

	Size(int width, int height) : width(width), height(height) {  }
};

class RWindow;

#define PROCEDURE_PARAMS RWindow &window, WPARAM wParam, std::vector<void*> &additional_info

struct Procedure {
	Procedure(std::function<void(PROCEDURE_PARAMS)> function, int message,
		WPARAM wparam, LPARAM lparam, std::vector<void*> additional_info = std::vector<void*>()) :
		function(function), message(message), wparam(wparam), lparam(lparam),
		additional_info(additional_info) {  }

	std::function<void(PROCEDURE_PARAMS)> function;
	int message;
	WPARAM wparam;
	LPARAM lparam;
	std::vector<void*> additional_info;

	bool notification;
};

class RWindow {
public:
	RWindow(WNDPROC window_procedure, HINSTANCE hInstance);
	RWindow(HINSTANCE hInstance);

	void set_up_window(Position position = Position(CW_USEDEFAULT, CW_USEDEFAULT),
		Size size = Size(500, 450), const std::string &name = "My Window",
		long style = WS_OVERLAPPEDWINDOW | WS_VISIBLE, HWND parent = NULL,
		long extended_style = NULL, HMENU menu = NULL, void* lpParam = NULL);

	void check_input();

	std::shared_ptr<HWND> get_window();
	HDC & get_dc();
	HINSTANCE get_hInstance();
	WNDCLASS & get_class();
	std::vector<std::shared_ptr<HWND>> & get_child_windows();
	std::vector<Procedure> & get_procedures();

	bool is_running() const noexcept;
	void is_running(bool running) noexcept;

	void clear_tab(RWindow &window, Tab &tab);
	void show_tab(Tab &tab);
	void refresh_tab(RWindow &window, Tab &tab);

private:
	std::shared_ptr<HWND> window;
	HDC dc;
	HINSTANCE hInstance;
	WNDCLASS window_class = {};
	std::vector<std::shared_ptr<HWND>> child_windows;
	std::vector<Procedure> procedures;
	
	bool running = true;

	static LRESULT CALLBACK wndproc(HWND hwnd, UINT32 uMsg, WPARAM wParam, LPARAM lParam);
};

static void background(RWindow &window, COLORREF color = RGB(255, 255, 255)) {
	PAINTSTRUCT ps = { };
	FillRect(window.get_dc(), &ps.rcPaint, (HBRUSH)color);
	EndPaint(*window.get_window(), &ps);
}

#endif
