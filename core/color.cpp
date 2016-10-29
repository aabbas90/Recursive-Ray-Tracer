#include "color.h"
#include<algorithm>

namespace rt
{
	RGBColor RGBColor::operator+(const RGBColor &c) const
	{
		return RGBColor(this->r + c.r, this->g + c.g, this->b + c.b);
	}

	RGBColor RGBColor::operator-(const RGBColor &c) const
	{
		return RGBColor(this->r - c.r, this->g - c.g, this->b - c.b);
	}

	RGBColor RGBColor::operator*(const RGBColor &c) const
	{
		return RGBColor(this->r * c.r, this->g * c.g, this->b * c.b);
	}

	bool RGBColor::operator==(const RGBColor &c) const
	{
		return (this->r == c.r && this->g == c.g && this->b == c.b) ? 1 : 0;
	}

	bool RGBColor::operator!=(const RGBColor &c) const
	{
		return (this->r != c.r || this->g != c.g || this->b != c.b) ? 1 : 0;
	}

	RGBColor RGBColor::clamp() const
	{
		return RGBColor(std::fmax(std::fmin(this->r, 1), 0), 
						std::fmax(std::fmin(this->g, 1), 0), 
						std::fmax(std::fmin(this->b, 1), 0));
	}

	RGBColor operator*(float scalar, const RGBColor & b)
	{
		return RGBColor(b.r * scalar, b.g * scalar, b.b * scalar);
	}

	RGBColor operator*(const RGBColor & a, float scalar)
	{
		return scalar * a;
	}

	RGBColor operator/(const RGBColor & a, float scalar)
	{
		return RGBColor(a.r / scalar, a.g / scalar, a.b / scalar);
	}
}
