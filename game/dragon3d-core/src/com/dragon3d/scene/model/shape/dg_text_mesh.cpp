#include "dg_text_mesh.h"


DGTextMesh::DGTextMesh(void){
	this->text = "Hello World";
	this->color = DGColor::white;
}


DGTextMesh::DGTextMesh(const char *text) {
	this->text = text;
	this->color = DGColor::white;
}

DGTextMesh::DGTextMesh(const char *text, DGColor color){
	this->text = text;
	this->color = color;
}


DGTextMesh::~DGTextMesh(void)
{
}


void DGTextMesh::start() {
	base = glGenLists(256);

	HFONT font = CreateFont(-12,					        // Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Comic Sans MS");				// Font Name

	SelectObject(wglGetCurrentDC(), font);							// Selects The Font We Created

	wglUseFontOutlines(wglGetCurrentDC(),							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						base,							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						gmf);							// Address Of Buffer To Recieve Data
}

void DGTextMesh::update(DGContext* ctx){

}

void DGTextMesh::draw(DGContext* ctx){
	DGuint textLen = strlen(text);

	DGfloat length = 0;
	for (DGuint loop=0; loop<textLen; loop++) {
		length += gmf[text[loop]].gmfCellIncX;			// Increase Length By Each Characters Width
	}

	glTranslatef(-length/2,0.0f,0.0f); // 把字符串居中
	glColor3f(color.r, color.g, color.b); //设置字体颜色

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base);									// Sets The Base Character to 0
	glCallLists(textLen, GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

void DGTextMesh::destroy(){
	glDeleteLists(base, 256);								// Delete All 256 Characters
}