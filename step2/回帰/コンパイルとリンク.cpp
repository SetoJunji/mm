/*
#include <stdio.h>
#include "PASSAGE.h"
#include "UST.h"
//������t���鎞�Ƀc���[�\�������߃v���O�������c������K�v������ȏ�,
//�����ł̍�Ƃ� READER() ���ɂȂ�
//��������t�@�C����UST�ɋ߂��`�ɂȂ�
//���_�͉��������Ȃ���Ԃ��}�X�^�[�t�@�C���Ƃ��ėǂ����Ƃ�������
//���̃p�[�g���ǉ��ł���悤�ɂ��邽�߂ɂ͍Œ�R�[�h�͉����������Ă����K�v������
//���_�F�R�[�h�����̓}�X�^�[�t�@�C���ł��Ă���!!
//�R���p�C���ƃ����J�͊e�y�했�ɂ��ꂼ���������ƂɂȂ�?
//���̃t�@�C���͖{���͓Ɨ����� main() �������ƂɂȂ�̂�,
//�{����main()��main2()�Ƃ��ɂ��ăr���h���邱��(��ƃf�B���N�g�����ς��邱��)


static FILE *outfp = NULL;
static char *outfn = "�M�^�[.ust";

int guitar_passage_compiler(char *beforefn,char *afterfn)//1�̊y�߃t�@�C�����R���p�C��//�{���͂��̊֐��ŉ��������߂�
{
	int i;
	int head;
	int tubunum;
	typedef struct{int note,length;}TUBU;
	TUBU *x;

	char cmd[1280];
	int length=-1,note=-1;
////////////////�ʎq��
	//int t = 0;
	FILE *ryofp;
	char *ryofn = "�ʎq��.txt";
////////////////

////////////////���炩��
	int t = 0;
	FILE *ngfp;
	char *ngfn = "���炩��.txt";

	FILE *nfp;
	char *nfn = "���炩.txt";
	int c = 0;
////////////////

	FILE *kaikifp = NULL;char *kaikifn = "��A�o��.txt";

	FILE *beforefp=NULL,*afterfp=NULL;
	FORMAT_PASSAGE pinf;
	extern FORMAT_PASSAGE passage_fscanf(FILE*);
	extern int reader_kaiki(FILE*,int);
	extern int q(char*,int);
	extern int nameraka(int,int,int);

//printf("\nBEFORE_FILENAME\n%s\n\n",beforefn);
//printf("\nAFTER_FILENAME\n%s\n\n",afterfn);


	beforefp = fopen(beforefn,"r");if(beforefp==NULL){printf("[%s]��������܂���\n",beforefn);return (-1);}
	else{pinf = passage_fscanf(beforefp);fclose(beforefp);}
	
	kaikifp = fopen(kaikifn,"w");//if(kaikifp==NULL){printf("[%s]���J���܂���\n");return (-1);}
	reader_kaiki(kaikifp,pinf.masterfile);
	fclose(kaikifp);kaikifp = NULL;

	
	
////////////////�ʎq��

	q(kaikifn,(1920/4));
	afterfp = fopen(afterfn,"w");
	ryofp = fopen(ryofn,"r");
	t = tubunum = 0;
	while(fscanf(ryofp,"%d,%d,%s",&head,&note,cmd)>0)
	{t++;
		if(head>0){fprintf(afterfp,"%d,%d\n",head*(1920/4),note);tubunum++;}
	}fclose(ryofp);
//printf("%d�s�� %d�̉�������܂�\n",t,tubunum);
	fclose(afterfp);afterfp = NULL;

//printf("�I��2\n");exit(1);


nameraka(tubunum,60,60);
x = (TUBU*)calloc(tubunum,sizeof(TUBU));if(x==NULL){printf("�������m�ۂɎ��s���܂���\n");exit(1);}
nfp = fopen(nfn,"r");if(nfp==NULL){printf("[%s]��������܂���\n",nfn);exit(1);}
for(i=0;i<tubunum;i++){fscanf(nfp,"%d,%d",&t,&x[i].note);}
fclose(nfp);nfp = NULL;
////////////////////////////////////
afterfp = fopen(afterfn,"r");
for(i=0;i<tubunum;i++){fscanf(afterfp,"%d,%d\n",&x[i].length,&t);}
fclose(afterfp);afterfp = NULL;




////////////////////////////////////
//for(i=0;i<tubunum;i++){printf("N = %d,L = %d\n",x[i].note,x[i].length);}

afterfp = fopen(afterfn,"w");
if(afterfp==NULL){printf("�t�@�C���쐬�Ɏ��s���܂���\n");exit(1);}
for(i=0;i<tubunum;i++){fprintf(afterfp,"%d,%d\n",x[i].length,x[i].note);}
fclose(afterfp);afterfp = NULL;

free(x);return 0;
}

int guitar_passage_linker(char *kyokuhennseifn)//�R���p�C����̊y�߃t�@�C���������Ȃ���1�Ȃ�
{
	extern int ust_file_out(char *,USTFILEINFO *);
	
	USTFILEINFO finf = {120,1};
	int c=0;
	char line[1280];
	
char *testfn = "GUITAR.txt";	
	FILE *testfp = NULL;
	
	FILE *cpfp;
	char cpfn[128];
	
	FILE *pfp;
	char pfn[128];
	FILE *khfp;

	printf("GUITAR[%s]�����N���܂�\n",kyokuhennseifn);
	
	testfp = fopen(testfn,"w");
	khfp = fopen(kyokuhennseifn,"r");
	while(fscanf(khfp,"%s",pfn)>0)
	{
		sprintf(cpfn,"GUITAR[%d].txt",c++);
		
//printf("[%s]�R���p�C���O\n",cpfn);
		guitar_passage_compiler(pfn,cpfn);
//printf("[%s]�R���p�C����\n",cpfn);

//���͍�������΂���ڍ��J�n
cpfp = fopen(cpfn,"r");
if(cpfp==NULL){printf("[%s]��������܂���\n",cpfn);}
//else{printf("[%s]���J���܂�\n",cpfn);}
while(fscanf(cpfp,"%s",line)>0)
{fprintf(testfp,"%s\n",line);}
fclose(cpfp);
//�ڍ��I��

	}
fclose(testfp);
	fclose(khfp);




	
ust_file_out("GUITAR",&finf);

	return 0;
}
*/
