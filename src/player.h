#include "obj.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
typedef struct _Player
{
    int speed,face;
    double velocity,state;
    int hp,bullet,bomb;
    bool touch_ground;
    ALLEGRO_BITMAP *sticman[7];
}Player;

Obj* create_player(int x, int y);
void player_draw(Obj *self);
void player_update(Obj *self,bool* key);
void player_collide(int overlapx,int overlapy,Obj *self,Obj *collider);
void player_jump(Obj *self);