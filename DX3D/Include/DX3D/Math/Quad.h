#pragma once
#include <DX3D/Math/Vertex.h>
#include <DX3D/Math/Triangle.h>

namespace dx3d
{
	class Quad
	{
	public:
		Quad() = default;
		Quad(Vertex topLeft, Vertex topRight, Vertex bottomRight, Vertex bottomLeft);
		Triangle leftTriangle{}, rightTriangle{};
	};
}