#ifndef PANEL_H
#define PANEL_H

#include "interfaces.h"

class Panel : public SizedWidget, public ResizableWidget {};

Panel * new_panel(unsigned int x, unsigned int y,
				  unsigned int sx, unsigned int sy);

#endif // #ifndef OBJECTPOINTER_H
