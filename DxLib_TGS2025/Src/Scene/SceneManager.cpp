#include "SceneManager.h"
#include "SceneType.h"

#include "../System/System.h"

#include "Title/TitleScene.h"
#include "InGame/InGameScene.h"
#include "Result/ResultScene.h"
#include "Help/HelpScene.h"

eSceneType current_scene_type;
int is_end_flag;

void SceneManagerDraw(void);
void ChangeScene(eSceneType new_scene_type);
void SceneInit(eSceneType new_scene_type);

//�V�[���}�l�[�W���[�̏�����
void SceneManagerInitialize(void)
{
	//�p����Ԃɂ���
	is_end_flag = 0;

	//�ŏ��̃V�[���̐ݒ�
	ChangeScene(eTitle);
}

void SceneManagerUpdate(void)
{
	//���̃V�[�������i�[����ϐ�
	eSceneType next_scene_type = eEnd;

	//�V�[���̍X�V
	switch (current_scene_type)
	{
	case eTitle:
		next_scene_type = TitleSceneUpdate();
		break;
	case eInGame:
		next_scene_type = InGameSceneUpdate();
		break;
	case eResult:
		next_scene_type = ResultSceneUpdate();
		break;
	case eHelp:
		next_scene_type = HelpSceneUpdate();
		break;
	case eEnd:
	default:
		break;
	}

	//�V�[���̕`��
	SceneManagerDraw();

	//���݂̃V�[���̃^�C�v�Ǝ��̃V�[���̃^�C�v���ׂ�
	if (current_scene_type != next_scene_type)
	{
		//����Ă�����A�V�[���؂�ւ����s��
		ChangeScene(next_scene_type);
	}
}

int IsFinish(void)
{
	return is_end_flag;
}

void SceneManagerDraw(void)
{
	switch (current_scene_type)
	{
	case eTitle:
		TitleSceneDraw();
		break;
	case eInGame:
		InGameSceneDraw();
		break;
	case eResult:
		ResultSceneDraw();
		break;
	case eHelp:
		HelpSceneDraw();
		break;
	case eEnd:
	default:
		break;
	}
}


void ChangeScene(eSceneType new_scene_type)
{
	//�P�x�������s���Ăق������e
	static int is_once = 1;
	if (is_once == 1)
	{
		is_once = 0;
		SceneInit(new_scene_type);
		return;
	}
	//�`�P�x�������s���Ăق������e


	//�Q��ڈȍ~�̌Ăяo������

	//�G���h��ʂ��Ăяo���ꂽ�烋�[�v�I��
	if (new_scene_type == eEnd)
	{
		is_end_flag = 1;
		return;
	}

	//�e�V�[���̏�����
	SceneInit(new_scene_type);

	//���݂̃V�[���^�C�v�̕ύX
	current_scene_type = new_scene_type;
}

//�e�V�[���̏���������
void SceneInit(eSceneType new_scene_type)
{
	switch (new_scene_type)
	{
	case eTitle:
		TitleSceneInit();
		break;
	case eInGame:
		InGameSceneInit();
		break;
	case eResult:
		ResultSceneInit();
		break;
	case eHelp:
		HelpSceneInit();
		break;
	case eEnd:
	default:
		break;
	}
}
