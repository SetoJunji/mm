//#include <stdio.h>
//#include <stdlib.h>
#include <bits/stdc++.h>
#include "PartsFunction.h"

typedef struct{char TrackName[200];char BeltFn[260];//���ꂪ NULL �łȂ���Ώo�͂���
}TRACK;
typedef struct{int NofTrack;TRACK *track;}TRACKS;

static int CreateTracks(TRACKS *dest,int argc,char *argv[])
{
	int i;dest->NofTrack = argc;dest->track = (TRACK*)calloc(argc,sizeof(TRACK));if(dest->track==NULL){printf("�������m�ێ��s");exit(1);}
	for(i=0;i<argc;i++)
	{
		//printf("%s\n",argv[i]);
		sprintf(dest->track[i].TrackName,"%s",argv[i]);
	}
	return 0;
}

static int OneTrackOut(const TRACK *source)
{
	USTFILEINFO ust={120};
	//if(source->BeltFn!=NULL)
	{
		printf("[%s]���t�@�C���o��\n",source->TrackName);
		ust_file_out(source->TrackName,&ust);
	}
	return 0;
}

static int AllTracksOut(const TRACKS *source){int i;for(i=0;i<source->NofTrack;i++){OneTrackOut(&source->track[i]);}return 0;}

static int DestroyTracks(TRACKS *x)
{//int i;for(i=0;i<x->NofTrack;i++){printf("�g���b�N��[%s]��j�����܂�\n",x->track[i].TrackName);}
	free(x->track);x->track = NULL;
	return 0;
}

/*
static int MakeTodo_TEST()//�ȑS�̗̂�������Ċe�y�߂ŉ������邩���߂�
{
	FILE *fp;int i;
	char *fn = "�M�^�[���e�y�߂ł��ׂ�����.txt";
	fp = fopen(fn,"w");
	for(i=1;i<=9;i++)
	{
		fprintf(fp,"2,");
		switch(i)
		{
		case 1:case 9:
			fprintf(fp,"���t");//�O�t��t
			break;
		case 2:case 6://A����
			fprintf(fp,"���Y��");
			break;
		case 3:case 7://�T�r�O
			fprintf(fp,"�A���y�W�I");
			break;
		case 4:case 8://�T�r
			fprintf(fp,"�R�[�h");
			break;
		case 5:
			fprintf(fp,"�\��");
			break;
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	return 0;
}
*/
static int WhatTodo_TEST(int PassageID,int time)
{
	int x;
	switch(PassageID)
	{
	case 1:case 6:x = 111;break;
	case 2:x = 222;break;
	case 3:x = 333;break;
	case 4:x = 444;break;
	case 5:x = 555;break;
	}
	return x;
}

static int Maker_JANICK_GERS_Passage(int PassageID,int time)
{
	int role;
	role = WhatTodo_TEST(PassageID,time);
	printf("ROAL = [%d]\n",role);
	return 0;
}


static int TestCall(){}
static char *IDtoFn_Movement(int ID){static char Fn[260];sprintf(Fn,"MOVEMENT_%d.txt",ID);return Fn;}

int Maker_JANICK_GERS_Movement(int MovementID)
{FILE *fp;char fn[260];
	FORMAT_MOVEMENT m;
	
	int i;
	TRACKS x;
	int NofTrack = 6;
	char *TrackName[] = {"�M�^�[_1st","�M�^�[_2st","�M�^�[_3st","�M�^�[_4st","�M�^�[_5st","�M�^�[_6st"};
	LoadMovementInfo(&m,MovementID);
	CreateTracks(&x,NofTrack,TrackName);
	
	
	for(i=0;i<NofTrack;i++){sprintf(fn,"%s.txt",TrackName[i]);fp = fopen(fn,"w");fprintf(fp,"1920,%d\n",i+60);fclose(fp);}
	
	///////////����܂łɃx���g�t�@�C�������Ȃ���΂Ȃ�Ȃ�
	AllTracksOut(&x);
	DestroyTracks(&x);
	UnloadMovementInfo(&m);
	return 0;
}
