#ifndef PARTS_COMMON_H
#define PARTS_COMMON_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//typedef struct{int ;}MYPART;
#ifndef PARTS_COMMON_C
extern int IsScaleNote(char *ScaleFn);//IsWhite()�̃o�[�W����
extern int ScaleNote(int base,int updown,int root,char *ScaleFn);
#endif
#endif
