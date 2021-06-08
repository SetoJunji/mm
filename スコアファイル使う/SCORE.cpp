//�p�[�g�����̃X�R�A�t�@�C���쐬�֐�
#define SCORE_C
#include <stdio.h>
#include <stdlib.h>
#include "SCORE.h"
#include "PASSAGE.h"
#include "masterfile.h"

#define LINEKIND_HEADER 1
#define LINEKIND_BODY   2

int score_line_sscanf(char *line,SCORE_LINE *dest)
{
	//�{���Ȃ當����|�C���^�������ɂ��ׂ�
	//�����������̊֐����Ă�ł���Ƃ������Ƃ� LINEKIND �͊��m�̂͂�
	//�ȂǍl���Ă邤���ɏC������
	
	SCORE_LINE x;
	sscanf(line,"%d,%d,%d,%d,%d,%d,%d,%d,%d",&x.length,&x.bh,&x.ch,&x.ah,&x.rh,&x.chord_root,&x.chord_kind,&x.passage_head,&x.passage_number);
	*dest = x;
	return 0;
}

static int score_line_fprintf(FILE *fp,SCORE_LINE *sour)
{
	SCORE_LINE x;
	x = *sour;
	fprintf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",LINEKIND_BODY,x.length,x.bh,x.ch,x.ah,x.rh,x.chord_root,x.chord_kind,x.passage_head,x.passage_number);
	return 0;
}

static int ScoreMaker_Master(FILE *scorefp,int masterfilenumber)//M�t�@�C�����瓾����X�R�A��FP�̖����ɒǉ�
{
	int t;//�K��
	
	int linekind;char line[1280];
	FILE *mapfp;
	char mapfn[FILENAME_MAX];
	
	SCORE_LINE s = {-1,-2,-3,-4,-5,-6,-7};
	
	MASTERFORMAT m;
	FILE *masterfp;
	masterfp = masteropen(masterfilenumber);
	m = master_fscanf(masterfp);
	fclose(masterfp);

	//fprintf(scorefp,"M_[%d]�̃X�R�A�ǉ����܂� by ScoreMaker_Master()\n",masterfilenumber);

	sprintf(mapfn,"MAP_%d_NEW.txt",masterfilenumber);//���� MAP_NEW �t�@�C���Q��
	mapfp = fopen(mapfn,"r");
	if(mapfp!=NULL)//if(�����Ŗ��߂�,�܂�R�[�h���U�ς݂̃t�@�C��������)
	{
		t=1;//���͊y�߃w�b�h�� 1 ���g�p�{���Ȃ瑼�̂悤�ɒ����ɂ��ׂ�

		while(fscanf(mapfp,"%d,%s",&linekind,line)>0)
		{
			if(linekind==LINEKIND_BODY)
			{
				fprintf(scorefp,"2,%s,%d,%d\n",line,t,masterfilenumber);//���͊y�ߌŗL�̒l�Ƀ}�X�^�[�t�@�C���̃i���o�[���g�p
				t=0;
			}
			//score_line_fprintf(scorefp,&s);
		}
		fclose(mapfp);
	}//else if(�q���B�ɖ��߂Ă��炤){���J��;}
	
	

	return 0;
}

static int ScoreMaker_Passage(FILE *scorefp,char *passagefn)//�y�߃t�@�C�����瓾����X�R�A��FP�̖����ɒǉ�
{
	FORMAT_PASSAGE p;
	FILE *passagefp;
	passagefp = fopen(passagefn,"r");
	p = passage_fscanf(passagefp);
	
	//fprintf(scorefp,"\n[%s]�̃X�R�A�ǉ����܂� by ScoreMaker_Passage()\n",passagefn);
	
	ScoreMaker_Master(scorefp,p.masterfile);
	
fclose(passagefp);
	return 0;
}

int ScoreMaker_Movement(char *movementfn)//�y��(1��)�̃X�R�A�t�@�C���쐬�֐�
{
	char passagefn[FILENAME_MAX];
	
	FILE *scorefp;
	char scorefn[FILENAME_MAX];
	
	FILE *movementfp;
	
	sprintf(scorefn,"�X�R�A.txt");
	scorefp = fopen(scorefn,"w");
	fprintf(scorefp,"%d,120\n",LINEKIND_HEADER);
	
	movementfp = fopen(movementfn,"r");
	if(movementfp==NULL){printf("[%s]��������܂���=>�I�����܂�\n",movementfn);exit(1);}
	while(fscanf(movementfp,"%s",passagefn)>0){ScoreMaker_Passage(scorefp,passagefn);}
	fclose(movementfp);
	
	fclose(scorefp);
	return 0;
}

/*
//�o�b�N�A�b�v
static int ScoreMaker_Master(FILE *scorefp,int masterfilenumber)//M�t�@�C�����瓾����X�R�A��FP�̖����ɒǉ�
{
	SCORE_LINE scoreline = {-1,-2,-3,-4,-5,-6,-7};
	
	MASTERFORMAT m;
	FILE *masterfp;
	masterfp = masteropen(masterfilenumber);
	m = master_fscanf(masterfp);
	fclose(masterfp);

	fprintf(scorefp,"M_[%d]�̃X�R�A�ǉ����܂� by ScoreMaker_Master()\n",masterfilenumber);
	//if(�����Ŗ��߂�)
	{score_line_fprintf(scorefp,&scoreline);}
	//else if(�q���B�ɖ��߂Ă��炤){���J��;}
	

	return 0;
}
*/
