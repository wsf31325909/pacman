#pragma once
#include "stdafx.h"
#include "GMap.h"


#define IRANGE 10 //图形范围
#define DEV 2 //绘图误差
#define PAINTR  (IRANGE+DEV)//绘图范围
#define SPEED 9 //主角移速
#define ENERMYSPEED 4 //敌人移速
#define FOOTNUM 5 //敌人脚的大小



enum TWARDS {LEFT,RIGHT,UP,DOWN,OVER};


class GObject {
protected:
	int mX; //逻辑坐标x
	int mY; //逻辑坐标y
	int speed;//速度
	int flageA;//是否为中心点标记，0为否，1为是
	int flageB;//是否碰壁标记，0为否，1为是
	void CenterJudge();//中心判定方法
	void WallJudge();//碰壁判定
	int frame; //帧数
	TWARDS twCommand; //指令缓存
	POINT point;
	void twCal();	//方向判定
public:
	TWARDS tw; //方向指令
	int coorX; //实际坐标中心x
	int coorY; //实际坐标中心y
	static GMap* pStage; //创建静态地图指针
	void DrawBlank(HDC& hdc);//绘制对象
	virtual void Draw(HDC& hdc) = 0;
	void virtual action() = 0;	//移动方法
	void SetPosition(int Row, int Array);
	void getPosition();//当移动到中心点时，把缓存指令赋值给tw
	GObject(int dRow,int dArray) {
		frame = 1;
		this->mX = dRow;
		this->mY = dArray;
		this->point.x = mX * pStage->LD + pStage->LD / 2;
		this->point.y = mY * pStage->LD + pStage->LD / 2;
		coorX = point.x;
		coorY = point.y;
	}
};

class PacMan :public GObject {
public:
	void Draw(HDC& hdc);
	void action();
	void peasCal();
	void SetTwCommand(TWARDS command);//设置方向指令缓存
	bool win();	//游戏胜利判定
	bool static godie;	//判定主角是否死亡
	bool exit=false;
	TWARDS GetTw();
	PacMan(int x, int y) :GObject(x, y) {
		twCommand = tw = UP;
		this->speed = SPEED;
	}
};

class Enemy :public GObject {
public:
	static PacMan* player;
	//int speed;//敌人移速，公共点
	COLORREF color;
	void Draw(HDC& hdc);//绘画外貌，公共点
	void virtual AI()=0;//敌人AI
	void  action();
	void catchP();//抓捕方法
	Enemy(int x, int y) : GObject(x, y) {
		this->speed = ENERMYSPEED;
		tw = UP;
		twCommand = UP;
	}
};

class RedEn :public Enemy {
public:
	void virtual AI();
	RedEn(int x, int y) :Enemy(x, y) {
		color = RGB(255, 0, 0);
	}
};
class BlueEn :public Enemy {
public:
	void virtual AI();
	BlueEn(int x, int y) :Enemy(x, y) {
		color = RGB(0, 0, 255);
	}
};

class YellowEn :public Enemy {
public:
	void virtual AI();
	YellowEn(int x, int y) :Enemy(x, y) {
		color = RGB(200, 200, 100);
	}
};