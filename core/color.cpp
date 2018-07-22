#include "color.h"

#include <algorithm>
#include <cmath>

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
	std::ostream& operator<<(std::ostream& os, const RGBColor& c)
	{
	    os << "COLOR R:" << c.r << " G:" << c.g << " B:" << c.b;
	    return os;
	}
	float RGBColor::grayscale() const
	{
		return (this->r + this->g + this->b) / 3;
	}

	RGBColor RGBColor::white()
	{
		return RGBColor(1.0f, 1.0f, 1.0f);
	}
	RGBColor RGBColor::black()
	{
		return RGBColor(0.0f, 0.0f, 0.0f);
	}
}
