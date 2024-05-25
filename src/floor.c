#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "floor.h"


Obj* create_floor(int x,int y,int w,int h){
    Floor* floor=(Floor*)malloc(sizeof(Floor));
    floor->map=al_load_bitmap("img/projectile.png");
    Obj* obj=(Obj*)malloc(sizeof(Obj));
    obj->x=x;
    obj->y=y;
    obj->width=w;
    obj->height=h;
    obj->sub_obj=floor;
    obj->draw=floor_draw;
    obj->update=floor_update;
    obj->collide=floor_collide;
    obj->type=1;
    return obj;
}

void floor_draw(Obj *self){
    Floor *floor=(Floor*)(self->sub_obj);
    int x=self->x;
    int y=self->y;
    int w=self->width;
    int h=self->height;
    //al_draw_bitmap(floor->map,x,y,0);
    al_draw_filled_rectangle(x-w/2,y-h/2,x+w/2,y+h/2,al_map_rgb(100,150,100));
}
void floor_update(Obj *self,bool *key){

}
void floor_collide(int overlapx,int overlapy,Obj *self,Obj *collider){

};