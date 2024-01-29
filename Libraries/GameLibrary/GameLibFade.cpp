/*
	�t�F�[�h�Ǘ�
*/
#include "../../Game/GameMain.h"

// �t�F�[�h�̊���
float g_fadeRate = 0.0f;

// �t�F�[�h�̏I���t���O
bool g_fadeEnd = false;

/*---------------------------------------------------
�t�F�[�h�C���i��ʂ������Ă���j�̍X�V
�߂�l	�F	�t�F�[�h�����ǂ���
---------------------------------------------------*/
bool FadeInUpdate(float time)
{
	float deltaTime = GetFrameDeltaTime();

	g_fadeRate -= deltaTime / time;

	if (g_fadeRate < 0.0f || g_fadeEnd == true)
	{
		g_fadeRate = 0.0f;

		g_fadeEnd = false;

		return false;
	}

	return true;
}

/*---------------------------------------------------
�t�F�[�h�A�E�g�i��ʌ����Ȃ��Ȃ�j�̍X�V
�߂�l	�F	�t�F�[�h�����ǂ���
---------------------------------------------------*/
bool FadeOutUpdate(float time)
{
	float deltaTime = GetFrameDeltaTime();

	g_fadeRate += deltaTime / time;

	if (g_fadeRate > 1.0f || g_fadeEnd == true)
	{
		g_fadeRate = 1.0f;

		g_fadeEnd = false;

		return false;
	}

	return true;
}

/*---------------------------------------------------
�t�F�[�h�}�X�N�̕`��
����	�F	unsigned int color(�}�X�N�̐F)
---------------------------------------------------*/
void FadeDraw(unsigned int color)
{
	DrawAlphaBox(
		SCREEN_LEFT,
		SCREEN_TOP,
		SCREEN_RIGHT,
		SCREEN_BOTTOM,
		color,
		g_fadeRate
	);
}

/*---------------------------------------------------
�t�F�[�h�̏I��
---------------------------------------------------*/
void FadeEnd()
{
	g_fadeEnd = true;
}

/*---------------------------------------------------
�t�F�[�h�A�E�g����������Ԃɂ���
---------------------------------------------------*/
void SetFadeOut()
{
	g_fadeRate = 1.0f;
}

/*---------------------------------------------------
�t�F�[�h�C������������Ԃɂ���
---------------------------------------------------*/
void SetFadeIn()
{
	g_fadeRate = 0.0f;
}