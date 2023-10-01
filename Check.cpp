#include "console_paint.h"

int main()
{
	Canvas canvas = {};
	init(&canvas, 100, 50, '-');

	Position position = { 20, 20 };
	Line line1 = {};
	init(&line1, 9, 1, '*', position, 0);

	position = { 24, 23 };
	Line line2 = {};
	init(&line2, 17, 0, '*', position, 0);

	position = {28, 18};
	Line line3 = {};
	init(&line3, 9, -1, '*', position, 0);

	position = { 40, 27 };
	Rectangle rectangle = {};
	init(&rectangle, 6, 4, '6', position);

	position = {40, 20};
	Triangle triangle = {};
	init(&triangle, 6, '0', position);

	position = { 40, 22 };
	Circle circle = {};
	init(&circle, 5, '#', position);

	add(&canvas, line1);
	add(&canvas, line2);
	add(&canvas, line3);

	add(&canvas, rectangle);

	add(&canvas, triangle);

	add(&canvas, circle);

	display(&canvas);
}