#include <core/float4.h>

namespace rt 
{
	Float4::Float4(const Point& p)
	{
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
		this->w = 1.0f;
	}
	Float4::Float4(const Vector& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = 0.0f;
	}

	float& Float4::operator[](int idx)
	{
		switch(idx)
		{
			case 0: return x;
					break;
			case 1: return y;
					break;    
			case 2: return z;
					break;            
			case 3: return w;
					break;
			default: return x;
		}
	}
	float Float4::operator[](int idx) const
	{
		switch(idx)
		{
			case 0: return x;
					break;
			case 1: return y;
					break;    
			case 2: return z;
					break;            
			case 3: return w;
					break;
			default: return x;
		}
	}
	Float4 Float4::operator+(const Float4& b) const
	{
		return Float4(this->x + b.x, this->y + b.y, this->z + b.z, this->w + b.w);
	}
	Float4 Float4::operator-(const Float4& b) const
	{
		return Float4(this->x - b.x, this->y - b.y, this->z - b.z, this->w - b.w);
	}
	Float4 Float4::operator*(const Float4& b) const
	{
		return Float4(this->x * b.x, this->y * b.y, this->z * b.z, this->w * b.w);
	}
	Float4 Float4::operator/(const Float4& b) const
	{
		return Float4(this->x / b.x, this->y / b.y, this->z / b.z, this->w / b.w);
	}
	Float4 Float4::operator-() const
	{
		return Float4(-this->x, -this->y, -this->z, -this->w);
	}
	bool Float4::operator==(const Float4& b) const
	{
		return (this->x == b.x && this->y == b.y && this->z == b.z && this->w == b.w);    
	}
	bool Float4::operator!=(const Float4& b) const
	{
		return !(*this == b);
	}

	Float4 operator*(float scalar, const Float4& b)
	{
		return Float4(b.x * scalar, b.y * scalar, b.z * scalar, b.w * scalar);
	}
	Float4 operator*(const Float4& a, float scalar)
	{
		return scalar * a;
	}
	Float4 operator/(const Float4& a, float scalar)
	{
		return Float4((1 / scalar) * a);
	}
	float dot(const Float4& a, const Float4& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z +  a.w * b.w;
	}
	Float4 min(const Float4& a, const Float4& b)
	{
		return Float4(a.x < b.x ? a.x : b.x,
				a.y < b.y ? a.y : b.y,
				a.z < b.z ? a.z : b.z,
				a.w < b.w ? a.w : b.w);
	}
	Float4 max(const Float4& a, const Float4& b)
	{
		return Float4(a.x > b.x ? a.x : b.x,
				a.y > b.y ? a.y : b.y,
				a.z > b.z ? a.z : b.z,
				a.w > b.w ? a.w : b.w);
	}
}