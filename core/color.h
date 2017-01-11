#ifndef CG1RAYTRACER_RGBCOLOR_HEADER
#define CG1RAYTRACER_RGBCOLOR_HEADER

#include <core/macros.h>
#include <iostream>

namespace rt {

class Float4;

class ALIGN(16) RGBColor {
public:
    float r, g, b;

    RGBColor() {}
    RGBColor(float r, float g, float b) : r(r), g(g), b(b) {}
    explicit RGBColor(const Float4& f4);

    static RGBColor rep(float v) { return RGBColor(v,v,v); }

    RGBColor operator+(const RGBColor& c) const;
    RGBColor operator-(const RGBColor& c) const;
    RGBColor operator*(const RGBColor& c) const;
    
    bool operator==(const RGBColor& b) const;
    bool operator!=(const RGBColor& b) const;

    RGBColor clamp() const;
    RGBColor gamma(float gam) const;
    float grayscale() const;
    float luminance() const;
    static RGBColor white();
    static RGBColor black();
};

RGBColor operator*(float scalar, const RGBColor& b);
RGBColor operator*(const RGBColor& a, float scalar);
RGBColor operator/(const RGBColor& a, float scalar);
std::ostream& operator<<(std::ostream& os, const RGBColor& c);

}

#endif
