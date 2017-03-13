#ifndef BUTTONS_H
#define BUTTONS_H

#include "interfaces.h"

class Button : public SizedWidget, public ResizableWidget, public ValuedWidget {};
class GraphicButton : public SizedWidget {};
class Icon : public SizedWidget, public ValuedWidget {};

Button * new_button(unsigned int x, unsigned int y, unsigned int sx, unsigned int sy, std::string const& value);
GraphicButton * new_graphic_button(unsigned int x, unsigned int y);
Icon * new_icon(unsigned int x, unsigned int y, std::string const& value);

#endif // #ifndef OBJECTPOINTER_H
