#pragma once

#include "dg_config.h"
#include "dg_screen.h"
#include "dg_color.h"

#if !defined(DG_GUI_TEXT)
#define DG_GUI_TEXT

class DGGUIText
{
public:
	DGGUIText();
	virtual ~DGGUIText(void);

public:
	void init(DGScreen* screen);
	void print(GLint x, GLint y, const char *fmt, ...);
	void print(GLint x, GLint y, DGColor color, const char *fmt, ...);
	void destroy();

private:
	GLuint base;
	DGScreen* screen;
};

#endif
