/*
//MF��MakeFile�̗�
//fn��FileName�̗�i,o = input,output
//�t�H�[�}�b�g
//int MF(){FILE *fp;char ofn[] = ".txt";fp = fopen(ofn,"w");fclose(fp);return 0;}


#define NFY_C
#include "music.h"



int MFjyunnkann(int n,CHORD start)//�z�R�[�h.txt���o��
{
	int i;
	CHORD *list;
	FILE *fp;
	char ofn[] = "�z�R�[�h.txt";
	fp = fopen(ofn,"w");
	list = (CHORD*)calloc(n,sizeof(CHORD));

	for(i=0;i<n;i++)//���͓K���ł�
	{
		list[i].dia  = i;
		list[i].kind = i*2;
	}


	for(i=0;i<n;i++){fprintf(fp,"%d,%d\n",list[i].dia,list[i].kind);}
	free(list);
	fclose(fp);
	return 0;
}

int MFkyokuhennsei()//���� 3_1.txt(���_�o�[�W����)�݂����Ȋ���
{
	FILE *fp;char ofn[] = "�ȕҐ�.txt";fp = fopen(ofn,"w");fprintf(fp,"�܂������\n");fclose(fp);
	return 0;
}

int testmain()
{
	
	CHORD start ={1,3};
	
	MFkyokuhennsei();

	printf("1\n");
	
	MFjyunnkann(8,start);
	
	printf("2\n");
	
	MFdouki();
	
	printf("3\n");


	return 0;
}

int MFdouki()//�z�R�[�h.txt��H����,���@.txt���o��
{
	int Odia,Okind,Osubmotive,Obar,Ocut,Ochordborder;//����΃t�H�[�}�b�g
	int i;
	int NObar = 4;//NofBar
	int NObeatInBar = 8;
	FILE *out,*jyunnkannchordfile;
	char outputfilename[] = "���@.txt";
	char jyunnkannchordfilename[] = "�z�R�[�h.txt";

	out = fopen(outputfilename,"w");
	jyunnkannchordfile = fopen(jyunnkannchordfilename,"r");
	
	for(i=0;i<NObar*NObeatInBar;i++)
	{
		Osubmotive = 0;
		Obar = (i%NObeatInBar==0) ? 1:0;Ocut = 0;if(Obar==1){Ochordborder = 1;}else{Ochordborder = 0;}//�ЂƂ܂����߂̓�
		if(Ochordborder==1){fscanf(jyunnkannchordfile,"%d,%d",&Odia,&Okind);}
		fprintf(out,"%d,%d,%d,%d,%d,%d\n",Odia,Okind,Osubmotive,Obar,Ocut,Ochordborder);
	}
	
	fclose(out);
	fclose(jyunnkannchordfile);
	return 0;
}


int testmain()
{
	CHORD start ={1,3};
	MFjyunnkann(8,start);
	return 0;
}
*/
