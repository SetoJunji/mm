#define MUSIC_C
#include "MUSIC.h"
#include <stdlib.h>

int IsChordTone(int ust,CHORD *chord)//�m���R�[�h�g�[����(-1)��Ԃ��֐�
{//dia=7�͖��
	//���̊֐��̓R�[�h�g�[���ō�������̍���Ԃ�
	//�܂蓯���Ȃ� 0 ���Ԃ��킯��,
	//�ǂ��炩�Ƃ����΃m���R�[�h�g�[����(-1)��Ԃ��Ƃ����F����

	int interval;//���͓K����3�x��Ԃ��Ă���
	int myroot;//0-11�ň����̃R�[�h�̍���
	switch(chord->dia)
	{
	case 1:case 4:case 5:
		if(chord->kind!=CHORD_KIND_M){
			//printf("���̎��_��[%d,%d]������Ă���Ȃ�Ă��蓾�Ȃ��񂾂��ǂ� by IsChordTone()\n",chord->dia,chord->kind);
		}break;}
	switch(chord->dia)
	{
	case 2:case 3:case 6:
		if(chord->kind!=CHORD_KIND_m){
			//printf("���̎��_��[%d,%d]������Ă���Ȃ�Ă��蓾�Ȃ��񂾂��ǂ� by IsChordTone()\n",chord->dia,chord->kind);
		}break;}
	switch(chord->dia)
	{
	case 7:
		if(chord->kind!=CHORD_KIND_dim){
			//printf("���̎��_��[%d,%d]������Ă���Ȃ�Ă��蓾�Ȃ��񂾂��ǂ� by IsChordTone()\n",chord->dia,chord->kind);
		}break;}
	if(chord->dia >0)
	{
		//printf("IsChordTone(%d,%d)\n",ust,chord->dia);
		switch(chord->dia)
		{
		case 1:myroot =  0;break;
		case 2:myroot =  2;break;
		case 3:myroot =  4;break;
		case 4:myroot =  5;break;
		case 5:myroot =  7;break;
		case 6:myroot =  9;break;
		case 7:myroot = 11;break;
		default:printf("�ُ��DIA = [%d]\n�I�����܂�\nby IsChordTone()\n",chord->dia);exit(1);
			myroot= -1;break;
		}//1-7���[�h�Ȃ̂�0-11���[�h�ɐ؂�ւ�
	}
	//else{0-11���[�h;myroot = chord->root;}
	
	/*
	printf("\nUST[%d]��",ust);
	switch(ust%12)//���̕\�����Ƃ��ƕ֗�
	{
	case 0:printf("[C]\n");break;
	case 1:printf("[Des]\n");break;
	case 2:printf("[D]\n");break;
	case 3:printf("[Es]\n");break;
	case 4:printf("[E]\n");break;
	case 5:printf("[F]\n");break;
	case 6:printf("[Fis]\n");break;
	case 7:printf("[G]\n");break;
	case 8:printf("[As]\n");break;
	case 9:printf("[A]\n");break;
	case 10:printf("[B]\n");break;
	case 11:printf("[H]\n");break;
	default:printf("�ُ��UST = [%d]\n�I�����܂�\nby IsChordTone()\n",ust);exit(1);
	}
	*/
	interval = ((12+ust%12)-myroot) % 12;//myroot=11�͖��
	
	//printf("U,R = [%d,%d]\n",ust,myroot);
	/*
	printf("INTERVAL = [%d] �܂� => ",interval);
	switch(interval)
	{
	case 0:printf("���S1�x\n");break;
	case 1:printf("�Z2�x\n");break;
	case 2:printf("��2�x\n");break;
	case 3:printf("�Z3�x\n");break;
	case 4:printf("��3�x\n");break;
	case 5:printf("���S4�x\n");break;
	case 6:printf("��4�x\n");break;
	case 7:printf("���S5�x\n");break;
	case 8:printf("�Z6�x\n");break;
	case 9:printf("��6�x\n");break;
	case 10:printf("�Z7�x\n");break;
	case 11:printf("��7�x\n");break;
	default:printf("�Ӗ��s���� INTERVAL = [%d]\n���f���o�邺!!\n",interval);exit(1);
		break;
	}
	*/

	//if(chord->dia==7)printf("interval = [%d]\n",interval);

	switch(chord->kind)
	{
	case CHORD_KIND_M:if(interval==0 || interval==4 || interval==7){return interval;}else{break;}
	case CHORD_KIND_m:if(interval==0 || interval==3 || interval==7){return interval;}else{break;}
	case CHORD_KIND_aug:if(interval==0 || interval==4 || interval==8){return interval;}else{break;}
	case CHORD_KIND_dim:if(interval==0 || interval==3 || interval==6){return interval;}else{break;}
	case CHORD_KIND_6:if(interval==0 || interval==4 || interval==7 || interval==9){return interval;}else{break;}
	case CHORD_KIND_m6:if(interval==0 || interval==3 || interval==7 || interval==9){return interval;}else{break;}
	case CHORD_KIND_maj7:if(interval==0 || interval==4 || interval==7 || interval==11){return interval;}else{break;}
	case CHORD_KIND_mmaj7:if(interval==0 || interval==3 || interval==7 || interval==11){return interval;}else{break;}
	case CHORD_KIND_7:if(interval==0 || interval==4 || interval==7 || interval==10){return interval;}else{break;}
	case CHORD_KIND_m7:if(interval==0 || interval==3 || interval==7 || interval==10){return interval;}else{break;}
	case CHORD_KIND_7aug:if(interval==0 || interval==4 || interval==8 || interval==10){return interval;}else{break;}
	case CHORD_KIND_7f5:if(interval==0 || interval==4 || interval==6 || interval==10){return interval;}else{break;}
	case CHORD_KIND_m7aug:if(interval==0 || interval==4 || interval==8 || interval==10){return interval;}else{break;}
	case CHORD_KIND_m7f5:if(interval==0 || interval==4 || interval==6 || interval==10){return interval;}else{break;}
	case CHORD_KIND_sus4:if(interval==0 || interval==5 || interval==7){return interval;}else{break;}
	case CHORD_KIND_7sus4:if(interval==0 || interval==5 || interval==7 || interval==10){return interval;}else{break;}
	default:
		printf("�Ӗ��s���� CHORD_KIND = [%d]\n���f���o�邺!!\n",chord->kind);
		printf("�I�����܂�\n");exit(1);
		break;
	}
	return (-1);
}

int NearChordTone(int base,int key,int updown,CHORD *chord,int interval)//interval==1�ō�����Ԃ�
{int x;
	//���� interval>0 �Ȃ烊�N�G�X�g�ɉ�����ׂ�
	//if(dia>0){1-7���[�h;}else{0-11���[�h;}
	int i,ust,pm;pm = (updown>0)?1:-1;ust = base;//printf("NearChordTone(�J�n)\n");
	for(i=0;i<24;i++)
	{
		x = IsChordTone(ust,chord);//printf("x=[%d] => " ,x);
		if(x==0 && interval==1){
			//printf("����[%d]��Ԃ��܂� by NearChordTone(%d,%d)\n",ust,chord->dia,interval);
			return ust;}
		else if(x==7 && interval==5){
			//printf("5��[%d]��Ԃ��܂� by NearChordTone(%d,%d)\n",ust,chord->dia,interval);
			return ust;}
		else if(((x==3&&chord->kind==CHORD_KIND_m)||(x==4&&chord->kind==CHORD_KIND_M)) && interval==3)
		{
			//printf("5��[%d]��Ԃ��܂� by NearChordTone(%d,%d)\n",ust,chord->dia,interval);
			return ust;}
		else if(x>=0 && interval<=0){
			//printf("���ƂȂ�[%d]��Ԃ��܂� by NearChordTone(%d,%d,%d)\n",ust,chord->dia,chord->kind,interval);
			return ust;}
		else{ust += pm;}
	}
	return (-1);
}