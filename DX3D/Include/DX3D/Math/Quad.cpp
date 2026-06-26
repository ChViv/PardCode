#include <DX3D/Math/Quad.h>

dx3d::Quad::Quad(Vertex topLeft, Vertex topRight, Vertex bottomRight, Vertex bottomLeft)
{
	leftTriangle.p1 = topLeft;
	leftTriangle.p2 = bottomRight;
	leftTriangle.p3 = bottomLeft;

	rightTriangle.p1 = topLeft;
	rightTriangle.p2 = topRight;
	rightTriangle.p3 = bottomRight;
}