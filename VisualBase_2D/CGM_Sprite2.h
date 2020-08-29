#pragma once

#include "CGM_Canvas.h"
#include <string>

namespace CGM {

	typedef CGM::Array2D<char> Sprite;

	void Save_Sprite_ToFile(CGM::Sprite* Spr, std::string FileName);
	void Load_Sprite_FromFile(CGM::Sprite* Spr, std::string FileName);

	void Append_Sprite_ToCanvas(CGM::Canvas* Can, CGM::Sprite* Spr, int xPos, int yPos, int IgnoredColor = CGM::Color::Black);
	void Append_Sprite_ToCanvas(CGM::Canvas* Can, CGM::Sprite* Spr, CGM::Vector2i Position, int IgnoredColor = CGM::Color::Black);

};