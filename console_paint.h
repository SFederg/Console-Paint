#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int x;
	int y;
}
Position;

typedef struct
{
	int count_points;
	double angle_factor;
	char fill_character;
	Position position;
	int is_argument_const;
}
Line;

void init(Line *line, int count_points, double angle_factor, char fill_character, Position position, int is_argument_const)
{
	if (count_points <= 0 && (is_argument_const > 1 || is_argument_const < 0))
	{
		throw "Incorrect arguments";
	}
	line->count_points = count_points;
	line->angle_factor = angle_factor;
	line->fill_character = fill_character;
	line->position = position;
	line->is_argument_const = is_argument_const;
}

void draw(Line *line, char* draw_area, int draw_area_width, int draw_area_height)
{
	int correct_count_points = line->count_points;
	int y = -1, x = -1 * (correct_count_points / 2);

	while (correct_count_points != 0)
	{
		int flag = 1;
		if (!line->is_argument_const)
		{
			x++;
			y = -1 * line->angle_factor * x;
			flag = ((-1 * line->angle_factor * x) - int(-1 * line->angle_factor * x)) == 0;
		}
		else
		{
			x = 0;
			y++;
		}

		if (flag)
		{
			correct_count_points--;
			if ((x + line->position.x) < draw_area_width && (y + line->position.y) < draw_area_height)
				*(draw_area + (y + line->position.y) * draw_area_width + (x + line->position.x)) = line->fill_character;
		}
	}
}

typedef struct
{
	int sides_length;
	char fill_character;
	Position position;
	Line first_side;
	Line second_side;
	Line third_side;
}
Triangle;

void init(Triangle *triangle, int sides_length, char fill_character, Position position)
{
	if (sides_length < 2)
	{
		throw "Incorrect sides_length";
	}

	triangle->sides_length = sides_length;
	triangle->fill_character = fill_character;
	triangle->position = position;

	Position line_position = position;
	triangle->first_side = {};
	init(&triangle->first_side, sides_length, 1, fill_character, line_position, 0);

	line_position = {position.x + sides_length - 1, sides_length % 2 == 0 ? position.y - 1 : position.y - 2};
	triangle->second_side = {};
	init(&triangle->second_side, sides_length, -1, fill_character, line_position, 0);

	line_position = {sides_length % 2 == 0 ? position.x + sides_length / 2 - 1: position.x + sides_length / 2, position.y + sides_length / 2 - 1};
	triangle->third_side = {};
	init(&triangle->third_side, sides_length * 2 - 1, 0, fill_character, line_position, 0);
}

void draw(Triangle* triangle, char* draw_area, int draw_area_width, int draw_area_height)
{
	draw(&triangle->first_side, draw_area, draw_area_width, draw_area_height);
	draw(&triangle->second_side, draw_area, draw_area_width, draw_area_height);
	draw(&triangle->third_side, draw_area, draw_area_width, draw_area_height);
}

typedef struct
{
	int vertiacal_sides_length;
	int horizontal_sides_length;
	char fill_character;
	Position position;
	Line first_side;
	Line second_side;
	Line third_side;
	Line fourth_side;

} Rectangle;

void init(Rectangle *rectangle, int vertiacal_sides_length, int horizontal_sides_length, char fill_character, Position position)
{
	if (vertiacal_sides_length < 2 || horizontal_sides_length < 2)
	{
		throw "Incorrect sides length";
	}

	rectangle->vertiacal_sides_length = vertiacal_sides_length;
	rectangle->horizontal_sides_length = horizontal_sides_length;
	rectangle->fill_character = fill_character;
	rectangle->position = position;

	Position line_position = position;
	rectangle->first_side = {};
	init(&rectangle->first_side, horizontal_sides_length, 0, fill_character, line_position, 0);

	line_position = { position.x - (horizontal_sides_length / 2 - 1), position.y};
	rectangle->second_side = {};
	init(&rectangle->second_side, vertiacal_sides_length, 0, fill_character, line_position, 1);

	if (horizontal_sides_length % 2 == 0)
		line_position = { position.x + (horizontal_sides_length / 2), position.y };
	else
		line_position = { position.x + (horizontal_sides_length / 2) + 1, position.y };

	rectangle->third_side = {};
	init(&rectangle->third_side, vertiacal_sides_length, 0, fill_character, line_position, 1);

	line_position = { position.x, position.y + (vertiacal_sides_length - 1) };
	rectangle->fourth_side = {};
	init(&rectangle->fourth_side, horizontal_sides_length, 0, fill_character, line_position, 0);
}

void draw(Rectangle* rectangle, char* draw_area, int draw_area_width, int draw_area_height)
{
	draw(&rectangle->first_side, draw_area, draw_area_width, draw_area_height);
	draw(&rectangle->second_side, draw_area, draw_area_width, draw_area_height);
	draw(&rectangle->third_side, draw_area, draw_area_width, draw_area_height);
	draw(&rectangle->fourth_side, draw_area, draw_area_width, draw_area_height);
}

typedef struct
{
	int radius;
	char fill_character;
	Position position;
}
Circle;

void init(Circle *circle, int radius, char fill_character, Position position)
{
	if (radius < 3)
	{
		throw "Incorrect radius";
	}

	circle->radius = radius;
	circle->fill_character = fill_character;
	circle->position = position;
}

void draw(Circle* circle, char* draw_area, int draw_area_width, int draw_area_height)
{
	int radius = circle->radius;
	int centerX = circle->position.x;
	int centerY = circle->position.y;

	for (int y = -radius; y <= radius + centerY; y++)
	{
		for (int x = -radius; x <= radius + centerX; x++)
		{
			if (((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY)) <= (radius * radius))
			{
				if ((x + centerX) < draw_area_width && (y + centerY) < draw_area_height)
				{
					*(draw_area + (y + centerY) * draw_area_width + (x + centerX)) = circle->fill_character;
				}
			}
		}
	}
}

typedef struct
{
	int width;
	int height;
	char fill_character;
	char *draw_area;
}
Canvas;

void clear(Canvas *canvas)
{
	for (int i = 0; i < canvas->height; i++)
	{
		for (int j = 0; j < canvas->width; j++)
		{
			*(canvas->draw_area + i * canvas->width + j) = canvas->fill_character;
		}
	}
}

void init(Canvas *canvas, int width, int height, char fill_character)
{
	canvas->width = width;
	canvas->height = height;
	canvas->fill_character = fill_character;

	canvas->draw_area = (char*)malloc(canvas->height * canvas->width * sizeof(char));

	clear(canvas);
}

void add(Canvas *canvas, Line line)
{
	draw(&line, canvas->draw_area, canvas->width, canvas->height);
}

void add(Canvas* canvas, Rectangle rectagle)
{
	draw(&rectagle, canvas->draw_area, canvas->width, canvas->height);
}

void add(Canvas* canvas, Triangle triangle)
{
	draw(&triangle, canvas->draw_area, canvas->width, canvas->height);
}

void add(Canvas* canvas, Circle circle)
{
	draw(&circle, canvas->draw_area, canvas->width, canvas->height);
}

void display(Canvas *canvas)
{
	for (int i = 0; i < canvas->height; i++)
	{
		for (int j = 0; j < canvas->width; j++)
		{
			printf("%c", *(canvas->draw_area + i * canvas->width + j));
		}
		printf("\n");
	}
}