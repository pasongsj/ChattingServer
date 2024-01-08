#pragma once

// 설명 :
class EngineMath final
{

private:
	// 직접 사용할 수 없도록 추상화 시킴
	virtual ~EngineMath() = 0;

};

class float4
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		struct
		{
			float PosX;
			float PosY;
			float SizeX;
			float SizeY;
		};

		float Arr1D[4];
	};

	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{
	}

	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{
	}

	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	inline int ix() const
	{
		return static_cast<int>(x);
	}

	inline int iy() const
	{
		return static_cast<int>(y);
	}

	inline int iz() const
	{
		return static_cast<int>(z);
	}

	inline int iw() const
	{
		return static_cast<int>(w);
	}

	inline bool operator ==(const float4& _Value) const
	{
		return _Value.x == x && _Value.y == y && _Value.z == z;
	}

	inline float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}

	inline float4 operator *(const float4& _Value) const
	{
		float4 Return;
		Return.x = x * _Value.x;
		Return.y = y * _Value.y;
		Return.z = z * _Value.z;
		return Return;
	}

	inline float4 operator +(const float4& _Value) const
	{
		float4 Return;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	inline float4 operator -(const float4& _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}



	inline float4 operator /(const float4& _Value) const
	{
		float4 Return;
		Return.x = x / _Value.x;
		Return.y = y / _Value.y;
		Return.z = z / _Value.z;
		return Return;
	}


	inline float4 operator /(const float _Value) const
	{
		float4 Return;
		Return.x = x / _Value;
		Return.y = y / _Value;
		Return.z = z / _Value;
		return Return;
	}

	inline float4 operator -() const
	{
		return { -x, -y, -z, w };
	}

	inline float4& operator +=(const float4& _Other)
	{
		*this = *this + _Other;
		return *this;
	}

	inline float4& operator *=(const float _Value)
	{
		*this = *this * _Value;
		return *this;
	}

	inline float4& operator /=(const float _Value)
	{

		*this = *this / _Value;
		return *this;
	}

	inline float4& operator *=(const float4& _Other)
	{
		*this = *this * _Other;
		return *this;
	}

	inline float4& operator -=(const float4& _Other)
	{
		*this = *this - _Other;
		return *this;
	}

	inline float4& operator /=(const float4& _Other)
	{
		*this = *this / _Other;
		return *this;
	}

};