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

void shifted(PROCEDURE_PARAMS) {
	RCheckbox *checkbox = static_cast<RCheckbox*>(additional_info[0]);
	RButton *add_button = static_cast<RButton*>(additional_info[1]);
	RButton *remove_button = static_cast<RButton*>(additional_info[2]);

	if (checkbox->is_checked() == RCheckbox::State::Checked) {
		add_button->set_position(add_button->get_position()+20);
		remove_button->set_position(remove_button->get_position()+20);
	} else {
		add_button->set_position(add_button->get_position()-20);
		remove_button->set_position(remove_button->get_position()-20);
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	RWindow window(hInstance);
	window.set_up_window();

	RTextBox add_item_text_box(window, { 5, 10 }, { 200, 24 }, "List item", (HMENU)0);
	RButton add_item_button(window, { 5, 30 }, { 200, 24 }, "Add Item", (HMENU)1);
	RButton remove_item_button(window, { 5, 54 }, { 200, 24 }, "Remove Selected Item", (HMENU)2);
	RListBox list(window, { 5, 90 }, { 200, 250 }, (HMENU)3);
	RCheckbox checkbox(window, { 5, 350 }, { 200, 24 }, "Checkbox", (HMENU)4);

	window.get_procedures().push_back(
		Procedure(add_item, (HMENU)1, (int)RButton::Notification::Clicked, { &list, &add_item_text_box })
	);
	window.get_procedures().push_back(
		Procedure(remove_item, (HMENU)2, (int)RButton::Notification::Clicked, { &list })
	);
	window.get_procedures().push_back(
		Procedure(shifted, (HMENU)4, (int)RButton::Notification::Clicked, { &checkbox, &add_item_button, &remove_item_button })
	);

	while (window.is_running()) {
		window.check_input();
		Sleep(10);
	}

	return 0;
}
