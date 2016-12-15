#include "interpolate.h"
#include "assert.h"

namespace rt {

    template <typename T>
    T lerp(const T& px0, const T& px1, float xPoint) {
		//TODO
        NOT_IMPLEMENTED;
    }

    template <typename T>
    T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight) {
		//TODO
        NOT_IMPLEMENTED;
    }

    template <typename T>
    T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight) {
		//TODO
        NOT_IMPLEMENTED;
    }

    template <typename T>
    T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
        const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
        float xPoint, float yPoint, float zPoint) {
			//TODO
            NOT_IMPLEMENTED;
    }

}

