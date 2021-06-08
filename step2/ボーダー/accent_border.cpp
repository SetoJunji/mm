#define ACCENT_BORDER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "masterfile.h"

FILE *accent_border_open(int number)
{
	FILE *fp;
	char fn[FILENAME_MAX];
	sprintf(fn,"ACCENTBORDER_%d.txt",number);
	fp = fopen(fn,"r");

	if(fp==NULL){printf("�t�@�C��[%s]��������܂���\n",fn);return NULL;}
	else{return fp;}
}
FILE *new_accent_border_open(int number)
{
	FILE *fp;
	char fn[FILENAME_MAX];
	sprintf(fn,"ACCENTBORDER_%d.txt",number);
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
static int test_ab_out(FILE *fp,int length)
{
	int i;
	int tubu;//���̌�
	int to;
	to = (1920/8);
	tubu = length / to;
	//printf("��%d���̒����ł�\n",tubu);
	if(tubu==0 && length>0){fprintf(fp,"%d,%d\n",length,1+rand()%11);}
	else{for(i=0;i<tubu;i++){fprintf(fp,"%d,%d\n",to,1+rand()%11);}}
	return 0;
}
int kaiki_accent_border(int masternumber)
{
	int i,j;
	int child;//�}�X�^�[�t�@�C���̎q���̃t�@�C���i���o�[
	MASTERFORMAT m;
	FILE *masterfp;FILE *myfp;
	masterfp = masteropen(masternumber);
	m = master_fscanf(masterfp);
	fclose(masterfp);
	

	if(m.accent_border_painted==0)/*���h���Ȃ炻�̎q���B���P��*/
	{
		for(i=0;i<m.linenumber;i++)
		{
			masterfp = masteropen(masternumber);
			m = master_fscanf(masterfp);

			for(j=0;j<i;j++){fscanf(masterfp,"%d",&child);}
			if(fscanf(masterfp,"%d",&child)>0){fclose(masterfp);kaiki_accent_border(child);}
			else{fclose(masterfp);}
		}
	}
	
	else if(m.accent_border_file>0 && m.accent_border_painted>0)/*���̎��͍��Ȃ���΂Ȃ�Ȃ�*/
	{
		myfp = new_accent_border_open(m.accent_border_file);

		if(myfp==NULL){//printf("AB���P�ς�\n");
		return 0;}
		
		//printf("����(%d)��AB�t�@�C��(%d)�����܂�\n",m.length,m.accent_border_file);


		test_ab_out(myfp,m.length);

		fclose(myfp);
	}
	
	else if(m.accent_border_painted>0)
	{printf("����ȏ�l����K�v�͖���(%d,%d)\n",m.accent_border_painted,m.accent_border_file);return 0;}
	
	
	return 0;
}
