#include <rt/textures/constant.h>

namespace rt
{
    ConstantTexture::ConstantTexture(const RGBColor& color)
    {
        constantColor = color;
    }
    RGBColor ConstantTexture::getColor(const Point& coord)
    {
        return constantColor;
    }
    RGBColor ConstantTexture::getColorDX(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
    RGBColor ConstantTexture::getColorDY(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
}