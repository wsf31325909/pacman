#pragma once
#include "stdafx.h"
#define MAPLENGTH 20
#define INITR 9  //��ʼ��
#define INITA 13 //��ʼ��
#define E_ROW 9
#define E_ARRAY 9
class GMap {
protected:
	static int LD;//ǽ�ڴ�С
	static int PD;//���Ӵ�С
	bool mapData[MAPLENGTH][MAPLENGTH];
	bool peasData[MAPLENGTH][MAPLENGTH];//���ӵ�ͼ
	void initOP();//���ӵ�ͼ�Ż�
	COLORREF color;
public:
	void DrawMap(HDC& hdc);
	void DrawPeas(HDC& hdc);
	

friend class GObject;//����������ʹ��ֱ�ߵ������յ����Ϣ����ײ���
friend class PacMan;
};

class Stage_1 :public GMap {
protected:
	bool initData[MAPLENGTH][MAPLENGTH];
public:
	Stage_1();
};

class Stage_2 :public GMap {
protected:
	bool initData[MAPLENGTH][MAPLENGTH];
public:
	Stage_2();
};
class Stage_3 :public GMap {
protected:
	bool initData[MAPLENGTH][MAPLENGTH];
public:
	Stage_3();
};