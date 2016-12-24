#include <rt/textures/perlin.h>
#include <core/point.h>
#include <core/interpolate.h>
#include <core/scalar.h>
#include <math.h>
#include <core/interpolate.h>

namespace rt 
{

    /* returns a value in range -1 to 1 */
    float noise(int x, int y, int z) 
    {
        int n = x + y * 57 + z * 997;
        n = (n<<13) ^ n;
        return ( 1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    }
 
    PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black)
        :white(white), black(black) {}

    void PerlinTexture::addOctave(float amplitude, float frequency)
    {
        amplitudes.push_back(amplitude);
        frequencies.push_back(frequency);
    }
    float getNoiseAtCubeCenter(const Point& coord)
    {
        //lattice coordinates
        int lu = floor(coord.x);
        int lv = floor(coord.y);
        int lw = floor(coord.z);

        float fu = coord.x - lu;
        float fv = coord.y - lv;
        float fw = coord.z - lw;

        //noise at 8 corners
        float corner1 = noise(lu, lv, lw);
        float corner2 = noise(lu + 1, lv, lw);
        float corner3 = noise(lu, lv + 1, lw);
        float corner4 = noise(lu + 1, lv + 1, lw);
        float corner5 = noise(lu, lv, lw + 1);
        float corner6 = noise(lu + 1, lv, lw + 1);
        float corner7 = noise(lu , lv + 1, lw + 1);
        float corner8 = noise(lu + 1, lv + 1, lw + 1);
        
        //trilinear interpolation
        // px0y0z0, px1y0z0, px0y1z0, px1y1z0, px0y0z1, px1y0z1, px0y1z1, px1y1z1
        return lerp3d(corner1, corner2, corner3, corner4, corner5, corner6, corner7, corner8, fu, fv, fw);
    }
    RGBColor PerlinTexture::getColor(const Point& coord)
    {
        float noiseColor = 0.0f; 
        for(int i = 0; i < frequencies.size(); ++i)
        {
            noiseColor += getNoiseAtCubeCenter(coord * frequencies[i]) * amplitudes[i];
        }
        return lerp(black, white, noiseColor);
    }
    RGBColor PerlinTexture::getColorDX(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
    RGBColor PerlinTexture::getColorDY(const Point& coord)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }


}
