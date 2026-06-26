#pragma once
#include <DX3D/Math/Vec3.h>

namespace dx3d
{
	class Cube
	{
	public:
		Cube(Vec3 _position, Vec3 _scale);

		Vec3 position{};
		Vec3 scale{};
		Vec3 rotation{};
	};
}