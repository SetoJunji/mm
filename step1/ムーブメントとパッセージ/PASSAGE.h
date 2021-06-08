#ifndef PASSAGE_H
#define PASSAGE_H
#include "music.h"
typedef struct{
	int masterfile,length,chordlength;
	CHORD start,end;//end�͂��܂�C�ɂ���Ȃ��ׂ�
	int kind;
	int NofBar,count,size;
	int auftaktID;
	int CoreID;
	int Unit;//��{�ƂȂ鏬��(�R�A)�̌�(2�̗ݏ�̂�)
}FORMAT_PASSAGE;//�𗧂���
typedef struct{int key;}PASSAGE_HEADER;//NEW

typedef struct{char MovenentName[200];int tempo;}FORMAT_MOVEMENT;

#ifndef PASSAGE_C
extern FORMAT_PASSAGE passage_fscanf(FILE *fp);//�𗧂���
extern int PassageMaker(char *movementfn,int linenumber);//NEW
//���s��(linenumber)�̊y�߂�����ė~�������ŗǂ��Ȃ�?
#endif
#endif
