#include <stdio.h>
#include "dg_gui_text.h"

DGGUIText::DGGUIText() {
	base = 0;
}


DGGUIText::~DGGUIText(void)
{
}


void DGGUIText::init(DGScreen* screen){
	this->screen = screen;

	base = 0;

	HFONT	newFont;												// 用以保存新的字体对象
	HFONT	oldFont;												// 用以保存原字体对象

	base = glGenLists(256);											// 存储256个字符

	newFont = CreateFont(-14,									// 字体的高度
							0,										// 字体的宽度
							0,										// 旋转的角度
							0,										// 定位角度
							FW_THIN,								// 字体的粗细
							FALSE,									// 斜体?
							FALSE,									// 下划线?
							FALSE,									// 删除线?
							ANSI_CHARSET,							// 字符集
							OUT_TT_PRECIS,							// 输出精度
							CLIP_DEFAULT_PRECIS,					// 裁减精度
							ANTIALIASED_QUALITY,					// 输出质量
							FF_DONTCARE|DEFAULT_PITCH,				// 间距和字体族
							"Courier New");							// 字体名称

	oldFont = (HFONT)SelectObject(wglGetCurrentDC(), newFont); 		// 选进设备描述表
	wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, base);				// 建立256个字符
	SelectObject(wglGetCurrentDC(), oldFont);							// 恢复设备描述表
	DeleteObject(newFont);											// 删除新字体
}

void DGGUIText::print(GLint x, GLint y, const char *fmt, ...){
	va_list		ap;

	va_start(ap, fmt);												// 遍历字符串，查找变量
	    this->print(x, y, DGColor::white, fmt, ap);
	va_end(ap);
}

void DGGUIText::print(GLint x, GLint y, DGColor color, const char *fmt, ...) {
	char		text[256];											// 用以保存格式化后的字符串
	va_list		ap;													// 指向参数列表的指针

	if (fmt == NULL)												// 没有可输出的字符？
		return;														// 返回

	va_start(ap, fmt);												// 遍历字符串，查找变量
	    vsprintf(text, fmt, ap);									// 将变量转换为显示的数字
	va_end(ap);														// 结果保存在text内

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glOrtho(0, 640, 0, 480, -1, 1);
	glOrtho(0, screen->getWidth(), 0, screen->getHeight(), -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslated(x, y, 0);

	glRasterPos3f(-0.54f, 0.39f, -1.0f);
	glColor3f(color.r, color.g, color.b);

	glPushAttrib(GL_LIST_BIT);										// 显示表状态入栈
	glListBase(base);												// 显示表偏移量
	glCallLists((int)strlen(text), GL_UNSIGNED_BYTE, text);			// 绘制字符串
	glPopAttrib();													// 显示表状态出栈

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void DGGUIText::destroy(){
	glDeleteLists(base, 256);
}

