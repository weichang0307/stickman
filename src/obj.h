#ifndef OBJ_H
#define OBJ_H
#include <string.h>
typedef struct _Obj
{
    int x,y;
    int width, height;
    int type;
    void* sub_obj;
    void (*draw)();
    void (*update)();
    void (*collide)();
}Obj;
#endif
