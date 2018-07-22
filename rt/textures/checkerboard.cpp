#include <rt/textures/checkerboard.h>
#include <math.h>
#include <core/point.h>

namespace rt
{
    CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
    :white(white), black(black) {}

    RGBColor CheckerboardTexture::getColor(const Point& coord)
    {
        //lattice coordinates
        int lx = floor(2 * coord.x + BIG_POINT);//floor(2 * coord.x + BIG_POINT);
        int ly = floor(2 * coord.y + BIG_POINT);
        int lz = floor(2 * coord.z + BIG_POINT);

        //compute parity
        int parity = abs(lx + ly + lz) % 2;
        if(parity == 0)
            return black;    
        else
            return white;  

    }
    RGBColor CheckerboardTexture::getColorDX(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
    RGBColor CheckerboardTexture::getColorDY(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
}