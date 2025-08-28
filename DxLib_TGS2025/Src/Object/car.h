#pragma once
#include "../Utility/Geometry.h"

enum Direction
{
    eUp,
    eDown,
    eRight,
    eLeft,
    eStop,
};

struct Car
{
    //Car
    Vector2D position;
    Vector2D velocity;
    Vector2D speed;
    Vector2D overcount;
    int animation;
    int image[4];
    int img_idx;
    int move_image[4];
    int animation_count;

    //Ivy
    int ivy_anim_left[20];
    int ivy_anim_right[20];
    int ivy_anim_up[20];
    int ivy_anim_down[20];
    bool ivy_flag;
    int ivy_count;
    int ivy_num;
    int ivy_se;
    int ivy_eff_img[7];
    int ivy_eff_idx;
    
    //Boom
    int boom_right_animtion[7];
    int boom_left_animtion[7];
    int boom_up_animtion[7];
    int boom_down_animtion[7];
    bool boom_flag;
    int boom_count;
    int boom_num;
    int boom_se;

    //Lake
    int lake_right_anim[10];
    int lake_left_anim[10];
    int lake_up_anim[10];
    int lake_down_anim[10];
    bool lake_flag;
    int lake_count;
    int lake_num;
    int lake_se;
    int lake_mul;

    //Mole
    bool mole_flag;
    int mole_1[4];
    int mole_2[4];
    int mole_3[4];
    int mole_4[4];
    int mole_5[4];

    //Smoke
    int smo_img_R[5];
    int smo_img_L[5];
    int smo_img_U[5];
    int smo_img_D[5];
    int smo_cnt;
    int smo_idx;
    

    int cutin_image[3];

    //CarMove
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
    
    //Warn
    int warn_image[2];
    int warn_se[2];
    bool warn_image_flag;
    int warn_count_max;
    int warn_count;
    int warn_num;
    float warn_range;

    //goal
    int goal_count;
    int jet_num;
    int jet_image[9];
    float jet_angle;
    int jet_num2;
    int jet_image2[2];
    int jet_se;

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

struct CarAnimation
{
    int img[5];
};

void CarInit(void);
void CarManagerUpdate(void);
void CarDraw(void);

const Car* GetCar(void);
const GameOver* GetGameOver(void);

void CarReset(void);

void CarWarnSE(void);
void CarWarnDraw(void);
void CarResourceInit(void);
