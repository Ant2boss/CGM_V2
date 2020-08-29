#include "CGM_TextBox.h"

#include <sstream>
#include <conio.h>

int get_word_len(std::string word, int start_index) {
	int count = 0;

	for (int i = start_index; i < word.length(); ++i) {
		if (word[i] == ' ') break;
		++count;
	}

	return count;
}

std::string get_next_word(std::string word, int start_index) {
	std::stringstream ss;

	for (int i = start_index; i < word.length(); ++i) {
		ss << word[i];
		if (word[i] == ' ') break;
	}

	return ss.str();
}

void CGM::TextBox::resize_my_arrays() {
	this->MyBoolArray.Resize(this->GetSize());
	this->MyCharArray.Resize(this->GetSize());
	this->MyColorArray.Resize(this->GetSize());
}

void CGM::TextBox::check_cursor_pos() {
	if (this->MyCursorPos.x >= this->GetSize().x) this->MyCursorPos.Init(0, this->MyCursorPos.y + 1);
	if (this->MyCursorPos.y >= this->GetSize().y) this->MyCursorPos.Init(0, 0);
}

void CGM::TextBox::add_word_to_arrays(std::string word) {

	for (int i = 0; i < word.size(); ++i) {
		this->check_cursor_pos();
		if (word[i] == '\n') {
			this->SetCursorPosition(0, this->MyCursorPos.y + 1);
			continue;
		}

		this->MyBoolArray.SetAt(true, this->MyCursorPos);
		this->MyCharArray.SetAt(word[i], this->MyCursorPos);
		this->MyColorArray.SetAt(this->MyTextColor, this->MyCursorPos);

		this->MyCursorPos.Offset(1, 0);
	}

}

CGM::TextBox::TextBox(CGM::Canvas* Can, CGM::Vector2i Size) {
	this->MyCan = Can;
	this->MyColider.Size = Size;
	this->resize_my_arrays();
}

CGM::TextBox& CGM::TextBox::operator<<(std::string str) {
	int t_index = 0;
	int len;

	CGM::Vector2i t_Cursor;

	while (t_index <= str.length()) {
		
		len = get_word_len(str, t_index);
		t_Cursor = this->GetCursorPosition();
		t_Cursor.Offset(len, 0);

		if (t_Cursor.x >= this->GetSize().x) {
			this->SetCursorPosition(t_Cursor);
		}

		this->add_word_to_arrays(get_next_word(str, t_index));

		t_index += len + 1;

	}

	return *this;
}

CGM::TextBox& CGM::TextBox::operator<<(bool Val) {
	std::stringstream ss;
	ss << Val;
	return this->operator<<(std::string(ss.str()));
}

CGM::TextBox& CGM::TextBox::operator<<(char Val) {
	std::stringstream ss;
	ss << Val;
	return this->operator<<(std::string(ss.str()));
}

CGM::TextBox& CGM::TextBox::operator<<(int Val) {
	std::stringstream ss;
	ss << Val;
	return this->operator<<(std::string(ss.str()));
}

CGM::TextBox& CGM::TextBox::operator<<(float Val) {
	std::stringstream ss;
	ss << Val;
	return this->operator<<(std::string(ss.str()));
}

CGM::TextBox& CGM::TextBox::operator<<(double Val) {
	std::stringstream ss;
	ss << Val;
	return this->operator<<(std::string(ss.str()));
}

void CGM::TextBox::SetCursorPosition(CGM::Vector2i Pos) {
	this->MyCursorPos = Pos;
	this->check_cursor_pos();
}

void CGM::TextBox::SetSize(CGM::Vector2i Size) {
	this->MyColider.Size = Size;
	this->resize_my_arrays();
}

void CGM::TextBox::SetColider(CGM::Colider2i Col) {
	this->MyColider = Col;
	this->resize_my_arrays();
}

void CGM::TextBox::Center_TopBottom() {
	int yStart = -1;
	int yEnd = -1;

	for (int y = 0; y < this->GetSize().y; ++y) {
		for (int x = 0; x < this->GetSize().x; ++x) {
			if (this->MyBoolArray.GetAt(x, y)) {
				yStart = y;
				break;
			}
		}
		if (yStart != -1) break;
	}
	if (yStart == -1) return;

	for (int y = this->GetSize().y - 1; y >= 0; --y) {
		for (int x = this->GetSize().x - 1; x >= 0; --x) {
			if (this->MyBoolArray.GetAt(x, y)) {
				yEnd = y;
				break;
			}
		}
		if (yEnd != -1) break;
	}
	if (yEnd == -1) return;

	std::vector<bool> b_arr;
	std::vector<char> c_arr;
	std::vector<int> i_arr;
	for (int y = yStart; y <= yEnd; ++y) {
		for (int x = 0; x < this->GetSize().x; ++x) {
			b_arr.push_back(this->MyBoolArray.GetAt(x, y));
			c_arr.push_back(this->MyCharArray.GetAt(x, y));
			i_arr.push_back(this->MyColorArray.GetAt(x, y));
		}
	}

	int yDelta = yEnd - yStart;

	int yNewStart = (this->GetSize().y / 2) - (yDelta / 2);

	this->Clear();

	int t = 0;
	for (int y = yNewStart; y <= yDelta + yNewStart; ++y) {
		for (int x = 0; x < this->GetSize().x; ++x) {
			this->MyBoolArray.SetAt(b_arr[t], x, y);
			this->MyCharArray.SetAt(c_arr[t], x, y);
			this->MyColorArray.SetAt(i_arr[t], x, y);

			++t;
		}
	}

	this->SetCursorPosition(0, 0);

}

void CGM::TextBox::Center_LeftRight() {
	int xStart = -1;
	int xEnd = -1;

	for (int x = 0; x < this->GetSize().x; ++x) {
		for (int y = 0; y < this->GetSize().y; ++y) {
			if (this->MyBoolArray.GetAt(x, y)) {
				xStart = x;
				break;
			}
		}
		if (xStart != -1) break;
	}
	if (xStart == -1) return;

	for (int x = this->GetSize().x - 1; x >= 0; --x) {
		for (int y = this->GetSize().y - 1; y >= 0; --y) {
			if (this->MyBoolArray.GetAt(x, y)) {
				xEnd = x;
				break;
			}
		}
		if (xEnd != -1) break;
	}
	if (xEnd == -1) return;

	std::vector<bool> b_arr;
	std::vector<char> c_arr;
	std::vector<int> i_arr;
	for (int x = xStart; x <= xEnd; ++x) {
		for (int y = 0; y < this->GetSize().y; ++y) {
			b_arr.push_back(this->MyBoolArray.GetAt(x, y));
			c_arr.push_back(this->MyCharArray.GetAt(x, y));
			i_arr.push_back(this->MyColorArray.GetAt(x, y));
		}
	}

	int xDelta = xEnd - xStart;

	int xNewStart = (this->GetSize().x / 2) - (xDelta / 2);

	this->Clear();

	int t = 0;
	for (int x = xNewStart; x <= xDelta + xNewStart; ++x) {
		for (int y = 0; y < this->GetSize().y; ++y) {
			this->MyBoolArray.SetAt(b_arr[t], x, y);
			this->MyCharArray.SetAt(c_arr[t], x, y);
			this->MyColorArray.SetAt(i_arr[t], x, y);

			++t;
		}
	}

	this->SetCursorPosition(0, 0);
}

void CGM::TextBox::Clear() {
	this->MyBoolArray.Clear(false);
	this->MyCharArray.Clear();
	this->MyColorArray.Clear();
}

void CGM::TextBox::Append() {
	CGM::Vector2i t_index;
	for (int y = 0; y < this->GetSize().y; ++y) {
		for (int x = 0; x < this->GetSize().x; ++x) {
			t_index.Init(x, y);
			t_index += this->GetPosition();

			if(!CGM::Check_Colider2_VectorInColider(t_index, this->MyCan->GetColider())) continue;
			if (this->MyBoolArray.GetAt(x, y)) {
				
				CHAR_INFO& val = this->MyCan->at(t_index);
				int t_BackCol = CGM::Get_Color_BackColorFromMix(val.Attributes);

				val.Char.UnicodeChar = this->MyCharArray.GetAt(x, y);
				val.Attributes = CGM::Get_Color_ClacMixColor(t_BackCol, this->MyColorArray.GetAt(x, y));

			}

		}
	}

}

std::string CGM::Get_User_InputFromTextBox(CGM::Canvas* Can, CGM::TextBox* Text) {
	//Wait loop
	while (1) {
		if (CGM::Check_Mouse_LeftClick()) continue;
		else if (CGM::Check_Mouse_RightClick()) continue;
		else if (_kbhit()) {
			char c = _getwch();
			continue;
		}
		break;
	}

	std::string Input;

	while (1) {
		
		Can->Draw();
		
		char in;
		//We wait for input
		while (1) {

			if (_kbhit()) {
				in = _getwch();
				break;
			}
			else if (CGM::Check_Mouse_LeftClick()) {
				in = 13;
				break;
			}
		}

		CGM::Vector2i tPos;
		switch (in) {
		case 13:
			return Input;
			break;

		case 8:
			if (Input.length() == 0) break;
			else {
				tPos = Text->GetCursorPosition();
				tPos.Offset(-1, 0);

				Text->SetCursorPosition(tPos);
				Text->operator<<(' ');
				Text->Append();
				Text->SetCursorPosition(tPos);

				Input.pop_back();
			}
			break;

		default:
			Input.push_back(in);

			Text->operator<<(in);
			Text->Append();
			break;
		}

	}
}
