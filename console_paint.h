#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

class Position
{
private:
	int x;
	int y;
public:
	Position()
	{
		this->x = 0;
		this->y = 0;
	}

	Position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	~Position()
	{

	}

	int GetX()
	{
		return x;
	}

	int GetY()
	{
		return y;
	}
};

class Shape
{
protected:
	Position position;
	char fill_character;

public:
	Shape(Position position, char fill_character)
	{
		this->position = position;
		this->fill_character = fill_character;
	}

	virtual void draw(char* draw_area, int draw_area_width, int draw_area_height) = 0;
};

class Line : public Shape
{
private:
	int count_points;
	double angle_factor;
	int is_argument_const;

public:
	Line(int count_points, double angle_factor, char fill_character, Position position, int is_argument_const) : Shape(position, fill_character)
	{
		if (count_points <= 0 && (is_argument_const > 1 || is_argument_const < 0))
		{
			throw "Incorrect arguments";
		}

		this->count_points = count_points;
		this->angle_factor = angle_factor;
		this->is_argument_const = is_argument_const;
	}

	~Line()
	{
		
	}

	void draw(char* draw_area, int draw_area_width, int draw_area_height) override
	{
		int correct_count_points = count_points;
		int y = -1, x = -1 * (correct_count_points / 2);

		while (correct_count_points != 0)
		{
			int flag = 1;
			if (!is_argument_const)
			{
				x++;
				y = -1 * angle_factor * x;
				flag = ((-1 * angle_factor * x) - int(-1 * angle_factor * x)) == 0;
			}
			else
			{
				x = 0;
				y++;
			}

			if (flag)
			{
				correct_count_points--;
				if ((x + position.GetX()) < draw_area_width && (y + position.GetY()) < draw_area_height)
					*(draw_area + (y + position.GetY()) * draw_area_width + (x + position.GetX())) = fill_character;
			}
		}
	}
};

class Triangle : public Shape
{
private:
	int sides_length;
	Line *first_side;
	Line *second_side;
	Line *third_side;

public:
	Triangle(int sides_length, char fill_character, Position position) : Shape(position, fill_character)
	{
		if (sides_length < 2)
		{
			throw "Incorrect sides_length";
		}

		this->sides_length = sides_length;

		Position line_position = position;
		first_side = new Line(sides_length, 1, fill_character, line_position, 0);

		line_position = { position.GetX() + sides_length - 1, sides_length % 2 == 0 ? position.GetY() - 1 : position.GetY() - 2 };
		second_side = new Line(sides_length, -1, fill_character, line_position, 0);

		line_position = { sides_length % 2 == 0 ? position.GetX() + sides_length / 2 - 1 : position.GetX() + sides_length / 2, position.GetY() + sides_length / 2 - 1 };
		third_side = new Line(sides_length * 2 - 1, 0, fill_character, line_position, 0);
	}

	~Triangle()
	{
		delete first_side;
		delete second_side;
		delete third_side;
	}

	void draw(char* draw_area, int draw_area_width, int draw_area_height) override
	{
		first_side->draw(draw_area, draw_area_width, draw_area_height);
		second_side->draw(draw_area, draw_area_width, draw_area_height);
		third_side->draw(draw_area, draw_area_width, draw_area_height);
	}
};

class Rectangle : public Shape
{
private:
	int vertiacal_sides_length;
	int horizontal_sides_length;
	Line *first_side;
	Line *second_side;
	Line *third_side;
	Line *fourth_side;

public:
	Rectangle(int vertiacal_sides_length, int horizontal_sides_length, char fill_character, Position position) : Shape(position, fill_character)
	{
		if (vertiacal_sides_length < 2 || horizontal_sides_length < 2)
		{
			throw "Incorrect sides length";
		}

		this->vertiacal_sides_length = vertiacal_sides_length;
		this->horizontal_sides_length = horizontal_sides_length;

		Position line_position = position;
		first_side = new Line(horizontal_sides_length, 0, fill_character, line_position, 0);

		line_position = { position.GetX() - (horizontal_sides_length / 2 - 1), position.GetY() };
		second_side = new Line(vertiacal_sides_length, 0, fill_character, line_position, 1);

		if (horizontal_sides_length % 2 == 0)
			line_position = { position.GetX() + (horizontal_sides_length / 2), position.GetY() };
		else
			line_position = { position.GetX() + (horizontal_sides_length / 2) + 1, position.GetY() };

		third_side = new Line(vertiacal_sides_length, 0, fill_character, line_position, 1);

		line_position = { position.GetX(), position.GetY() + (vertiacal_sides_length - 1) };
		fourth_side = new Line(horizontal_sides_length, 0, fill_character, line_position, 0);
	}

	~Rectangle()
	{
		delete first_side;
		delete second_side;
		delete third_side;
		delete fourth_side;
	}

	void draw(char* draw_area, int draw_area_width, int draw_area_height) override
	{
		first_side->draw(draw_area, draw_area_width, draw_area_height);
		second_side->draw(draw_area, draw_area_width, draw_area_height);
		third_side->draw(draw_area, draw_area_width, draw_area_height);
		fourth_side->draw(draw_area, draw_area_width, draw_area_height);
	}

	
};

class Circle : public Shape
	{
	private:
		int radius;
	public:
		Circle(int radius, char fill_character, Position position) : Shape(position, fill_character)
		{
			if (radius < 3)
			{
				throw "Incorrect radius";
			}

			this->radius = radius;
		}

		~Circle()
		{
			
		}

		void draw(char* draw_area, int draw_area_width, int draw_area_height) override
		{
			int radius = this->radius;
			int centerX = position.GetX();
			int centerY = position.GetY();

			for (int y = -radius; y <= radius + centerY; y++)
			{
				for (int x = -radius; x <= radius + centerX; x++)
				{
					if (((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY)) <= (radius * radius))
					{
						if ((x + centerX) < draw_area_width && (y + centerY) < draw_area_height)
						{
							*(draw_area + (y + centerY) * draw_area_width + (x + centerX)) = fill_character;
						}
					}
				}
			}
		}
	};

class Canvas
{
private:
	int width;
	int height;
	char fill_character;
	char* draw_area;
public:
	Canvas(int width, int height, char fill_character)
	{
		this->width = width;
		this->height = height;
		this->fill_character = fill_character;
		draw_area = (char*)malloc(this->height * this->width * sizeof(char));
		clear();
	}

	~Canvas()
	{
		delete draw_area;
	}

	void clear()
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				*(draw_area + i * width + j) = fill_character;
			}
		}
	}

	void add(Shape *shape)
	{
		shape->draw(draw_area, width, height);
	}

	void display()
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				printf("%c", *(draw_area + i * width + j));
			}
			printf("\n");
		}
	}
};