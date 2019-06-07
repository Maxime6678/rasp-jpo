#include "header/cursor.h"
#include <stdlib.h>

void initCursor(Cursor* cursor, int MAXWIDTH){
  cursor->x = MAXWIDTH/2;
  cursor->width = 16;
  cursor->height = 2;
}
