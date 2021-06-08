#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char header1[] = {0x4D,0x54,0x68,0x64,0x00,0x00,0x00,0x06,0x00,0x01,0x00,0x01,0x01,0xE0};//�t�@�C���w�b�_
char header2[] = {0x4D,0x54,0x72,0x6B};//�g���b�N�w�b�_
union{char charsize[4];int intsize;}unionsize;

//char partname[] ="Oboe Sm";
char header3[] = {0x00,0xFF,0x03};//���̌�ɃT�C�Y�ƃp�[�g��
char footer[] = {0x00,0xFF,0x2F,0x00};

static unsigned int mypow(unsigned int x,unsigned int y)
{
	unsigned int i,answer=1;
	for(i=0;i<y;i++){answer *= x;}//printf("[%d]��[%d]���[%d]�ł�\n",x,y,answer);
	return answer;
}

static unsigned int mylog(unsigned int x,unsigned int y)
{
	unsigned int i,answer=0;
	for(i=0;i<y;i++){if(mypow(x,i)>y){answer = i-1;break;}}
	//printf("Log(%d,%d) = [%d]\n",x,y,answer);
	return answer;
}

static int IntFileOut(FILE *MidiFp,int x,int HaveParent/*�e�͉����ɂ��Ȃ����ƌ���*/)//127�i�����Ǝv����
{int NofZero;int i;int t;
	unsigned char out;
	unsigned int rest;
	unsigned int bite;//���o�C�g�K�v��(�܂�127�i���ł̌���)

	//printf("\n");printf("X = [%d] �ŌĂяo��\n",x);

	bite = 1 + mylog(128,x);//printf("[%d]�o�C�g�K�v\n",bite);
	if((bite-1)>0){out = x/mypow(128,(bite-1));}else{out = x;}//printf("�擪��[%d]\n",out);
	
	t = mypow(128,(bite-1));
	rest = x - out * t;
	//printf("%d - %d * %d ���",x,out,t);printf("�c���[%d]\n",rest);

	//printf("%d = %d * %d + %d �ɂȂ�͂� => [%d]\n",x,out,t,rest,out*t+rest);
	if(bite==1)
	{


		NofZero = HaveParent-bite;//printf("�e�̗v�� = [%d]\n",HaveParent);
		if(NofZero>0)
		{//printf("[%d]�� 0 �Ŗ��߂�\n",NofZero);
			for(i=0;i<NofZero;i++)
			{
				fputc(0x80,MidiFp);
			}
		}
		fputc(out,MidiFp);
	}
	else if(bite>1)
	{
		out += 0x80;
		NofZero = HaveParent-bite;//printf("�e�̗v�� = [%d]\n",HaveParent);
		if(NofZero>0)
		{//printf("[%d]�� 0 �Ŗ��߂�\n",NofZero);
			for(i=0;i<NofZero;i++)
			{
				fputc(0x80,MidiFp);
			}
		}
		fputc(out,MidiFp);IntFileOut(MidiFp,rest,bite-1);
	}
	return 0;
}

static int PutMidiNote(int MidiNote,int Length,FILE *MidiFp)
{
	static int vel = (0x66);
	//fputc(0x00,MidiFp);//�{��,�����͂����ł��ׂ�(����Ăяo���O�ɂ��ׂ�)
	fputc(0x90,MidiFp);//on
	fputc(MidiNote,MidiFp);
	
	//vel = (vel+4)%(0x66);//�V��
	fputc(vel,MidiFp);
	
	IntFileOut(MidiFp,Length,0);
	fputc(0x80,MidiFp);//off
	fputc(MidiNote,MidiFp);
	
	fputc(vel,MidiFp);//�x���V�e�B�͌Œ�
	
	//fputc(0x00,MidiFp);//�{��,�����͑O�ɂ��ׂ�
	return 0;
}

int MidiFileOut(char *TrackName)
{
	
	typedef struct{int length,note,ok;}MIDI_NOTE;
	MIDI_NOTE *m;
	FILE *InputFp;char InputFn[260];//�x���� -1 �̋l�߂��t�@�C��
	FILE *TempFp;char TempFn[260];
	FILE *MidiFp;char MidiFn[260];
	int i;char x;
	int InputLineNumber;char line[1200];
	
	
	sprintf(InputFn,"%s_BELT.txt",TrackName);
	sprintf(TempFn,"%s_MIDITEMP.c",TrackName);
	sprintf(MidiFn,"%s.mid",TrackName);
	InputFp = fopen(InputFn,"r");
	for(InputLineNumber=0;fscanf(InputFp,"%s",line)>0;InputLineNumber++);
	rewind(InputFp);
	//printf("InputLineNumber = [%d]\n",InputLineNumber);

	m = (MIDI_NOTE*)calloc(InputLineNumber,sizeof(MIDI_NOTE));
	for(i=0;i<InputLineNumber;i++){fscanf(InputFp,"%d,%d,%s",&m[i].length,&m[i].note,line);}
	//for(i=0;i<InputLineNumber;i++){printf("%d,%d\n",m[i].length,m[i].note);}
	for(i=0;i<InputLineNumber;i++){m[i].ok = (m[i].note>=0 && m[i].note<128) ? 1:(-1);}
	fclose(InputFp);

	TempFp = fopen(TempFn,"wb");
	
	for(i=0;i<sizeof(header3);i++){fputc(header3[i],TempFp);}
	fputc(strlen(TrackName),TempFp);
	fprintf(TempFp,"%s",TrackName);
	for(i=0;i<InputLineNumber;i++)
	{
		if(m[i].ok>0)//����ȉ��̏�����
		{
			if(i!=0 && m[i-1].ok<0){IntFileOut(TempFp,m[i-1].length,0);}//1�O�̉����ُ�
			else{IntFileOut(TempFp,0,0);}
			PutMidiNote(m[i].note,m[i].length,TempFp);
		}//else{printf("%s�Ɉُ�ȉ�\n=>�I�����܂�\n",InputFn);exit(1);}
	}
	for(i=0;i<sizeof(footer);i++){fputc(footer[i],TempFp);}
	unionsize.intsize = ftell(TempFp);
	//printf("[%d]�o�C�g�ł�\n",unionsize.intsize);
	fclose(TempFp);
	
	TempFp = fopen(TempFn,"rb");
	MidiFp = fopen(MidiFn,"wb");
	for(i=0;i<sizeof(header1);i++){fputc(header1[i],MidiFp);}
	for(i=0;i<sizeof(header2);i++){fputc(header2[i],MidiFp);}
	for(i=sizeof(int)-1;i>=0;i--){fputc(unionsize.charsize[i],MidiFp);}
	for(i=0;i<unionsize.intsize;i++){x = fgetc(TempFp);fputc(x,MidiFp);}
	fclose(MidiFp);fclose(TempFp);
	free(m);

	//remove(TempFn);
	return 0;
}
