#include "DxLib.h"
#include "car.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Object/map.h"
#include"../Object/tool.h"
#include"../Object/Goal.h"
#include "../Utility/PadInputManager.h"

//1マスの大きさ
#define CAR_TROUT_LNEGTH (80.0f)
#define JET_START	(100)
#define JET_DRAW_START	(JET_START-30)

int overroad;
int groundreef_botom;

void CarStart(const InGame* ingame);
void CarDetectPosition(const CreateStage* stage);
void GetNextDestination(const Tool* tool,int x,int y);
void OverRoad(void);
void CarGoalCheck(const CreateStage* stage);
void Play_Sound_Car(int sound, int volume);
void Play_Sound_Car_Loop(int sound, int volume);
void CarMovePosition(const CreateStage*stage, const InGame* ingame);
void GetCarStageNum(const InGame*ingame);
void CarWarnUpdate(const Goal* goal, const GameOver* gameover,const InGame* ingame);

//GameOverでどの演出にするかの分岐
void GameOverBranch(int stg_arr);

void CarIvyAnimation(void);
void CarIvyDraw(int carx, int cary);
void CarLakeAnimation(void);
void CarLakeDraw(int carx, int cary,const InGame*ingame);
void CarBoomAnimation(void);
void CarBoomDraw(int carx, int cary);

void CarMoleAnimation(void);
void CarMoleDraw(float carx, float cary);
void CarWoodMoleDraw(float carx, float cary);

void CarSmokeAnimation(void);
void CarSmokeDraw(int carx, int cary);



void CarJetAnimation(void);
void CarJetDraw(float x, float y, int direction);


void CarJetAnimation2(void);
void CarJetDraw2(float x, float y,int direction);



Car car;
GameOver gameover;
CarAnimation car_anim[5];
void CarInit(void)
{

	overroad = 0;

	car.position.x = car.current_x * CAR_TROUT_LNEGTH + 200.0f;//初期位置
	car.position.y = car.current_y * CAR_TROUT_LNEGTH + 120.0f;
	car.velocity.x = 0.2f;//速度
	car.velocity.y = 0.1f;
	car.velocity.y = 0.1f;
	car.direction = eRight;//進行方向
	car.road_count = 0;//取得する道のカウント
	car.next_count = 0;//取得した道の配列番号
	car.img_idx = 0;

	car.animation_count = 0;
	car.goal_flag = false;//ゴールまで道がつながっているかどうか

	car.ivy_flag = false;//ツタのアニメーションフラグ
	car.ivy_count = 0;//ツタのアニメーションカウント
	car.ivy_num = 0;//ツタのアニメーションナンバー
	car.ivy_eff_idx = 0;

	car.lake_flag = false;//湖の中に落ちるアニメーションフラグ
	car.lake_count = 0;//湖の中に落ちるアニメーションカウント
	car.lake_num = 0;//湖の中に落ちるアニメーションナンバー
	car.lake_mul = 0;//湖の中に落ちるアニメーション**

	car.boom_flag = false;//爆発のアニメーションフラグ
	car.boom_count = 0;//爆発のアニメーションカウント
	car.boom_num = 0;//爆発のアニメーションナンバー

	car.mole_flag = false;// モグラのアニメーションフラグ
	car.woodmole_flag = false;
	car.mole_count = 0;// モグラのアニメーションカウント
	car.mole_num = 0;// モグラのアニメーションナンバー
	car.mole_car_num = 0;
	car.add_carp = 0.0f;
	car.car_angle = 0.0f;

	car.goal_count = 0;		// ゴールに道をつないだら増えるカウント
	car.jet_angle = 0.0f;	// ジェット画像の角度
	car.jet_num = 0;		// 画像番号
	car.jet_num2 = 0;		// 画像番号

	car.overcount.x = 0.0f;
	car.overcount.y = 0.0f;


	gameover.image_flag = false;//GameOverをだすか
	gameover.image_count = 0;//GameOverの画像を出す時間のカウント
	gameover.flag = false;//GameOver後にリセットさせるフラグ


	//画像の読み込み
	
	car.warn_image_flag = false;
	car.warn_count = 0;
	car.warn_count_max = 40;//警告マークを表示する時間
	car.warn_num = 0;


	car.start = false;//車の処理フラグ
	car.menu_flag = false;
	car.mitibiki_flag = false;
	car.warntutorial_car_flag = false;
	
	//ステージ番号と車の初期位置を取得
	GetCarStageNum(GetInGame());
	car.animation = car_anim[eRight].img[0];

	//次の目的地の初期化
	for (int i = 0; i < 84; i++)
	{
		car.next_x[i] = -1;
		car.next_y[i] = -1;
	}
}

void CarResourceInit(void)
{

	car_anim[eRight].img[0] = LoadGraph("Resource/images/car2_right.png");
	car_anim[eRight].img[1] = LoadGraph("Resource/images/car2_right2.png");
	car_anim[eRight].img[2] = LoadGraph("Resource/images/car2_right3.png");
	car_anim[eRight].img[3] = LoadGraph("Resource/images/car2_right4.png");

	car_anim[eLeft].img[0] = LoadGraph("Resource/images/car2_left.png");
	car_anim[eLeft].img[1] = LoadGraph("Resource/images/car2_left2.png");
	car_anim[eLeft].img[2] = LoadGraph("Resource/images/car2_left3.png");
	car_anim[eLeft].img[3] = LoadGraph("Resource/images/car2_left4.png");

	car_anim[eUp].img[0] = LoadGraph("Resource/images/car2_up.png");
	car_anim[eUp].img[1] = LoadGraph("Resource/images/car2_up2.png");

	car_anim[eDown].img[0] = LoadGraph("Resource/images/car2_down.png");
	car_anim[eDown].img[1] = LoadGraph("Resource/images/car2_down2.png");

	car.ivy_eff_img[1] = LoadGraph("Resource/images/put_rock_0.png");
	car.ivy_eff_img[2] = LoadGraph("Resource/images/put_rock_1.png");
	car.ivy_eff_img[3] = LoadGraph("Resource/images/put_rock_2.png");
	car.ivy_eff_img[4] = LoadGraph("Resource/images/put_rock_3.png");
	car.ivy_eff_img[5] = LoadGraph("Resource/images/put_rock_4.png");
	car.ivy_eff_img[6] = LoadGraph("Resource/images/put_rock_5.png");

	// GameOverの食虫植物の画像
	LoadDivGraph("Resource/images/PlantAnim_L.png", 19, 4, 5, 400, 400, car.ivy_anim_left);    // 左
	LoadDivGraph("Resource/images/PlantAnim_R.png", 19, 4, 5, 400, 400, car.ivy_anim_right);   // 右
	LoadDivGraph("Resource/images/PlantAnim_U.png", 19, 4, 5, 400, 400, car.ivy_anim_up);      // 上
	LoadDivGraph("Resource/images/PlantAnim_D.png", 19, 4, 5, 400, 400, car.ivy_anim_down);    // 下

	car.ivy_se = LoadSoundMem("Resource/Sounds/ivy_se.mp3");                                    // 音

	car.lake_right_anim[0] = LoadGraph("Resource/images/car_inR_lake0.png");
	car.lake_right_anim[1] = LoadGraph("Resource/images/car_inR_lake1.png");
	car.lake_right_anim[2] = LoadGraph("Resource/images/car_inR_lake2.png");
	car.lake_right_anim[3] = LoadGraph("Resource/images/car_inR_lake3.png");
	car.lake_right_anim[4] = LoadGraph("Resource/images/car_inR_lake4.png");
	car.lake_right_anim[5] = LoadGraph("Resource/images/car_inR_lake5.png");
	car.lake_right_anim[6] = LoadGraph("Resource/images/car_inR_lake6.png");

	car.lake_left_anim[0] = LoadGraph("Resource/images/car_inL_lake0.png");
	car.lake_left_anim[1] = LoadGraph("Resource/images/car_inL_lake1.png");
	car.lake_left_anim[2] = LoadGraph("Resource/images/car_inL_lake2.png");
	car.lake_left_anim[3] = LoadGraph("Resource/images/car_inL_lake3.png");
	car.lake_left_anim[4] = LoadGraph("Resource/images/car_inL_lake4.png");
	car.lake_left_anim[5] = LoadGraph("Resource/images/car_inL_lake5.png");
	car.lake_left_anim[6] = LoadGraph("Resource/images/car_inL_lake6.png");

	car.lake_up_anim[0] = LoadGraph("Resource/images/car_inU_lake0.png");
	car.lake_up_anim[1] = LoadGraph("Resource/images/car_inU_lake1.png");
	car.lake_up_anim[2] = LoadGraph("Resource/images/car_inU_lake2.png");
	car.lake_up_anim[3] = LoadGraph("Resource/images/car_inU_lake3.png");
	car.lake_up_anim[4] = LoadGraph("Resource/images/car_inU_lake4.png");
	car.lake_up_anim[5] = LoadGraph("Resource/images/car_inU_lake5.png");
	car.lake_up_anim[6] = LoadGraph("Resource/images/car_inU_lake6.png");

	car.lake_down_anim[0] = LoadGraph("Resource/images/car_inD_lake0.png");
	car.lake_down_anim[1] = LoadGraph("Resource/images/car_inD_lake1.png");
	car.lake_down_anim[2] = LoadGraph("Resource/images/car_inD_lake2.png");
	car.lake_down_anim[3] = LoadGraph("Resource/images/car_inD_lake3.png");
	car.lake_down_anim[4] = LoadGraph("Resource/images/car_inD_lake4.png");
	car.lake_down_anim[5] = LoadGraph("Resource/images/car_inD_lake5.png");
	car.lake_down_anim[6] = LoadGraph("Resource/images/car_inD_lake6.png");

	car.boom_right_animtion[0] = LoadGraph("Resource/images/car2_right_boom_base.png");
	car.boom_right_animtion[1] = LoadGraph("Resource/images/car2_right_boom0.png");
	car.boom_right_animtion[2] = LoadGraph("Resource/images/car2_right_boom1.png");
	car.boom_right_animtion[3] = LoadGraph("Resource/images/car2_right_boom2.png");
	car.boom_right_animtion[4] = LoadGraph("Resource/images/fire_car_right_0.png");
	car.boom_right_animtion[5] = LoadGraph("Resource/images/fire_car_right_1.png");
	car.boom_right_animtion[6] = LoadGraph("Resource/images/fire_car_right_2.png");

	car.boom_left_animtion[0] = LoadGraph("Resource/images/car2_left_boom_base.png");
	car.boom_left_animtion[1] = LoadGraph("Resource/images/car2_left_boom0.png");
	car.boom_left_animtion[2] = LoadGraph("Resource/images/car2_left_boom1.png");
	car.boom_left_animtion[3] = LoadGraph("Resource/images/car2_left_boom2.png");
	car.boom_left_animtion[4] = LoadGraph("Resource/images/fire_car2_left0.png");
	car.boom_left_animtion[5] = LoadGraph("Resource/images/fire_car2_left1.png");
	car.boom_left_animtion[6] = LoadGraph("Resource/images/fire_car2_left2.png");

	car.boom_up_animtion[0] = LoadGraph("Resource/images/car2_up_base.png");
	car.boom_up_animtion[1] = LoadGraph("Resource/images/car2_boom_up0.png");
	car.boom_up_animtion[2] = LoadGraph("Resource/images/car2_boom_up1.png");
	car.boom_up_animtion[3] = LoadGraph("Resource/images/car2_boom_up2.png");
	car.boom_up_animtion[4] = LoadGraph("Resource/images/car2_fire_up0.png");
	car.boom_up_animtion[5] = LoadGraph("Resource/images/car2_fire_up1.png");
	car.boom_up_animtion[6] = LoadGraph("Resource/images/car2_fire_up2.png");

	car.boom_down_animtion[0] = LoadGraph("Resource/images/car2_boom_down_base.png");
	car.boom_down_animtion[1] = LoadGraph("Resource/images/car2_boom_down0.png");
	car.boom_down_animtion[2] = LoadGraph("Resource/images/car2_boom_down1.png");
	car.boom_down_animtion[3] = LoadGraph("Resource/images/car2_boom_down2.png");
	car.boom_down_animtion[4] = LoadGraph("Resource/images/car2_fire_down0.png");
	car.boom_down_animtion[5] = LoadGraph("Resource/images/car2_fire_down1.png");
	car.boom_down_animtion[6] = LoadGraph("Resource/images/car2_fire_down2.png");

	// モグラのゲームオーバーアニメーション画像
	LoadDivGraph("Resource/images/GOmole1.png", 5, 5, 1, 100, 100, car.mole_1);
	LoadDivGraph("Resource/images/GOmole2.png", 5, 5, 1, 100, 100, car.mole_2);
	LoadDivGraph("Resource/images/GOmole3.png", 5, 5, 1, 100, 100, car.mole_3);
	LoadDivGraph("Resource/images/GOmole4.png", 5, 5, 1, 100, 100, car.mole_4);
	LoadDivGraph("Resource/images/GOwoodmole1.png", 5, 5, 1, 100, 100, car.woodmole_1);
	LoadDivGraph("Resource/images/GOwoodmole2.png", 5, 5, 1, 100, 100, car.woodmole_2);
	LoadDivGraph("Resource/images/GOwoodmole3.png", 5, 5, 1, 100, 100, car.woodmole_3);
	LoadDivGraph("Resource/images/GOwoodmole4.png", 5, 5, 1, 100, 100, car.woodmole_4);
	LoadDivGraph("Resource/images/GOmole_carR.png", 5, 5, 1, 200, 200, car.mole_carR);
	LoadDivGraph("Resource/images/GOmole_carL.png", 5, 5, 1, 200, 200, car.mole_carL);
	LoadDivGraph("Resource/images/GOmole_carU.png", 5, 5, 1, 200, 200, car.mole_carU);
	LoadDivGraph("Resource/images/GOmole_carD.png", 5, 5, 1, 200, 200, car.mole_carD);

	// 排気ガスの画像
	LoadDivGraph("Resource/images/car_SmokeAnim_L.png", 4, 4, 1, 75, 75, car.smo_img_L);   // 左
	LoadDivGraph("Resource/images/car_SmokeAnim_R.png", 4, 4, 1, 75, 75, car.smo_img_R);   // 右
	LoadDivGraph("Resource/images/car_SmokeAnim_U.png", 4, 4, 1, 75, 75, car.smo_img_U);   // 上
	LoadDivGraph("Resource/images/car_SmokeAnim_D.png", 4, 4, 1, 75, 75, car.smo_img_D);   // 下

	car.warn_image[0] = LoadGraph("Resource/images/Warn_image2.png");
	car.warn_image[1] = LoadGraph("Resource/images/Warn_image.png");
	car.warn_se[0] = LoadSoundMem("Resource/Sounds/Warn3_se.mp3");
	car.warn_se[1] = LoadSoundMem("Resource/Sounds/Warn3_se4.mp3");
	car.lake_se = LoadSoundMem("Resource/Sounds/water1.mp3");

	LoadDivGraph("Resource/images/all_jet.png", 9, 9, 1, 200, 200, car.jet_image);
	car.jet_image2[0] = LoadGraph("Resource/images/speed_up1.png");
	car.jet_image2[1] = LoadGraph("Resource/images/speed_up2.png");
	car.jet_se = LoadSoundMem("Resource/Sounds/jet.mp3");
	ChangeVolumeSoundMem(100, car.jet_se);

	gameover.circle = LoadGraph("Resource/images/car_circle_black.png");
	groundreef_botom = LoadGraph("Resource/images/MapOriginal10_botom.png");
}

void CarManagerUpdate(void)
{
	//車の処理をスタートするフラグ
	CarStart(GetInGame());

	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			//次の進行場所を取得する
			GetNextDestination(Get_Tool(),i,j);

		}
	}
	
	//警告更新
	CarWarnUpdate(GetGoal(), GetGameOver(), GetInGame());
	//処理開始がtrueなら
	if (car.start == true && car.menu_flag == false&&car.mitibiki_flag == false)
	{
		//車の移動処理
		CarGoalCheck(GetStage());
		CarMovePosition(GetStage(),GetInGame());
		CarIvyAnimation();
		CarLakeAnimation();
		CarBoomAnimation();
		CarSmokeAnimation();
		CarJetAnimation();
		CarJetAnimation2();
		CarMoleAnimation();
	}
	else if (car.start == false && car.menu_flag == false && car.mitibiki_flag == false)
	{
		//ステージ切り替えの時リセットする
		CarReset();
	}
}

void CarDraw(void)
{
	//車の描画
	if (car.lake_flag == false && car.ivy_flag == false && car.boom_flag==false&&car.mole_flag==false&&car.woodmole_flag==false)
	{
		CarSmokeDraw(car.position.x, car.position.y);
		if (car.direction == eUp)
		{
			DrawRotaGraph(car.position.x, car.position.y, 0.1, 0.0, car.animation, TRUE);
			CarJetDraw(car.position.x, car.position.y, car.direction);
			CarJetDraw2(car.position.x, car.position.y, car.direction);
		}
		else
		{
			CarJetDraw(car.position.x, car.position.y, car.direction);
			DrawRotaGraph(car.position.x, car.position.y, 0.1, 0.0, car.animation, TRUE);
			CarJetDraw2(car.position.x, car.position.y, car.direction);
		}
	}
	//警告マークの描画
	/*CarWarnDraw();*///インゲームに移動
	CarWarnSE();

	//ツタの描画
	CarIvyDraw(car.position.x, car.position.y);
	CarLakeDraw(car.position.x, car.position.y, GetInGame());
	CarBoomDraw(car.position.x, car.position.y);
	CarMoleDraw(car.position.x, car.position.y);
	CarWoodMoleDraw(car.position.x, car.position.y);
	/*CarSmokeDraw(car.position.x, car.position.y);*/

	/*DrawFormatString(930, 300, GetColor(255, 255, 255), "%d,%d,%d   %d", car.start,car.menu_flag,car.mitibiki_flag,car.goal_count);*/
	/*DrawFormatString(930, 100, GetColor(255, 0, 255), "%d\n%d", car.next_y[car.road_count], car.current_y);*/
	//DrawFormatString(300, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.next_x[car.road_count], car.next_y[car.road_count], car.road_count);
	//DrawFormatString(350, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.next_x[car.next_count], car.next_y[car.next_count], car.next_count);
	/*DrawFormatString(400, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.lake_flag, car.lake_num,car.lake_count);*/
	//DrawFormatString(450, 350, GetColor(255, 255, 255), "%f\n%f\n%f\n%f\n", car.position.x, car.position.y,car.overcount.x,car.overcount.y);
	/*DrawFormatString(200, 350, GetColor(255, 255, 255), "%d %d",car.boom_count,car.boom_flag);*/
}


//車の処理をスタートするフラグ
void CarStart(const InGame* ingame)
{
	if (ingame->start == true && ingame->menu_flag == false && ingame->mitibiki_flag == false)
	{
		car.start = true;
	}
	else if (ingame->start == false && ingame->menu_flag == false && ingame->mitibiki_flag == false)
	{
		car.start = false;
	}
	car.menu_flag = ingame->menu_flag;
	car.mitibiki_flag= ingame->mitibiki_flag;
}

//車の情報を取得
const Car* GetCar(void)
{
	return &car;
}

//ゲームオーバー情報を取得
const GameOver* GetGameOver(void)
{
	return &gameover;
}

//ステージ切り替えするときのリセット
void CarReset(void)
{
	for (int i = 0; i < 84; i++)
	{
		car.next_x[i] = -1;
		car.next_y[i] = -1;
	}
	GetCarStageNum(GetInGame());
	//car.current_x = 2;//ステージ①の初期位置
	//car.current_y = 3;
	car.position.x = car.current_x * CAR_TROUT_LNEGTH + 200.0f;
	car.position.y = car.current_y * CAR_TROUT_LNEGTH + 120.0f;
	car.direction = eRight;
	car.velocity.x = 0.2f;//速度
	car.velocity.y = 0.2f;
	car.road_count = 0;
	car.next_count = 0;
	car.img_idx = 0;// 画像番号
	car.animation_count = 0;

	car.goal_flag = false;//ゴールまで道がつながっているかどうか
	overroad = 0;
	car.start = false;//車の処理フラグ
	car.warntutorial_car_flag = false;
	car.warn_image_flag = false;//警告マークのフラグ
	car.warn_count = 0;//警告マークを表示する時間
	car.warn_count_max = 40;//警告マークを表示する時間
	car.warn_num = 0;
	car.menu_flag == false;//車のメニュー処理フラグ
	car.animation = car_anim[eRight].img[0];
	car.mitibiki_flag = false;
	car.overcount.x = 0.0f;
	car.overcount.y = 0.0f;

	car.ivy_flag = false;
	car.ivy_count = 0;
	car.ivy_num = 0;
	car.ivy_eff_idx = 0;

	car.lake_flag = false;//湖の中に落ちるアニメーションフラグ
	car.lake_count = 0;//湖の中に落ちるアニメーションカウント
	car.lake_num = 0;//湖の中に落ちるアニメーションナンバー

	car.boom_flag = false;//爆発するアニメーションフラグ
	car.boom_count = 0;//爆発するアニメーションカウント
	car.boom_num = 0;//爆発するアニメーションナンバー

	car.mole_flag = false;
	car.woodmole_flag = false;
	car.mole_count = 0;
	car.mole_num = 0;
	car.add_carp = 0.0f;
	car.mole_car_num = 0;
	car.car_angle = 0.0f;

	car.goal_count = 0;		// ゴールに道をつないだら増えるカウント
	car.jet_angle = 0.0f;	// ジェット画像の角度
	car.jet_num = 0;		// 画像番号
	car.jet_num2 = 0;		// 画像番号
	ChangeVolumeSoundMem(100, car.jet_se);		//音量リセット

	car.smo_cnt = 0;
	car.smo_idx = 0;

	gameover.image_flag = false;//GameOverをだすか
	gameover.image_count = 0;//GameOverの画像を出す時間のカウント
	gameover.flag = false;//GameOver後にリセットさせるフラグ

	//仮
	/*DeleteSoundMem(car.lake_se);
	car.lake_se = LoadSoundMem("Resource/Sounds/water1.mp3");*/
	car.goal_count = 0;
}

//次の進行場所を取得する
void GetNextDestination(const Tool* tool, int x, int y)
{
	//道が置かれたときの座標を取得して番号をつける
	//次の移動位置が同じでないなら
	if (tool->road_flag[x][y] == true || tool->wood_road_flag[x][y] == true)
	{
		car.road_count++;
		car.next_x[car.road_count] = x;
		car.next_y[car.road_count] = y;


	}
}


//車の移動処理
void CarMovePosition(const CreateStage* stage, const InGame* ingame)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	//Carアニメーションカウントと画像番号
	car.animation_count++;

	if (car.animation_count > 60)
	{
		car.img_idx = 0;
		car.animation_count = 0;
	}

	switch (car.direction)
	{

	case eStop://止まる
		if (car.goal_flag == false)
		{
			if (overroad < 300)
			{
				OverRoad();
				/*gameover.image_flag = true;*/
			}
			if (overroad > 299)
			{
				gameover.image_count++;
				car.position.x += 0.0f;
				car.position.y += 0.0f;
				gameover.image_flag = true;
				Stop_InGameBgm();
				if (gameover.image_count > 240)
				{
					gameover.flag = true;
					gameover.image_count = 0;
				}
			}
		}
		break;

	case eUp://上に
		if (car.animation_count < 30)
		{
			car.animation = car_anim[eUp].img[0];
		}
		else
		{
			car.animation = car_anim[eUp].img[1];
		}
		if (ingame->stage_num == eOne && car.warntutorial_car_flag == true)
		{
			car.position.y += 0;
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress && car.warn_image_flag == false)
			{
				car.warntutorial_car_flag = false;
			}
		}
		else if ((ingame->stage_num == eOne && car.warntutorial_car_flag == false) || ingame->stage_num != eOne)
		{
			car.position.y -= car.velocity.y;
		}
		if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 120.2f)//微調整で120に0.2足している
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition(GetStage());

		}
		else if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 120.0f + car.warn_range * 0.3 &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 1;
		}
		else if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 120.0f + car.warn_range &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 0;
		}
		break;

	case eDown://下に
		if (car.animation_count < 30)
		{
			car.animation = car_anim[eDown].img[0];
		}
		else
		{
			car.animation = car_anim[eDown].img[1];
		}
		if (ingame->stage_num == eOne && car.warntutorial_car_flag == true)
		{
			car.position.y +=0;
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress && car.warn_image_flag == false)
			{
				car.warntutorial_car_flag = false;
			}
		}
		else if ((ingame->stage_num == eOne && car.warntutorial_car_flag == false) || ingame->stage_num != eOne)
		{
			car.position.y += car.velocity.y;
		}
		
		if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 119.8f)//微調整で120から0.2引いている
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition(GetStage());

		}
		else if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 120.0f - car.warn_range * 0.3 &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 1;
		}
		else if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 120.0f - car.warn_range &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 0;
		}

		break;

	case eRight://右に

		//carのアニメーション切り替え
		car.animation = car_anim[eRight].img[car.img_idx];

		if (ingame->stage_num == eOne && car.warntutorial_car_flag == true)
		{
			car.position.x += 0;
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress&&car.warn_image_flag==false)
			{
				car.warntutorial_car_flag = false;
			}
		}
		else if ((ingame->stage_num == eOne && car.warntutorial_car_flag == false) || ingame->stage_num != eOne)
		{
			car.position.x += car.velocity.x;
		}
		if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 199.8f)//微調整で200から0.2引いている
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition(GetStage());

		}
		else if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 200.0f - car.warn_range * 0.3 &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 1;
		}
		else if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 200.0f - car.warn_range &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 0;
		}
		break;

	case eLeft:
		//carのアニメーション切り替え
		car.animation = car_anim[eLeft].img[car.img_idx];

		if (ingame->stage_num ==eOne &&car.warntutorial_car_flag == true)
		{
			car.position.x -= 0;
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress && car.warn_image_flag == false)
			{
				car.warntutorial_car_flag = false;
			}
		}
		else if ((ingame->stage_num == eOne && car.warntutorial_car_flag == false)|| ingame->stage_num != eOne)
		{
			car.position.x -= car.velocity.x;
		}
		if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) + 200.2f)//微調整で200から0.2足している
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition(GetStage());

		}
		else if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) + 200.0f + car.warn_range * 0.3 &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 1;
		}
		else if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) + 200.0f + car.warn_range &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 0;
		}
		break;

	default:
		break;
	}

	//一番下に置いていないとフレーム飛びしてしまう
	if (car.animation_count != 0 && car.animation_count % 15 == 0)
	{
		car.img_idx++;
	}
}

//車の現在位置を検知して次の進行方向を決める
void CarDetectPosition(const CreateStage* stage)
{
	//現在のX位置よりも次のX位置が大きかったら
	if (car.current_x < car.next_x[car.next_count] &&
		car.current_y == car.next_y[car.next_count])
	{
		if (car.direction != eRight)
		{
			car.position.x += car.overcount.x;
			car.position.y += car.overcount.y;
		}
		car.overcount.x = 0.0f;
		car.overcount.y = 0.0f;
		car.direction = eRight;//右に
		car.old_direction = eRight;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	else if (car.current_x > car.next_x[car.next_count] &&
		car.current_y == car.next_y[car.next_count])
	{
		if (car.direction != eLeft)
		{
			car.position.x += car.overcount.x;
			car.position.y += car.overcount.y;
		}
		car.overcount.x = 0.0f;
		car.overcount.y = 0.0f;
		car.direction = eLeft;//右に
		car.old_direction = eLeft;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;
	}
	//現在のY位置よりも次のY位置が小さかったら
	else if (car.current_y > car.next_y[car.next_count] &&
		car.current_x == car.next_x[car.next_count])
	{
		if (car.direction != eUp)
		{
			car.position.x += car.overcount.x;
			car.position.y += car.overcount.y;
		}
		car.overcount.x = 0.0f;
		car.overcount.y = 0.0f;
		car.direction = eUp;//上に
		car.old_direction = eUp;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	//現在のY位置よりも次のY位置が大きかったら
	else if (car.current_y < car.next_y[car.next_count] &&
		car.current_x == car.next_x[car.next_count])
	{
		if (car.direction != eDown)
		{
			car.position.x += car.overcount.x;
			car.position.y += car.overcount.y;
		}
		car.overcount.x = 0.0f;
		car.overcount.y = 0.0f;
		car.direction = eDown;//下に
		car.old_direction = eDown;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	//次の進行位置がなければストップ
	else
	{
		if (car.goal_flag == false)
		{
			//car.direction = eStop;//ストップ
			switch (car.direction)
			{
			case eUp://上に
				car.overcount.y += car.speed.y;
				if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 90.0f)
				{
					GameOverBranch(stage->array[car.current_x][car.current_y - 1]);
					car.direction = eStop;//ストップ
					car.overcount.y = 0.0f;
				}
				break;
			case eDown://下に
				car.overcount.y -= car.speed.y;
				if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 150.0f)
				{
					GameOverBranch(stage->array[car.current_x][car.current_y + 1]);
					
					car.direction = eStop;//ストップ
					car.overcount.y = 0.0f;
				}
				break;
			case eRight://右に
				car.overcount.x -= car.speed.x;
				if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 230.0f)
				{
					GameOverBranch(stage->array[car.current_x + 1][car.current_y]);
					
					car.direction = eStop;//ストップ
					car.overcount.x = 0.0f;
				}
				break;
			case eLeft://左に
				car.overcount.x += car.speed.x;
				if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) + 170.0f)
				{
					GameOverBranch(stage->array[car.current_x - 1][car.current_y]);
					
					car.direction = eStop;//ストップ
					car.overcount.x = 0.0f;
				}
				break;
			default:
				break;
			}
		}
		else
		{
			car.direction = eStop;//ストップ
			car.overcount.y = 0.0f;
		}
	}
}

//GameOverでどの演出にするかの分岐
void GameOverBranch(int stg_arr) 
{
	switch (stg_arr)
	{
	case 6:
		if (car.next_y[car.road_count] != 0)
		{
			car.lake_flag = true;
		}
		break;
	case 1:case 2:
	case 9: 
		if (car.next_y[car.road_count] != 0)
		{
			car.boom_flag = true;
		}
		break;
	case 3:
		if (car.next_y[car.road_count] != 0)
		{
			car.mole_flag = true;
		}
		break;
	case 10:
		if (car.next_y[car.road_count] != 0)
		{
			car.woodmole_flag = true;
		}
		break;
	default:
		car.ivy_flag = true;
		break;
	}

	if (car.lake_flag != true && car.boom_flag != true&&car.mole_flag!=true&&car.woodmole_flag!=true)
	{
		car.ivy_flag = true;
	}
}

//GameOver時のアニメーション
void OverRoad(void)
{
	switch (car.old_direction)
	{
	case eUp://上に
		/*car.position.y -= 0.1f;*/
		overroad += 2;
		break;
	case eDown://下に
		/*car.position.y += 0.1f;*/
		overroad += 2;
		break;
	case eRight://右に
		/*car.position.x += 0.1f;*/
		overroad += 2;
		break;
	case eLeft:
		/*car.position.x -= 0.1f;*/
		overroad += 2;
		break;

	default:
		break;
	}
}

//ゴールしたのかどうか
void CarGoalCheck(const CreateStage* stage)
{
	//右または上または下にゴールがあるなら
	if (stage->array[car.next_x[car.road_count] + 1][car.next_y[car.road_count]] == 7 && car.next_x[car.road_count] != 11 ||
		stage->array[car.next_x[car.road_count] - 1][car.next_y[car.road_count]] == 7 && car.next_x[car.road_count] != 0 ||
		stage->array[car.next_x[car.road_count]][car.next_y[car.road_count] - 1] == 7 && car.next_y[car.road_count] != 0 ||
		stage->array[car.next_x[car.road_count]][car.next_y[car.road_count] + 1] == 7 && car.next_y[car.road_count] != 6)
	{
		car.goal_count++;
		if (car.goal_count > JET_START + 120)
		{
			//車の速度を上げる
			car.velocity.x = 5.0f;
			car.velocity.y = 5.0f;
		}
		else
		{
			car.velocity.x = 0.0f;
			car.velocity.y = 0.0f;
		}

		//ゴールの配列番号を一番先端に入れる
		car.next_x[car.road_count + 1] = stage->goal_x[0];
		car.next_y[car.road_count + 1] = stage->goal_y[0];

		//ゴールまで道がつながったかどうか
		car.goal_flag = true;
	}
	else
	{
		//ゴール以外の時の速度
		car.velocity.x = car.speed.x;
		car.velocity.y = car.speed.y;
	}

}

//警告音
void CarWarnSE(void) 
{
	if (car.warn_image_flag == true && car.next_x[car.next_count] == -1 && car.next_y[car.next_count] == -1)
	{
		switch (car.warn_num)
		{
		case 0:
			if (CheckSoundMem(car.warn_se[0]) == 0 && CheckSoundMem(car.warn_se[1]) == 0)
			{
				Play_Sound_Car(car.warn_se[0], 100);
			}
			break;
		case 1:
			if (CheckSoundMem(car.warn_se[0]) == 0 && CheckSoundMem(car.warn_se[1]) == 0)
			{
				Play_Sound_Car(car.warn_se[1], 100);
			}
			break;
		}
		
	}
	else if(car.warn_image_flag == false)
	{
		StopSoundMem(car.warn_se[0]);
		StopSoundMem(car.warn_se[1]);
	}
}

//SE用
void Play_Sound_Car(int sound, int volume)
{
	if (CheckSoundMem(sound) == 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(volume, sound);
	}

}
//ループするSE用
void Play_Sound_Car_Loop(int sound, int volume)
{
	//TRUEだとバック再生
	PlaySoundMem(sound, DX_PLAYTYPE_LOOP, TRUE);
	ChangeVolumeSoundMem(volume, sound);
}

//警告アップデート
void CarWarnUpdate(const Goal*goal,const GameOver*gameover,const InGame*ingame)
{
	//警告マークの点滅速度を変える
	switch (car.warn_num)
	{
	case 0:
		car.warn_count_max = 40;
		break;
	case 1:
		car.warn_count_max = 20;
		break;
	}

	if (car.next_x[car.next_count] != -1 && car.next_y[car.next_count] != -1||
		goal->print_flag == true || gameover->image_flag == true ||ingame->menu_flag==true||car.direction==eStop)
	{
		car.warn_image_flag = false;
		car.warn_count = 0;
	}
}

//警告マークの描画
 void CarWarnDraw(void)
{
	 if (car.warn_image_flag == true && car.next_x[car.next_count] == -1 && car.next_y[car.next_count] == -1)
	 {
		 car.warn_count++;
		 if (car.warn_count % car.warn_count_max< car.warn_count_max / 2)
		 {
			 switch (car.direction)
			 {
			 case eUp: case eDown:
				 DrawRotaGraphF(car.position.x - 80.0f, car.position.y, 1.0, 0.0, car.warn_image[car.warn_num], TRUE);
				 car.warntutorial_car_flag = true;
				 break;
			 case eRight: case eLeft:
				 DrawRotaGraphF(car.position.x, car.position.y - 80.0f, 1.0, 0.0, car.warn_image[car.warn_num], TRUE);
				 car.warntutorial_car_flag = true;
				 break;
			 }
			 //car.warntutorial_car_flag = false;
		 }
	 }
	
}

 //GameOverの植物アニメーション
 void CarIvyAnimation(void)
 {
	 if (car.ivy_flag == true)
	 {
		 car.ivy_count++;
		 if (car.ivy_count > 20&&car.ivy_count % 3 == 0 && car.ivy_num < 18)
		 {
			 car.ivy_num++;
		 }

		 if (car.ivy_count > 20 && car.ivy_count % 7 == 0 && car.ivy_eff_idx < 7)
		 {
			 car.ivy_eff_idx++;
		 }

		 if (car.start == false)
		 {
			 car.ivy_flag = false;
			 car.ivy_count = 0;
			 car.ivy_num = 0;
		 }
	 }
 }

 //植物の描画
 void CarIvyDraw(int carx, int cary)
 {
	 if (car.ivy_flag == true)
	 {
		 switch (car.old_direction)
		 {
		 case eUp:
			 DrawRotaGraphF(carx + 18, cary - 50, 1.7, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx + 18, cary - 55, 0.4, 0.0, car.ivy_anim_up[car.ivy_num], TRUE);
			 DrawRotaGraphF(carx + 40, cary - 75, 1.8, 0.0, car.ivy_eff_img[car.ivy_eff_idx], TRUE);
			 if (car.ivy_num < 18)
			 {
				 DrawRotaGraphF(carx + 18, cary - 55, 0.4, 0.0, car.ivy_anim_up[0], TRUE);
			 }
			 break;
		 case eDown:
			 DrawRotaGraphF(carx - 18, cary + 50, 1.7, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx - 18, cary + 30, 0.4, 0.0, car.ivy_anim_down[car.ivy_num], TRUE);
			 DrawRotaGraphF(carx - 40, cary + 35, 1.8, 0.0, car.ivy_eff_img[car.ivy_eff_idx], TRUE);
			 break;
		 case eRight:
			 DrawRotaGraphF(carx + 22, cary - 25, 1.7, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx + 14, cary - 44, 0.4, 0.0, car.ivy_anim_right[car.ivy_num], TRUE);
			 DrawRotaGraphF(carx + 50, cary - 44, 1.8, 0.0, car.ivy_eff_img[car.ivy_eff_idx], TRUE);
			 if (car.ivy_num < 18)
			 {
				 DrawRotaGraphF(carx + 14, cary - 44, 0.4, 0.0, car.ivy_anim_right[0], TRUE);
			 }
			 break;
		 case eLeft:
			 DrawRotaGraphF(carx - 22, cary - 25, 1.7, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx - 14, cary - 44, 0.4, 0.0, car.ivy_anim_left[car.ivy_num], TRUE);
			 DrawRotaGraphF(carx - 50, cary - 44, 1.8, 0.0, car.ivy_eff_img[car.ivy_eff_idx], TRUE);
			 if (car.ivy_num < 18)
			 {
				 DrawRotaGraphF(carx - 14, cary - 44, 0.4, 0.0, car.ivy_anim_left[0], TRUE);
			 }
			 break;
		 }
		 /* DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
		  DrawRotaGraphF(carx - 14, cary - 44, 0.4, 0.0, car.ivy_animation[car.ivy_num], TRUE);*/
		 if (car.ivy_count < 60)
		 {
			 Play_Sound_Car(car.ivy_se, 150);
		 }
	 }
	 else if (car.ivy_flag == false)
	 {
		 StopSoundMem(car.ivy_se);
	 }
	 DrawRotaGraphF(640, 360, 1.0, 0.0, groundreef_botom, TRUE);
 }

 //GameOverの池に落ちるアニメーション
 void CarLakeAnimation(void)
 {
	 if (car.lake_flag == true)
	 {
		 car.lake_count++;
		 if (car.lake_count > 30 && car.lake_count % 8 == 0 && car.lake_num < 6)
		 {
			 car.lake_num++;
			 
		 }

		 if (car.start == false)
		 {
			 car.lake_flag = false;
			 car.lake_count = 0;
			 car.lake_num = 0;
		 }
	 }
 }

 //池に落ちる描画
 void CarLakeDraw(int carx, int cary,const InGame*ingame)
 {
	 if (car.lake_flag == true)
	 {
		 switch (car.old_direction)
		 {
		 case eUp:
			 DrawRotaGraphF(carx, cary - car.lake_num * 8 - 5, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary - car.lake_num * 8 - 5, 0.1, 0.0, car.lake_up_anim[car.lake_num], TRUE);
			 break;
		 case eDown:
			 DrawRotaGraphF(carx, cary + car.lake_num * 2 + 10, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary + car.lake_num * 2 + 5, 0.1, 0.0, car.lake_down_anim[car.lake_num], TRUE);
			 break;
		 case eRight:
			 DrawRotaGraphF(carx + car.lake_num * 8, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx + car.lake_num * 8, cary, 0.1, 0.0, car.lake_right_anim[car.lake_num], TRUE);
			 break;
		 case eLeft:
			 DrawRotaGraphF(carx - car.lake_num * 8, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx - car.lake_num * 8, cary, 0.1, 0.0, car.lake_left_anim[car.lake_num], TRUE);
			 break;
		 }
		 /*if (car.lake_count > 40 && car.lake_count < 170 && ingame->menu_flag == false)
		 {
			 PlaySoundMem(car.lake_se, DX_PLAYTYPE_BACK, FALSE);
		 }
		 else if (car.lake_count >= 170)
		 {
			 StopSoundMem(car.lake_se);
		 }
		 
		 if (CheckSoundMem(car.lake_se)==1&&car.menu_flag == true)
			 {
				 StopSoundMem(car.lake_se);
			 }*/

		 if (car.lake_count > 40 && car.lake_count < 50)
		 {
			 Play_Sound_Car(car.lake_se, 200);
		 }
	 }
	 else if (car.lake_flag == false)
	 {
		 StopSoundMem(car.lake_se);
	 }
 }

 //爆発アニメーション
 void CarBoomAnimation(void)
 {
	 if (car.boom_flag == true)
	 {
		 car.boom_count++;
		 if (car.boom_count > 30 && car.boom_count % 10 == 0 && car.boom_num < 6)
		 {
			 car.boom_num++;
		 }
		 if (car.boom_num == 6)
		 {
			 car.boom_num = 4;
		 }
		 if (car.start == false)
		 {
			 car.boom_flag = false;
			 car.boom_count = 0;
			 car.boom_num = 0;
		 }
	 }
 }

 //爆発の描画
 void CarBoomDraw(int carx,int cary)
 {
	 if (car.boom_flag == true)
	 {
		 switch (car.old_direction)
		 {
		 case eRight:
			 DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary, 0.111, 0.0, car.boom_right_animtion[car.boom_num], TRUE);
			 break;
		 case eLeft:
			 DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary, 0.113, 0.0, car.boom_left_animtion[car.boom_num], TRUE);
			 break;
		 case eUp:
			 DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary, 0.128, 0.0, car.boom_up_animtion[car.boom_num], TRUE);
			 break;
		 case eDown:
			 DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary, 0.12, 0.0, car.boom_down_animtion[car.boom_num], TRUE);
			 break;
		 }
		 //if (car.boom_count > 30)
		 //{
			 //if (car.boom_count < 60)
			 //{
				// Play_Sound_Car(car.boom_se, 150);
			 //}
		 //}
	 }
 }

 // モグラ演出のアニメーション
 void CarMoleAnimation(void)
 {
	 if (car.mole_flag == true||car.woodmole_flag==true)
	 {
		 car.mole_count++;
		 // モグラが潜る画像の切り替え
		 if (car.mole_count > 9 && car.mole_count % 5 == 0 && car.mole_num < 4)
		 {
			 car.mole_num++;
		 }

		 // 車
		 if (car.mole_count < 60)
		 {
			 car.add_carp = (float)car.mole_count;		// 車を少し移動
		 }
		 else if (car.mole_count > 100 && car.mole_count % 2 == 0 && car.mole_car_num < 4)
		 {
			 car.mole_car_num++;		// 車の画像切り替え
		 }

		 // 車の角度
		 if (car.mole_count > 70 && car.mole_count < 100)
		 {
			 if (car.mole_count % 6 == 0)
			 {
				 car.car_angle = 10.0f * 3.14f / 180.0f;
			 }
			 else if (car.mole_count % 3 == 0)
			 {
				 car.car_angle = -10.0f * 3.14f / 180.0f;
			 }
		 }
		 else
		 {
			 car.car_angle = 0.0f;
		 }
	 }
 }

 // モグラ演出の描画
 void CarMoleDraw(float carx, float cary)
 {
	 if (car.mole_flag == true)
	 {
		 switch (car.old_direction)
		 {
		 case eRight:
			 DrawRotaGraphF(carx + 50.0f, cary, 1.0, 0.0, car.mole_3[car.mole_num], TRUE);											// モグラ
			 DrawRotaGraphF(carx + car.add_carp * 0.8f, cary, 1.0, 0.0, gameover.circle, TRUE);										// ライト
			 DrawRotaGraphF(carx + car.add_carp * 0.8f, cary, 0.4, (double)car.car_angle, car.mole_carR[car.mole_car_num], TRUE);	// 車
			 break;
		 case eLeft:
			 DrawRotaGraphF(carx - 50.0f, cary, 1.0, 0.0, car.mole_4[car.mole_num], TRUE);
			 DrawRotaGraphF(carx - car.add_carp * 0.8f, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx - car.add_carp * 0.8f, cary, 0.4, (double)car.car_angle, car.mole_carL[car.mole_car_num], TRUE);
			 break;
		 case eUp:
			 DrawRotaGraphF(carx, cary - 50.0f, 1.0, 0.0, car.mole_1[car.mole_num], TRUE);
			 DrawRotaGraphF(carx, cary - car.add_carp * 0.8f, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary - car.add_carp * 0.8f, 0.4, (double)car.car_angle, car.mole_carU[car.mole_car_num], TRUE);
			 break;
		 case eDown:
			 if (car.mole_num < 4)
			 {
				 DrawRotaGraphF(carx, cary + car.add_carp * 0.8f, 1.0, 0.0, gameover.circle, TRUE);
				 DrawRotaGraphF(carx, cary + car.add_carp * 0.8f, 0.4, (double)car.car_angle, car.mole_carD[car.mole_car_num], TRUE);
				 DrawRotaGraphF(carx, cary + 50.0f, 1.0, 0.0, car.mole_2[car.mole_num], TRUE);
			 }
			 else
			 {
				 DrawRotaGraphF(carx, cary + 50.0f, 1.0, 0.0, car.mole_2[car.mole_num], TRUE);
				 DrawRotaGraphF(carx, cary + car.add_carp * 0.8f, 1.0, 0.0, gameover.circle, TRUE);
				 DrawRotaGraphF(carx, cary + car.add_carp * 0.8f, 0.4, (double)car.car_angle, car.mole_carD[car.mole_car_num], TRUE);
			 }
			 break;
		 }
	 }
 }

 void CarWoodMoleDraw(float carx, float cary)
 {
	 if (car.woodmole_flag == true)
	 {
		 switch (car.old_direction)
		 {
		 case eRight:
			 DrawRotaGraphF(carx + 50.0f, cary, 1.0, 0.0, car.woodmole_3[car.mole_num], TRUE);											// モグラ
			 DrawRotaGraphF(carx + car.add_carp * 0.8f, cary, 1.0, 0.0, gameover.circle, TRUE);										// ライト
			 DrawRotaGraphF(carx + car.add_carp * 0.8f, cary, 0.4, (double)car.car_angle, car.mole_carR[car.mole_car_num], TRUE);	// 車
			 break;
		 case eLeft:
			 DrawRotaGraphF(carx - 50.0f, cary, 1.0, 0.0, car.woodmole_4[car.mole_num], TRUE);
			 DrawRotaGraphF(carx - car.add_carp * 0.8f, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx - car.add_carp * 0.8f, cary, 0.4, (double)car.car_angle, car.mole_carL[car.mole_car_num], TRUE);
			 break;
		 case eUp:
			 DrawRotaGraphF(carx, cary - 50.0f, 1.0, 0.0, car.woodmole_1[car.mole_num], TRUE);
			 DrawRotaGraphF(carx, cary - car.add_carp * 0.8f, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary - car.add_carp * 0.8f, 0.4, (double)car.car_angle, car.mole_carU[car.mole_car_num], TRUE);
			 break;
		 case eDown:
			 if (car.mole_num < 4)
			 {
				 DrawRotaGraphF(carx, cary + car.add_carp * 0.8f, 1.0, 0.0, gameover.circle, TRUE);
				 DrawRotaGraphF(carx, cary + car.add_carp * 0.8f, 0.4, (double)car.car_angle, car.mole_carD[car.mole_car_num], TRUE);
				 DrawRotaGraphF(carx, cary + 50.0f, 1.0, 0.0, car.woodmole_2[car.mole_num], TRUE);
			 }
			 else
			 {
				 DrawRotaGraphF(carx, cary + 50.0f, 1.0, 0.0, car.woodmole_2[car.mole_num], TRUE);
				 DrawRotaGraphF(carx, cary + car.add_carp * 0.8f, 1.0, 0.0, gameover.circle, TRUE);
				 DrawRotaGraphF(carx, cary + car.add_carp * 0.8f, 0.4, (double)car.car_angle, car.mole_carD[car.mole_car_num], TRUE);
			 }
			 break;
		 }
	 }
 }

 //車からでる排気ガスのアニメーション
 void CarSmokeAnimation(void)
 {
	 car.smo_cnt++;
	 if (car.smo_cnt != 0 && car.smo_cnt % 20 == 0)
	 {
		 car.smo_idx++;
	 }
	 
	 if (car.smo_cnt > 71)
	 {
		 car.smo_cnt = 0;
		 car.smo_idx = 0;
	 }
 }

 //排気ガスの描画
 void CarSmokeDraw(int carx, int cary)
 {
	 if (car.goal_flag == false)
	 {
		 switch (car.direction)
		 {
		 case eRight:
			 DrawRotaGraphF(carx - 80, cary, 1.0, 0.0, car.smo_img_R[car.smo_idx], TRUE);
			 break;
		 case eLeft:
			 DrawRotaGraphF(carx + 80, cary, 1.0, 0.0, car.smo_img_L[car.smo_idx], TRUE);
			 break;
		 case eUp:
			 DrawRotaGraphF(carx-10 , cary+ 60, 1.0, 0.0, car.smo_img_U[car.smo_idx], TRUE);
			 break;
		 case eDown:
			 DrawRotaGraphF(carx + 10, cary - 60, 1.0, 0.0, car.smo_img_D[car.smo_idx], TRUE);
			 break;
		 default:
			 break;
		 }
		 
	 }
 }

 // ジェットアニメーション2
 void CarJetAnimation2(void)
 {
	 if (car.goal_flag == true)
	 {
		 int num;
		 
		 num = car.goal_count / 10;
		 car.jet_num2 = num%2;
	 }
 }

 // ジェット描画2
 void CarJetDraw2(float x,float y,int direction)
 {
	 if (car.goal_flag == true)
	 {
		 if(car.goal_count>= JET_START + 120)
		 switch (direction)
		 {
		 case eUp:
			 if (car.jet_num2 == 0)
			 {
				 DrawRotaGraph(car.position.x, car.position.y, 0.5, -1.57, car.jet_image2[car.jet_num2], TRUE);
			 }
			 else
			 {
				 DrawRotaGraph(car.position.x, car.position.y, 0.25, -1.57, car.jet_image2[car.jet_num2], TRUE);
			 }
			 break;

		 case eDown:
			 if (car.jet_num2 == 0)
			 {
				 DrawRotaGraph(car.position.x, car.position.y, 0.5, 1.57, car.jet_image2[car.jet_num2], TRUE);
			 }
			 else
			 {
				 DrawRotaGraph(car.position.x, car.position.y, 0.25, 1.57, car.jet_image2[car.jet_num2], TRUE);
			 }
			 break;

		 case eRight:
			 if (car.jet_num2 == 0)
			 {
				 DrawRotaGraph(car.position.x, car.position.y, 0.5, 0.0, car.jet_image2[car.jet_num2], TRUE);
			 }
			 else
			 {
				 DrawRotaGraph(car.position.x, car.position.y, 0.25, 0.0, car.jet_image2[car.jet_num2], TRUE);
			 }
			 break;

		 case eLeft:
			 if (car.jet_num2 == 0)
			 {
				 DrawRotaGraph(car.position.x, car.position.y, 0.5, 3.14, car.jet_image2[car.jet_num2], TRUE);
			 }
			 else
			 {
				 DrawRotaGraph(car.position.x, car.position.y, 0.25, 3.14, car.jet_image2[car.jet_num2], TRUE);
			 }
			 break;

		 default:
			 break;
		 }
	 }
 }

 // ジェットアニメーション
 void CarJetAnimation(void)
 {
	 if (car.goal_flag)
	 {
		 car.jet_angle = (3.14 / 180) * car.goal_count;
	 }

	 if (car.goal_count < JET_START)
	 {
		 car.jet_num = 0;
	 }
	 else if (car.goal_count < JET_START+30)
	 {
		 car.jet_num = 1;
	 }
	 else if (car.goal_count < JET_START+120)
	 {
		 car.jet_num = 2;
	 }
	 else if (car.goal_count < JET_START+140)
	 {
		 car.jet_num = 4;
	 }
	 else if (car.goal_count < JET_START+150)
	 {
		 car.jet_num = 6;
	 }
	 else if (car.goal_count < JET_START+160)
	 {
		 car.jet_num = 7;
	 }
	 else if (car.goal_count < JET_START+180)
	 {
		 car.jet_num = 8;
	 }
 }

 // ジェット描画
 void CarJetDraw(float x, float y, int direction)
 {
	 if (car.goal_flag)
	 {
		 switch (direction)
		 {
		 case eUp:
			 if (car.goal_count < JET_START+120&&car.goal_count>JET_DRAW_START)
			 {
				 DrawRotaGraph(x, y + 10.0f, 1.0, car.jet_angle, car.jet_image[car.jet_num], TRUE);
			 }
			 else if (car.goal_count < JET_START + 180 && car.goal_count>JET_DRAW_START)
			 {
				 DrawRotaGraph(x, y + 70.0f, 1.0, -1.57, car.jet_image[car.jet_num], TRUE);
			 }
			 break;
		 case eDown:
			 if (car.goal_count < JET_START + 120 && car.goal_count>JET_DRAW_START)
			 {
				 DrawRotaGraph(x, y - 10.0f, 1.0, car.jet_angle, car.jet_image[car.jet_num], TRUE);
			 }
			 else if (car.goal_count < JET_START + 180 && car.goal_count>JET_DRAW_START)
			 {
				 DrawRotaGraph(x, y - 70.0f, 1.0, 1.57, car.jet_image[car.jet_num], TRUE);
			 }
			 break;
		 case eRight:
			 if (car.goal_count < JET_START + 120 && car.goal_count>JET_DRAW_START)
			 {
				 DrawRotaGraph(x - 50.0f, y + 10.0f, 1.0, car.jet_angle, car.jet_image[car.jet_num], TRUE);
			 }
			 else if (car.goal_count < JET_START + 180 && car.goal_count>JET_DRAW_START)
			 {
				 DrawRotaGraph(x - 100.0f, y + 10.0f, 1.0, 0.0, car.jet_image[car.jet_num], TRUE);
			 }
			 break;
		 case eLeft:
			 if (car.goal_count < JET_START + 120 && car.goal_count>JET_DRAW_START)
			 {
				 DrawRotaGraph(x + 50.0f, y + 10.0f, 1.0, car.jet_angle, car.jet_image[car.jet_num], TRUE);
			 }
			 else if (car.goal_count < JET_START + 180 && car.goal_count>JET_DRAW_START)
			 {
				 DrawRotaGraph(x + 100.0f, y + 10.0f, 1.0, 3.14, car.jet_image[car.jet_num], TRUE);
			 }
			 break;
		 default:
			 break;
		 }
	 }

	 if (car.goal_count > JET_START-20&& car.goal_count <200)
	 {
		 if (CheckSoundMem(car.jet_se) == 0)
		 {
			 PlaySoundMem(car.jet_se, DX_PLAYTYPE_BACK);
		 }
		 if (car.goal_count > 150)
		 {
			 int add = (car.goal_count-150)*2;
			 if (add+100 > 255)
			 {
				 add = 155;
			 }
			 ChangeVolumeSoundMem(100+add, car.jet_se);
		 }
	 }
 }

//ステージ番号と車の初期位置を取得
void GetCarStageNum(const InGame* ingame)
{
	//ステージごとの初期位置
	switch (ingame->stage_num)
	{
	case eOne:
		car.current_x = 1;//ステージ①の初期位置
		car.current_y = 4;
		car.speed.x = 0.05f;
		car.speed.y = 0.05f;
		car.next_x[0] = 3;
		car.next_y[0] = 4;
		car.warn_range = 20.0f;
		break;
	case eTwo:
		car.current_x = 1;//ステージ②の初期位置
		car.current_y = 3;
		car.speed.x = 0.1f;
		car.speed.y = 0.1f;
		car.next_x[0] = 3;
		car.next_y[0] = 3;
		car.warn_range = 20.0f;
		break;
	case eThree:
		car.current_x = 1;//ステージ③の初期位置
		car.current_y = 3;
		car.speed.x = 0.1f;
		car.speed.y = 0.1f;
		car.next_x[0] = 3;
		car.next_y[0] = 3;
		car.warn_range = 20.0f;
		break;
	case eFour:
		car.current_x = 0;//ステージ④の初期位置
		car.current_y = 0;
		car.speed.x = 0.2f;
		car.speed.y = 0.2f;
		car.next_x[0] = 2;
		car.next_y[0] = 0;
		car.warn_range = 40.0f;
		break;
	case eFive:
		car.current_x = 1;//ステージ⑤の初期位置
		car.current_y = 3;
		car.speed.x = 0.25f;
		car.speed.y = 0.25f;
		car.next_x[0] = 3;
		car.next_y[0] = 3;
		car.warn_range = 50.0f;
		break;
	case eSix:
		car.current_x = 0;//ステージ⑥の初期位置
		car.current_y = 6;
		car.speed.x = 0.3f;
		car.speed.y = 0.3f;
		car.next_x[0] = 2;
		car.next_y[0] = 6;
		car.warn_range = 60.0f;
		break;
	}
}