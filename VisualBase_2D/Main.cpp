#include "CGM_Vector2.h"
#include "CGM_Colider2.h"
#include "CGM_Canvas.h"
#include "CGM_Sprite2.h"
#include "CGM_Button2.h"
#include "CGM_TextBox.h"
#include "CGM_Animation2.h"

#include <iostream>
using namespace std;

/*
TODO:

	PixelEditor

*/

int main() {

	CGM::Canvas Can(128, 48);

	CGM::Animation Anim(&Can, "TestAnimation");

	//int off = 0;

	//Anim.AddFrame();
	//Anim.SetAt_CurrentFrame(CGM::Color::Blue, 0 + off, 0 + off);
	//Anim.SetAt_CurrentFrame(CGM::Color::Blue, 1 + off, 0 + off);
	//Anim.SetAt_CurrentFrame(CGM::Color::Blue, 0 + off, 1 + off);
	//Anim.SetAt_CurrentFrame(CGM::Color::Blue, 1 + off, 1 + off);
	//Anim.SetAt_CurrentFrame(CGM::Color::Blue, 2 + off, 0 + off);
	//Anim.SetAt_CurrentFrame(CGM::Color::Blue, 3 + off, 0 + off);

	//off = 1;
	//Anim.AddFrame();
	//Anim.SetAt(CGM::Color::Red, 1, 0 + off, 0 + off);
	//Anim.SetAt(CGM::Color::Red, 1, 1 + off, 0 + off);
	//Anim.SetAt(CGM::Color::Red, 1, 0 + off, 1 + off);
	//Anim.SetAt(CGM::Color::Red, 1, 1 + off, 1 + off);
	//Anim.SetAt(CGM::Color::Red, 1, 2 + off, 0 + off);
	//Anim.SetAt(CGM::Color::Red, 1, 3 + off, 0 + off);

	//CGM::Save_Animation_ToFile(&Anim, "TestAnimation");

	//Anim.NextFrame();

	//CGM::Save_Animation_SaveSingleFrameAsSprite(&Anim, 0, "Attempt1");

	Anim.AppendAndNextFrame();
	Can.Draw();

	cin.get();

	CGM::Sprite spr;
	CGM::Load_Sprite_FromFile(&spr, "Attempt1");

	Anim.Append();
	CGM::Append_Sprite_ToCanvas(&Can, &spr, CGM::Vector2i(20, 20));
	Can.Draw();

	cin.get();

	CGM::Load_Animation_LoadSpriteFromFileAndAddToAnimation(&Anim, "Attempt1");
	
	Anim.SetPosition(6, 6);
	Anim.NextFrame();
	Anim.Append();
	Can.Draw();

	cin.get();
	cin.get();

	return 0;
}