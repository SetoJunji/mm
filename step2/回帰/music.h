#ifndef MUSIC_H
#define MUSIC_H
#include <bits/stdc++.h>
typedef struct{int dia,kind;}CHORD;//root�𑫂��ׂ�!?
#define CHORD_KIND_M       1
#define CHORD_KIND_m       2
#define CHORD_KIND_aug     3
#define CHORD_KIND_dim     4
#define CHORD_KIND_6       5
#define CHORD_KIND_m6      6
#define CHORD_KIND_maj7    7
#define CHORD_KIND_mmaj7   8
#define CHORD_KIND_7       9
#define CHORD_KIND_m7     10
#define CHORD_KIND_7aug   11
#define CHORD_KIND_7f5    12
#define CHORD_KIND_m7aug  13
#define CHORD_KIND_m7f5   14
#define CHORD_KIND_sus4   15
#define CHORD_KIND_7sus4  16

#ifndef MUSIC_C
extern int IsChordTone(int ust,CHORD *chord);
extern int NearChordTone(int base,int key,int updown,CHORD *chord,int interval);//����֗�����
//extern int RandChordTone(CHORD *chord);//<=���ꂾ�Ƃǂ̉��悩������Ȃ��̂Ŗ��ɗ����Ȃ�
#endif
#endif
