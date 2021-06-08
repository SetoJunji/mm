#define PartsFunction_C
#include "PartsFunction.h"

PART **CreatePart(int n,int NofOP,int MovementID,int PassageID)
{int i;
	PART **x;
	x = (PART**)calloc(n,sizeof(PART*));//�s�����|�C���^�m��
	for(i=0;i<n;i++){x[i] = (PART*)calloc(NofOP,sizeof(PART));}//�e�|�C���^�Ƀ������m��
	LoadSession_Passage(x,NofOP,1,PassageID);
	return x;
}
int DestroyPart(PART **x,int NofOP)
{
	int i;for(i=0;i<NofOP;i++){free(x[i]);x[i]=NULL;}
	free(x);x=NULL;
	return 1;
}
int IsWhite(int note,int key)
{
	switch(note%12)
	{
	case 0:case 2:case 4:case 5:case 7:case 9:case 11:return (1);
	default:return (-1);
	}
}
int NearWhite(int note,int whitefile,int pm)//�D�݂̃X�P�[���ł����񂶂�Ȃ�?
{
	int key;int x,y;for(x=note,y=(pm>0)?1:-1;IsWhite(x,key)<0;x+=y);
	return x;
}

FILE *WaveFileOpen(int n,int WaveID)// n �̋l�߂��g�̃t�@�C�����o��
{
	//�g����悤�ɉ��悪�y��ɂ���ĈႤ���Ƃ���PRE�͔ėp�����Ⴂ
	//�ω����o�������ꏊ���珑�������邱�Ƃ��l����Ǝn�܂�̑O�̉��v���X�}�C�i�X�̕�������
	int i;typedef struct{int pm;}WAVE;WAVE *w;
	FILE *wavefp;char wavefn[FILENAME_MAX];
	sprintf(wavefn,"WAVE_%d_%d.txt",n,WaveID);//���̃p�[�g�Ƌ��ʂ̖��O���g���Ȃ�
	wavefp = fopen(wavefn,"r");
	if(wavefp==NULL)
	{
		wavefp = fopen(wavefn,"w");
		w = (WAVE *)calloc(n,sizeof(WAVE));
		for(i=0;i<n;i++){w[i].pm = (rand()%2==0) ? 1:-1;if(i==0){w[i].pm = 0;}}
		for(i=0;i<n;i++){fprintf(wavefp,"%d\n",w[i].pm);}
		free(w);
		fclose(wavefp);
		wavefp = fopen(wavefn,"r");
	}
	return wavefp;
}

CHILDREN_SIDE *CreateCside(int n,int MasterNumber)
{
	CHILDREN_SIDE *cside=NULL;
	cside = (CHILDREN_SIDE *)calloc(n,sizeof(CHILDREN_SIDE));
	fill_children_side(MasterNumber,cside,n);
	return cside;
}
static FILE *PassageOpen(int PassageID)
{
	FILE *fp;char fn[260];
	switch(PassageID)
	{
	case 1:sprintf(fn,"PASSAGE[�O�t].txt");break;
	case 2:sprintf(fn,"PASSAGE[A����].txt");break;
	case 3:sprintf(fn,"PASSAGE[B����].txt");break;
	case 4:sprintf(fn,"PASSAGE[�T�r].txt");break;
	case 5:sprintf(fn,"PASSAGE[�ԑt].txt");break;
	case 6:sprintf(fn,"PASSAGE[��t].txt");break;
	default:printf("\n�s���Ȋy��ID = [%d]\n�I�����܂�\n",PassageID);exit(1);break;
	}
	fp = fopen(fn,"r");
	if(fp==NULL){printf("[%s]��������܂��� by PassageOpen()\n�I�����܂�\n",fn);exit(1);}
	//else{printf("[%s]���J���܂� by PassageOpen()\n",fn);}
	return fp;
}
int balance(int MasterID,int pre)//��̂̒l�������ɂ��Đ��m�Ȓl��Ԃ�
{
	typedef struct{int ChildID;int NofATK;}CHILD;CHILD *c;
	int i;int x = 0;MASTERFORMAT m;
	FILE *masterfp;
	masterfp = masteropen(MasterID);m = master_fscanf(masterfp);
	c = (CHILD*)calloc(m.linenumber,sizeof(CHILD));
	if(m.linenumber==0)
	{
		//printf("�q������ X = [%d] by balance()\n",pre);
		return pre;
	}
	for(i=0;i<m.linenumber;i++){fscanf(masterfp,"%d",&c[i].ChildID);}
	for(i=0;i<m.linenumber;i++){c[i].NofATK = (i%2==0) ? (pre/3):(pre/6);if(m.linenumber==2)c[i].NofATK *=2;}//��̂̒l�𒍗�
	for(i=0;i<m.linenumber;i++){c[i].NofATK = balance(c[i].ChildID,c[i].NofATK);x += c[i].NofATK;}//���m�Ȓl�ɕύX
	free(c);fclose(masterfp);
printf("�A�^�b�N��(���)[%d] �ɑ΂��� �A�^�b�N��(���m)[%d] by balance()\n",pre,x);
	return x;
}

int LoadMovementInfo(FORMAT_MOVEMENT *dest,int MovementID)
{
	FILE *MovementFp;char MovementFn[260];MovementFp = fopen(MovementFn,"r");fclose(MovementFp);
	return 1;
}

int UnloadMovementInfo(FORMAT_MOVEMENT *x){return 0;}

int LoadPassageInfo(FORMAT_PASSAGE *dest,int PassageID)
{
	FILE *Passagefp;
	Passagefp = PassageOpen(PassageID);
	*dest = passage_fscanf(Passagefp);
	fclose(Passagefp);
	return 1;
}

int LoadMasterInfo(MASTERFORMAT *dest,int MasterID)//����œ��I�m�ۂ����ꍇ CHILDNUMBER �����܂��Ă���̂�UNLOAD�֐����ĂԂ���
{
	int i;
	FILE *MasterFp;
	//printf("LoadMasterInfo(%d)�J�n\n",MasterID);
	MasterFp = masteropen(MasterID);
	*dest = master_fscanf(MasterFp);
	dest->ChildID = (int*)calloc(dest->linenumber,sizeof(int));//����͓��I�m��
	for(i=0;i<dest->linenumber;i++){fscanf(MasterFp,"%d",&(dest->ChildID[i]));}
	fclose(MasterFp);
	//printf("LoadMasterInfo(%d)�I��\n",MasterID);
	return 0;
}

int UnloadMasterInfo(MASTERFORMAT *x)//��n���֐�
{free(x->ChildID);return 0;}
