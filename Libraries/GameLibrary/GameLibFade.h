/*
	�t�F�[�h�Ǘ�
*/
#pragma once

// �t�F�[�h�C���i��ʂ������Ă���j�̍X�V
bool FadeInUpdate(float time);

// �t�F�[�h�A�E�g�i��ʌ����Ȃ��Ȃ�j�̍X�V
bool FadeOutUpdate(float time);

// �t�F�[�h�}�X�N�̕`��
void FadeDraw(unsigned int color);

// �t�F�[�h�̏I��
void FadeEnd();

// �t�F�[�h�A�E�g����������Ԃɂ���
void SetFadeOut();

// �t�F�[�h�C������������Ԃɂ���
void SetFadeIn();