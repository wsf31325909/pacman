#include "stdafx.h"
#include "GMap.h"


//bool Stage_1::
int GMap::PD = 6;
int GMap::LD = 36;

void GMap::initOP() {
	peasData[INITA][INITR] = true;
}


void GMap::DrawMap(HDC& memDc) {
	for (int i = 0; i < MAPLENGTH;i++) {
		for (int j = 0; j < MAPLENGTH;j++) {
			if (mapData[i][j]) {
				RECT rect;
				rect.left = j * LD;
				rect.right = (j + 1) * LD;
				rect.top = i * LD;
				rect.bottom = (i + 1) * LD;
				FillRect(memDc,&rect,CreateSolidBrush(color));
			}
		}
	}
}
void GMap::DrawPeas(HDC& memDc) {
	for (int i = 0; i < MAPLENGTH; i++) {
		for (int j = 0; j < MAPLENGTH; j++) {
			if (!peasData[i][j]) {
				Ellipse(memDc,j*LD + LD/2 - PD/2,i*LD + LD/2 - PD/2, j*LD + LD/2 + PD/2, i*LD + LD/2 + PD/2);
			}
		}
	}
}
#define A true
#define B false
Stage_1::Stage_1() {
	color = RGB(140, 240, 240);
	bool initData[MAPLENGTH][MAPLENGTH] =
	{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
		A,A,A,A,A,A,A,A,A,B,A,A,A,A,A,B,A,A,A,A,//0
		A,A,A,A,A,A,A,A,A,B,A,A,A,A,A,B,A,A,A,A,//1
		A,A,A,A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,A,//2
		A,A,A,A,B,A,A,A,A,A,A,A,A,A,B,A,A,A,B,A,//3
		A,A,A,A,B,B,A,A,A,A,A,A,A,A,B,A,A,A,B,A,//4
		A,A,A,A,A,B,A,A,A,A,B,B,B,B,B,A,A,A,B,A,//5
		A,A,A,B,B,B,B,A,A,B,B,A,A,A,A,A,A,A,B,A,//6
		B,B,A,B,A,A,B,A,A,B,B,A,A,A,A,A,A,A,B,B,//7
		A,B,A,B,A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,A,//8
		A,B,B,B,A,B,A,B,B,B,B,B,A,A,A,A,A,A,A,A,//9
		A,B,A,B,B,B,A,B,A,B,A,B,A,A,A,A,A,A,A,A,//10
		B,B,A,A,B,A,A,B,B,A,B,B,A,A,B,B,B,B,B,B,//11
		A,A,A,A,B,B,B,B,B,B,B,B,B,B,B,A,A,A,A,A,//12
		A,A,A,A,B,A,A,A,A,B,A,A,B,A,A,A,A,A,A,A,//13
		A,A,A,A,B,A,A,A,A,B,A,A,B,A,A,A,A,A,A,A,//14
		A,A,A,A,B,A,A,A,A,B,A,A,B,B,B,A,A,A,A,A,//15
		A,A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,A,A,A,A,//16
		A,A,B,A,B,A,A,A,A,B,A,A,A,A,A,B,A,A,A,A,//17
		A,A,B,B,B,A,A,A,A,B,A,A,A,A,A,B,A,A,A,A,//18
		A,A,A,A,A,A,A,A,A,B,A,A,A,A,A,B,A,A,A,A,//19
	};
	for (int i = 0; i < MAPLENGTH; i++) {
		for (int j = 0; j < MAPLENGTH; j++) {
			mapData[i][j] =initData[i][j];
			peasData[i][j] = initData[i][j];
		}
	}
	initOP();
}
#undef A
#undef B

#define A true
#define B false
Stage_2::Stage_2() {
	color = RGB(140, 240, 240);
	bool initData[MAPLENGTH][MAPLENGTH] =
	{
		//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
			A,A,B,A,A,A,A,A,B,A,A,A,A,B,A,A,A,A,A,A,//0
			A,A,B,A,A,A,A,A,B,A,A,A,A,B,B,B,A,A,A,A,//1
			A,A,B,A,A,A,A,A,B,A,A,A,A,A,A,B,A,A,A,A,//2
			B,B,B,A,A,A,A,A,B,A,A,A,A,A,A,B,B,B,B,B,//3
			A,A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,A,A,A,A,//4
			A,A,A,B,B,B,A,A,B,A,A,A,B,B,B,A,A,A,A,A,//5
			A,A,A,B,B,B,A,A,B,A,A,A,B,B,B,A,A,A,A,A,//6
			A,A,A,B,A,A,A,A,B,A,A,A,A,A,B,A,A,A,A,A,//7
			A,A,A,B,A,A,A,A,B,B,A,A,A,A,B,A,A,A,A,A,//8
			A,A,A,B,A,A,A,A,B,B,A,A,A,A,B,A,A,A,A,A,//9
			A,A,A,B,A,A,A,A,B,B,A,A,A,A,B,A,A,A,A,A,//10
			A,A,A,B,A,A,A,A,B,A,A,A,A,A,B,B,A,A,A,A,//11
			A,A,A,B,A,A,A,A,B,A,A,A,A,A,A,B,A,A,A,A,//12
			A,A,B,B,B,B,B,A,B,B,B,B,B,B,B,B,A,A,A,A,//13
			A,A,B,B,A,B,B,B,B,B,B,A,A,B,A,A,A,A,A,A,//14
			A,A,B,A,A,B,A,A,B,A,A,A,A,B,B,B,B,B,A,A,//15
			A,A,A,A,A,B,A,A,B,A,A,A,A,A,A,A,A,B,A,A,//16
			A,A,A,A,B,B,A,A,B,A,A,A,A,A,A,A,A,B,A,A,//17
			A,A,B,B,B,A,A,A,B,B,B,B,B,B,B,B,B,B,A,A,//18
			A,A,B,A,A,A,A,A,B,A,A,A,A,B,A,A,A,A,A,A,//19
	};
	for (int i = 0; i < MAPLENGTH; i++) {
		for (int j = 0; j < MAPLENGTH; j++) {
			mapData[i][j] = initData[i][j];
			peasData[i][j] = initData[i][j];
		}
	}
	initOP();
}
#undef A
#undef B

#define A true
#define B false
Stage_3::Stage_3() {
	color = RGB(140, 240, 240);
	bool initData[MAPLENGTH][MAPLENGTH] =
	{
		//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//0
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//1
			B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,//2
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//3
			B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,//4
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//5
			B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,//6
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//7
			A,A,A,A,A,A,A,A,B,B,A,A,A,A,A,A,A,A,A,A,//8
			B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,//9
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//10
			B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,//11
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//12
			B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,//13
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//14
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//15
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//16
			B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,//17
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//18
			A,A,A,A,A,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,//19
	};
	for (int i = 0; i < MAPLENGTH; i++) {
		for (int j = 0; j < MAPLENGTH; j++) {
			mapData[i][j] = initData[i][j];
			peasData[i][j] = initData[i][j];
		}
	}
	initOP();
}
#undef A
#undef B