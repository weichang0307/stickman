#include "obj.h"
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
typedef struct _Floor
{
    ALLEGRO_BITMAP* map;
}Floor;

Obj* create_floor(int x, int y,int w,int h);
void floor_draw(Obj *self);
void floor_update(Obj *self,bool *key);
void floor_collide(int overlapx,int overlapy,Obj *self,Obj *collider);