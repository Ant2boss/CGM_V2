#pragma once

namespace CGM {
	
	template<typename T>
	struct Vector2 {

		T x;
		T y;

		Vector2() : x(0), y(0) {}
		Vector2(T x, T y) : x(x), y(y) {}

		void Init(T x, T y);
		
		CGM::Vector2<T>& Offset(T x, T y);
		CGM::Vector2<T> temp_Offset(T x, T y) const;

		CGM::Vector2<T> operator+ (CGM::Vector2<T> v2) const;
		CGM::Vector2<T> operator- (CGM::Vector2<T> v2) const;
		CGM::Vector2<T> operator* (T Val) const;
		CGM::Vector2<T> operator/ (T Val) const;

		CGM::Vector2<T>& operator+= (CGM::Vector2<T> v2);
		CGM::Vector2<T>& operator-= (CGM::Vector2<T> v2);
		CGM::Vector2<T>& operator*= (T Val);
		CGM::Vector2<T>& operator/= (T Val);

		bool operator== (CGM::Vector2<T> v2) const;
		bool operator!= (CGM::Vector2<T> v2) const;

	};

	typedef Vector2<int> Vector2i;
	typedef Vector2<double> Vector2d;

	double Get_Vector2_Lenght(CGM::Vector2i Vec);
	double Get_Vector2_Lenght(CGM::Vector2d Vec);

	double Get_Vector2_Angle(CGM::Vector2i Vec);
	double Get_Vector2_Angle(CGM::Vector2d Vec);
	double Get_Vector2_Angle(CGM::Vector2i Vec1, CGM::Vector2i Vec2);
	double Get_Vector2_Angle(CGM::Vector2d Vec1, CGM::Vector2d Vec2);

	CGM::Vector2d Get_Vector2_Normal(CGM::Vector2i Vec);
	CGM::Vector2d Get_Vector2_Normal(CGM::Vector2d Vec);

	double Get_Vector2_Dot(CGM::Vector2i V1, CGM::Vector2i V2);
	double Get_Vector2_Dot(CGM::Vector2d V1, CGM::Vector2d V2);

	double Get_Vector2_Distance(CGM::Vector2i V1, CGM::Vector2i V2);
	double Get_Vector2_Distance(CGM::Vector2d V1, CGM::Vector2d V2);

	CGM::Vector2i Get_Vector2_MinVector(CGM::Vector2i Vec1, CGM::Vector2i Vec2);
	CGM::Vector2d Get_Vector2_MinVector(CGM::Vector2d Vec1, CGM::Vector2d Vec2);

	CGM::Vector2i Get_Vector2_MaxVector(CGM::Vector2i Vec1, CGM::Vector2i Vec2);
	CGM::Vector2d Get_Vector2_MaxVector(CGM::Vector2d Vec1, CGM::Vector2d Vec2);

	template<typename T>
	inline void Vector2<T>::Init(T x, T y) {
		this->x = x;
		this->y = y;
	}

	template<typename T>
	inline CGM::Vector2<T>& Vector2<T>::Offset(T x, T y) {
		return *this = this->temp_Offset(x, y);
	}

	template<typename T>
	inline CGM::Vector2<T> Vector2<T>::temp_Offset(T x, T y) const {
		return CGM::Vector2<T>(this->x + x, this->y + y);
	}

	template<typename T>
	inline CGM::Vector2<T> Vector2<T>::operator+(CGM::Vector2<T> v2) const {
		return this->temp_Offset(v2.x, v2.y);
	}

	template<typename T>
	inline CGM::Vector2<T> Vector2<T>::operator-(CGM::Vector2<T> v2) const {
		return this->temp_Offset(-v2.x, -v2.y);
	}

	template<typename T>
	inline CGM::Vector2<T> Vector2<T>::operator*(T Val) const {
		return CGM::Vector2<T>(this->x * Val, this->y * Val);
	}

	template<typename T>
	inline CGM::Vector2<T> Vector2<T>::operator/(T Val) const {
		return CGM::Vector2<T>(this->x / Val, this->y / Val);
	}

	template<typename T>
	inline CGM::Vector2<T>& Vector2<T>::operator+=(CGM::Vector2<T> v2) {
		return *this = this->operator+(v2);
	}

	template<typename T>
	inline CGM::Vector2<T>& Vector2<T>::operator-=(CGM::Vector2<T> v2) {
		return *this = this->operator-(v2);
	}

	template<typename T>
	inline CGM::Vector2<T>& Vector2<T>::operator*=(T Val) {
		return *this = this->operator*(Val);
	}

	template<typename T>
	inline CGM::Vector2<T>& Vector2<T>::operator/=(T Val) {
		return *this = this->operator/(Val);
	}

	template<typename T>
	inline bool Vector2<T>::operator==(CGM::Vector2<T> v2) const {
		return (this->x == v2.x && this->y == v2.y);
	}

	template<typename T>
	inline bool Vector2<T>::operator!=(CGM::Vector2<T> v2) const {
		return !this->operator==(v2);
	}

}