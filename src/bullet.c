
#include "bullet.h"
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>

Obj* create_bullet(int x,int y,int face){
    Bullet* bullet=(Bullet*)malloc(sizeof(Bullet));
    bullet->state=0;
    bullet->velocity=face*10;
    Obj* obj=(Obj*)malloc(sizeof(Obj));
    obj->x=x;
    obj->y=y;
    obj->width=30;
    obj->height=15;
    obj->sub_obj=bullet;
    obj->draw=bullet_draw;
    obj->update=bullet_update;
    obj->collide=bullet_collide;
    obj->type=2;
    return obj;
}

void bullet_draw(Obj *self){
    int x=self->x;
    int y=self->y;
    int w=self->width;
    int h=self->height;
    al_draw_filled_rectangle(x-w/2,y-h/2,x+w/2,y+h/2,al_map_rgb(50,50,100));
}
void bullet_update(Obj *self,bool *key){
    Bullet* bullet=(Bullet*)(self->sub_obj);
    self->x+=bullet->velocity;
    if(self->x<0||self->x>1800){bullet->state=-1;}
    
}
void bullet_collide(int overlapx,int overlapy,Obj *self,Obj *collider){
    Bullet* bullet=(Bullet*)(self->sub_obj);
    bullet->state=1;
};