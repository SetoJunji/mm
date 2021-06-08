
//int nameraka()�̂݊O������A�N�Z�X�\

#define NAMERAKA_C
#include "nameraka.h"

static int RandInRange(int a,int b);
static int rerativeUST(int base,int key,int pm/*�v���X�}�C�i�X*/);
static int USTtoDIA(int ust,int key);
static int whitepm(int ustA,int ustB,int key);//B���傫����ΐ�
static int FillList_WAVE(LIST *list,int n,int start,int end);//n�̉�(WAVE�͔����ōl����)
static int FillList_UST(LIST *list,int n,int start,int end);
int nameraka(int n,int s,int e);//n��UST�ōl����

static int RandInRange(int a,int b)
{
	int x;
	int low,high,gap;
	if(a==b)return a;
	if(a>b){high = a;low = b;}
	else{high = b;low = a;}
	gap = (high-low);
	x = rand()%(gap+1);
	x+=low;
	return x;
}

static int rerativeUST(int base,int key,int pm/*�v���X�}�C�i�X*/)
{

	int updown;
	int i;
	int ust;
	int n;//N��㉺����
	
	if(key!=0){printf("���̓g�����̂�\n");}
	
	if(pm>0){n = pm;updown = 1;}
	else if(pm<0){n = -pm;updown = -1;}
	else{return base;}

	ust = base;
	for(i=0;i<n;i++)
	{
		while(1)
		{
			ust += updown;
			if(USTtoDIA(ust,key) > 0){break;}
		}
	}
	return ust;
}

static int USTtoDIA(int ust,int key)
{
	int x = (-1);
	
	if(key!=0){printf("���̓g�����̂�\n");}
	
	switch(ust%12)
	{
	case 0:/*C*/x = 1;break;
	case 1:/*C#*/break;
	case 2:/*D*/x = 2;break;
	case 3:/*D#*/break;
	case 4:/*E*/x = 3;break;
	case 5:/*F*/x = 4;break;
	case 6:/*F#*/break;
	case 7:/*G*/x = 5;break;
	case 8:/*G#*/break;
	case 9:/*A*/x = 6;break;
	case 10:/*A#*/break;
	case 11:/*B*/x = 7;break;
	default:break;
	}
	return x;
}

static int whitepm(int ustA,int ustB,int key)//B���傫����ΐ�
{
	int x=0;
	int i;
	if(ustA < ustB)
	{
		for(i=ustA+1;i<=ustB;i++){if(USTtoDIA(i,key)>0){x++;}}
		return x;
	}
	else if(ustA > ustB)
	{
		for(i=ustB+1;i<=ustA;i++){if(USTtoDIA(i,key)>0){x++;}}
		return (-x);
	}else{return 0;}
}

static int FillList_WAVE(LIST *list,int n,int start,int end)//n�̉�(WAVE�͔����ōl����)
{
	int i,w;
	int key = 0;
	int kai;if(end>start){for(i=0;i<whitepm(start,end,key);i++){list[RandInRange(1,n-1)].wave += 1;}}
	else if(end<start){for(i=0;i<whitepm(end,start,key);i++){list[RandInRange(1,n-1)].wave -= 1;}}//���2�s�Ő�ɒi�̍��𖄂߂Ă���
kai = n/2;//�ЂƂ܂�
//printf("%d�񍷂�����\n",kai);
	for(i=0;i<kai;i++){w = RandInRange(1,2);list[RandInRange(1,n-1)].wave += w;list[RandInRange(1,n-1)].wave -= w;}return 0;
}

static int FillList_UST(LIST *list,int n,int start,int end)
{
	int i,w;
	list[0].ust = start;

	for(i=1;i<n;i++){list[i].ust = rerativeUST(list[i-1].ust,0,list[i].wave);}
	
	if(list[n-1].ust != end)
	{
		printf("UST����G���[�ł�!(%d != %d)\n",list[n-1].ust,end);
		//���̂Ƃ��Ӓn�ł�UST��END�������ׂ���?���̏ꍇ�ɂ͔��[�ȃY���͍Ō�̉��ł��������Ȃ�
	}
	return 0;
}

int nameraka(int n,int s,int e)//n��UST�ōl����
{FILE *fp;char *fn = "���炩.txt";
	int i;
	LIST *list;
	list = (LIST*)calloc(n,sizeof(LIST));
//printf("%d�̉���%d��%d�����炩�Ɍq��WAVE,UST\n",n,s,e);
//printf("���͔���%d���ł�\n",whitepm(s,e,0));

	FillList_WAVE(list,n,s,e);
	FillList_UST(list,n,s,e);
fp = fopen(fn,"w");
for(i=0;i<n;i++){fprintf(fp,"%d,%d\n",list[i].wave,list[i].ust);}
fclose(fp);
	free(list);
	return 0;
}

//int main(){srand(time(0));nameraka(5,69,69);return 0;}