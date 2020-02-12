#include "PAINT_pch.h"
#include "PAINT_Ellipse.h"
#include "GFX_Coords.h"
#include "GFX_Line.h"

using namespace paint;

static std::vector<int> ellipse(int const x, int const a2, int const b2, int const h, int const k)
{
	std::vector<int> yEllipse;
	auto const sqrtPart = sqrt((1 - (pow((x - h), 2) / a2)) * b2);
	yEllipse.push_back(k + sqrtPart);
	yEllipse.push_back(k - sqrtPart);
	return yEllipse;
}

std::vector<gfx::Line> Ellipse::getGeometry(gfx::Coords startCoords, gfx::Coords currentCoords)
{
	if (startCoords.x > currentCoords.x)
	{
		auto const tmp = currentCoords.x;
		currentCoords.x = startCoords.x;
		startCoords.x = tmp;
	}
	if (startCoords.y > currentCoords.y) {
		auto const tmp = currentCoords.y;
		currentCoords.y = startCoords.y;
		startCoords.y = tmp;
	}
	auto const a = abs(currentCoords.x - startCoords.x) / 2;
	auto const a2 = pow(a, 2);
	auto const b = abs(currentCoords.y - startCoords.y) / 2;
	auto const b2 = pow(b, 2);
	auto const h = startCoords.x + a;
	auto const k = startCoords.y + b;
	std::vector<gfx::Line> shapeLines;
	for (auto i=startCoords.x; i<(startCoords.x + 2*a); i+=2)
	{
		shapeLines.push_back({ i, ellipse(i, a2, b2, h, k)[0], i + 2, ellipse(i + 2, a2, b2, h, k)[0] });
		shapeLines.push_back({ i, ellipse(i, a2, b2, h, k)[1], i + 2, ellipse(i + 2, a2, b2, h, k)[1] });
	}
	return shapeLines;
}

