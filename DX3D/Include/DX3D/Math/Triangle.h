#pragma once
#include <DX3D/Math/Vertex.h>

namespace dx3d
{
	class Triangle
	{
	public:
		Triangle() = default;
		Triangle(Vertex p1, Vertex p2, Vertex p3) : p1(p1), p2(p2), p3(p3) {}
		Vertex p1{}, p2{}, p3{};
	};
}