#include "PAINT_pch.h"
#include "PAINT_Ellipse.h"
#include "WIN_Coords.h"
#include "GFX_Line.h"

using namespace paint;
using namespace win;

std::vector<gfx::Line> Ellipse::shapeGeometry(win::Coords startCoords, win::Coords currentCoords)
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
	auto const b = abs(currentCoords.y - startCoords.y) / 2;
	auto const h = startCoords.x + a;
	auto const k = startCoords.y + b;
	std::vector<gfx::Line> shapeLines;
	for (auto i=startCoords.x; i<(startCoords.x + 2*a); ++i)
	{
		shapeLines.push_back({ i, ellipse(i, a, b, h, k)[0], i + 1, ellipse(i + 1, a, b, h, k)[0] });
		shapeLines.push_back({ i, ellipse(i, a, b, h, k)[1], i + 1, ellipse(i + 1, a, b, h, k)[1] });
	}
	return shapeLines;
}

std::vector<int> Ellipse::ellipse(int x, int a, int b, int h, int k) const
{
	std::vector<int> yEllipse;
	yEllipse.push_back(k + sqrt((1 - (pow((x - h), 2) / pow(a, 2))) * pow(b, 2)));
	yEllipse.push_back(k - sqrt((1 - (pow((x - h), 2) / pow(a, 2))) * pow(b, 2)));
	return yEllipse;
}
