#ifndef CURSOR_H_
#define CURSOR_H_
typedef struct Cursor
{

	int x;
	int width;
	int height;

} Cursor;
#endif

void initCursor(Cursor* cursor, int MAXWIDTH);
