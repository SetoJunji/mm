#define CHORDMAKER_C
//#include <stdio.h>
//#include <stdlib.h>
#include <bits/stdc++.h>
#include "MUSIC.h"
#include "PASSAGE.h"
#include "masterfile.h"

extern int nchord(int,int,int);

static int ChordPoolMaker(int passageID)
{
	FILE *cpfp;char cpfn[260];sprintf(cpfn,"CHORD_POOL_%d.txt",passageID);
	cpfp = fopen(cpfn,"w");fprintf(cpfp,"�D�悵�Ďg���ׂ��R�[�h�i�s\n");
	fclose(cpfp);return 0;
}


//�}�X�^�[�t�@�C�����Ɍ�������Ă����
static int ChordMaker_Master(int masterfilenumber,char *outputfn,CHORD *start,CHORD *end,int chordpool,int passageID)//����pID�͍ŏ��̃}�X�^�[�� chordpool = pID
{//if(requestfp!=NULL){���N�G�X�g�ɂ��������܂�;}else{�D������Ɍ��߂܂�;}
	char kouhofn[260];typedef struct{int c_masterfilenumber;char c_outputfn[260];CHORD c_start;CHORD c_end;}CHILD;CHILD *c;
	typedef struct{int length,bh,ch,ah,rh;}MAP_LINE;MAP_LINE *map;int NofLine=0;int linekind;char line[1000];int i=0;int NofC=0;
	FILE *mapfp;char mapfn[FILENAME_MAX];
	FILE *masterfp;MASTERFORMAT m;
//printf("[POOL,pID] = [%d,%d]\n",chordpool,passageID);
//printf("ChordMaker_Master(%d)\n",masterfilenumber);
	masterfp = masteropen(masterfilenumber);m = master_fscanf(masterfp);//�Ȍ�}�X�^�[�ɃA�N�Z�X�\
//////////////////////////////////////////////////////////////////MAP�ǂݍ��݊J�n
	sprintf(mapfn,"MAP_%d.txt",masterfilenumber);
	mapfp = fopen(mapfn,"r");while(fscanf(mapfp,"%d,%s",&linekind,line)>0){switch(linekind){case 1:break;case 2:NofLine++;break;}}fclose(mapfp);mapfp=NULL;
	map = (MAP_LINE*)calloc(NofLine,sizeof(MAP_LINE));
	mapfp = fopen(mapfn,"r");
	while(fscanf(mapfp,"%d,%s",&linekind,line)>0){switch(linekind){case 1:break;case 2:sscanf(line,"%d,%d,%d,%d,%d",&map[i].length,&map[i].bh,&map[i].ch,&map[i].ah,&map[i].rh);if(map[i].ch>0){NofC++;}i++;break;}}
	fclose(mapfp);mapfp=NULL;
//////////////////////////////////////////////////////////////////MAP�ǂݍ��ݏI��

	//�����ŕ��������������E��,������Ȃ��������E�̗��������s
	//�܂肱���ŃP�[�f���X�Ƃ��ďo�͂���,�q���B�ɂ��ꂼ�ꌈ�߂Ă��炤
///////////////////////////////////////////////////////////////////////////////���E1�̎n�܂�(�����Ō��߂�)
	nchord(NofC,start,end);sprintf(kouhofn,"�R�[�h���_[%d].txt",masterfilenumber);rename("N�R�[�h.txt",kouhofn);
///////////////////////////////////////////////////////////////////////////////���E1�̏I���

///////////////////////////////////////////////////////////////////////////////���E2�̎n�܂�(�q���B�Ɍ��߂Ă��炤)
	c = (CHILD*)calloc(m.linenumber,sizeof(CHILD));
	for(i=0;i<m.linenumber;i++)
	{
		fscanf(masterfp,"%d",&c[i].c_masterfilenumber);
		if(i%2==0){c[i].c_start = *start;c[i].c_end.dia = 5;c[i].c_end.kind = 1;}
		else if(i==m.linenumber-1){c[i].c_start.dia = 4;c[i].c_start.kind = 2;c[i].c_end = *end;}
		else{c[i].c_start.dia = 4;c[i].c_start.kind = 2;c[i].c_end.dia = 1;c[i].c_end.kind = 1;}
	}
	//for(i=0;i<m.linenumber;i++){printf("[%d]�̎q����[%d] by ChordMaker_Master()\n",masterfilenumber,c[i].c_masterfilenumber);}
for(i=0;i<m.linenumber;i++){ChordMaker_Master(c[i].c_masterfilenumber,c[i].c_outputfn,&c[i].c_start,&c[i].c_end,chordpool,passageID);}
	free(c);
///////////////////////////////////////////////////////////////////////////////���E2�̏I���
	
	//for(i=0;i<NofLine;i++){printf("%2d = %d\n",i,map[i].bh);}
	free(map);map=NULL;fclose(masterfp);masterfp=NULL;
	return 0;
}

//�y�߃t�@�C���ɍ����R�[�h�i�s�쐬��i�͑I�΂Ȃ�
static int ChordMaker_Passage(char *passagefn,char *outputfn)//�ʂ� �o��==NULL �Ȃ�o�͕s�v ?
{int passageID;
	//CHORD start={1,CHORD_KIND_M},end={1,CHORD_KIND_M};
	typedef struct{int length,bh,ch,ah,rh;}MAP_LINE;MAP_LINE *map;int NofLine=0;int linekind;char line[1000];int i=0;int NofC=0;
	FILE *mapfp;char mapfn[FILENAME_MAX];
	FILE *passagefp,*outputfp;FORMAT_PASSAGE p;
	//printf("[%s]�ɍ����R�[�h�i�s���l���܂�\n�o�� => [%s] by ChordMaker()\n",passagefn,outputfn);
	passagefp = fopen(passagefn,"r");p = passage_fscanf(passagefp);
	fclose(passagefp);passagefp=NULL;passageID = p.masterfile;
ChordPoolMaker(passageID);
	ChordMaker_Master(p.masterfile,NULL,&p.start,&p.end,p.masterfile,passageID);
/*
	sprintf(mapfn,"MAP_%d.txt",p.masterfile);
	mapfp = fopen(mapfn,"r");while(fscanf(mapfp,"%d,%s",&linekind,line)>0){switch(linekind){case 1:break;case 2:NofLine++;break;}}fclose(mapfp);
	map = (MAP_LINE*)calloc(NofLine,sizeof(MAP_LINE));
	
	mapfp = fopen(mapfn,"r");
	while(fscanf(mapfp,"%d,%s",&linekind,line)>0)
	{
		switch(linekind)
		{
		case 1:break;
		case 2:
			sscanf(line,"%d,%d,%d,%d,%d",&map[i].length,&map[i].bh,&map[i].ch,&map[i].ah,&map[i].rh);if(map[i].ch>0){NofC++;}
			i++;break;
		}
	}
	fclose(mapfp);//for(i=0;i<NofLine;i++){printf("%2d = %d\n",i,map[i].bh);}
	
	outputfp = fopen(outputfn,"w");
	//printf("[%d]�s�ł� =>[%d]�̃R�[�h\n",NofLine,NofC);
	fclose(outputfp);outputfp=NULL;free(map);
*/
	return 0;
}

int ChordMaker_Movement(char *movementfn)
{//�܂��ȑS�̂����Ă��ꂼ��̊y�߂Ŏg���R�[�h�v�[�����쐬���邱��
	int m,time,id;char name[20];
	int linekind;char line[1000];
	FILE *movementfp;int i=0;
	char passagefn[FILENAME_MAX];
	char chordfn[FILENAME_MAX];
	movementfp = fopen(movementfn,"r");
	if(movementfp==NULL){printf("[]��������܂���\n�I�����܂� by ChordMaker_Movement()\n",movementfn);exit(1);}
	while(fscanf(movementfp,"%d,%s",&linekind,line)>0)
	{
		switch(linekind)
		{
		case 1:break;
		case 2:
			sscanf(line,"%d,%d,%d,%s",&m,&time,&id,name);
			sprintf(chordfn,"[%s(%d���)]�̃R�[�h�i�s.txt",name,time);
			sprintf(passagefn,"PASSAGE[%s].txt",name);
			ChordMaker_Passage(passagefn,chordfn);
			break;
		}
	}
	fclose(movementfp);movementfp=NULL;
	return 0;
}
