#ifndef CG1RAYTRACER_TEXTURES_IMAGETEX_HEADER
#define CG1RAYTRACER_TEXTURES_IMAGETEX_HEADER

#include <core/vector.h>
#include <core/image.h>
#include <rt/textures/texture.h>

namespace rt {

class ImageTexture : public Texture {
public:
    enum BorderHandlingType {
        CLAMP,
        MIRROR,
        REPEAT
    };

    enum InterpolationType {
        NEAREST,
        BILINEAR
    };

    ImageTexture();
    ImageTexture(const Image& image, BorderHandlingType bh=REPEAT, InterpolationType i=BILINEAR);
    ImageTexture(const std::string& filename, BorderHandlingType bh=REPEAT, InterpolationType i=BILINEAR);
    std::pair <float,float> getTextureCoordinates(const Point& coord) const;
    RGBColor getColorAtXY(const float x, const float y) const;
    virtual RGBColor getColor(const Point& coord);
    virtual RGBColor getColorDX(const Point& coord);
    virtual RGBColor getColorDY(const Point& coord);
private:
    Image image;
    BorderHandlingType bh;
    InterpolationType i;
    std::string filename;
};

}

#endif
