#pragma once

#include "CGM_Vector2.h"

namespace CGM {
	
	template<typename T>
	struct Colider2 {

		CGM::Vector2<T> Position;
		CGM::Vector2<T> Size;

	};

	template<typename T>
	class inherit_Colider2 {

	protected:
		CGM::Colider2<T> MyColider;

	public:
		void SetPosition(T xPos, T yPos);
		void SetPosition(CGM::Vector2<T> Pos);

		void SetSize(T xSize, T ySize);
		void SetSize(CGM::Vector2<T> Size);

		CGM::Vector2<T> GetSize() const;
		CGM::Vector2<T> GetPosition() const;
		CGM::Colider2<T> GetColider() const;

	};

	typedef Colider2<int> Colider2i;
	typedef Colider2<double> Colider2d;

	typedef inherit_Colider2<int> inherit_Colider2i;
	typedef inherit_Colider2<double> inherit_Colider2d;

	CGM::Colider2i Get_Colider2_FromStartAndEnd(CGM::Vector2i Start, CGM::Vector2i End);
	CGM::Colider2i Get_Colider2_FromStartAndEnd(int xStart, int yStart, int xEnd, int yEnd);

	CGM::Colider2d Get_Colider2_FromStartAndEnd(CGM::Vector2d Start, CGM::Vector2d End);
	CGM::Colider2d Get_Colider2_FromStartAndEnd(double xStart, double yStart, double xEnd, double yEnd);


	CGM::Colider2i Get_Colider2_FromPosAndSize(CGM::Vector2i Pos, CGM::Vector2i Size);
	CGM::Colider2i Get_Colider2_FromPosAndSize(int xPos, int yPos, int xSize, int ySize);

	CGM::Colider2d Get_Colider2_FromPosAndSize(CGM::Vector2d Pos, CGM::Vector2d Size);
	CGM::Colider2d Get_Colider2_FromPosAndSize(double xPos, double yPos, double xSize, double ySize);


	bool Check_Colider2_VectorInColider(CGM::Vector2i Vec2i, CGM::Colider2i Col2i);
	bool Check_Colider2_VectorInColider(CGM::Vector2d Vec2d, CGM::Colider2d Col2d);

	bool Check_Colider2_ColiderInColider(CGM::Colider2i Col2i1, CGM::Colider2i Col2i2);
	bool Check_Colider2_ColiderInColider(CGM::Colider2d Col2d1, CGM::Colider2d Col2d2);

	template<typename T>
	inline void inherit_Colider2<T>::SetPosition(T xPos, T yPos) {
		this->SetPosition(CGM::Vector2<T>(xPos, yPos));
	}

	template<typename T>
	inline void inherit_Colider2<T>::SetPosition(CGM::Vector2<T> Pos) {
		this->MyColider.Position = Pos;
	}

	template<typename T>
	inline void inherit_Colider2<T>::SetSize(T xSize, T ySize) {
		this->SetSize(CGM::Vector2<T>(xSize, ySize));
	}

	template<typename T>
	inline void inherit_Colider2<T>::SetSize(CGM::Vector2<T> Size) {
		this->MyColider.Size = Size;
	}

	template<typename T>
	inline CGM::Vector2<T> inherit_Colider2<T>::GetSize() const {
		return this->MyColider.Size;
	}

	template<typename T>
	inline CGM::Vector2<T> inherit_Colider2<T>::GetPosition() const {
		return this->MyColider.Position;
	}

	template<typename T>
	inline CGM::Colider2<T> inherit_Colider2<T>::GetColider() const {
		return this->MyColider;
	}

}