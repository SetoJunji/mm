#define SESSION_C
#include "SESSION.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int NumberOfParts(char *sessionfn,int movementID);
int AddSession_Passage(int movementID,int passageID,char *addpartfn);
int LoadSession_Passage(PART **part,int NofPart,int movementID,int passageID);

int NumberOfParts(char *sessionfn,int movementID)
{int passageID = 1;
	char line[1000];char*pointer;
	FILE *fp;char fn[260];int x;
	if(sessionfn==NULL){sprintf(fn,"SESSION_%d_%d.txt",movementID,passageID);}else{sprintf(fn,"%s",sessionfn);}
	fp = fopen(fn,"r");if(fp==NULL){printf("[%s]��������܂��� by NumberOfParts()\n",fn);return 0;}
	if(fscanf(fp,"%s",line)>0){for(x=1,pointer=line;pointer!=NULL;x++){pointer = strstr(pointer,",");if(pointer==NULL){break;}else{pointer++;}}}
	else{x = 0;}
	fclose(fp);printf("X = [%d] by NumberOfParts(%d,%d)\n",x,movementID,passageID);
	return x;
}

int AddSession_Passage(int movementID,int passageID,char *addpartfn)
{
	char Line1[1000] = {0};
	char Line2[1000] = {0};
	FILE *addpartfp=NULL;
	FILE *tempfp=NULL;char *tempfn = "SESSION_TEMP.txt";
	FILE *sessionfp;
	char sessionfn[FILENAME_MAX];
	
	//if(NOP!=NumberOfParts(NULL,movementID)){printf("�ŏ��ƈقȂ� NOP �̃t�@�C���ɂ͎Q���o���܂���\n");return 0;}
	
	sprintf(sessionfn,"SESSION_%d_%d.txt",movementID,passageID);
	addpartfp = fopen(addpartfn,"r");sessionfp = fopen(sessionfn,"r");
	if(sessionfp==NULL)
	{
		sessionfp = fopen(sessionfn,"w");
		while(fscanf(addpartfp,"%s",Line1)>0){fprintf(sessionfp,"%s\n",Line1);}
		fclose(sessionfp);
		//printf("�܂��Ƒt�ł� by AddSession_Passage()\n");
		return 0;
	}//else{printf("�Z�b�V�����ł�\n");}
	tempfp = fopen(tempfn,"w");//�S�t�@�C���I�[�v��
	while(fscanf(sessionfp,"%s",Line1)>0){fscanf(addpartfp,"%s",Line2);fprintf(tempfp,"%s,%s\n",Line1,Line2);}
	fclose(tempfp);fclose(sessionfp);fclose(addpartfp);tempfp = NULL;sessionfp = NULL;addpartfp = NULL;//�S�t�@�C���N���[�Y
	remove(sessionfn);rename(tempfn,sessionfn);
	return 0;
}

int LoadSession_Passage(PART **part,int NofPart,int movementID,int passageID)
{
	char *pointer;char sessionline[1000];
	int i,j,m=64,n;//m�͍s��,n�̓p�[�g��
	FILE *sessionfp;char sessionfn[FILENAME_MAX];

	//n = NumberOfParts(NULL,movementID,passageID);
	//n = NOP;
	n = NofPart;
	sprintf(sessionfn,"SESSION_%d_%d.txt",movementID,passageID);sessionfp = fopen(sessionfn,"r");
	if(sessionfp==NULL){/*printf("[%s]��������܂��� by LoadSession()\n",sessionfn);*/return -1;}else{if(n!=NofPart){printf("����[%d]�Ǝ��ۂ̃p�[�g��[%d]�������܂���\n",NofPart,n);exit(1);}}
	for(i=0;i<m;i++)
	{
		fscanf(sessionfp,"%s",sessionline);
		for(j=0,pointer=sessionline;j<n && pointer!=NULL;j++)
		{
			sscanf(pointer,"%d",&part[i][j].note);
			//printf("%2d�s_%d�p�[�g = [%d](%x,%s)\n",i,j,part[i][j].note,pointer,pointer);
			pointer = strstr(pointer,",");if(pointer==NULL){/*printf("���̍s�ɂ���ȏ�̃p�[�g�͂���܂���\n");*/break;}else{pointer++;}
			
		}
	}
	fclose(sessionfp);
	return 0;
}