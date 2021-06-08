//�t�H�[�}�b�g�\���̂ƃ����o�[���̒�`
//�t�@�C������1�s�ǂ�ō\���̂�Ԃ��֐�
//�\���̂�ǂ�Ńt�@�C����1�s�o�͂���֐�
//�}�X�^�[�i���o�[���������ɂ��ă{�[�_�[�̌��J�E���g�����A�ďo�֐�
//���g�����֐�
//�e�̃}�C�i���o�[,����,�t���[�Y,���g,�R�[�h,���g,�A�N�Z���g => f[6] �Ƃ���(�\���̂ɂ��Ă��̂܂�܂̏��ŏ������ނׂ�)
//�w�b�_�[����2�s(1�t�H�[�}�b�g,2����)
//�ȉ��͏���

#define MASTERFILEC
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "masterfile.h"
#include "PASSAGE.h"

int newmynumber(void);

const char *master_header_string = "�e�̃i���o�[,����,CB,P,AB,P,RB,P,�s��,�y��,�����ʒu(AA'BC),���ߐ�,��������,1�������̒���,BAR�v���p�e�B,JOINT,���߂̓�������,BAR�t�@�C��,CHORD�t�@�C��,RHYTHM�t�@�C��\n";

int NewMasterMake(FORMAT_PASSAGE *passage)/*�ŏ��ɏ����̃t�@�C����V�K�쐬��1,�쐬���Ȃ����(-1)*/
{
	int *intpointer;
	int i;MASTERFORMAT m;
	
	int masternumber;//passage->NofBar = ;passage->count = ;passage->size = ;
	FORMAT_PASSAGE p;
	int linen = 2;
	FILE *fp;
	char fn[128];

	p = *passage;masternumber = p.masterfile;
	sprintf(fn,"MASTER_%d.txt",masternumber);
	for(i=0,intpointer = (int*)&m;i<sizeof(MASTERFORMAT)/sizeof(int);i++,intpointer++){*intpointer = (i>7) ? (-1):0;}
	
	fp = fopen(fn,"r");
	if(fp!=NULL){fclose(fp);return (-1);}
	else
	{
		fp = fopen(fn,"w");
		fprintf(fp,"%s",master_header_string);

		m.length = p.length;
		m.linenumber = linen;
		m.count = p.count;
		m.size = p.size;
		
		m.NofBar = p.NofBar;
		m.passage = p.kind;
		m.position = 1;

		m.auftaktID = p.auftaktID;
		m.Unit = p.Unit;
		m.CoreID = p.CoreID;
		
		master_fprintf(fp,&m);
		fclose(fp);
		return 1;
	}
}

MASTERFORMAT childini(MASTERFORMAT *parent)//�e��HEADER��񂩂猈��o����q����HEADER��Ԃ�
{
	MASTERFORMAT child = {0},x;
	x = *parent;

	if(x.linenumber<=0){printf("LINENUMBER = %d �Ŏq����ݒ肵�悤�Ƃ���Ƃ�!! by childini()\n");exit(1);}

	child.accent_border_painted = x.accent_border_painted;
	child.chord_border_painted = x.chord_border_painted;
	child.rythm_border_painted = x.rythm_border_painted;

	child.length = x.length / x.linenumber;
	
	
	if(child.accent_border_painted>0 && child.chord_border_painted>0 && child.rythm_border_painted>0){child.linenumber = 0;}//���R�Ȃ���S�Č���ς݂̃t�@�C���͎q��������Ă͂����Ȃ�
	else{child.linenumber = 2;}

	child.passage = x.passage;

	child.NofBar = x.NofBar / x.linenumber;
	child.count = x.count / x.linenumber;
	child.size = x.size;

	return child;
}

FILE *masteropen(int masterfilenumber)
{
	char cut[1280];
	FILE *fp;
	char fn[128];
	sprintf(fn,"MASTER_%d.txt",masterfilenumber);
	fp = fopen(fn,"r");
	if(fp==NULL){printf("%s��������܂���!!\n",fn);exit(1);}
	fscanf(fp,"%s",cut);
	return fp;
}

MASTERFORMAT master_fscanf(FILE *masterfp)
{
	MASTERFORMAT x;

	


	fscanf(masterfp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d"
		,&x.parent
		,&x.length
		
		,&x.chord_border_file,&x.chord_border_painted
		,&x.accent_border_file,&x.accent_border_painted
		,&x.rythm_border_file,&x.rythm_border_painted

		,&x.linenumber
		,&x.passage,&x.position
		,&x.NofBar,&x.count,&x.size
		,&x.barpropaty,&x.joint

		,&x.barhead
		,&x.file_bar
		,&x.file_chord
		,&x.file_rhythm
		,&x.auftaktID,&x.Unit,&x.CoreID);
	return x;
}
//barhead,file_bar,file_chord,file_rhythm

int master_fprintf(FILE *masterfp,MASTERFORMAT *source)
{//NofBar,count,size;
	
	MASTERFORMAT x;
	x = *source;
	fprintf(masterfp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"
		,x.parent
		,x.length
		
		,x.chord_border_file,x.chord_border_painted
		,x.accent_border_file,x.accent_border_painted
		,x.rythm_border_file,x.rythm_border_painted
		
		,x.linenumber
		,x.passage
		,x.position
		,x.NofBar,x.count,x.size
		,x.barpropaty,x.joint

		,x.barhead
		,x.file_bar
		,x.file_chord
		,x.file_rhythm
		,x.auftaktID,x.Unit,x.CoreID);
	return 0;
}

int writer_kaiki(int mynumber)//�}�X�^�[�t�@�C���̉�A�ďo�쐬
{
	int should_make_cb = 0;
	int should_make_ab = 0;
	int should_make_rb = 0;

	extern int map(int);
	
	MASTERFORMAT myinf;
	MASTERFORMAT cinf[3];
	int i = 0;
	struct CHILDREN
	{
		int cmynumber;
		FILE *cmylifefp;
		char cmylifefn[128];
	}children[3];//children[2];
	//int cnumber = 2;//�q�̐l������ 2
	int cnumber = 3;//�q�̐l������ 3
	FILE *mylifefp;
	char mylifefn[128] = {0};

	mylifefp = masteropen(mynumber);myinf = master_fscanf(mylifefp);fclose(mylifefp);

	if(myinf.linenumber==2){cnumber = 1;}if(myinf.linenumber==4){cnumber = 3;}


	//if(myinf.length <400){return 0;}//�{���͑S�Č���ς݂ɂȂ��Ă���return�ɂ��ׂ�
	if((myinf.chord_border_painted==1)&&(myinf.accent_border_painted==1)&&(myinf.rythm_border_painted==1)){return 0;}


	for(i=0;i<cnumber;i++)/*�q���(�������㏉���ݒ�)*/
	{
		cinf[i] = childini(&myinf);
		cinf[i].parent = mynumber;
		children[i].cmynumber = newmynumber();
		sprintf(children[i].cmylifefn,"MASTER_%d.txt",children[i].cmynumber);
	}
	
	for(i=0;i<cnumber;i++)/*�q���(��������e��l�ݒ�)*/
	{
		if(cinf[i].chord_border_painted ==1){should_make_cb = 0;}else{should_make_cb = ((rand()%100>20) || myinf.NofBar<=4) ? 1:0;}
		if(cinf[i].accent_border_painted==1){should_make_ab = 0;}else{should_make_ab = ((rand()%100>50) || myinf.NofBar<=4) ? 1:0;}
		if(cinf[i].rythm_border_painted ==1){should_make_rb = 0;}else{should_make_rb = ((rand()%100>30) || myinf.NofBar<=2) ? 1:0;}
		if(should_make_cb==1){cinf[i].chord_border_file = newmynumber();cinf[i].chord_border_painted = 1;}
		if(should_make_ab==1){cinf[i].accent_border_file= newmynumber();cinf[i].accent_border_painted= 1;}
		if(should_make_rb==1){cinf[i].rythm_border_file = newmynumber();cinf[i].rythm_border_painted = 1;}
		if(cinf[i].chord_border_painted==1 && cinf[i].accent_border_painted==1 && cinf[i].rythm_border_painted==1)
		{
			//printf("�S�ēh���������܂��� by writer_kaiki()\n");
			cinf[i].linenumber = 0;
		}
	}


///////////////////////////////////////////�ȉ��q�����̕K�v���������g�ɒǉ�LINE�������݊J�n
	sprintf(mylifefn,"MASTER_%d.txt",mynumber);
	mylifefp = fopen(mylifefn,"a");if(mylifefn==NULL){printf("�t�@�C��[%s]��������܂���!!\n",mylifefn);exit(1);}
	if(myinf.linenumber==2)//���� A A'
	{cinf[0].position = 1;cinf[1].position = 1;cinf[0].CoreID = myinf.CoreID;cinf[0].Unit = myinf.Unit;
		fprintf(mylifefp,"%d\n%d\n"
			,children[0].cmynumber
			,children[0].cmynumber);
	}
	if(myinf.linenumber==4)//A B A C//linenumber��length���画�f����
	{
		cinf[0].position=1;
		cinf[1].position=2;
		cinf[2].position=3;

		fprintf(mylifefp,"%d\n%d\n%d\n%d\n"
			,children[0].cmynumber
			,children[1].cmynumber
			,children[0].cmynumber
			,children[2].cmynumber);
	}
	fclose(mylifefp);
	
	for(i=0;i<cnumber;i++)/*�q���(���ۂɎq���B�쐬 & HEADER��������)*/
	{//���̎��_�Ŏq���B��CB�Ƃ��͌��܂��Ă��܂�
		children[i].cmylifefp = fopen(children[i].cmylifefn,"w");
		fprintf(children[i].cmylifefp,"%s",master_header_string);
		//fprintf(children[i].cmylifefp,"�e�̃i���o�[,����,CB,P,AB,P,RB,P,�s��,�y��,�����ʒu(AA'BC),���ߐ�,��������,1�������̒���\n");
		master_fprintf(children[i].cmylifefp,&cinf[i]);
		fclose(children[i].cmylifefp);
	}
	
	
	for(i=0;i<cnumber;i++){writer_kaiki(children[i].cmynumber);}
	return 0;
}

int fill_children_side(int masterfilenumber,CHILDREN_SIDE *dest,int n)//�}�X�^�[�t�@�C�����g���֐��ɂ͕֗�����
{
	MASTERFORMAT m,c;int x;CHILDREN_SIDE non={-1,-1,-1};//���̏�����,��Ŗ��ɂȂ�?(-1)�̂ق�������?
	//int x=(-1);//�ꖇ��Ȃ�S������������
	int i,j;FILE *masterfp=NULL,*childfp=NULL;
	masterfp = masteropen(masterfilenumber);m = master_fscanf(masterfp);
	//if(n!=m.count){printf("\n\nfill_children_side()\n[%d] <= m.count\n[%d] <= n (����)\n�I�����܂�\n\n",m.count,n);exit(1);}
	if(m.linenumber==0){for(i=0;i<n;i++){dest[i] = non;}return (-1);}
	for(i=0;i<n;i++)
	{if(m.linenumber==0 || (n/m.linenumber)==0){printf("0 �Ŋ��낤�Ƃ��Ă� N = [%d],L = [%d]\n�I�����܂� by fill_children_side()\n",n,m.linenumber);exit(1);}
		if(i%(n/m.linenumber) ==0){fscanf(masterfp,"%d",&x);//printf("X = [%d]\n",x);
		dest[i].c_head = 1;dest[i].have_more_children = 1;
		}
		dest[i].c_file = x;
	}
	for(i=0;i<n;i++)
	{
		if(dest[i].c_head==1)//�w�b�h�L���b�`
		{
			childfp = masteropen(dest[i].c_file);c = master_fscanf(childfp);if(c.linenumber>0){dest[i].have_more_children = 1;}
			fclose(childfp);
			for(j=i;j<n;dest[i].c_head++,j++){if(j==n-1 || dest[j+1].c_head>0)break;}//���͂���,����Ȃɓ�����Ƃł͂Ȃ�
		}
	}
	fclose(masterfp);masterfp = NULL;return 1;
}