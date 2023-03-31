#include "rwindow.h"

RWindow *this_window_wndproc;

LRESULT CALLBACK RWindow::wndproc(HWND hwnd, UINT32 uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	if (this_window_wndproc != nullptr) {
		for (Procedure &p : this_window_wndproc->get_procedures()) {
			if (uMsg == p.message) {
				if (wParam == p.wparam) {
					if (lParam == p.lparam || p.lparam == NULL) {
						p.function(*this_window_wndproc, wParam, p.additional_info);
					}
				}
			}
		}
		if (uMsg == WM_CLOSE) {
			this_window_wndproc->is_running(false);
		} else if (uMsg == WM_PAINT) {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
			EndPaint(hwnd, &ps);
		} else {
			result = DefWindowProcW(hwnd, uMsg, wParam, lParam);
		}
	} else {
		result = DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
	
	return result;
}

RWindow::RWindow(WNDPROC window_procedure, HINSTANCE hInstance) {
	
	window_class.style         =    CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName =    L"Window Class";
	window_class.lpfnWndProc   =    window_procedure;

	this->hInstance = hInstance;

	RegisterClassW(&window_class);
}

RWindow::RWindow(HINSTANCE hInstance) {

	window_class.style         =    CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName =    L"Window Class";
	window_class.lpfnWndProc   =    wndproc;

	this->hInstance = hInstance;

	RegisterClassW(&window_class);
}

void RWindow::set_up_window(Position position, Size size, const std::string &name, long style, HWND parent, long extended_style, HMENU menu, void* lpParam) {
	HWND hwnd = CreateWindowExW(extended_style, window_class.lpszClassName, string_to_wstring(name).c_str(),
		style, position.x, position.y,
		size.width, size.height, parent, menu, hInstance, lpParam);

	window = std::make_shared<HWND>(hwnd);
	dc = GetDC(*window);
}

void RWindow::check_input() {
	MSG message;
	while (PeekMessageW(&message, *window, 0, 0, PM_REMOVE)) {
		this_window_wndproc = this;

		TranslateMessage(&message);
		DispatchMessageW(&message);
	}
}

std::shared_ptr<HWND> RWindow::get_window() {
	return window;
}

HDC & RWindow::get_dc() {
	return dc;
}
HINSTANCE RWindow::get_hInstance() {
	return hInstance;
}

WNDCLASS & RWindow::get_class() {
	return window_class;
}
std::vector<std::shared_ptr<HWND>> & RWindow::get_child_windows() {
	return child_windows;
}

std::vector<Procedure> & RWindow::get_procedures() {
	return procedures;
}

bool RWindow::is_running() const noexcept {
	return running;
}

void RWindow::is_running(bool running) noexcept {
	this->running = running;
}
