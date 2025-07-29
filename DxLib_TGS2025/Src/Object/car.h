#pragma once


#include "../Utility/Geometry.h"

enum CarDirection
{
    eUp,
    eDown,
    eRight,
    eLeft,
    eStop,
};

struct Car
{
    Vector2D position;
    Vector2D velocity;
    Vector2D speed;
    Vector2D overcount;
    int animation;
    int image[4];
    int move_image[4];
    int animation_count;

    int ivy_image[4];
    int ivy_anim_left[20];
    int ivy_anim_right[20];
    int ivy_anim_up[20];
    int ivy_anim_down[20];
    bool ivy_flag;
    int ivy_count;
    int ivy_num;
    int ivy_se;

    int boom_right_animtion[6];
    int boom_left_animtion[6];
    int boom_up_animtion[6];
    int boom_down_animtion[6];
    bool boom_flag;
    int boom_count;
    int boom_num;
    int boom_se;

    int lake_right_anim[10];
    int lake_left_anim[10];
    int lake_up_anim[10];
    int lake_down_anim[10];
    bool lake_flag;
    int lake_count;
    int lake_num;
    int lake_se;
    int lake_mul;

    int cutin_image[3];

    int x;
    int y;
    int direction;
    int current_x;
    int current_y;
    int next_x[84];
    int next_y[84];
    int road_count;
    int next_count;
    int old_direction;

    bool start;
    bool goal_flag;
    bool menu_flag;
    
    
    int warn_image[2];
    int warn_se[2];
    bool warn_image_flag;
    int warn_count_max;
    int warn_count;
    int warn_num;
    float warn_range;

    bool mitibiki_flag;

    bool warntutorial_car_flag;
};

struct GameOver
{
    bool image_flag;
    int image;
    int image_count;
    bool flag;
    int circle;
};

void CarInit(void);
void CarManagerUpdate(void);
void CarDraw(void);

const Car* GetCar(void);
const GameOver* GetGameOver(void);

void CarReset(void);

void CarWarnSE(void);
void CarResourceInit(void);