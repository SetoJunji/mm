#ifndef RYTHM_BORDERH
#define RYTHM_BORDERH
//�t�H�[�}�b�g�\���̂ƃ����o�[���̒�`
//#define FORMATNUMBER 1
typedef struct{int parent,length,chord_border_painted,chord_border_file,rythm_border_painted,rythm_border_file,accent_border_painted,accent_border_file;}FORMAT;

#ifndef RYTHM_BORDERC
extern int count_rythm_border(int masternumber);//�}�X�^�[�i���o�[���������ɂ��ă{�[�_�[�̌��J�E���g�����A�ďo�֐�
extern int kaiki_rythm_border(int masternumber);//���g�����֐�
//extern FORMAT fscanf_rythm_border(int number);//�t�@�C������1�s�ǂ�ō\���̂�Ԃ��֐�
//extern int printf_rythm_border(int number);//�\���̂�ǂ�Ńt�@�C����1�s�o�͂���֐�
#endif

#endif
