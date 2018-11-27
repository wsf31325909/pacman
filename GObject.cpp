#include "stdafx.h"
#include "GObject.h"
#include <iostream>
#define random(a,b) (rand()%(b-a+1)+a)

using namespace std;
bool PacMan::godie = false;
GMap* GObject::pStage = NULL;
void GObject::CenterJudge() {
	int flageI=0;//临时计数标记
	for (int i = 0; i < MAPLENGTH; i++) {
		for (int j = 0; j < MAPLENGTH; j++) {
			if ((coorX - pStage->LD / 2) == j * pStage->LD && (coorY - pStage->LD / 2) == i * pStage->LD) {
				flageI++;
				mX = j;
				mY = i;
			}
		}
	}
	if (flageI==1) {
		flageA = 1;
	}
	else {
		flageA = 0;
	}
}

void GObject::WallJudge() {
	if (flageA == 1) {
		switch (tw)
		{
		case LEFT:
			if (pStage->mapData[mY][mX - 1] == true && mX > 0) {
				flageB = 1;
			}
			else {
				flageB = 0;
			}
			break;
		case RIGHT:
			if (pStage->mapData[mY][mX + 1] == true && mX <MAPLENGTH-1) {
				flageB = 1;
			}
			else {
				flageB = 0;
			}
			break;
		case UP:
			if (pStage->mapData[mY-1][mX] == true && mY > 0) {
				flageB = 1;
			}
			else {
				flageB = 0;
			}
			break;
		case DOWN:
			if (pStage->mapData[mY+1][mX] == true && mY <MAPLENGTH-1) {
				flageB = 1;
			}
			else {
				flageB = 0;
			}
			break;
		case OVER:
			break;
		default:
			break;
		}
		
	}
}

void PacMan::Draw(HDC& memDc) {
	int XX1 = coorX - PAINTR;//绘图约束范围（XX1,YY1）,(XX2,YY2)
	int YY1 = coorY - PAINTR;
	int XX2 = coorX + PAINTR;
	int YY2 = coorY + PAINTR;
	int X1, X2, Y1, Y2;
	if ((frame-2)%5==0||frame%5==0) {//嘴巴形态
		if (tw==LEFT) {
			X1 = X2 = coorX - PAINTR / 2 - DEV;
			Y1 = coorY + PAINTR / 2 + DEV;
			Y2 = coorY - PAINTR / 2 - DEV;
		}
		else if ( tw == DOWN) {
			X1 = coorX + PAINTR / 2 + DEV;
			Y1 = Y2 = coorY + PAINTR / 2 + DEV;
			X2 = coorX - PAINTR / 2 - DEV;
		}
		else if (tw == RIGHT) {
			X1 = X2 = coorX + PAINTR / 2 +DEV;
			Y1 = coorY - PAINTR / 2 - DEV;
			Y2 = coorY + PAINTR / 2 + DEV;
		}
		else {
			X1 = coorX - PAINTR / 2-DEV;
			Y1 = Y2 = coorY - PAINTR / 2- DEV;
			X2 = coorX + PAINTR / 2+ DEV;
		}
		Arc(memDc, XX1, YY1, XX2, YY2, X1, Y1, X2, Y2);
		MoveToEx(memDc, X1, Y1, NULL);
		LineTo(memDc, coorX, coorY);
		LineTo(memDc, X2, Y2);
	}
	else if ((frame - 1) % 5 == 0) {//整圆
		Ellipse(memDc,coorX-PAINTR, coorY -PAINTR, coorX +PAINTR,coorY+PAINTR);
	}
	else {//半圆形态
		int XX1 = coorX - PAINTR;//绘图约束范围（XX1,YY1）,(XX2,YY2)
		int YY1 = coorY - PAINTR;
		int XX2 = coorX + PAINTR;
		int YY2 = coorY + PAINTR;
		int X1, X2, Y1, Y2;
		if (tw==OVER) {
		
		}else if (tw==LEFT) {
			X1 = X2 = coorX ;
			Y1 = coorY + PAINTR;
			Y2 = coorY - PAINTR;
		}
		else if (tw==DOWN) {
			X1 = coorX + PAINTR;
			Y1 = Y2 = coorY;
			X2 = coorX - PAINTR;
		}
		else if (tw==RIGHT) {
			X1 = X2 = coorX;
			Y1 = coorY - PAINTR;
			Y2 = coorY + PAINTR;
		}
		else if (tw==UP) {
			Y1 = Y2 = coorY;
			X1 = coorX - PAINTR;
			X2 = coorX + PAINTR;
		}
		Arc(memDc, XX1, YY1, XX2, YY2, X1, Y1, X2, Y2);
		MoveToEx(memDc, X1, Y1, NULL);
		LineTo(memDc, X2, Y2);
	}
	frame++;
}
void GObject::DrawBlank(HDC& hdc)
{
	RECT rect;
	rect.top = coorY - PAINTR-2;
	rect.left = coorX - PAINTR-2;
	rect.right = coorX + PAINTR+2;
	rect.bottom = coorY + PAINTR+2;
	FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 255, 255)));
}

void  GObject::twCal() {
	int MIN = -pStage->LD / 2;
	int MAX = MAPLENGTH * pStage->LD + pStage->LD/2;
	switch (tw) {
	case LEFT:
		if (flageB==0) {
			coorX -= speed;
			if (coorX < MIN) {
				coorX = MAX;
			}
		}
		
		break;
	case DOWN:
		if (flageB == 0) {
			coorY += speed;
			if (coorY > MAX) {
				coorY = MIN;
			}
		}
		break;
	case RIGHT:
		if (flageB == 0) {
			coorX += speed;
			if (coorX > MAX) {
				coorX = MIN;
			}
		}
		break;
	case UP:
		if (flageB == 0) {
			coorY -= speed;
			if (coorY < MIN) {
				coorY = MAX;
			}
		}
		break;
	}
}

void PacMan::action() {
	peasCal();
	twCal();
	CenterJudge();
	WallJudge();
}

void PacMan::peasCal() {
	for (int i = 0; i < MAPLENGTH; i++) {
		for (int j = 0; j < MAPLENGTH; j++) {
			//注意下面的除法不是整除
			if (j*pStage->LD<coorX&&coorX <(j+1)*pStage->LD&&i*pStage->LD<coorY&&coorY <(i+1)*pStage->LD) {
				pStage->peasData[i][j] = true;
			}
		}
	}
}
void PacMan::SetTwCommand(TWARDS command) {
	twCommand = command;
}
void GObject::getPosition() {
	if (flageA==1) {
		if (twCommand == LEFT&&pStage->mapData[mY][mX-1]==false&&mY>0) {
			tw = twCommand;
		}
		else if (twCommand == DOWN && pStage->mapData[mY+1][mX] == false&&mY<MAPLENGTH) {
			tw = twCommand;
		}
		else if (twCommand ==RIGHT && pStage->mapData[mY][mX+1] == false&&mX<MAPLENGTH) {
			tw = twCommand;
		}
		else if (twCommand ==UP && pStage->mapData[mY-1][mX] == false&&mX>0) {
			tw = twCommand;
		}
	}
}

bool PacMan::win() {
	int ii = 0;
	for (int i = 0; i < MAPLENGTH;i++) {
		for (int j = 0; j < MAPLENGTH;j++) {
			if (!pStage->peasData[i][j]) {
				ii++;
			}
		}
	}
	if (ii<1) {
		return true;
	}
	else {
		return false;
	}
}
void GObject::SetPosition(int Row,int Array) {
	this->mX = Row;
	this->mY = Array;
	this->point.x = mX * pStage->LD + pStage->LD / 2;
	this->point.y = mY * pStage->LD + pStage->LD / 2;
	coorX = point.x;
	coorY = point.y;
}

void Enemy::Draw(HDC& memDc) {
	HPEN pen = ::CreatePen(0, 0, color);
	HPEN oldPen = (HPEN)SelectObject(memDc, pen);
	int XX1 = coorX - IRANGE;
	int YY1 = coorY - IRANGE;
	int XX2 = coorX + IRANGE;
	int YY2 = coorY + IRANGE;
	int X1 = XX2;
	int	Y1 = coorY;
	int X2 = XX1;
	int Y2 = coorY;
	//画头
	Arc(memDc,XX1,YY1,XX2,YY2,X1,Y1,X2,Y2);
	//画身子
	MoveToEx(memDc,X2,Y2,NULL);
	LineTo(memDc,X2,Y2+IRANGE);
	MoveToEx(memDc, X1, Y1, NULL);
	LineTo(memDc, X1, Y1 + IRANGE);
	//根据帧数画脚
	//int FR = IRANGE / FOOTNUM;//脚的直径
	int FR = 2;
	if (frame%2==0) {
		int FX1 = XX1;
		int FY1 = YY2;
		int FX2 = XX1 + 2*FR;;
		int FY2 = YY2;
		for (int i = 0; i < FOOTNUM;i++) {
			Arc(memDc,XX1 + i * 2 * FR,YY2-FR,XX1+2*FR + i * 2 * FR,YY2+FR,FX1-1 + i * 2 * FR,FY1, FX2 + 1 + i * 2 * FR,FY2);

		}
	}
	else {
		int FY1 = YY2;
		int FY2 = YY2;
		int FX1 = XX1 - FR  ;
		int FX2 = XX1 + FR ;
		for (int i = 0; i < FOOTNUM+1; i++) {
			Arc(memDc, XX1 + i * 2 * FR-FR, YY2 - FR, XX1 +  FR + i * 2 * FR, YY2 + FR, FX1 - 1 + i * 2 * FR, FY1, FX2 + 1  + i * 2 * FR, FY2);
		}
		RECT rectLeft;
		rectLeft.left = XX1-FR-1;
		rectLeft.top = YY2-FR;
		rectLeft.right = XX1-1;
		rectLeft.bottom = YY2 + FR;
		FillRect(memDc,&rectLeft,CreateSolidBrush(RGB(255,255,255)));

		RECT rectLeft2;
		rectLeft2.left = XX1 - FR+11*FR+1;
		rectLeft2.top = YY2 - FR;
		rectLeft2.right = XX1 + 11*FR+1;
		rectLeft2.bottom = YY2 + FR;
		FillRect(memDc, &rectLeft2, CreateSolidBrush(RGB(255, 255, 255)));
	}
	

	//画眼睛
	switch (tw) {
	case LEFT:
		Ellipse(memDc, coorX - 8, coorY - 2, coorX - 4, coorY + 2);
		Ellipse(memDc, coorX-4,coorY-2,coorX,coorY+2);
		break;
	case DOWN:
		Ellipse(memDc, coorX - 6, coorY+2, coorX - 2, coorY + 6);
		Ellipse(memDc, coorX + 2, coorY+2 , coorX + 6, coorY + 6);
		break;
	case RIGHT:
		Ellipse(memDc, coorX +4, coorY - 2, coorX +8, coorY + 2);
		Ellipse(memDc, coorX , coorY - 2, coorX+4, coorY + 2);
		break;
	case UP:
		Ellipse(memDc, coorX - 6, coorY -6, coorX - 2, coorY -2);
		Ellipse(memDc, coorX + 2, coorY -6, coorX + 6, coorY -2);
		break;
	}
	frame++;
	SelectObject(memDc, oldPen);
	DeleteObject(pen);
}

void Enemy::action() {
	catchP();//抓捕函数
	twCal();//具体移动
	CenterJudge();//判定中心点
	WallJudge();//判定碰壁
	AI();//计算方向
	getPosition();//将缓存方向有效的转换为实际方向
}

int randA() {//未碰时，随机数，0自身，1顺时针位，2逆时针位，3反向
	int randI;//随机数
	randI = random(1, 4);
	if (randI > 3) {//小概率转弯
		randI = random(1, 2);
		if (randI < 2) {
			return 2;
		}
		else {
			return 1;
		}
	}
	else {
		return 0;
	}
}

int randB() {//碰壁时，随机数，0自身，1顺时针位，2逆时针位，3反向
	int randI;//随机数
	randI = random(1, 3);
	if (randI < 3) {//大概率转弯
		randI = random(1, 2);
		if (randI < 2) {
			return 2;
		}
		else {
			return 1;
		}
	}
	else {//小概率回头
		return 3;
	}
}

TWARDS twChange(int* x) {
	//形参x为2位数组，第一位是产生的随机位置代表，第二位是当前tw的参数代表
	//x[1]代表：{LEFT,DOWN,RIGHT,UP}
	switch (x[1])
	{
	//LEFT时，第一位x[0]下的分别代表{ LEFT,UP,DOWN,RIGHT };
	case 0:
		switch (x[0])
		{
		case 0:
			return LEFT;
		case 1:
			return UP;
		case 2:
			return DOWN;
		case 3:
			return RIGHT;
		default:
			return LEFT;
		}
	//DOWN时，第一位x[0]下的分别代表{ DOWN,LEFT,RIGHT,UP };
	case 1:
		switch (x[0])
		{
		case 0:
			return DOWN;
		case 1:
			return LEFT;
		case 2:
			return RIGHT;
		case 3:
			return UP;
		default:
			return LEFT;
		}
	//RIGHT时，第一位x[0]下的分别代表{ RIGHT,DOWN,UP,LEFT };
	case 2:
		switch (x[0])
		{
		case 0:
			return RIGHT;
		case 1:
			return DOWN;
		case 2:
			return UP;
		case 3:
			return LEFT;
		default:
			return LEFT;
		}
	//UP时，第一位x[0]下的分别代表{ UP,RIGHT,LEFT,DOWN };
	case 3:
		switch (x[0])
		{
		case 0:
			return UP;
		case 1:
			return RIGHT;
		case 2:
			return LEFT;
		case 3:
			return DOWN;
		default:
			return LEFT;
		}
	default:
		return LEFT;
	}
	return LEFT;

}

void RedEn::AI() {
	int ii[2] = {0};
	if (flageA == 1) {
		switch (tw) {
		case LEFT:
			if (flageB==0) {//未碰壁时
				ii[0] = randA();
				ii[1] = 0;
			}
			else {//碰壁时
				ii[0] = randB();
				ii[1] = 0;
			}
			break;
		case DOWN:
			if (flageB == 0) {//未碰壁时
				ii[0] = randA();
				ii[1] = 1;
			}
			else {//碰壁时
				ii[0] = randB();
				ii[1] = 1;
			}
			break;
		case RIGHT:
			if (flageB == 0) {//未碰壁时
				ii[0] = randA();
				ii[1] = 2;
			}
			else {//碰壁时
				ii[0] = randB();
				ii[1] = 2;
			}
			break;
		case UP:
			if (flageB == 0) {//未碰壁时
				ii[0] = randA();
				ii[1] = 3;
			}
			else {//碰壁时
				ii[0] = randB();
				ii[1] = 3;
			}
			break;
		}
		twCommand = twChange(ii);
	}
}

void BlueEn::AI() {
	if ((coorX == player->coorX|| coorY == player->coorY)&&flageB==0) {
		if (coorX == player->coorX) {
			if (coorY > player->coorY) {
				twCommand = UP;
			}
			else {
				twCommand = DOWN;
			}
		}
		else {
			if (coorX > player->coorX) {
				twCommand = LEFT;
			}
			else {
				twCommand = RIGHT;
			}
		}
	}
	else {
		int ii[2] = { 0 };
		if (flageA == 1) {
			switch (tw) {
			case LEFT:
				if (flageB == 0) {//未碰壁时
					ii[0] = randA();
					ii[1] = 0;
				}
				else {//碰壁时
					ii[0] = randB();
					ii[1] = 0;
				}
				break;
			case DOWN:
				if (flageB == 0) {//未碰壁时
					ii[0] = randA();
					ii[1] = 1;
				}
				else {//碰壁时
					ii[0] = randB();
					ii[1] = 1;
				}
				break;
			case RIGHT:
				if (flageB == 0) {//未碰壁时
					ii[0] = randA();
					ii[1] = 2;
				}
				else {//碰壁时
					ii[0] = randB();
					ii[1] = 2;
				}
				break;
			case UP:
				if (flageB == 0) {//未碰壁时
					ii[0] = randA();
					ii[1] = 3;
				}
				else {//碰壁时
					ii[0] = randB();
					ii[1] = 3;
				}
				break;
			}
			twCommand = twChange(ii);
		}
	}
}

void YellowEn::AI() {
	if (flageB==0) {
		if ((coorX == player->coorX || coorY == player->coorY)) {
			if (coorX == player->coorX) {
				if (coorY > player->coorY) {
					twCommand = UP;
				}
				else {
					twCommand = DOWN;
				}
			}
			else {
				if (coorX > player->coorX) {
					twCommand = LEFT;
				}
				else {
					twCommand = RIGHT;
				}
			}
		}
		else {
			int randI;//随机数
			randI = random(1, 2);
			if (randI == 1) {
				if (coorX > player->coorX) {
					twCommand = LEFT;
				}
				else if (coorX < player->coorX) {
					twCommand = RIGHT;

				}
			}
			else {
				if (coorY > player->coorY) {
					twCommand = UP;
				}
				else if (coorY < player->coorY) {
					twCommand = DOWN;

				}
			}
		}
	}else{
		int ii[2] = { 0 };
		if (flageA == 1) {
			switch (tw) {
			case LEFT:
				if (flageB == 0) {//未碰壁时
					ii[0] = randA();
					ii[1] = 0;
				}
				else {//碰壁时
					ii[0] = randB();
					ii[1] = 0;
				}
				break;
			case DOWN:
				if (flageB == 0) {//未碰壁时
					ii[0] = randA();
					ii[1] = 1;
				}
				else {//碰壁时
					ii[0] = randB();
					ii[1] = 1;
				}
				break;
			case RIGHT:
				if (flageB == 0) {//未碰壁时
					ii[0] = randA();
					ii[1] = 2;
				}
				else {//碰壁时
					ii[0] = randB();
					ii[1] = 2;
				}
				break;
			case UP:
				if (flageB == 0) {//未碰壁时
					ii[0] = randA();
					ii[1] = 3;
				}
				else {//碰壁时
					ii[0] = randB();
					ii[1] = 3;
				}
				break;
			}
			twCommand = twChange(ii);
		}
	}
}

PacMan* Enemy::player = NULL;
void Enemy::catchP() {
	if (coorX==player->coorX) {
		double gap = coorY - player->coorY;
		if ((gap>0&&gap< PAINTR)||(gap>-PAINTR&&gap<0)) {
			cout<<"逮到你了！！"<<gap<<endl;
			player->godie = true;
		}
	}
	else if (coorY == player->coorY) {
		double gap = coorX - player->coorX;
		if ((gap > 0 && gap < PAINTR) || (gap > -PAINTR && gap < 0)) {
			cout << "逮到你了！！" << gap << endl;
			player->godie = true;
		}
	}
}
