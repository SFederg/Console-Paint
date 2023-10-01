#include "console_paint.h"

int main()
{
    Canvas canvas(100, 50, ' ');
    Shape* shape;
    Position position = {74, 34};
    Line line1(9, 0, '*', position, 1);
    shape = &line1;
    canvas.add(shape);

    position = { 86, 34 };
    Line line2(9, 0, '*', position, 1);
    shape = &line2;
    canvas.add(shape);

    position = { 86, 25 };
    Line line3(9, 1, '*', position, 0);
    shape = &line3;
    canvas.add(shape);

    position = { 71, 22 };
    Line line4(9, -1, '*', position, 0);
    shape = &line4;
    canvas.add(shape);

    position = {75, 30};
    Triangle triangle1(9, '0', position);
    shape = &triangle1;
    canvas.add(shape);

    position = {40, 10};
    Circle circle(5, '#', position);
    shape = &circle;
    canvas.add(shape);

    position = { 30, 20 };
    Rectangle rectangle(20, 40, '=', position);
    shape = &rectangle;
    canvas.add(shape);

    position = { 19, 11 };
    Triangle triangle(21, '0', position);
    shape = &triangle;
    canvas.add(shape);

    canvas.display();
}