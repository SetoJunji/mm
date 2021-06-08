//�t�H�[�}�b�g�\���̂ƃ����o�[���̒�`
//�t�@�C������1�s�ǂ�ō\���̂�Ԃ��֐�
//�\���̂�ǂ�Ńt�@�C����1�s�o�͂���֐�
//�}�X�^�[�i���o�[���������ɂ��ă{�[�_�[�̌��J�E���g�����A�ďo�֐�
//���g�����֐�

//�s���̕s���ȃt�@�C���ō\���̂�Ԃ��ꍇ�|�C���^���g��(�X�L�����G���[�Ȃ̂�������Ȃ��̂�)
//�w�b�_�[���݂����ȕK���L��ƕ������Ă���ꍇ�̂�
#define CHORD_BORDERC
#include "chord_border.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "masterfile.h"

FILE *new_chord_border_open(int number)
{
	FILE *fp;
	char fn[FILENAME_MAX];
	sprintf(fn,"CHORDBORDER_%d.txt",number);
	//sprintf(fn,"CHORDBORDER_%d.txt",number);
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

FILE *chord_border_open(int number)
{
	FILE *fp;
	char fn[FILENAME_MAX];
	sprintf(fn,"BORDER_C_[%d].txt",number);
	//sprintf(fn,"CHORDBORDER_%d.txt",number);
	fp = fopen(fn,"r");
	return fp;
}

//�R�[�h�{�[�_�[�t�@�C���̉�A�ďo�쐬
	//�}�X�^�[�t�@�C�����J���ăt�@�C���i���o�[�ʂ�̃t�@�C�������
	//�������̓}�X�^�[�t�@�C���̃i���o�[�ł��肱�̊֐����L�̂��̂ł͖���
	//�R�[�h�{�[�_�[�̃t�@�C�����̓}�X�^�[�t�@�C���Ɋ܂܂�Ă���


static int test_border_out(FILE *fp,int length)
{
	const int bar = 1920;
	int lest;
	int i,n;
	FORMAT_CHORD_BORDER x = {0};
	
	n = length /bar;
	lest = length %bar;
	for(i=0;i<n;i++){x.length = bar;x.chord.dia = (2+rand()%5);x.chord.kind = 3;fprintf_chord_border(fp,&x);}
	if(lest > 0){x.length = lest;x.chord.dia = 1;x.chord.kind = 4;fprintf_chord_border(fp,&x);}
	//static int tekito = 1;
	//fprintf(fp,"%d,%d\n",1+(rand()%7),length);//�����牽�ł��K���߂���o��
/*
	int i;
	int n,lest;
	
	for(i=0;i<n;i++,tekito++){fprintf(fp,"%d,%d\n",tekito,1920);}
	
*/
	return 0;
}

static int kaiki_chord_border(int masternumber)//�R�[�h�{�[�_�[�t�@�C�����o���̂̓R�C�c�g��Ȃ��̂ŃN�r
{
	extern int map(int);

	int i,j;
	int child;//�}�X�^�[�t�@�C���̎q���̃t�@�C���i���o�[
	MASTERFORMAT m;
	FILE *masterfp;FILE *myfp;
	masterfp = masteropen(masternumber);
	m = master_fscanf(masterfp);
	fclose(masterfp);
printf("M_[%d]����ɂ�����O�Ƀ}�b�s���O\n",masternumber);
	//��������̂�����t�@�C���������͓̂��R
	map(masternumber);

	if(m.chord_border_painted==0)/*���h���Ȃ炻�̎q���B���P��*/
	{
		//printf("���h��\n");
		for(i=0;i<m.linenumber;i++)
		{
			masterfp = masteropen(masternumber);
			m = master_fscanf(masterfp);

			for(j=0;j<i;j++){fscanf(masterfp,"%d",&child);}
			if(fscanf(masterfp,"%d",&child)>0){fclose(masterfp);kaiki_chord_border(child);}
			else{fclose(masterfp);}
		}
	}
	
	else if(m.chord_border_file>0 && m.chord_border_painted>0)/*���̎��͍��Ȃ���΂Ȃ�Ȃ�*/
	{
		myfp = new_chord_border_open(m.chord_border_file);
		if(myfp==NULL){//printf("CB���P�ς�\n");
		return 0;}
		//printf("����(%d)��CB�t�@�C��(%d)�����܂�\n",m.length,m.chord_border_file);
		
		test_border_out(myfp,m.length);//�����牽�ł��K���߂���o��
		
		fclose(myfp);
	}
	
	else if(m.chord_border_painted>0)
	{printf("����ȏ�l����K�v�͖���(%d,%d)\n",m.chord_border_painted,m.chord_border_file);return 0;}
	
	
	return 0;
}

int count_chord_border(int masternumber)//�}�X�^�[�i���o�[���������ɂ��ă{�[�_�[�̌���Ԃ�(�}�b�v�t�@�C���Q�ƌ^)
{
	int x;int linekind;
	char mapfn[FILENAME_MAX];
	FILE *mapfp = NULL;
	sprintf(mapfn,"MAP_%d.txt",masternumber);
	mapfp = fopen(mapfn,"r");
	fscanf(mapfp,"%d,%d",&linekind,&x);
	fclose(mapfp);
	//printf("M_[%d]�ɂ�[%d]�̃R�[�h by count_chord_border()\n",masternumber,x);
	return x;
}

int count_chord_border_kubi(int masternumber)//�}�X�^�[�i���o�[���������ɂ��ă{�[�_�[�̌��J�E���g�����A�ďo�֐�
{int x=0;//char mapfn[FILENAME_MAX];FILE *mapfp = NULL;
	char cmd[1280];
	int t;//�z���g�͍\���̂̃����o
	static int n = 0;
	int nest;

	
	int i,j;
	int child;//�}�X�^�[�t�@�C���̎q���̃t�@�C���i���o�[
	MASTERFORMAT m;
	FILE *masterfp;FILE *myfp;

	nest = n++;
	//for(i=0;i<nest;i++){printf("-");}printf("[%d]\n",masternumber);


	masterfp = masteropen(masternumber);
	m = master_fscanf(masterfp);
	fclose(masterfp);
	

	if(m.chord_border_painted==0)/*���h���Ȃ炻�̎q���B���P�����͂�*/
	{
		for(i=0;i<m.linenumber;i++)
		{
			masterfp = masteropen(masternumber);
			m = master_fscanf(masterfp);

			for(j=0;j<i;j++){fscanf(masterfp,"%d",&child);}
			if(fscanf(masterfp,"%d",&child)>0){fclose(masterfp);x += count_chord_border(child);}
			else{fclose(masterfp);}
		}
	}
	
	else if(m.chord_border_file>0 && m.chord_border_painted>0)/*���̎��͍�����͂�(����𐔂��ĕԂ�)*/
	{
		myfp = chord_border_open(m.chord_border_file);

		//printf("BORFILE = (%d)\n",m.chord_border_file);

		while(fscanf(myfp,"%d,%s",&t,cmd) > 0){if(t>0){x++;}}//�K���ɐ�����
		
		fclose(myfp);
	}
	
	//else if(m.chord_border_painted>0){printf("����ȏ�l����K�v�͖���(%d,%d)\n",m.chord_border_painted,m.chord_border_file);return 0;}
	
	//for(i=0;i<nest;i++){printf("-");}
	printf("M_[%d]�ɂ�%d�̃{�[�_�[\n",masternumber,x);
	return x;
}

FORMAT_CHORD_BORDER fscanf_chord_border(FILE *fp)//�t�@�C������1�s�ǂ�ō\���̂�Ԃ��֐�
{
	FORMAT_CHORD_BORDER x = {0};//:�G���[�̎������Ԃ�?
	if(fscanf(fp,"%d,%d,%d",&x.length,&x.chord.dia,&x.chord.kind)<0)
	{
		printf("\nfscanf_chord_border()�ł̃X�L�����G���[\n");
		printf("%d,%d,%d\n",x.length,x.chord.dia,x.chord.kind);
	}else if(x.length<=0 || x.chord.dia<=0 || x.chord.kind<=0)
	{
		printf("\n�X�L�����͏o������,���炩�Ɉُ�\n");
		printf("�ُ� => [%d,%d,%d]\n",x.length,x.chord.dia,x.chord.kind);
	}
	return x;
}

int fprintf_chord_border(FILE *fp,FORMAT_CHORD_BORDER *format)//�\���̂�ǂ�Ńt�@�C����1�s�o�͂���֐�
{
	FORMAT_CHORD_BORDER x;

	x = *format;

	//fprintf(fp,"%d,%d\n",x.chord.dia,x.length);

	fprintf(fp,"%d,%d,%d\n",x.length,x.chord.dia,x.chord.kind);

	return 0;
}
