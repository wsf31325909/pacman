#pragma once
#include "stdafx.h"
#include "GMap.h"


#define IRANGE 10 //ͼ�η�Χ
#define DEV 2 //��ͼ���
#define PAINTR  (IRANGE+DEV)//��ͼ��Χ
#define SPEED 9 //��������
#define ENERMYSPEED 4 //��������
#define FOOTNUM 5 //���˽ŵĴ�С



enum TWARDS {LEFT,RIGHT,UP,DOWN,OVER};


class GObject {
protected:
	int mX; //�߼�����x
	int mY; //�߼�����y
	int speed;//�ٶ�
	int flageA;//�Ƿ�Ϊ���ĵ��ǣ�0Ϊ��1Ϊ��
	int flageB;//�Ƿ����ڱ�ǣ�0Ϊ��1Ϊ��
	void CenterJudge();//�����ж�����
	void WallJudge();//�����ж�
	int frame; //֡��
	TWARDS twCommand; //ָ���
	POINT point;
	void twCal();	//�����ж�
public:
	TWARDS tw; //����ָ��
	int coorX; //ʵ����������x
	int coorY; //ʵ����������y
	static GMap* pStage; //������̬��ͼָ��
	void DrawBlank(HDC& hdc);//���ƶ���
	virtual void Draw(HDC& hdc) = 0;
	void virtual action() = 0;	//�ƶ�����
	void SetPosition(int Row, int Array);
	void getPosition();//���ƶ������ĵ�ʱ���ѻ���ָ�ֵ��tw
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
	void SetTwCommand(TWARDS command);//���÷���ָ���
	bool win();	//��Ϸʤ���ж�
	bool static godie;	//�ж������Ƿ�����
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
	//int speed;//�������٣�������
	COLORREF color;
	void Draw(HDC& hdc);//�滭��ò��������
	void virtual AI()=0;//����AI
	void  action();
	void catchP();//ץ������
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