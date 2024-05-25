#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>

#include "player.h"
#include "floor.h"
#include "header.h"
#include "bullet.h"

#define FPS 60
#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 900

void collision_test(Obj** objs,int obj_count);

int main(int argc, char **argv) {
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    bool key[ALLEGRO_KEY_MAX]={false};
    int count=0;

    Obj* objs[200];
    int obj_count=0;

    Obj* player=create_player(500,500);
    objs[obj_count]=player;
    obj_count++;

    
    objs[obj_count]=create_floor(900,800,1500,30);
    obj_count++;
    objs[obj_count]=create_floor(1200,700,300,50);
    obj_count++;
    

    
    ALLEGRO_DISPLAY *display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    
    al_install_mouse();
    al_install_keyboard();

    ALLEGRO_TIMER* timer=al_create_timer(1.0/FPS);
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    ALLEGRO_EVENT ev;

    ALLEGRO_FONT *font=al_load_font("font/whz.ttf",24,0);
    
    
    al_start_timer(timer);
    bool running = true;
    while (running) {
        al_wait_for_event(event_queue, &ev);
        switch (ev.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running=false;
                break;
            case ALLEGRO_EVENT_TIMER:
                

                al_clear_to_color(al_map_rgb(255,255,0));
                collision_test(objs,obj_count);
                for(int i=0;i<obj_count;i++){
                    if(objs[i]){
                        (objs[i]->update)(objs[i],key);
                        (objs[i]->draw)(objs[i]);
                        if(objs[i]->type==2&&((Bullet*)objs[i]->sub_obj)->state<0){
                            objs[i]=NULL;
                        }
                    }
                }
                al_flip_display();
                count++;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                key[ev.keyboard.keycode] = true;
                if(ev.keyboard.keycode==ALLEGRO_KEY_W){
                    player_jump(player);
                }
                if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE){
                    objs[obj_count]=create_bullet(player->x+((Player*)player->sub_obj)->face*player->width+20,player->y,((Player*)player->sub_obj)->face);
                    obj_count++;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[ev.keyboard.keycode] = false;
                break;
            default:
                break;
        }
    }


    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}


void collision_test(Obj** objs,int obj_count){
    for(int i=0;i<obj_count;i++){
        for(int j=i+1;j<obj_count;j++){
            Obj* A=objs[i];
            Obj* B=objs[j];
            if(A&&B){
                int ax=A->x;
                int ay=A->y;
                int aw=A->width;
                int ah=A->height;
                int bx=B->x;
                int by=B->y;
                int bw=B->width;
                int bh=B->height;
                
                
                int overlapy=(ah/2+bh/2)-abs(ay-by);
                int overlapx=(aw/2+bw/2)-abs(ax-bx);
                if(overlapx>0&&overlapy>0){
                    int signy=(ay-by)/abs(ay-by);
                    int signx=(ax-bx)/abs(ax-bx);
                    A->collide(signx*overlapx,signy*overlapy,A,B);
                    B->collide(-signx*overlapx,-signy*overlapy,B,A);
                }
            }
            
        }
    }
}