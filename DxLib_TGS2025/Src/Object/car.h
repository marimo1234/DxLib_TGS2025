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
    int animation;
    int image[4];
    int move_image[4];
    int animation_count;

    int ivy_image[4];
    int ivy_animation[7];
    bool ivy_flag;
    int ivy_count;
    int ivy_num;
    int ivy_se;


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