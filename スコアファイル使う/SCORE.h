//�p�[�g�����̃X�R�A�t�@�C���쐬�֐�
#ifndef SCORE_H
#define SCORE_H
typedef struct{int tempo;}SCORE_HEADER;
typedef struct{int length,bh,ch,ah,rh,chord_root,chord_kind,passage_head,passage_number;}SCORE_LINE;//passage_head,passage_number�����邩�ᖡ���邱��
#ifndef SCORE_C
extern int ScoreMaker_Movement(char *movementfn);//�y��(1��)�̃X�R�A�t�@�C���쐬�֐�
extern int score_line_sscanf(char *line,SCORE_LINE *dest);
#endif
#endif