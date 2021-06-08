//���� ID �Ȃ烋�[�c�͓���(���������S�R�s�[�Ƃ͌���Ȃ�)
//#include <stdio.h>
//#include <stdlib.h>

#include <bits/stdc++.h>
#include "PASSAGE.h"
#include "masterfile.h"

static int pow(unsigned int x,unsigned int n){
	int ret=1;
	int i;
	for(i=0;i<n;i++){ret *= x;}
	return ret;
}

static int pow2(const int big,const int small)
{
	int i;
	for(i=0;;i++){if(small*pow(2,i)==big){return i;}else if(small*pow(2,i)>big){printf("[%d] IS NOT POW\n",big);return -1;exit(1);}}
}

static int TestBaiCore(int CoreID,int NofBar)
{
	extern int newmynumber();MASTERFORMAT m={0};
	FILE *MasterFp;char MasterFn[260];int HowManyTimesBai;
	HowManyTimesBai = pow2(NofBar,TestCoreBarNumber(CoreID));
	printf("CORE[%d] �� [%d] ��{����[%d]���ߕ��̃}�X�^�[�t�@�C���쐬 by TestBaiCore()\n",CoreID,HowManyTimesBai,NofBar);
	sprintf(MasterFn,"MASTER_��_%d.txt",newmynumber());MasterFp = fopen(MasterFn,"w");master_fprintf(MasterFp,&m);fclose(MasterFp);
	return 0;
}

int TestCoreMaker(int CoreID,int NofBar){
	int i;int NofBeatPerBar = 8;
	int Length,BH,CH,AH,RH;int pucchoID;
	
	FILE *Corefp;char Corefn[260];sprintf(Corefn,"CORE_%d.txt",CoreID);
	Corefp = fopen(Corefn,"w");
	fprintf(Corefp,"0,���ߐ�\n1,%d\n",NofBar);
	for(i=0;i<NofBar*NofBeatPerBar;i++)
	{
		Length = 240;
		BH = (i%NofBeatPerBar==0)?1:0;
		CH = 1;AH = 2;RH = 3;
		fprintf(Corefp,"2,%d,%d,%d,%d,%d\n",Length,BH,CH,AH,RH);
	}
	fclose(Corefp);//printf("�I�����܂�\n");exit(1);
	return 0;
}

int TestCoreBarNumber(int CoreID){
	int LineKind,x;char Line[1280];
	FILE *Corefp;char Corefn[260];
	sprintf(Corefn,"CORE_%d.txt",CoreID);
	Corefp = fopen(Corefn,"r");
	while(fscanf(Corefp,"%d,%s",&LineKind,Line)>0)
	{
		//printf("[%d,%s] by TestCoreBarNumber()\n",LineKind,Line);
		if(LineKind==1){fclose(Corefp);sscanf(Line,"%d",&x);
		//printf("CORE[%d]��[%d]�̏��� by TestCoreBarNumber()\n",CoreID,x);
		return x;}
	}
}

int TEST_MASTER_PARENT_Maker(int PassageID,int NofBar)//NofBar�̏��߂��܂ރ}�X�^�[�t�@�C�����쐬���Ă��� ID ��Ԃ�
{FORMAT_PASSAGE p;
	int MasterID;printf("TEST_MASTER_PARENT_Maker(%d) �J�n\n",PassageID);
	PassageLoad(&p,PassageID);
	TestCoreMaker(p.CoreID,NofBar/4);//�ЂƂ܂��S�̂� 1/4 �̃R�A�ɂ��Ƃ�
	printf("CORE[%d]��[%d]�̏��� by TEST_MASTER_PARENT_Maker()\n",p.CoreID,TestCoreBarNumber(p.CoreID));
	TestBaiCore(p.CoreID,NofBar);
	//printf("�I�����܂� by TEST_MASTER_PARENT_Maker(%d)\n",PassageID);exit(1);
	return MasterID;
}

int PassageLoad(FORMAT_PASSAGE *dest,int PassageID)
{
	char *table[] = {"PASSAGE[�O�t].txt","PASSAGE[A����].txt","PASSAGE[B����].txt","PASSAGE[�T�r].txt","PASSAGE[�ԑt].txt","PASSAGE[��t].txt"};
	FILE *PassageFp;char PassageFn[260];FORMAT_PASSAGE x;sprintf(PassageFn,"%s",table[PassageID-1]);
	PassageFp = fopen(PassageFn,"r");x = passage_fscanf(PassageFp);fclose(PassageFp);
	*dest = x;
	//printf("�I�����܂�\n");exit(1);
	return 1;
}

int MasterMaker_Passage(int MovementID,int PassageID)
{
	int LineKind;char Line[1280];FILE *PassageFp;char PassageFn[260];printf("MasterMaker_Passage(%d)�J�n\n",PassageID);
	printf("MasterMaker_Passage(%d)�J�n\n",PassageID);sprintf(PassageFn,"PASSAGE_%d_%d.txt",MovementID,PassageID);

TEST_MASTER_PARENT_Maker(PassageID,16);
//exit(1);
/*
	PassageFp = fopen(PassageFn,"r");if(PassageFp==NULL){printf("[%s]��������܂���\n\n",PassageFn);exit(1);}
	while(fscanf(PassageFp,"%d,%s",&LineKind,Line)>0)
	{
		switch(LineKind)
		{
		case 1:default://���͉��ł��\��
			printf("[%s]���X�L�������܂��� by MasterMaker_Passage()\n",Line);
			break;//�ǂ��ł��������{�����0�ŃX���[���Ă��Ƃ�
		}
	}
	fclose(PassageFp);
*/
//printf("�I�����܂� by MasterMaker_Passage()\n");exit(1);
	return 0;
}

int MasterMaker_Movement(int MovementID)
{int count,time,PassageID;
	int LineKind;char Line[1280];FILE *MovementFp;char MovementFn[260];printf("MasterMaker_Movement(%d) �J�n\n",MovementID);

	sprintf(MovementFn,"MOVEMENT_%d.txt",MovementID);
	MovementFp = fopen(MovementFn,"r");if(MovementFp==NULL){printf("[%s]��������܂���\n",MovementFn);return (-1);}
	while(fscanf(MovementFp,"%d,%s",&LineKind,Line)>0)
	{
		switch(LineKind)
		{
		case 2:
			sscanf(Line,"%d,%d,%d",&count,&time,&PassageID);//�{���͐�p�̃X�L�����֐����g���ׂ�
			MasterMaker_Passage(MovementID,PassageID);break;
		case 1:default://���͉��ł��\��
			printf("[%s]���X�L�������܂��� by MasterMaker_Movement()\n",Line);
			break;/*�ǂ��ł��������{�����0�ŃX���[���Ă��Ƃ�*/
		}
	}
	fclose(MovementFp);
	//printf("�I�����܂� by MasterMaker_Movement()\n");exit(1);
	return 0;
}
