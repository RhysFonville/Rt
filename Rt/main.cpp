#include <fstream>
#include <string>
#include "rwindow.h"
#include "rlistbox.h"
#include "rbutton.h"
#include "rcheckbox.h"
#include "rtextbox.h"

bool show_prompt = true;

void println(const std::string &s) {
	std::ofstream file;

	file.open("debug.txt", std::ios_base::app);

	if (file.fail())
		throw std::ios_base::failure("Failure Opening Debug Text File");

	file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

	file << s << std::endl; 
}

void add_item(PROCEDURE_PARAMS) {
	RListBox *list = static_cast<RListBox*>(additional_info[0]);
	RTextBox *text_box = static_cast<RTextBox*>(additional_info[1]);
	list->add(text_box->get_text());
}

void remove_item(PROCEDURE_PARAMS) {
	RListBox *list = static_cast<RListBox*>(additional_info[0]);
	list->remove(list->get_selection_index());
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	RWindow window(hInstance);
	window.set_up_window();

	RTextBox add_item_text_box(window, { 5, 10 }, { 200, 24 }, "List item", (HMENU)0);
	RButton add_item_button(window, { 5, 30 }, { 200, 24 }, "Add Item", (HMENU)1);
	RButton remove_item_button(window, { 5, 54 }, { 200, 24 }, "Remove Selected Item", (HMENU)2);
	RListBox list(window, { 5, 90 }, { 200, 250 }, (HMENU)3);

	window.get_procedures().push_back(
		Procedure(std::function<void(PROCEDURE_PARAMS)>(add_item), WPROCMESSAGE::CMD, MAKEWPARAM(1, BN_CLICKED), NULL, { &list, &add_item_text_box })
	);
	window.get_procedures().push_back(
		Procedure(std::function<void(PROCEDURE_PARAMS)>(remove_item), WPROCMESSAGE::CMD, MAKEWPARAM(2, BN_CLICKED), NULL, { &list })
	);

	while (window.is_running()) {
		window.check_input();
		Sleep(10);
	}

	return 0;
}
