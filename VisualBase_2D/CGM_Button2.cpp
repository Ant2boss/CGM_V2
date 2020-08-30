#include "CGM_Button2.h"

CGM::Button::Button(CGM::Canvas* Can, CGM::Vector2i Size) : MyTextBox(Can, Size) {

	this->MyCan = Can;
	this->SetSize(Size);

}

void CGM::Button::SetColor(int Color) {
	this->SetBaseColor(Color);
	this->SetSelectedColor(Color);
}

void CGM::Button::SetButtonText(std::string str, int str_color) {
	this->MyTextBox.Clear();
	this->MyTextBox.SetTextColor(str_color);

	this->MyTextBox << str;
	this->MyTextBox.Center();
}

void CGM::Button::SetSize(CGM::Vector2i Size) {
	if (Size == this->MyColider.Size) return;
	this->MyColider.Size = Size;
	this->MyTextBox.SetSize(Size);
}

void CGM::Button::SetPosition(CGM::Vector2i Pos) {
	this->MyColider.Position = Pos;
	this->MyTextBox.SetPosition(Pos);
}

void CGM::Button::SetColider(CGM::Colider2i Col) {
	this->MyColider = Col;
	this->MyTextBox.SetColider(Col);
}

bool CGM::Button::IsHovered() const {
	CGM::Vector2i tMouse;

	if (CGM::Check_Mouse_MousePosition(this->MyCan, &tMouse)) {
		return CGM::Check_Colider2_VectorInColider(tMouse, this->GetColider());
	}

	return false;
}

void CGM::Button::ClearText() {
	this->MyTextBox.Clear();
}

void CGM::Button::Append() {

	switch (this->IsHovered()) {
	case true:
		CGM::Append_Canvas_Rectangle(this->MyCan, this->MyHoveredColor, this->GetColider());
		break;
	case false:
		CGM::Append_Canvas_Rectangle(this->MyCan, this->MyColor, this->GetColider());
		break;
	}

	this->MyTextBox.Append();

}

void CGM::Button_Matrix::resize_ButtonArray() {
	this->MyButtonArray.clear();

	int total = this->MyMatrixSize.x * this->MyMatrixSize.y;
	for (int i = 0; i < total; ++i) {
		this->MyButtonArray.emplace_back(this->MyCan);
	}
}

void CGM::Button_Matrix::move_ButtonArray() {
	CGM::Vector2i tNextButtonPos;

	for (int y = 0; y < this->GetMatrixSize().y; ++y) {
		for (int x = 0; x < this->GetMatrixSize().x; ++x) {

			tNextButtonPos = this->GetMatrixOrigin();
			tNextButtonPos.Offset(x * (this->GetButtonSize().x + this->GetSpaceBetweenButtons().x)
				,y * (this->GetButtonSize().y + this->GetSpaceBetweenButtons().y));

			this->MyButtonArray[this->indexOf(x, y)].SetPosition(tNextButtonPos);

		}
	}

}

void CGM::Button_Matrix::update_ButtonArray() {

	for (int i = 0; i < this->MyButtonArray.size(); ++i) {

		this->MyButtonArray[i].SetSize(this->MyButtonSize);
		this->MyButtonArray[i].SetBaseColor(this->MyButtonBaseColor);
		this->MyButtonArray[i].SetSelectedColor(this->MyButtonSelectColor);

	}

}

CGM::Button_Matrix::Button_Matrix(CGM::Canvas* Can, CGM::Vector2i MatrixSize) 
	: Button_Matrix(Can) {
	
	this->SetMatrixSize(MatrixSize);
}

void CGM::Button_Matrix::SetButtonSize(CGM::Vector2i Size) {
	this->MyButtonSize = Size;
	this->MyArrayNeedsUpdating = true;
}

void CGM::Button_Matrix::SetButtonColor(int Color) {
	this->SetButtonBaseColor(Color);
	this->SetButtonSelectedColor(Color);
}

void CGM::Button_Matrix::SetButtonBaseColor(int Color) {
	this->MyButtonBaseColor = Color;
	this->MyArrayNeedsUpdating = true;
}

void CGM::Button_Matrix::SetButtonSelectedColor(int Color) {
	this->MyButtonSelectColor = Color;
	this->MyArrayNeedsUpdating = true;
}

void CGM::Button_Matrix::SetButtonColor_Index(int ButtonIndex, int Color) {
	this->SetButtonBaseColor_Index(ButtonIndex, Color);
	this->SetButtonSelectedColor_Index(ButtonIndex, Color);
}

void CGM::Button_Matrix::SetButtonBaseColor_Index(int ButtonIndex, int Color) {
#ifdef _DEBUG
	if (ButtonIndex < 0 || ButtonIndex >= this->MyButtonArray.size()) DebugBreak();
#endif
	this->MyButtonArray[ButtonIndex].SetBaseColor(Color);
}

void CGM::Button_Matrix::SetButtonSelectedColor_Index(int ButtonIndex, int Color) {
#ifdef _DEBUG
	if (ButtonIndex < 0 || ButtonIndex >= this->MyButtonArray.size()) DebugBreak();
#endif
	this->MyButtonArray[ButtonIndex].SetSelectedColor(Color);
}

void CGM::Button_Matrix::SetMatrixOrigin(CGM::Vector2i Pos) {
	this->MyMatrixOrigin = Pos;
	this->MyArrayNeedsUpdating = true;
}

void CGM::Button_Matrix::SetMatrixSize(CGM::Vector2i Size) {
	this->MyMatrixSize = Size;
	this->resize_ButtonArray();
}

void CGM::Button_Matrix::SetSpaceBetweenButtons(int xDist, int yDist) {
	this->MySpaceBetweenButtons.Init(xDist, yDist);
	this->MyArrayNeedsUpdating = true;
}

void CGM::Button_Matrix::SetButtonText_Index(std::string str, int str_color, unsigned int Index) {
#ifdef _DEBUG
	if (Index < 0 || Index >= this->GetMatrixSize().x * this->GetMatrixSize().y) DebugBreak();
#endif
	if (this->MyArrayNeedsUpdating) {
		this->update_ButtonArray();
		this->move_ButtonArray();
		this->MyArrayNeedsUpdating = false;
	}

	this->MyButtonArray[Index].SetButtonText(str, str_color);
}

CGM::Colider2i CGM::Button_Matrix::GetMatrixColider() const {
	CGM::Vector2i ElementSize;
	ElementSize = this->GetButtonSize() + this->GetSpaceBetweenButtons();

	CGM::Colider2i tCol;

	tCol.Position = this->GetMatrixOrigin();

	tCol.Size.x = this->GetMatrixSize().x * ElementSize.x;
	tCol.Size.y = this->GetMatrixSize().y * ElementSize.y;

	tCol.Size -= this->GetSpaceBetweenButtons();

	return tCol;
}

bool CGM::Button_Matrix::IsHovered(CGM::Vector2i* HoveredIndex) {
	if (this->MyArrayNeedsUpdating) {
		this->update_ButtonArray();
		this->move_ButtonArray();
		this->MyArrayNeedsUpdating = false;
	}

	for (int y = 0; y < this->GetMatrixSize().y; ++y) {
		for (int x = 0; x < this->GetMatrixSize().x; ++x) {
			HoveredIndex->Init(x, y);
			if (this->MyButtonArray[this->indexOf(x, y)].IsHovered()) return true;
		}
	}

	HoveredIndex->Init(-1, -1);
	return false;
}

bool CGM::Button_Matrix::IsHovered_Index(int* HoveredIndex) {
	if (this->MyArrayNeedsUpdating) {
		this->update_ButtonArray();
		this->move_ButtonArray();
		this->MyArrayNeedsUpdating = false;
	}

	for (int i = 0; i < this->MyButtonArray.size(); ++i) {
		*HoveredIndex = i;
		if (this->MyButtonArray[i].IsHovered()) return true;
	}

	*HoveredIndex = -1;
	return false;
}

void CGM::Button_Matrix::Append() {
	if (this->MyArrayNeedsUpdating) {
		this->update_ButtonArray();
		this->move_ButtonArray();
		this->MyArrayNeedsUpdating = false;
	}

	for (auto& el : this->MyButtonArray) el.Append();
}

