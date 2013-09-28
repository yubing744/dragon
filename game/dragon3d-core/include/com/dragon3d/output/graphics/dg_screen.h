#pragma once

#include "dg_config.h"

#if !defined(DG_SCREEN)
#define DG_SCREEN

class DGScreen
{
public:
	DGScreen(void);
	virtual ~DGScreen(void);

public:
	DGuint getWidth();
	DGuint getHeight();

	void resize(DGuint width, DGuint height);

private:
	DGuint width;
	DGuint height;
};

#endif