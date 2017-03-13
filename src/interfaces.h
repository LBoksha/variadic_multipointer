#ifndef INTERFACES_H
#define INTERFACES_H

#include <string>

class SizedWidget
{
public:
	virtual void set_position(unsigned int, unsigned int) = 0;
	virtual unsigned int get_x() const = 0;
	virtual unsigned int get_y() const = 0;
	virtual unsigned int get_width() const = 0;
	virtual unsigned int get_height() const = 0;
	virtual ~SizedWidget() {}
};

class ResizableWidget
{
public:
	virtual void set_size(unsigned int, unsigned int) = 0;
	virtual ~ResizableWidget() {}
};

class ValuedWidget
{
public:
	virtual void set_value(std::string const&) = 0;
	virtual std::string get_value() const = 0;
	virtual ~ValuedWidget() {}
};

#endif // #ifndef INTERFACES_H
