#ifndef CHORD_BORDERH
#define CHORD_BORDERH
#include "music.h"
//�t�H�[�}�b�g�\���̂ƃ����o�[���̒�`
//#define FORMATNUMBER 1
typedef struct{int length;CHORD chord;}FORMAT_CHORD_BORDER;

#ifndef CHORD_BORDERC
extern FILE *new_chord_border_open(int masterfilenumber);
extern FILE *chord_border_open(int number);
extern int count_chord_border(int masternumber);//�}�X�^�[�i���o�[���������ɂ��ă{�[�_�[�̌��J�E���g�����A�ďo�֐�
extern int kaiki_chord_border(int masternumber);//���g�����֐�
extern FORMAT_CHORD_BORDER fscanf_chord_border(FILE *fp);//�t�@�C������1�s�ǂ�ō\���̂�Ԃ��֐�
extern int fprintf_chord_border(FILE *fp,FORMAT_CHORD_BORDER *format);//�\���̂�ǂ�Ńt�@�C����1�s�o�͂���֐�
#endif

#endif
