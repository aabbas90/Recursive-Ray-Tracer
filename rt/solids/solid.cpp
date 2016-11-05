#include "solid.h"
#include <core/assert.h>

namespace rt
{
	Solid::Solid(CoordMapper * texMapper, Material * material)
	{
		this->texMapper = texMapper;
		this->material = material;
	}

	Point Solid::sample() const
	{
		NOT_IMPLEMENTED;
	}
}