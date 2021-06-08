#define RYTHM_BORDER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "masterfile.h"


FILE *rythm_border_open(int number)
{
	FILE *fp;
	char fn[FILENAME_MAX];
	sprintf(fn,"RYTHMBORDER_%d.txt",number);
	sprintf(fn,"BORDER_R_[%d].txt",number);
	fp = fopen(fn,"r");
	if(fp==NULL){printf("�t�@�C��[%s]��������܂���\n",fn);exit(1);return NULL;}
	else{return fp;}
}
FILE *new_rythm_border_open(int number)
{
	FILE *fp;
	char fn[FILENAME_MAX];
	sprintf(fn,"RYTHMBORDER_%d.txt",number);
	fp = fopen(fn,"r");
	if(fp != NULL)
	{
		//printf("���ɑ��݂���i���o�[�ł�\n");
		fclose(fp);
		return NULL;
	}
	fp = fopen(fn,"w");
	return fp;
}

static int test_rb_out(FILE *fp,int length)//���CB�t�@�C���ɒ������̒��g����������(1���őS�ď�������)
{static int a=0;
	int *box;
	int i,j;
	int tubu;//���̌�
	int to;
	to = (1920/8);
	tubu = length / to;

printf("��%d���̒����ł�\n",tubu);
if(tubu==0 && length>0)//1�������Ȃ���Β������̉��Ŗ��߂�
{
	fprintf(fp,"%d,%d\n",length,9);//����9
	return 0;
}

box = (int*)calloc(tubu,sizeof(int));
for(i=0;i<tubu;i++){printf("%d-",box[i]);}printf("\n");
for(i=0;i<tubu;i++){if(rand()%2==0 || i==0){box[i] = 1;}}
for(i=0;i<tubu;i++){printf("%d-",box[i]);}printf("\n");
for(i=0;i<tubu;i++)
{
	if(box[i]>0)
	{
		j=i+1;if(i==tubu||j==tubu){break;}
		while(1){if(box[j]==0){box[i]++;j++;}else{break;}}
	}
}
for(i=0;i<tubu;i++){printf("%d-",box[i]);}printf("\n");

for(i=0;i<tubu;i++){if(box[i]>0){fprintf(fp,"%d,%d\n",to*(box[i]),7);}}//����7


free(box);
	return 0;
}
int kaiki_rythm_border(int masternumber)
{
	int i,j;
	int child;//�}�X�^�[�t�@�C���̎q���̃t�@�C���i���o�[
	MASTERFORMAT m;
	FILE *masterfp;FILE *myfp;
	masterfp = masteropen(masternumber);
	m = master_fscanf(masterfp);
	fclose(masterfp);
	

	if(m.rythm_border_painted==0)/*���h���Ȃ炻�̎q���B���P��*/
	{
		for(i=0;i<m.linenumber;i++)
		{
			masterfp = masteropen(masternumber);
			m = master_fscanf(masterfp);

			for(j=0;j<i;j++){fscanf(masterfp,"%d",&child);}
			if(fscanf(masterfp,"%d",&child)>0){fclose(masterfp);kaiki_rythm_border(child);}
			else{fclose(masterfp);}
		}
	}
	
	else if(m.rythm_border_file>0 && m.rythm_border_painted>0)/*���̎��͍��Ȃ���΂Ȃ�Ȃ�*/
	{
		myfp = new_rythm_border_open(m.rythm_border_file);

		if(myfp==NULL){//printf("RB���P�ς�\n");
		return 0;}
		
		//printf("����(%d)��RB�t�@�C��(%d)�����܂�\n",m.length,m.rythm_border_file);


test_rb_out(myfp,m.length);//�����牽�ł��K���߂���o��
		//fprintf(myfp,"�����ɏo��\n");
		
		fclose(myfp);
	}
	
	else if(m.rythm_border_painted>0)
	{printf("����ȏ�l����K�v�͖���(%d,%d)\n",m.rythm_border_painted,m.rythm_border_file);return 0;}
	
	
	return 0;
}
