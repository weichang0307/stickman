#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <math.h>

#include "player.h"



Obj* create_player(int x,int y){
    Player* player=(Player*)malloc(sizeof(Player));
    player->speed=2;
    player->bomb=2;
    player->bullet=10;
    player->velocity=0;
    player->face=1;
    player->touch_ground=false;
    player->sticman[0]=al_load_bitmap("img/stickman/stickman01.png");
    player->sticman[1]=al_load_bitmap("img/stickman/stickman02.png");
    player->sticman[2]=al_load_bitmap("img/stickman/stickman03.png");
    player->sticman[3]=al_load_bitmap("img/stickman/stickman04.png");
    player->sticman[6]=al_load_bitmap("img/stickman/stickman01.png");
    player->sticman[5]=al_load_bitmap("img/stickman/stickman02.png");
    player->sticman[4]=al_load_bitmap("img/stickman/stickman03.png");
    player->state=0;
    Obj* obj=(Obj*)malloc(sizeof(Obj));
    obj->x=x;
    obj->y=y;
    obj->width=80;
    obj->height=150;
    obj->sub_obj=player;
    obj->draw=player_draw;
    obj->update=player_update;
    obj->collide=player_collide;
    obj->type=0;

    return obj;
}
void player_draw(Obj *self){
    Player *player=(Player*)(self->sub_obj);
    int x=self->x;
    int y=self->y;
    int w=self->width;
    int h=self->height;
    //al_draw_filled_rectangle(x-w/2,y-h/2,x+w/2,y+h/2,al_map_rgb(100,100,0));
    int ii=(int)player->state%7;
    al_draw_scaled_bitmap(player->sticman[ii],0,0,al_get_bitmap_width(player->sticman[ii]),al_get_bitmap_height(player->sticman[ii]),x-w/2*player->face,y-h/2+abs(ii-4)*3,player->face*w,h,0);

}
void player_update(Obj *self,bool *key){
    Player *player=(Player*)(self->sub_obj);
    if(key[ALLEGRO_KEY_D]){
        self->x+=player->speed;
        player->face=1;
        player->state+=0.2;
    }else if(key[ALLEGRO_KEY_A]){
        self->x-=player->speed;
        player->face=-1;
        player->state+=0.2;
    }else{
        player->state=1;
    }
    player->velocity+=0.3;
    self->y+=player->velocity;

}
void player_collide(int overlapx,int overlapy,Obj *self,Obj *collider){
    Player *player=(Player*)(self->sub_obj);
    double ratio=0;
    switch (collider->type)
    {
        case 1:
            ratio=1;
            if(abs(overlapx)>abs(overlapy)){
                if(overlapy*player->velocity<0){
                    player->velocity=0;
                }
                if(overlapy<0){
                    player->touch_ground=true;
                }else{
                    
                }
            }
            break;
        default:
            break;
    }
    if(abs(overlapx)>abs(overlapy)){
        self->y+=overlapy*ratio;
    }
    if(abs(overlapx)<abs(overlapy)){
        self->x+=overlapx*ratio;
    }
    
}

void player_jump(Obj* self){
    Player *player=(Player*)(self->sub_obj);
    if(player->touch_ground){
        player->velocity=-10;
        player->touch_ground=false;
    }
}