#include <iostream>
#include "buttons.h"

struct ButtonImplementation : public Button
{
	unsigned int x, y, sx, sy;
	std::string value;

	ButtonImplementation(unsigned int x, unsigned int y, unsigned int sx, unsigned int sy, std::string const& value)
	: x(x), y(y), sx(sx), sy(sy), value(value)
	{
		std::cout << "Created a panel: {" << x << ", " << y << ", " << sx << ", " << sy << "}" << std::endl;
	}

	~ButtonImplementation()
	{
		std::cout << "Deleted a panel: {" << x << ", " << y << ", " << sx << ", " << sy << "}" << std::endl;
	}

	virtual void set_position(unsigned int nx, unsigned int ny) override
	{
		x = nx;
		y = ny;
	}

	virtual unsigned int get_x() const override
	{
		return x;
	}

	virtual unsigned int get_y() const override
	{
		return y;
	}

	virtual unsigned int get_width() const override
	{
		return sx;
	}

	virtual unsigned int get_height() const override
	{
		return sy;
	}

	virtual void set_size(unsigned int nsx, unsigned int nsy) override
	{
		sx = nsx;
		sy = nsy;
	}

	virtual void set_value(std::string const& new_value) override
	{
		value = new_value;
	}

	virtual std::string get_value() const override
	{
		return value;
	}
};

struct GraphicButtonImplementation : GraphicButton
{
	unsigned int x, y;

	GraphicButtonImplementation(unsigned int x, unsigned int y)
	: x(x), y(y)
	{
		std::cout << "Created a panel: {" << x << ", " << y << "}" << std::endl;
	}

	~GraphicButtonImplementation()
	{
		std::cout << "Deleted a panel: {" << x << ", " << y << "}" << std::endl;
	}

	virtual void set_position(unsigned int nx, unsigned int ny) override
	{
		x = nx;
		y = ny;
	}

	virtual unsigned int get_x() const override
	{
		return x;
	}

	virtual unsigned int get_y() const override
	{
		return y;
	}

	virtual unsigned int get_width() const override
	{
		return 32;
	}

	virtual unsigned int get_height() const override
	{
		return 32;
	}
};

struct IconImplementation : public Icon
{
	unsigned int x, y;
	std::string value;

	IconImplementation(unsigned int x, unsigned int y, std::string const& value)
	: x(x), y(y), value(value)
	{
		std::cout << "Created an icon: {" << x << ", " << y << ", " << value << "}" << std::endl;
	}

	~IconImplementation()
	{
		std::cout << "Deleted an icon: {" << x << ", " << y << ", " << value << "}" << std::endl;
	}

	virtual void set_position(unsigned int nx, unsigned int ny) override
	{
		x = nx;
		y = ny;
	}

	virtual unsigned int get_x() const override
	{
		return x;
	}

	virtual unsigned int get_y() const override
	{
		return y;
	}

	virtual unsigned int get_width() const override
	{
		return 32;
	}

	virtual unsigned int get_height() const override
	{
		return 32;
	}

	virtual void set_value(std::string const& new_value) override
	{
		value = new_value;
	}

	virtual std::string get_value() const override
	{
		return value;
	}
};

Button * new_button(unsigned int x, unsigned int y, unsigned int sx, unsigned int sy, std::string const& value)
{
	return new ButtonImplementation(x, y, sx, sy, value);
}

GraphicButton * new_graphic_button(unsigned int x, unsigned int y)
{
	return new GraphicButtonImplementation(x, y);
}

Icon * new_icon(unsigned int x, unsigned int y, std::string const& value)
{
	return new IconImplementation(x, y, value);
}
