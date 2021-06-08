//�X�R�A��ǂ�Ŋe�p�[�g�̋��ʎ���
//�ǂ�ȃX�N���b�v�t�@�C������邩�͊e�p�[�g��p�̊֐��ɂ��C��
//�X�R�A�Ƀp�[�g�X�N���b�v�������t���邾���̃V�P���֐�
//�������Ȃ��炱�̊֐��̂������ŃA�E�t�^�N�g���ӎ������ɂ��ނ悤�ɂȂ�
//�e�p�[�g�X�R�A�e�p�[�g�ƃX�R�A��ʂ����Ƃ�,
//�p�[�g�Ԃł̉��̂Ȃ�����l���鎖���ł�,
//�`���̏��ߐ��̂悤�ɕs�m��v�f�ɂ��C�����s����
#define SCRAP_C
#include "SCRAP.h"
#include <stdio.h>
#include <stdlib.h>
#include "SCORE.h"
#include "MUSIC.h"
#include "UST.h"
#define LINEKIND_BODY 2

static int maxnote = 101,minnote = 70;

typedef struct{int wave,pre,note;}X;

static int NearWhite(int note,int whitefile,int pm)
{
	int x,y;x = note;y = (pm>0) ? 1:-1;
	while(x%12!=0 && x%12!=2 && x%12!=4 && x%12!=5 && x%12!=7 && x%12!=9 && x%12!=11)//�C�ɐH��Ȃ���
	{x+=y;}//printf("X = %d by NearWhite()\n",x);
	return x;
}
//���߂�"�g���b�N"�ɂ��Ƃ���

static FILE *OpenScrapFileW(int ID)//��̃X�N���b�v�t�@�C�������݂���Ƃ��̂� A���[�h�ŊJ��
{
	char line[1000];int E=1;
	FILE *fp;char fn[FILENAME_MAX];if(ID<0){printf("����ID = [%d] �͓n���܂��� by MakeNewScrapFile()\n",ID);exit(1);}sprintf(fn,"SCRAP_%d.txt",ID);
	fp = fopen(fn,"r");if(fp==NULL){exit(1);}if(fscanf(fp,"%s",line)>0){E=0;}fclose(fp);
	if(E==1){fp = fopen(fn,"a");return fp;}else{return NULL;}
}

static FILE *OpenScrapFileR(int ID)//�X�N���b�v�t�@�C�������݂���Ƃ��̂� R���[�h�ŊJ��
{
	FILE *fp;char fn[FILENAME_MAX];if(ID<0){printf("����ID = [%d] �͓n���܂��� by MakeNewScrapFile()\n",ID);exit(1);}sprintf(fn,"SCRAP_%d.txt",ID);
	fp = fopen(fn,"r");if(fp==NULL){exit(1);}return fp;
}

static int ScrapLoad(X *dest,int ID,int n)//dest �� SCRAP_ID.txt �� n�s���[�h����֐�
{
	//�{���Ȃ璆�r���[�ȃ��[�h��h�����߂ɂ܂Ȕ����ĂɈڂ��ׂ�
	X x;
	FILE *scrapfp;
	int i;
	scrapfp = OpenScrapFileR(ID);
	for(i=0;i<n;i++)
	{
		if(fscanf(scrapfp,"%d,%d,%d",&x.pre,&x.wave,&x.note)>0){dest[i] = x;}
		else{fclose(scrapfp);return -1;}
	}
	fclose(scrapfp);return 1;
}

static int MakeNewScrapFile(int ID)//�V�K�쐬�� ID ��Ԃ�
{
	FILE *fp;char fn[FILENAME_MAX];
	if(ID<0){printf("����ID = [%d] �͓n���܂��� by MakeNewScrapFile()\n",ID);exit(1);}
	sprintf(fn,"SCRAP_%d.txt",ID);fp = fopen(fn,"r");
	if(fp!=NULL){//printf("[%s]�͊��ɑ��݂��܂� by MakeNewScrapFile()\n",fn);
	fclose(fp);return (-1);}
	else{//printf("[%s]���쐬���܂� by MakeNewScrapFile()\n",fn);
	fp = fopen(fn,"w");fclose(fp);return ID;}
}

static int Maker_Oboe_Passage(int passageID,SCORE_LINE *s,X *x,int n)//�����уt�@�C���쐬���ׂ�(�����̂�)
{
#define Oboe_MODE_SOLO 1
#define Oboe_MODE_SOLI 2
#define Oboe_MODE_CHORD_BACKING 3
	int mode =(-1);
	char *testline = "-1,-2,-3,-4,-5,-6,-7";int testint[8]={0};int outnote;
	typedef struct{int length,note;}PART;char PartsScaner[1000]={0};
	PART **OP;//OtherParts�̗�(�|�C���^�e�[�u��)
	int NofOP=4;
	int i;CHORD nowchord;int ID;FILE *scrapfp;
	OP = (PART**)calloc(n,sizeof(PART*));//�s�����|�C���^���m��
	for(i=0;i<n;i++)
	{
		OP[i] = (PART*)calloc(NofOP,sizeof(PART));//���ꂼ��̍s�Ƀp�[�g����
		if(OP[i]==NULL){printf("�������m�ێ��s\n");}
		//else{strcat(PartsScaner,"%d,");printf(PartsScaner,1,2,3,4,5,6,8);
		//sscanf(testline,PartsScaner,&testint[0],&testint[1],&testint[2],&testint[3],&testint[4],&testint[5],&testint[6],&testint[7]);
		//printf("\n�����Ȃ� => %d/%d/%d/%d/%d/%d/%d/%d",testint[0],testint[1],testint[2],testint[3],testint[4],testint[5],testint[6],testint[7]);
		//printf("�p�[�g�i���o�[[%d]�̐擪�A�h���X = [%X]\n",i,OP[i]);}
	}
	for(i=0;i<NofOP;i++){free(OP[i]);OP[i]=NULL;}
	free(OP);OP=NULL;

	for(i=0;i<n;i++){x[i].wave = i;}
	for(i=0;i<n;i++)
	{
		if(i==0){x[i].pre = minnote + rand()%(maxnote-minnote);}else{x[i].pre = x[i-1].pre + (rand()%3-1);}
		if(x[i].pre>maxnote){x[i].pre = x[i-1].pre-2;}
		if(x[i].pre<minnote){x[i].pre = x[i-1].pre+2;}
		
	}//���̎��_�ŉ���ɖ������Ȃ��悤��
	for(i=0;i<n;i++)
	{
		if(s[i].rh>0)//�A�^�b�N
		{
			nowchord.dia = s[i].chord_root;nowchord.kind= s[i].chord_kind;
			if(s[i].ah>0){x[i].note = NearChordTone(x[i].pre,0,1,&nowchord,0);}
			else{x[i].note = NearWhite(x[i].pre,0,1);}
		}//else{x[i].note = 0;}//�x��(0�ł����̂�?)
		//else{x[i].note = x[i-1].note;}//���͋x�������O�̉��Ɠ�����
		else{x[i].note = -1;}//
	}for(i=n-1;i>0;i--){if(x[i].note>0){x[i].note = -1;break;}}
	for(i=n-1;i>0;i--){if(x[i].note>0){x[i].note = 60;break;}}//�����ɍŌ�̉��� C �ɂ���
if(passageID==1|| passageID==5 || passageID==6){for(i=0;i<n;i++){x[i].wave = 0;x[i].pre = 0;x[i].note = 0;}}
	ID = MakeNewScrapFile(s[i].passage_number);
			if(ID>0)
			{
				scrapfp = OpenScrapFileW(ID);
				for(i=0;s[i].passage_number==ID;i++){fprintf(scrapfp,"%d,%d,%d\n",x[i].pre,x[i].wave,x[i].note);}
				fclose(scrapfp);
			}else{ScrapLoad(&x[i],s[i].passage_number,n);}
	for(i=0,outnote=0;i<n;i++){if(x[i].note>0){outnote=x[i].note;}/*printf("%2d = %d ����Ȃ̂������уt�@�C���ɂ����? by Maker_Oboe_Passage()\n",i,outnote);*/}
	return 0;
}

int Maker_Oboe(char *scorefn)//TrackMaker(scorefn,partname)�ɂ��ׂ�?
{int NofPL;
	char test[1000];int ID;//�K�������y�߂ЂƂ܂Ƃ܂�Ƃ͌���Ȃ��̂� ID �Ƃ��Ă���//int now_passage=(-1);
	X *x;USTFILEINFO finf = {120,1};FILE *tfp=NULL;char *tfn = "Oboe.txt";
	int linekind;char line[1000];SCORE_LINE *s;int *parts;int m=0,n,i,j;//�p�[�g�̍s��
	FILE *scorefp=NULL;
	scorefp = fopen(scorefn,"r");while(fscanf(scorefp,"%d,%s",&linekind,line)>0){if(linekind==LINEKIND_BODY)m++;}fclose(scorefp);scorefp=NULL;
x = (X*)calloc(m,sizeof(X));	
	s = (SCORE_LINE*)calloc(m,sizeof(SCORE_LINE));
	if(s==NULL){printf("[%d]�� SCORE_LINE �������m�� => ���s by Oboe()\n",m);exit(1);}
	//else{printf("[%d]�� SCORE_LINE �������m�ہ@=> ���� by Oboe()\n",m);};

	scorefp = fopen(scorefn,"r");fscanf(scorefp,"%d,%s",&linekind,line);//�w�b�_�[�ǂݔ�΂�
	for(i=0;i<m;i++){fscanf(scorefp,"%d,%s",&linekind,line);score_line_sscanf(line,&s[i]);}//�ǂݍ���
	fclose(scorefp);scorefp=NULL;
//////////////////////////////////////////////////�X�R�A�t�@�C���ǂݍ��݊���(�{���Ȃ瑼�̃p�[�g�������܂łœǂݍ��ނׂ�)

//////////////////////////////////��������̑���͂�������

	for(i=0;i<m;i++)
	{
		if(s[i].passage_head==1)//���t���ăw�b�h�L���b�`
		{
			for(j=i,NofPL=1;j!=m-1 && s[j+1].passage_head==0;j++,NofPL++);
//printf("PASSAGE[%d]��[%d]�s��1�Z�b�g by Maker_Oboe()\n",s[i].passage_number,NofPL);
			Maker_Oboe_Passage(s[i].passage_number,&s[i],&x[i],NofPL);
		}
	}
//////////////////////////////////��������̑���͂����܂�

//////////////////////////////////////////////////�ȉ��o��
	tfp = fopen(tfn,"w");for(i=0;i<m;i++){fprintf(tfp,"%d,%d\n",s[i].length,x[i].note);}fclose(tfp);

	free(s);
free(x);

ust_file_out("Oboe",&finf);

	return 0;
}

static int cat_scrap(char *scorefn,char *scrapfn)//�o�͂�TEMP�t�@�C���ɕۑ����čŌ�Ɋm�F���Ă���
{
	//�s���Ɨv���ō����Ă��邩���m�F
	//�ꍇ�ɂ���Ă̓t�@�C�����C��
	//(�A�E�t�^�N�g�ɂ��o�����̕s�m��Ȃǂɂ��)FILE fp;fopen();fclose();
	FILE *scorefp=NULL;
	FILE *scrapfp=NULL;
	FILE *tempfp =NULL;
	char tempfn[FILENAME_MAX]={0};
	
	scorefp = fopen(scorefn,"r");//if(scorefp==NULL){printf("�X�R�A�t�@�C��[%s]��������܂���\n",scorefn);exit(1);}
	scrapfp = fopen(scrapfn,"r");//if(scrapfp==NULL){printf("�X�N���b�v�t�@�C��[%s]��������܂���\n",scrapfn);fclose(scorefp);exit(1);}
	
	fclose(scrapfp);
	fclose(scorefp);

	sprintf("[%s]��TEMP�o��.txt",scrapfn);
	tempfp = fopen(tempfn,"w");
	fclose(tempfp);

	//�����ł����X�R�A�t�@�C�����폜
	//TEMP�����l�[�����ĐV�X�R�A�t�@�C���Ƃ���

	return 0;
}