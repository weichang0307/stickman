#include "obj.h"
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
typedef struct _Bullet
{
    int state,velocity;
}Bullet;

Obj* create_bullet(int x, int y,int face);
void bullet_draw(Obj *self);
void bullet_update(Obj *self,bool *key);
void bullet_collide(int overlapx,int overlapy,Obj *self,Obj *collider);