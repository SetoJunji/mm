#define MOVEMENT_C
#include "MOVEMENT.h"
#include <stdio.h>
#include <stdlib.h>

int MovementMaker(MOVEMENT_INFO *movementinfo)
{
	int i;
	char *table[] = {"1,1,�O�t","1,2,A����","1,3,B����","1,4,�T�r","1,5,�ԑt","2,2,A����","2,3,B����","2,4,�T�r","1,6,��t"};
	
	FILE *fp=NULL;char fn[FILENAME_MAX] = "�f�t�H���g.txt";
	MOVEMENT_INFO x;//�����ō̗p����p�����[�^
	
	extern int test_HandP();//��X�����Ԃ����W���b�W�}���I�e�X�g�֐�
	test_HandP();

	x = *movementinfo;
	//�܂��͈����Ŗ��w��̃p�����[�^�������Ŗ��߂�
	if(180<x.tempo || x.tempo<100)
	{
		//printf("�ُ��TEMPO = [%d] => 120 �ɍĐݒ�\n",x.tempo);
		x.tempo = 120;
	}x.key = 0;//���̓n������
	
	//printf("���͉������Ă��Ȃ����� MovementMaker() �N��\n");
	//printf("TEMPO = [%d] ���Ă��Ƃ�\n",x.tempo);
sprintf(fn,"MOVEMENT_1.txt");//����ł�������
	fp = fopen(fn,"w");
	fprintf(fp,"1,%d,%d,[�s��,��,ID(�ŗL�̒l),������]\n",x.tempo,x.key);
	for(i=0;i<9;i++){fprintf(fp,"2,%d,%s\n",i+1,table[i]);}
	fclose(fp);
	//printf("�I�����܂� by MovementMaker()\n");exit(1);
	PassagesMaker(fn);


	return 0;
}
