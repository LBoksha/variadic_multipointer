#include <iostream>
#include "interfaces.h"
#include "multipointer.h"
#include "panel.h"
#include "buttons.h"

int main()
{
	// Classical style constructor:
	m_ptr<ResizableWidget, SizedWidget> a(new_panel(0, 1, 100, 101));
	std::cout << "a has pointers: " << a << std::endl;

	// New-style constructor:
	m_ptr<SizedWidget, ResizableWidget> b{new_panel(2, 3, 102, 103)};
	std::cout << "b has pointers: " << b << std::endl;
	// get() defaults to returning a pointer of the first class:
	delete a.get();
	a = b;
	// The order of the classes doesn't matter:
	std::cout << "after assigning b to a, a has pointers: " << a << std::endl;
	delete b.get();

	// Assignment constructor
	m_ptr<ResizableWidget, SizedWidget> c = new_panel(4, 5, 104, 105);
	std::cout << "c has pointers: " << c << std::endl;
	delete c.get();
	c = nullptr;
	std::cout << "after nullptr assignment, c has pointers: " << c << std::endl;

	// Default constructor followed by assignment
	m_ptr<ResizableWidget, SizedWidget> d;
	std::cout << "uninitialized d has pointers: " << d << std::endl;
	d = new_panel(6, 7, 106, 107);
	std::cout << "after assignment, d has pointers: " << d << std::endl;

	// Can't construct from pointers to objects that don't implement the right base classes
	// m_ptr<ResizableWidget, SizedWidget, ValuedWidget> bad(new_panel(0, 0, 10, 10));
	// error: cannot convert 'Panel*' to 'ValuedWidget*' in initialization

	// Can't assign them either
	// m_ptr<ResizableWidget, SizedWidget, ValuedWidget> bad;
	// bad = new_panel(0, 0, 10, 10);
	// error: cannot convert 'Panel*' to 'ValuedWidget*' in assignment

	// Can construct from other m_pointers
	m_ptr<ResizableWidget, SizedWidget> e(d);
	std::cout << "e has pointers: " << e << std::endl;

	// Class order does not matter
	m_ptr<SizedWidget, ResizableWidget> f(d);
	std::cout << "f has pointers: " << f << std::endl;

	// Assignment from another m_ptr
	m_ptr<ResizableWidget, SizedWidget> g;
	std::cout << "unassigned g has pointers: " << g << std::endl;
	g = e;
	std::cout << "after assignment, g has pointers: " << g << std::endl;

	// Construction from an m_ptr that requires less base classes works:
	m_ptr<ResizableWidget> h(f);
	std::cout << "after assignment, h has pointers: " << h << std::endl;

	// Assignment from an m_ptr that requires less base classes works:
	m_ptr<SizedWidget> i;
	i = f;

	// Can't assign ResizableWidget* to SizedWidget*
	// i = h;
	// h = i;
	// error: static assertion failed: incompatible pointer type

	// But we can compare the two pointers:
	std::cout << "Do i and h point to the same object? " << (i == h ? "Yes!" : "No!") << std::endl;
	i = new_panel(8, 9, 107, 108);
	std::cout << "Do i and h point to the same object now? " << (i == h ? "Yes!" : "No!") << std::endl;

	delete h.get();
	// Assigning nullptr works
	h = nullptr;
	std::cout << "after nullptr assignment, h has pointers: " << h << std::endl;
	std::cout << "Do i and h point to the same object now? " << (i == h ? "Yes!" : "No!") << std::endl;

	// Direct assignment doesn't work, of course, but we can do a dynamic cast
	h = do_dynamic_cast<ResizableWidget>(i);
	std::cout << "assigning i, h has pointers: " << h << std::endl;
	std::cout << "Do i and h point to the same object now? " << (i == h ? "Yes!" : "No!") << std::endl;

	m_ptr<ResizableWidget, SizedWidget, ValuedWidget> j = new_button(20, 20, 200, 20, "OK");
	std::cout << "j has pointers: " << j << std::endl;
	delete j.get();
	j = do_dynamic_cast<ResizableWidget, SizedWidget, ValuedWidget>(h);
	std::cout << "after assigning a bad dynamic cast, j has pointers: " << j << std::endl;

	delete j.get();

	m_ptr<ResizableWidget, SizedWidget> p = new_panel(0, 0, 10, 10);
	m_ptr<SizedWidget, ResizableWidget> q = p;
	m_ptr<SizedWidget> r = p;
	std::cout << "Our panel is: " << p.get<SizedWidget>()->get_width() << " pixels wide" << std::endl;
	std::cout << "Our panel is: " << q.get<SizedWidget>()->get_height() << " pixels high" << std::endl;
	p->set_size(20, 15); // Dereferencing directly gives the first class
	// So the following doesn't work (I kind of wish it did...)
	// q->set_size(20, 15);
	std::cout << "Now our panel is: " << q->get_width() << " pixels wide" << std::endl;
	std::cout << "Now our panel is: " << r->get_height() << " pixels high" << std::endl;
	// p.get<ValuedWidget>()->set_value("Hi!"); // Error! p doesn't know about ValuedWidget
	// p = q; // Error! q doesn't know about ResizableWidget
	delete p.get();
	return 0;
}
