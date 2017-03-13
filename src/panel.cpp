#include <iostream>
#include "panel.h"

struct PanelImplementation : public Panel
{
	unsigned int x, y, sx, sy;

	PanelImplementation(unsigned int x, unsigned int y, unsigned int sx, unsigned int sy)
	: x(x), y(y), sx(sx), sy(sy)
	{
		std::cout << "Created a panel: {" << x << ", " << y << ", " << sx << ", " << sy << "}" << std::endl;
	}

	~PanelImplementation()
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
};

Panel * new_panel(unsigned int x, unsigned int y, unsigned int sx, unsigned int sy)
{
	return new PanelImplementation{x, y, sx, sy};
}
