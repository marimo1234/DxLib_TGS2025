#pragma once

class Fade
{
private:
	int alpha;				// �����x
	bool is_fade_in;		// �t�F�[�h�C�����H�@true: �t�F�[�h�C��	false: �t�F�[�h�A�E�g
	bool end_flag;			// �t�F�[�h�I���t���O	true: �I������	false: �I�����Ă��Ȃ�

public:
	// �R���X�g���N�^
	Fade();
	// �f�X�g���N�^
	~Fade();

public:
	// ����������
	void Initialize(bool set_fade_in_flag);
	// �X�V����
	void Update();
	// �`�揈��
	void Draw() const;
	// �I������
	void Finalize();

public:
	// �t�F�[�h�I���t���O���擾����
	bool GetEndFlag() const;
};

