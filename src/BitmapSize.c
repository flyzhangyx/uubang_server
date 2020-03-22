#include"../head/SERVER.h"
int BitmapSize(FILE *fp)
{
    int size=0;
    fseek(fp, 0L, SEEK_END );
    size=ftell(fp);
    ftell(fp);
    return size;
}
