#pragma once
#include "stdafx.h"
#define MAPLENGTH 20
#define INITR 9  //初始列
#define INITA 13 //初始行
#define E_ROW 9
#define E_ARRAY 9
class GMap {
protected:
	static int LD;//墙壁大小
	static int PD;//豆子大小
	bool mapData[MAPLENGTH][MAPLENGTH];
	bool peasData[MAPLENGTH][MAPLENGTH];//豆子地图
	void initOP();//豆子地图优化
	COLORREF color;
public:
	void DrawMap(HDC& hdc);
	void DrawPeas(HDC& hdc);
	

friend class GObject;//允许物体类使用直线的起点和终点的信息做碰撞检测
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