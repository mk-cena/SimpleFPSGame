using namespace std;
#include <vector>
#ifdef _WIN32
#include <glut.h>
#else
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#endif

#include <stdio.h>
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <sstream>
#include <string>
#include "TextureBuilder.h"

#define GLUT_KEY_ENTER 13
#define GLUT_KEY_SPACE 32
#define r 50
#define XCONST 2000
#define ZCONST 10500
#define CROSSROADCONST 100
#define DOORCONST 10
#define DOORWIDTHCONST 100
#define DOORTIMECONSTANT 30
#define CLOSED 0
#define OPENING 1
#define OPENED 2
#define CLOSING 3
#define PLAY 0
#define LOST 1
#define WON 2
#define NUM_BULLETS 6
#define START 4


class SnowMan{
public:
float x,y,z,carrotPos,rotation,actualCarrotPosX,actualCarrotPosZ;
float lastX,lastZ;
float maxX, minX, maxZ, minZ;
bool fired,reverseX,reverseY,reverseZ,moveInX,fireInX,aLive;
SnowMan(float,float,float,float);
void Draw();
};

SnowMan::SnowMan(float X,float Y,float Z,float cx){
x = X;
y = 280;
z = Z;
lastX = 0;
lastZ = 0;
carrotPos = cx;
fired = false;
reverseX = false;
reverseZ = false;
aLive = true;
}

void SnowMan::Draw(){
if(aLive){
	glPushMatrix();
	

//Draw Body
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(x ,260, z);
	glutSolidSphere(60,20,20);
	glPopMatrix();
// Draw Head
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(x ,260, z);
	glTranslatef(0.0f, 90, 0.0f);
	glutSolidSphere(30,20,20);
	glPopMatrix();
	// Draw Eyes
	glPushMatrix();
	glTranslatef(x ,260, z);
	glTranslatef(0.0f, 80, 0.0f);
	glRotatef(-90 - rotation ,0,1,0);
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(10, 20, 25);
	glutSolidSphere(6,10,10);
	glTranslatef(-20, 0.0f, 0.0f);
	glutSolidSphere(6,10,10);
	glPopMatrix();

	// Draw Nose
	glPushMatrix();
	if(!fired){
	glTranslatef(x ,260, z);
	glTranslatef(0.0f, 70, 0.0f);
	lastX = x;
	lastZ = z;
	}else{
	glTranslatef(lastX ,260, lastZ);
	glTranslatef(0.0f, 70, 0.0f);
	}
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(-90 - rotation ,0.0f, 1.0f, 0.0f);
	glTranslatef(0, 15, 30 + carrotPos);
	glutSolidCone(5,20,100,100);
	glPopMatrix();

	// Draw Head tartoor
	glPushMatrix();
	glTranslatef(x ,260, z);
	glTranslatef(0.0f, 70, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(-90.0f,1.0f, 0.0f, 0.0f);
	glTranslatef(0, 0, 40);
	glutSolidCone(30,50,10,10);
	glPopMatrix();
	glPopMatrix();
	glutPostRedisplay();
	if(rotation > 90){
	actualCarrotPosX = lastX + carrotPos;		
	}else{
	actualCarrotPosX = lastX - carrotPos;		
	}
	if(rotation > 0){
	actualCarrotPosZ = lastZ - carrotPos;
	}
	else{
	actualCarrotPosZ = lastZ + carrotPos;
}
}
}





















bool bitmap[7000][12000];
bool bitmap2[7000][12000];
float CAMStride = 0;
float CAMrot = 0;
float camx=250;
int camy=320;
float camz=-650;
float gazex=camx;
float gazey=310;
float gazez=camz-50;
float camangle=90;
float fov=50;
float asp=1;
float near1=100;
float far1=10000;
float d1temp;
float d2temp;
float d4temp;
float d5temp;
float d6temp;
int door1State=CLOSED;
int door2State=CLOSED;
int door4State=CLOSED;
int door5State=CLOSED;
int door6State=CLOSED;
time_t time1Opened=0;
time_t time2Opened=0;
time_t time4Opened=0;
time_t time5Opened=0;
time_t time6Opened=0;
time_t gameStartTime=0;
bool firstTime=true;
int door=0;
float d1z1=-1400;
float d1z2=-1200;
float d2z1=-3100;
float d2z2=-2900;
float d4z1=-2600;
float d4z2=-2400;
float d5z1=300;
float d5z2=600;
float d6z1=-9000;
float d6z2=-8700;

int windowWidth = 1280;
int windowHeight = 900;
// FPS guy
float life = 100;
char lifeString[60];
bool lifeDecrease;

float actualBulletX[NUM_BULLETS] ;
float actualBulletZ[NUM_BULLETS] ;
float gunFireX[NUM_BULLETS] ;
float gunFireAngle[NUM_BULLETS] ;
float gunLastX[NUM_BULLETS] ;
float gunLastZ[NUM_BULLETS] ;
int bulletsLeft = 0;
char bulletsLeftString[60];
bool gunFired[NUM_BULLETS];


// Snowman
int numSnowMen = 17;
// color for the snowman's nose
float red = 1.0f, blue=0.5f, green=0.5f;
float xDelay = 250;
float yDelay = 250;
SnowMan* Snowmen = 
static_cast<SnowMan*>( ::operator new ( sizeof(SnowMan) * numSnowMen ) );
// scale of snowman
float scale = 1.0f;

bool gun=false;
bool hp=false;
bool prize=false;
bool key=false;
bool poison=false;
bool haveHp=false;
bool havePoison=false;
int gameState=START;
bool done=false;
long lastTime=0;




bool SantaStart =  true;

time_t startViper;
bool ViperStart = false;

time_t startHeal;
bool HealStart = false;

time_t startWin;
bool WinStart = false;

time_t startLose;
bool LoseStart = false;

time_t startKey;
bool KeyStart = false;

time_t startGun;
bool GunStart = false;

































void CheckHp()
{
	if(life<=0)
		gameState=LOST;
}

void BoxCollision()
{
	if(camx>=820&&camx<=980&&camz>=-1280&&camz<=-1170&&bulletsLeft == 0){
		gun=true;
		bulletsLeft = 6;

	}

	if(!Snowmen[3].aLive && !Snowmen[4].aLive &&!Snowmen[5].aLive && camx>=-480&&camx<=-370&&camz>=-3080&&camz<=-2970)
	{
		poison=true;
		if(!havePoison)
		{
			havePoison=true;
			life-=75;

			if(!ViperStart){
			startViper =  time(NULL);
			mciSendString(L"setaudio Santa.mp3 volume to 100", NULL, 0, 0);
			int rc2=mciSendString(L"play Viper.mp3", NULL, 0, 0); //Change mp3 file
			mciSendString(L"setaudio Viper.mp3 volume to 1000", NULL, 0, 0);
			ViperStart = true;
			SantaStart =  false;
			}
		}

	}
		
	if(!Snowmen[6].aLive &&!Snowmen[7].aLive &&!Snowmen[8].aLive && camx>=2370&&camx<=2480&&camz>=-2580&&camz<=-2470)
	{
		hp=true;
		if(!haveHp)
		{
			haveHp=true;
			life+=10;


			if(!HealStart){
			startHeal =  time(NULL);
			mciSendString(L"setaudio Santa.mp3 volume to 100", NULL, 0, 0);
			int rc2=mciSendString(L"play Heal.mp3", NULL, 0, 0); //Change mp3 file
			mciSendString(L"setaudio Heal.mp3 volume to 1000", NULL, 0, 0);
			HealStart = true;
			SantaStart =  false;
			}
		}
	}		
	if(!Snowmen[9].aLive &&!Snowmen[10].aLive &&!Snowmen[11].aLive && camx>=2870&&camx<=2980&&camz>=70&&camz<=180){
		key=true;

		if(!KeyStart){
			startKey =  time(NULL);
			mciSendString(L"play door.mp3", NULL, 0, 0); //Change mp3 file
			mciSendString(L"setaudio Santa.mp3 volume to 50", NULL, 0, 0);
			mciSendString(L"setaudio door.mp3 volume to 1000", NULL, 0, 0);
			KeyStart = true;
			SantaStart =  false;
			}
	}
	if(!Snowmen[12].aLive &&!Snowmen[13].aLive &&!Snowmen[14].aLive && !Snowmen[15].aLive &&!Snowmen[16].aLive &&camx>=2370&&camx<=2480&&camz>=-8880&&camz<=-8770)
	{
		prize=true;	
		gameState=WON;
	}
}
void SwitchCAM()
{
	switch(camy){
		case 320:camy = 1050; fov = 50;break;
		case 1050: camy = 8000; fov = 100; break;
		case 8000:camy = 320; fov = 50; break;
	}
	
}

void DefineDoor(int i,int j)
{
		if(i>=90&&i<=110)
		{
			if(j>=-3100&&j<=-2900)
			{
				door=2;
				d2temp=-3100;
			}
			return;
		} 
		if(i>=390&&i<=410)
		{
			if(j>=-1400&&j<=-1200)
			{
				door=1;
				d1temp=-1400;
			}
			return;
		} 
		if(i>=490&&i<=510)
		{
			if(j>=-9000&&j<=-8700)
			{
				door=6;
				d6temp=-9000;
			}
			return;
		} 
		if(i>=1590&&i<=1610)
		{
			if(j>=-2600&&j<=-2400)
			{
				door=4;
				d4temp=-2600;
			}
			return;
		}

		if(i>=1990&&i<=2010)
		{
			if(j>=300&&j<=600)
			{
				door=5;
				d5temp=300;
			}
			return;
			
		}
		door=0;
}
bool Door(float cx, float cz)
{
	int count=0;
	float t=115;
	float tcamx=camx-t;
	float tcamz=camz-t;
	cx-=t;
	cz-=t;

	for(int i=min(cx,tcamx); i<=max(cx,tcamx)+t;i++)
		for(int j=min(cz,tcamz); j<= max(cz,tcamz)+t;j++)
			if(bitmap2[i+XCONST][j+ZCONST])
			{
				count++;
				if(count>=DOORCONST)
				{
						DefineDoor(i,j);
						return true;
				}
			}


	count=0;
	cz+=(2*t);
	tcamz+=(2*t);
	for(int i=min(cx,tcamx); i<=max(cx,tcamx)+t;i++)
		for(int j=min(cz,tcamz)-t; j<= max(cz,tcamz);j++)
			if(bitmap2[i+XCONST][j+ZCONST])
			{
				count++;
				if(count>=DOORCONST)
				{
						DefineDoor(i,j);
						return true;
				}
			}


	count=0;
	cz-=(2*t);
	tcamz-=(2*t);
	cx+=(2*t);
	tcamx+=(2*t);
	for(int i=min(cx,tcamx)-t; i<=max(cx,tcamx);i++)
		for(int j=min(cz,tcamz); j<= max(cz,tcamz)+t;j++)
			if(bitmap2[i+XCONST][j+ZCONST])
			{
				count++;
				if(count>=DOORCONST)
				{
						DefineDoor(i,j);
						return true;
				}
			}


	count=0;
	cz+=(2*t);
	tcamz+=(2*t);
	for(int i=min(cx,tcamx)-t; i<=max(cx,tcamx);i++)
		for(int j=min(cz,tcamz)-t; j<= max(cz,tcamz);j++)
			if(bitmap2[i+XCONST][j+ZCONST])
			{
				count++;
				if(count>=DOORCONST)
				{
						DefineDoor(i,j);
						return true;
				}
			}


	count=0;

	return false;		
}
bool Collided(float cx, float cz)
{
	float t=115;
	float tcamx=camx-t;
	float tcamz=camz-t;
	cx-=t;
	cz-=t;

	for(int i=min(cx,tcamx); i<=max(cx,tcamx)+t;i++)
		for(int j=min(cz,tcamz); j<= max(cz,tcamz)+t;j++)
			if(bitmap[i+XCONST][j+ZCONST])
				return true;

	cz+=(2*t);
	tcamz+=(2*t);
	for(int i=min(cx,tcamx); i<=max(cx,tcamx)+t;i++)
		for(int j=min(cz,tcamz)-t; j<= max(cz,tcamz);j++)
			if(bitmap[i+XCONST][j+ZCONST])
				return true;
	
	cz-=(2*t);
	tcamz-=(2*t);
	cx+=(2*t);
	tcamx+=(2*t);
	for(int i=min(cx,tcamx)-t; i<=max(cx,tcamx);i++)
		for(int j=min(cz,tcamz); j<= max(cz,tcamz)+t;j++)
			if(bitmap[i+XCONST][j+ZCONST])
				return true;

	cz+=(2*t);
	tcamz+=(2*t);
	for(int i=min(cx,tcamx)-t; i<=max(cx,tcamx);i++)
		for(int j=min(cz,tcamz)-t; j<= max(cz,tcamz);j++)
			if(bitmap[i+XCONST][j+ZCONST])
				return true;

	return false;		
}
void RotateRight()
{
	camangle+=CAMrot;
	if(camangle>=360)
		camangle-=360;
	gazex=camx+r*cos(camangle*M_PI/180);
	gazez=camz-r*sin(camangle*M_PI/180);
	BoxCollision();
}
bool DoorOpened()
{
	switch(door)
	{
		case 1: return door1State==OPENED;
		case 2: return door2State==OPENED;
		case 4: return door4State==OPENED;
		case 5: return door5State==OPENED;
		case 6: return door6State==OPENED;
		default: return false;

	}
}

void GunShot()
{
	for (int i = 0; i < NUM_BULLETS; ++i)
	{
		
		
		
		actualBulletX[i]=gunFireX[i]*cos(gunFireAngle[i]*M_PI/180)+gunLastX[i];

		actualBulletZ[i]=gunFireX[i]*sin(-gunFireAngle[i]*M_PI/180)+gunLastZ[i];
	}




/*if((Collided(camx+x,camz-z)&&Door(camx+x,camz-z)&&DoorOpened())||
		!Collided(camx+x,camz-z))
	{
		camx+=x;
		camz-=z;
		gazex+=x;
		gazez-=z;	
	}
	BoxCollision();*/
}

void MoveForward()
{
	float x=CAMStride*cos(camangle*M_PI/180);
	float z=CAMStride*sin(camangle*M_PI/180);

	if((Collided(camx+x,camz-z)&&Door(camx+x,camz-z)&&DoorOpened())||
		!Collided(camx+x,camz-z))
	{
		camx+=x;
		camz-=z;
		gazex+=x;
		gazez-=z;	
	}
	BoxCollision();
}
void FillBitmap(int x1,int x2, int z1, int z2)
{
	for(int i=x1;i<=x2;i++)
		for(int j=z1;j<=z2;j++)
			bitmap[i][j]=true;
} 
void FillBitmap2(int x1,int x2, int z1, int z2)
{
	for(int i=x1;i<=x2;i++)
		for(int j=z1;j<=z2;j++)
			bitmap2[i][j]=true;
} 
void FillDoorMap()
{
	FillBitmap2(400+XCONST,400+XCONST,-1400+ZCONST-DOORWIDTHCONST,-1200+ZCONST+DOORWIDTHCONST);

	FillBitmap2(100+XCONST,100+XCONST,-3100+ZCONST-DOORWIDTHCONST,-2900+ZCONST+DOORWIDTHCONST);
	
	FillBitmap2(1600+XCONST,1600+XCONST,-2600+ZCONST-DOORWIDTHCONST,-2400+ZCONST+DOORWIDTHCONST);

 	FillBitmap2(2000+XCONST,2000+XCONST,300+ZCONST-DOORWIDTHCONST,600+ZCONST+DOORWIDTHCONST);
	
	FillBitmap2(500+XCONST,500+XCONST,-9000+ZCONST-DOORWIDTHCONST,-8700+ZCONST+DOORWIDTHCONST);

}
void FillWallMap()
{
	FillBitmap(100+XCONST,100+XCONST,-1200+ZCONST,-500+ZCONST);
	FillBitmap(400+XCONST,400+XCONST,-1200+ZCONST+DOORWIDTHCONST,-500+ZCONST);

	FillBitmap(100+XCONST,100+XCONST,-2900+ZCONST+DOORWIDTHCONST,-1200+ZCONST);
	FillBitmap(400+XCONST,400+XCONST,-3100+ZCONST+DOORWIDTHCONST,-1400+ZCONST-DOORWIDTHCONST);

	FillBitmap(100+XCONST,100+XCONST,-3700+ZCONST,-3100+ZCONST-DOORWIDTHCONST);
	FillBitmap(400+XCONST,400+XCONST,-3700+ZCONST,-3100+ZCONST-DOORWIDTHCONST);

	FillBitmap(400+XCONST,1300+XCONST,-3700+ZCONST,-3700+ZCONST);
	FillBitmap(400+XCONST,1600+XCONST,-4000+ZCONST,-4000+ZCONST);

	FillBitmap(100+XCONST,100+XCONST,-4800+ZCONST,-3700+ZCONST);
	FillBitmap(400+XCONST,400+XCONST,-4800+ZCONST,-4000+ZCONST);

	FillBitmap(1300+XCONST,1300+XCONST,-3700+ZCONST,-2800+ZCONST);
	FillBitmap(1600+XCONST,1600+XCONST,-4000+ZCONST,-2800+ZCONST);

	FillBitmap(1300+XCONST,1300+XCONST,-2800+ZCONST,-2600+ZCONST);
	FillBitmap(1600+XCONST,1600+XCONST,-2800+ZCONST,-2600+ZCONST-DOORWIDTHCONST);

	FillBitmap(1600+XCONST,1600+XCONST,-2400+ZCONST+DOORWIDTHCONST,-800+ZCONST);
	FillBitmap(1300+XCONST,1300+XCONST,-2800+ZCONST,-800+ZCONST);

	FillBitmap(1600+XCONST,1600+XCONST,-500+ZCONST,300+ZCONST);
	FillBitmap(1300+XCONST,1300+XCONST,-800+ZCONST,600+ZCONST);

	FillBitmap(1600+XCONST,2500+XCONST,-800+ZCONST,-800+ZCONST);
	FillBitmap(1600+XCONST,2800+XCONST,-500+ZCONST,-500+ZCONST);

	FillBitmap(2500+XCONST,2500+XCONST,-1900+ZCONST,-800+ZCONST);
	FillBitmap(2800+XCONST,2800+XCONST,-1600+ZCONST,-500+ZCONST);

	FillBitmap(2500+XCONST,3700+XCONST,-1900+ZCONST,-1900+ZCONST);
	FillBitmap(2800+XCONST,3700+XCONST,-1600+ZCONST,-1600+ZCONST);

	FillBitmap(4000+XCONST,4000+XCONST,-1900+ZCONST,1000+ZCONST);
	FillBitmap(3700+XCONST,3700+XCONST,-1600+ZCONST,700+ZCONST);

	FillBitmap(100+XCONST,4000+XCONST,1000+ZCONST,1000+ZCONST);
	FillBitmap(400+XCONST,3700+XCONST,700+ZCONST,700+ZCONST);

	FillBitmap(100+XCONST,100+XCONST,-500+ZCONST,1000+ZCONST);
	FillBitmap(400+XCONST,400+XCONST,-500+ZCONST,700+ZCONST);

	FillBitmap(1600+XCONST,2000+XCONST,300+ZCONST,300+ZCONST);
	FillBitmap(1300+XCONST,2000+XCONST,600+ZCONST,600+ZCONST);

	FillBitmap(100+XCONST,400+XCONST,-5100+ZCONST,-5100+ZCONST);

	FillBitmap(-1700+XCONST,100+XCONST,-5100+ZCONST,-5100+ZCONST);
	FillBitmap(-2000+XCONST,100+XCONST,-4800+ZCONST,-4800+ZCONST);

	FillBitmap(-1700+XCONST,-1700+XCONST,-8700+ZCONST,-5100+ZCONST);
	FillBitmap(-2000+XCONST,-2000+XCONST,-9000+ZCONST,-4800+ZCONST);

	FillBitmap(-1700+XCONST,500+XCONST,-8700+ZCONST,-8700+ZCONST);
	FillBitmap(-2000+XCONST,500+XCONST,-9000+ZCONST,-9000+ZCONST);

	FillBitmap(400+XCONST,4000+XCONST,-5100+ZCONST,-5100+ZCONST);
	FillBitmap(400+XCONST,3700+XCONST,-4800+ZCONST,-4800+ZCONST);

	FillBitmap(4000+XCONST,4000+XCONST,-5100+ZCONST,-1900+ZCONST);
	FillBitmap(3700+XCONST,3700+XCONST,-4800+ZCONST,-1900+ZCONST);


	FillBitmap(400+XCONST,1000+XCONST,-1000+ZCONST,-1000+ZCONST);
	FillBitmap(400+XCONST,1000+XCONST,-1600+ZCONST,-1600+ZCONST);
	FillBitmap(1000+XCONST,1000+XCONST,-1600+ZCONST,-1000+ZCONST);


	FillBitmap(-500+XCONST,100+XCONST,-2700+ZCONST,-2700+ZCONST);
	FillBitmap(-500+XCONST,100+XCONST,-3300+ZCONST,-3300+ZCONST);
	FillBitmap(-500+XCONST,-500+XCONST,-3300+ZCONST,-2700+ZCONST);


	FillBitmap(400+XCONST,1000+XCONST,-2700+ZCONST,-2700+ZCONST);
	FillBitmap(400+XCONST,1000+XCONST,-3300+ZCONST,-3300+ZCONST);
	FillBitmap(1000+XCONST,1000+XCONST,-3300+ZCONST,-2700+ZCONST);


	FillBitmap(2500+XCONST,2500+XCONST,-2800+ZCONST,-2200+ZCONST);
	FillBitmap(1600+XCONST,2500+XCONST,-2800+ZCONST,-2800+ZCONST);
	FillBitmap(1600+XCONST,2500+XCONST,-2200+ZCONST,-2200+ZCONST);


	FillBitmap(2000+XCONST,3000+XCONST,600+ZCONST,600+ZCONST);
	FillBitmap(2000+XCONST,2000+XCONST,-400+ZCONST,300+ZCONST);
	FillBitmap(2000+XCONST,3000+XCONST,-400+ZCONST,-400+ZCONST);
	FillBitmap(3000+XCONST,3000+XCONST,-400+ZCONST,600+ZCONST);


	FillBitmap(500+XCONST,500+XCONST,-10500+ZCONST,-9000+ZCONST);
	FillBitmap(500+XCONST,500+XCONST,-8700+ZCONST,-7200+ZCONST);
	FillBitmap(500+XCONST,2500+XCONST,-10500+ZCONST,-10500+ZCONST);
	FillBitmap(500+XCONST,2500+XCONST,-7200+ZCONST,-7200+ZCONST);
	FillBitmap(2500+XCONST,2500+XCONST,-10500+ZCONST,-7200+ZCONST);


	FillBitmap(400+XCONST,400+XCONST,-1400+ZCONST-DOORWIDTHCONST,-1200+ZCONST+DOORWIDTHCONST);

	FillBitmap(100+XCONST,100+XCONST,-3100+ZCONST-DOORWIDTHCONST,-2900+ZCONST+DOORWIDTHCONST);

	FillBitmap(1600+XCONST,1600+XCONST,-2600+ZCONST-DOORWIDTHCONST,-2400+ZCONST+DOORWIDTHCONST);

 	FillBitmap(2000+XCONST,2000+XCONST,300+ZCONST-DOORWIDTHCONST,600+ZCONST+DOORWIDTHCONST);
	
	FillBitmap(500+XCONST,500+XCONST,-9000+ZCONST-DOORWIDTHCONST,-8700+ZCONST+DOORWIDTHCONST);

}
void FillMap()
{
	FillWallMap();
	FillDoorMap();
}
void DrawWalls()
{

	static GLuint eboxTexture1 = LoadTexture("snowy.bmp", 512, 512, true);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, eboxTexture1);
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(10.0, 0.0);glVertex3f(-2000,200,-10500);
	glTexCoord2f(10.0, 10.0);glVertex3f(-2000,200,2000);
	glTexCoord2f(0.0, 0.0);glVertex3f(4000,200,2000);
	glTexCoord2f(0.0, 10.0);glVertex3f(4000,200,-10500);
	
	glEnd();



	
	
	
	static GLuint eboxTexture2 = LoadTexture("sky9.bmp", 432, 270, true);


	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, eboxTexture2);
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(-9000,800,-20500);
	glTexCoord2f(0.0, 10.0);glVertex3f(-9000,800,9000);
	glTexCoord2f(10.0, 10.0);glVertex3f(9000,800,9000);
	glTexCoord2f(10.0, 0.0);glVertex3f(9000,800,-20500);
	
	glEnd();



	/*
	glPushMatrix();
	GLUquadricObj* esphere = gluNewQuadric();
	static GLuint eboxTexture = LoadTexture("Earth.ppm", 720, 360, false);
	gluQuadricTexture(esphere, true);
	gluQuadricNormals(esphere, GLU_SMOOTH);
	glEnable(GL_TEXTURE_2D);		
	glBindTexture(GL_TEXTURE_2D, eboxTexture);
	//glEnable(GL_CULL_FACE);
	glTranslatef(lx, ly, 1.0f);
	gluSphere(esphere,50,200,200);
	gluDeleteQuadric(esphere);
	glPopMatrix();
	*/
	//glDisable(GL_TEXTURE_2D);
	//*/

	
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//static GLuint eboxTexture = LoadTexture("2_ice.ppm", 3456, 2304, false);
	//static GLuint eboxTexture = LoadTexture("Earth.ppm", 720, 360, false);
	//static GLuint eboxTexture = LoadTexture("assassins_creed_.bmp", 1366, 768, false);
	//static GLuint eboxTexture = LoadTexture("assassins_creed_revelations___00024-wallpaper-.bmp", 1366, 768, true);
	//static GLuint eboxTexture = LoadTexture("snow1.bmp", 2816, 2112, true);
	//static GLuint eboxTexture = LoadTexture("snow2.bmp", 2048, 1536, true);
	//static GLuint eboxTexture = LoadTexture("snow3.bmp", 3264, 2448, true);
	///static GLuint eboxTexture = LoadTexture("snow4.bmp", 793, 1007, true);
	//static GLuint eboxTexture = LoadTexture("snow5.bmp", 1024, 768, true);
	//static GLuint eboxTexture = LoadTexture("snow6.bmp", 2048, 1536, true);
	//static GLuint eboxTexture = LoadTexture("snow7.bmp", 2048, 1536, true);
	//static GLuint eboxTexture = LoadTexture("snow8.bmp", 2048, 1536, true);
	//static GLuint eboxTexture = LoadTexture("ice.bmp", 512, 512, true);
	static GLuint eboxTexture = LoadTexture("Eskimo.bmp", 512, 512, true);
	//static GLuint eboxTexture = LoadTexture("ice2.bmp", 512, 512, true);
	//static GLuint eboxTexture = LoadTexture("ice2.bmp", 512, 512, true);
	//static GLuint eboxTexture = LoadTexture("snowy.bmp", 512, 512, true);
	//static GLuint eboxTexture = LoadTexture("snow9.bmp", 512, 512, true);

	glBindTexture(GL_TEXTURE_2D, eboxTexture);
	//Wall1
	glPushMatrix();
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(100,200,-500);
	glTexCoord2f(0.0, 1.0);glVertex3f(100,600,-500);
	glTexCoord2f(1.0, 1.0);glVertex3f(100,600,-1200);
	glTexCoord2f(1.0, 0.0);glVertex3f(100,200,-1200);
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0);glVertex3f(400,200,-500);
	glTexCoord2f(1.0, 1.0);glVertex3f(400,600,-500);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-1200);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-1200);
	glEnd();
	glPopMatrix();
	

	//Wall2
	glPushMatrix();
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(2.0, 0.0);glVertex3f(100,200,-1200);
	glTexCoord2f(2.0, 1.0);glVertex3f(100,600,-1200);
	glTexCoord2f(0.0, 1.0);glVertex3f(100,600,-2900);
	glTexCoord2f(0.0, 0.0);glVertex3f(100,200,-2900);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(2.0, 0.0);glVertex3f(400,200,-1400);
	glTexCoord2f(2.0, 1.0);glVertex3f(400,600,-1400);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-3100);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-3100);
	glEnd();
	glPopMatrix();

	
	//Wall3
	glPushMatrix();
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0);glVertex3f(100,200,-3100);
	glTexCoord2f(1.0, 1.0);glVertex3f(100,600,-3100);
	glTexCoord2f(0.0, 1.0);glVertex3f(100,600,-3700);
	glTexCoord2f(0.0, 0.0);glVertex3f(100,200,-3700);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0);glVertex3f(400,200,-3100);
	glTexCoord2f(1.0, 1.0);glVertex3f(400,600,-3100);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-3700);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-3700);
	glEnd();
	glPopMatrix();


	//Wall4
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-3700);
	glTexCoord2f(1.0, 0.0);glVertex3f(1300,200,-3700);
	glTexCoord2f(1.0, 1.0);glVertex3f(1300,600,-3700);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-3700);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-4000);
	glTexCoord2f(1.0, 0.0);glVertex3f(1600,200,-4000);
	glTexCoord2f(1.0, 1.0);glVertex3f(1600,600,-4000);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-4000);
	glEnd();
	glPopMatrix();


	//Wall5
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(100,200,-3700);
	glTexCoord2f(2.0, 0.0);glVertex3f(100,200,-4800);
	glTexCoord2f(2.0, 1.0);glVertex3f(100,600,-4800);
	glTexCoord2f(0.0, 1.0);glVertex3f(100,600,-3700);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-4000);
	glTexCoord2f(2.0, 0.0);glVertex3f(400,200,-4800);
	glTexCoord2f(2.0, 1.0);glVertex3f(400,600,-4800);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-4000);
	glEnd();
	glPopMatrix();


	//Wall6
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(1.0, 0.0);glVertex3f(1300,200,-3700);
	glTexCoord2f(0.0, 0.0);glVertex3f(1300,200,-2800);
	glTexCoord2f(0.0, 1.0);glVertex3f(1300,600,-2800);
	glTexCoord2f(1.0, 1.0);glVertex3f(1300,600,-3700);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(2.0, 0.0);glVertex3f(1600,200,-4000);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,-2800);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,-2800);
	glTexCoord2f(2.0, 1.0);glVertex3f(1600,600,-4000);
	glEnd();
	glPopMatrix();


	//Wall7
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,-2600);
	glTexCoord2f(1.0, 0.0);glVertex3f(1600,200,-2800);
	glTexCoord2f(1.0, 1.0);glVertex3f(1600,600,-2800);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,-2600);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(1300,200,-2600);
	glTexCoord2f(1.0, 0.0);glVertex3f(1300,200,-2800);
	glTexCoord2f(1.0, 1.0);glVertex3f(1300,600,-2800);
	glTexCoord2f(0.0, 1.0);glVertex3f(1300,600,-2600);
	glEnd();
	glPopMatrix();


	//Wall8
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,-800);
	glTexCoord2f(2.0, 0.0);glVertex3f(1600,200,-2400);
	glTexCoord2f(2.0, 1.0);glVertex3f(1600,600,-2400);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,-800);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(1300,200,-800);
	glTexCoord2f(2.0, 0.0);glVertex3f(1300,200,-2600);
	glTexCoord2f(2.0, 1.0);glVertex3f(1300,600,-2600);
	glTexCoord2f(0.0, 1.0);glVertex3f(1300,600,-800);
	glEnd();
	glPopMatrix();


	//Wall9
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,-500);
	glTexCoord2f(1.0, 0.0);glVertex3f(1600,200,300);
	glTexCoord2f(1.0, 1.0);glVertex3f(1600,600,300);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,-500);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(1300,200,-800);
	glTexCoord2f(1.0, 0.0);glVertex3f(1300,200,600);
	glTexCoord2f(1.0, 1.0);glVertex3f(1300,600,600);
	glTexCoord2f(0.0, 1.0);glVertex3f(1300,600,-800);
	glEnd();
	glPopMatrix();


	//Wall10
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,-800);
	glTexCoord2f(1.0, 0.0);glVertex3f(2500,200,-800);
	glTexCoord2f(1.0, 1.0);glVertex3f(2500,600,-800);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,-800);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,-500);
	glTexCoord2f(1.0, 0.0);glVertex3f(2800,200,-500);
	glTexCoord2f(1.0, 1.0);glVertex3f(2800,600,-500);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,-500);
	glEnd();
	glPopMatrix();


	//Wall11
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(1.5, 0.0);glVertex3f(2500,200,-800);
	glTexCoord2f(0.0, 0.0);glVertex3f(2500,200,-1900);
	glTexCoord2f(0.0, 1.0);glVertex3f(2500,600,-1900);
	glTexCoord2f(1.5, 1.0);glVertex3f(2500,600,-800);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(2800,200,-500);
	glTexCoord2f(1.5, 0.0);glVertex3f(2800,200,-1600);
	glTexCoord2f(1.5, 1.0);glVertex3f(2800,600,-1600);
	glTexCoord2f(0.0, 1.0);glVertex3f(2800,600,-500);
	glEnd();
	glPopMatrix();


	//Wall12
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(2500,200,-1900);
	glTexCoord2f(1.6, 0.0);glVertex3f(3700,200,-1900);
	glTexCoord2f(1.6, 1.0);glVertex3f(3700,600,-1900);
	glTexCoord2f(0.0, 1.0);glVertex3f(2500,600,-1900);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(2800,200,-1600);
	glTexCoord2f(1.6, 0.0);glVertex3f(3700,200,-1600);
	glTexCoord2f(1.6, 1.0);glVertex3f(3700,600,-1600);
	glTexCoord2f(0.0, 1.0);glVertex3f(2800,600,-1600);
	glEnd();
	glPopMatrix();

	//Wall13
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(4000,200,-1900);
	glTexCoord2f(4.0, 0.0);glVertex3f(4000,200,1000);
	glTexCoord2f(4.0, 1.0);glVertex3f(4000,600,1000);
	glTexCoord2f(0.0, 1.0);glVertex3f(4000,600,-1900);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(3700,200,-1600);
	glTexCoord2f(4.0, 0.0);glVertex3f(3700,200,700);
	glTexCoord2f(4.0, 1.0);glVertex3f(3700,600,700);
	glTexCoord2f(0.0, 1.0);glVertex3f(3700,600,-1600);
	glEnd();
	glPopMatrix();


	//Wall14
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(5.0, 0.0);glVertex3f(4000,200,1000);
	glTexCoord2f(0.0, 0.0);glVertex3f(100,200,1000);
	glTexCoord2f(0.0, 1.0);glVertex3f(100,600,1000);
	glTexCoord2f(5.0, 1.0);glVertex3f(4000,600,1000);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(4.0, 0.0);glVertex3f(3700,200,700);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,700);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,700);
	glTexCoord2f(4.0, 1.0);glVertex3f(3700,600,700);
	glEnd();
	glPopMatrix();



	//Wall15
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(2.0, 0.0);glVertex3f(100,200,1000);
	glTexCoord2f(0.0, 0.0);glVertex3f(100,200,-500);
	glTexCoord2f(0.0, 1.0);glVertex3f(100,600,-500);
	glTexCoord2f(2.0, 1.0);glVertex3f(100,600,1000);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.8, 0.0);glVertex3f(400,200,700);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-500);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-500);
	glTexCoord2f(1.8, 1.0);glVertex3f(400,600,700);
	glEnd();
	glPopMatrix();


	//Wall16
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,300);
	glTexCoord2f(1.0, 0.0);glVertex3f(2000,200,300);
	glTexCoord2f(1.0, 1.0);glVertex3f(2000,600,300);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,300);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(1300,200,600);
	glTexCoord2f(1.0, 0.0);glVertex3f(2000,200,600);
	glTexCoord2f(1.0, 1.0);glVertex3f(2000,600,600);
	glTexCoord2f(0.0, 1.0);glVertex3f(1300,600,600);
	glEnd();
	glPopMatrix();


	//Wall17
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(100,200,-5100);
	glTexCoord2f(1.0, 0.0);glVertex3f(400,200,-5100);
	glTexCoord2f(1.0, 1.0);glVertex3f(400,600,-5100);
	glTexCoord2f(0.0, 1.0);glVertex3f(100,600,-5100);
	glEnd();
	glPopMatrix();


	//Wall18
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(2.0, 0.0);glVertex3f(100,200,-5100);
	glTexCoord2f(0.0, 0.0);glVertex3f(-1700,200,-5100);
	glTexCoord2f(0.0, 1.0);glVertex3f(-1700,600,-5100);
	glTexCoord2f(2.0, 1.0);glVertex3f(100,600,-5100);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(2.4, 0.0);glVertex3f(100,200,-4800);
	glTexCoord2f(0.0, 0.0);glVertex3f(-2000,200,-4800);
	glTexCoord2f(0.0, 1.0);glVertex3f(-2000,600,-4800);
	glTexCoord2f(2.4, 1.0);glVertex3f(100,600,-4800);
	glEnd();
	glPopMatrix();


	//Wall19
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(3.0, 0.0);glVertex3f(-1700,200,-5100);
	glTexCoord2f(0.0, 0.0);glVertex3f(-1700,200,-8700);
	glTexCoord2f(0.0, 1.0);glVertex3f(-1700,600,-8700);
	glTexCoord2f(3.0, 1.0);glVertex3f(-1700,600,-5100);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(4.0, 0.0);glVertex3f(-2000,200,-4800);
	glTexCoord2f(0.0, 0.0);glVertex3f(-2000,200,-9000);
	glTexCoord2f(0.0, 1.0);glVertex3f(-2000,600,-9000);
	glTexCoord2f(4.0, 1.0);glVertex3f(-2000,600,-4800);
	glEnd();
	glPopMatrix();


	//Wall20
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(-1700,200,-8700);
	glTexCoord2f(3.0, 0.0);glVertex3f(500,200,-8700);
	glTexCoord2f(3.0, 1.0);glVertex3f(500,600,-8700);
	glTexCoord2f(0.0, 1.0);glVertex3f(-1700,600,-8700);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(-2000,200,-9000);
	glTexCoord2f(3.0, 0.0);glVertex3f(500,200,-9000);
	glTexCoord2f(3.0, 1.0);glVertex3f(500,600,-9000);
	glTexCoord2f(0.0, 1.0);glVertex3f(-2000,600,-9000);
	glEnd();
	glPopMatrix();
	

	//Wall21
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-5100);
	glTexCoord2f(4.0, 0.0);glVertex3f(4000,200,-5100);
	glTexCoord2f(4.0, 1.0);glVertex3f(4000,600,-5100);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-5100);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-4800);
	glTexCoord2f(4.0, 0.0);glVertex3f(3700,200,-4800);
	glTexCoord2f(4.0, 1.0);glVertex3f(3700,600,-4800);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-4800);
	glEnd();
	glPopMatrix();


	
	//Wall22
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(4000,200,-5100);
	glTexCoord2f(5.0, 0.0);glVertex3f(4000,200,-1900);
	glTexCoord2f(5.0, 1.0);glVertex3f(4000,600,-1900);
	glTexCoord2f(0.0, 1.0);glVertex3f(4000,600,-5100);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(3700,200,-4800);
	glTexCoord2f(5.0, 0.0);glVertex3f(3700,200,-1900);
	glTexCoord2f(5.0, 1.0);glVertex3f(3700,600,-1900);
	glTexCoord2f(0.0, 1.0);glVertex3f(3700,600,-4800);
	glEnd();
	glPopMatrix();
	
	
	glDisable(GL_TEXTURE_2D);
	
}

void DrawDoors()
{


	glEnable(GL_TEXTURE_2D);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//static GLuint eboxTexture = LoadTexture("2_ice.ppm", 3456, 2304, false);
	//static GLuint eboxTexture = LoadTexture("Earth.ppm", 720, 360, false);
	//static GLuint eboxTexture = LoadTexture("assassins_creed_.bmp", 1366, 768, true);
	//static GLuint eboxTexture = LoadTexture("snow3.bmp", 3264, 2448, true);
	//static GLuint eboxTexture = LoadTexture("snow5.bmp", 1024, 768, true);
	static GLuint eboxTexture = LoadTexture("snow9.bmp", 512, 512, true);

	glBindTexture(GL_TEXTURE_2D, eboxTexture);
	//Door1
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,d1z2);
	glTexCoord2f(0.4, 0.0);glVertex3f(400,200,d1z1);
	glTexCoord2f(0.4, 1.0);glVertex3f(400,600,d1z1);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,d1z2);
	glEnd();
	glPopMatrix();
	

	//Door2
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(100,200,d2z1);
	glTexCoord2f(0.4, 0.0);glVertex3f(100,200,d2z2);
	glTexCoord2f(0.4, 1.0);glVertex3f(100,600,d2z2);
	glTexCoord2f(0.0, 1.0);glVertex3f(100,600,d2z1);
	glEnd();
	glPopMatrix();



	//Door4
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,d4z2);
	glTexCoord2f(0.4, 0.0);glVertex3f(1600,200,d4z1);
	glTexCoord2f(0.4, 1.0);glVertex3f(1600,600,d4z1);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,d4z2);
	glEnd();
	glPopMatrix();


	//Door5
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(2000,200,d5z1);
	glTexCoord2f(0.6, 0.0);glVertex3f(2000,200,d5z2);
	glTexCoord2f(0.6, 1.0);glVertex3f(2000,600,d5z2);
	glTexCoord2f(0.0, 1.0);glVertex3f(2000,600,d5z1);
	glEnd();
	glPopMatrix();


	//Door6(FINALDOOR)
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,1,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(500,200,d6z2);
	glTexCoord2f(0.6, 0.0);glVertex3f(500,200,d6z1);
	glTexCoord2f(0.6, 1.0);glVertex3f(500,600,d6z1);
	glTexCoord2f(0.0, 1.0);glVertex3f(500,600,d6z2);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void DrawBoxes()
{
	glEnable(GL_TEXTURE_2D);
	static GLuint eboxTexture2 = LoadTexture("Green.bmp", 960, 854, true);
	glBindTexture(GL_TEXTURE_2D, eboxTexture2);

	//GunBox
	if(!gun)
	{
		
		glPushMatrix();
		//up
		glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(850,230,-1200);
		glTexCoord2f(1.0, 0.0);glVertex3f(950,230,-1200);
		glTexCoord2f(1.0, 1.0);glVertex3f(950,230,-1250);
		glTexCoord2f(0.0, 1.0);glVertex3f(850,230,-1250);
		glEnd();
		
		//front
		glBegin(GL_QUADS);
		glColor3f(1,1,0);
		glTexCoord2f(0.0, 1.0);glVertex3f(850,200,-1200);
		glTexCoord2f(1.0, 1.0);glVertex3f(850,230,-1200);
		glTexCoord2f(1.0, 0.0);glVertex3f(850,230,-1250);
		glTexCoord2f(0.0, 0.0);glVertex3f(850,200,-1250);
		glEnd();
		
		//left
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(850,200,-1250);
		glTexCoord2f(1.0, 0.0);glVertex3f(950,200,-1250);
		glTexCoord2f(1.0, 1.0);glVertex3f(950,230,-1250);
		glTexCoord2f(0.0, 1.0);glVertex3f(850,230,-1250);
		glEnd();
		//right
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(850,200,-1200);
		glTexCoord2f(1.0, 0.0);glVertex3f(950,200,-1200);
		glTexCoord2f(1.0, 1.0);glVertex3f(950,230,-1200);
		glTexCoord2f(0.0, 1.0);glVertex3f(850,230,-1200);
		glEnd();
		//back
		glBegin(GL_QUADS);
		glColor3f(0,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(950,200,-1200);
		glTexCoord2f(1.0, 0.0);glVertex3f(950,230,-1200);
		glTexCoord2f(1.0, 1.0);glVertex3f(950,230,-1250);
		glTexCoord2f(0.0, 1.0);glVertex3f(950,200,-1250);
		glEnd();
		
		glPopMatrix();	
	}
	
	//Poison
	if(!poison)
	{
		glPushMatrix();
		//up
		glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glTexCoord2f(1.0, 1.0);glVertex3f(-400,230,-3000);
		glTexCoord2f(0.0, 1.0);glVertex3f(-450,230,-3000);
		glTexCoord2f(0.0, 0.0);glVertex3f(-450,230,-3050);
		glTexCoord2f(1.0, 0.0);glVertex3f(-400,230,-3050);
		glEnd();
		//front
		glBegin(GL_QUADS);
		glColor3f(1,1,0);
		glTexCoord2f(1.0, 0.0);glVertex3f(-400,200,-3000);
		glTexCoord2f(1.0, 1.0);glVertex3f(-400,230,-3000);
		glTexCoord2f(0.0, 1.0);glVertex3f(-400,230,-3050);
		glTexCoord2f(0.0, 0.0);glVertex3f(-400,200,-3050);
		glEnd();
		//left
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(1.0, 0.0);glVertex3f(-400,200,-3050);
		glTexCoord2f(0.0, 0.0);glVertex3f(-450,200,-3050);
		glTexCoord2f(0.0, 1.0);glVertex3f(-450,230,-3050);
		glTexCoord2f(1.0, 1.0);glVertex3f(-400,230,-3050);
		glEnd();
		//right
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(1.0, 0.0);glVertex3f(-400,200,-3000);
		glTexCoord2f(0.0, 0.0);glVertex3f(-450,200,-3000);
		glTexCoord2f(0.0, 1.0);glVertex3f(-450,230,-3000);
		glTexCoord2f(1.0, 1.0);glVertex3f(-400,230,-3000);
		glEnd();
		//back
		glBegin(GL_QUADS);
		glColor3f(0,0,1);
		glTexCoord2f(1.0, 0.0);glVertex3f(-450,200,-3000);
		glTexCoord2f(0.0, 0.0);glVertex3f(-450,200,-3050);
		glTexCoord2f(0.0, 1.0);glVertex3f(-450,230,-3050);
		glTexCoord2f(1.0, 1.0);glVertex3f(-450,230,-3000);
		glEnd();

		glPopMatrix();	
	}

	//hp
	if(!hp)
	{
		glPushMatrix();
		//up
		glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glTexCoord2f(0.0, 1.0);glVertex3f(2400,230,-2500);
		glTexCoord2f(1.0, 1.0);glVertex3f(2450,230,-2500);
		glTexCoord2f(1.0, 0.0);glVertex3f(2450,230,-2550);
		glTexCoord2f(0.0, 0.0);glVertex3f(2400,230,-2550);
		glEnd();
		//front
		glBegin(GL_QUADS);
		glColor3f(1,1,0);
		glTexCoord2f(1.0, 0.0);glVertex3f(2400,200,-2500);
		glTexCoord2f(1.0, 1.0);glVertex3f(2400,230,-2500);
		glTexCoord2f(0.0, 1.0);glVertex3f(2400,230,-2550);
		glTexCoord2f(0.0, 0.0);glVertex3f(2400,200,-2550);
		glEnd();
		//left
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2400,200,-2550);
		glTexCoord2f(1.0, 0.0);glVertex3f(2450,200,-2550);
		glTexCoord2f(1.0, 1.0);glVertex3f(2450,230,-2550);
		glTexCoord2f(0.0, 1.0);glVertex3f(2400,230,-2550);
		glEnd();
		//right
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2400,200,-2500);
		glTexCoord2f(1.0, 0.0);glVertex3f(2450,200,-2500);
		glTexCoord2f(1.0, 1.0);glVertex3f(2450,230,-2500);
		glTexCoord2f(0.0, 1.0);glVertex3f(2400,230,-2500);
		glEnd();
		//back
		glBegin(GL_QUADS);
		glColor3f(0,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2450,200,-2550);
		glTexCoord2f(1.0, 0.0);glVertex3f(2450,200,-2500);
		glTexCoord2f(1.0, 1.0);glVertex3f(2450,230,-2500);
		glTexCoord2f(0.0, 1.0);glVertex3f(2450,230,-2550);
		glEnd();

		glPopMatrix();	
	}
	//key
	if(!key)
	{
		glPushMatrix();
		//up
		glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2900,230,100);
		glTexCoord2f(1.0, 0.0);glVertex3f(2950,230,100);
		glTexCoord2f(1.0, 1.0);glVertex3f(2950,230,150);
		glTexCoord2f(0.0, 1.0);glVertex3f(2900,230,150);
		glEnd();
		//front
		glBegin(GL_QUADS);
		glColor3f(1,1,0);
		glTexCoord2f(0.0, 0.0);glVertex3f(2900,200,100);
		glTexCoord2f(0.0, 1.0);glVertex3f(2900,230,100);
		glTexCoord2f(1.0, 1.0);glVertex3f(2900,230,150);
		glTexCoord2f(1.0, 0.0);glVertex3f(2900,200,150);
		glEnd();
		//left
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2900,200,150);
		glTexCoord2f(1.0, 0.0);glVertex3f(2950,200,150);
		glTexCoord2f(1.0, 1.0);glVertex3f(2950,230,150);
		glTexCoord2f(0.0, 1.0);glVertex3f(2900,230,150);
		glEnd();
		//right
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2900,200,100);
		glTexCoord2f(1.0, 0.0);glVertex3f(2950,200,100);
		glTexCoord2f(1.0, 1.0);glVertex3f(2950,230,100);
		glTexCoord2f(0.0, 1.0);glVertex3f(2900,230,100);
		glEnd();
		//back
		glBegin(GL_QUADS);
		glColor3f(0,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2950,200,100);
		glTexCoord2f(1.0, 0.0);glVertex3f(2950,200,150);
		glTexCoord2f(1.0, 1.0);glVertex3f(2950,230,150);
		glTexCoord2f(0.0, 1.0);glVertex3f(2950,230,100);
		glEnd();

		glPopMatrix();	
	}
	//prize
	if(!prize)
	{
		glPushMatrix();
		//up
		glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glTexCoord2f(0.0, 1.0);glVertex3f(2400,230,-8800);
		glTexCoord2f(1.0, 1.0);glVertex3f(2450,230,-8800);
		glTexCoord2f(1.0, 0.0);glVertex3f(2450,230,-8850);
		glTexCoord2f(0.0, 0.0);glVertex3f(2400,230,-8850);
		glEnd();
		//front
		glBegin(GL_QUADS);
		glColor3f(1,1,0);
		glTexCoord2f(1.0, 0.0);glVertex3f(2400,200,-8800);
		glTexCoord2f(1.0, 1.0);glVertex3f(2400,230,-8800);
		glTexCoord2f(0.0, 1.0);glVertex3f(2400,230,-8850);
		glTexCoord2f(0.0, 0.0);glVertex3f(2400,200,-8850);
		glEnd();
		//left
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2400,200,-8850);
		glTexCoord2f(1.0, 0.0);glVertex3f(2450,200,-8850);
		glTexCoord2f(1.0, 1.0);glVertex3f(2450,230,-8850);
		glTexCoord2f(0.0, 1.0);glVertex3f(2400,230,-8850);
		glEnd();
		//right
		glBegin(GL_QUADS);
		glColor3f(1,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2400,200,-8800);
		glTexCoord2f(1.0, 0.0);glVertex3f(2450,200,-8800);
		glTexCoord2f(1.0, 1.0);glVertex3f(2450,230,-8800);
		glTexCoord2f(0.0, 1.0);glVertex3f(2400,230,-8800);
		glEnd();
		//back
		glBegin(GL_QUADS);
		glColor3f(0,0,1);
		glTexCoord2f(0.0, 0.0);glVertex3f(2450,200,-8850);
		glTexCoord2f(1.0, 0.0);glVertex3f(2450,200,-8800);
		glTexCoord2f(1.0, 1.0);glVertex3f(2450,230,-8800);
		glTexCoord2f(0.0, 1.0);glVertex3f(2450,230,-8850);
		glEnd();

		glPopMatrix();	
	}
	glDisable(GL_TEXTURE_2D);
}

void ResetGun()
{
 if(bulletsLeft<1)
 {
  gun = false;
  for(int i = 0; i < NUM_BULLETS; ++i){
   gunFired[i]=false;
   gunFireX[i]=0;

  } 
 }
 
}


void DrawRooms()
{


	glEnable(GL_TEXTURE_2D);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//static GLuint eboxTexture = LoadTexture("2_ice.ppm", 3456, 2304, false);
	//static GLuint eboxTexture = LoadTexture("Earth.ppm", 720, 360, false);
	//static GLuint eboxTexture = LoadTexture("assassins_creed_.bmp", 1366, 768, false);
	static GLuint eboxTexture = LoadTexture("Eskimo.bmp", 512, 512, true);

	glBindTexture(GL_TEXTURE_2D, eboxTexture);



	//Room1
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-1000);
	glTexCoord2f(1.0, 0.0);glVertex3f(1000,200,-1000);
	glTexCoord2f(1.0, 1.0);glVertex3f(1000,600,-1000);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-1000);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(400,200,-1600);
	glTexCoord2f(1.0, 0.0);glVertex3f(1000,200,-1600);
	glTexCoord2f(1.0, 1.0);glVertex3f(1000,600,-1600);
	glTexCoord2f(0.0, 1.0);glVertex3f(400,600,-1600);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(1.0, 0.0);glVertex3f(1000,200,-1000);
	glTexCoord2f(0.0, 0.0);glVertex3f(1000,200,-1600);
	glTexCoord2f(0.0, 1.0);glVertex3f(1000,600,-1600);
	glTexCoord2f(1.0, 1.0);glVertex3f(1000,600,-1000);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glEnable(GL_TEXTURE_2D);
	//Room2
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(1.0, 0.0);glVertex3f(100,200,-2700);
	glTexCoord2f(0.0, 0.0);glVertex3f(-500,200,-2700);
	glTexCoord2f(0.0, 1.0);glVertex3f(-500,600,-2700);
	glTexCoord2f(1.0, 1.0);glVertex3f(100,600,-2700);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(1.0, 0.0);glVertex3f(100,200,-3300);
	glTexCoord2f(0.0, 0.0);glVertex3f(-500,200,-3300);
	glTexCoord2f(0.0, 1.0);glVertex3f(-500,600,-3300);
	glTexCoord2f(1.0, 1.0);glVertex3f(100,600,-3300);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(1.0, 0.0);glVertex3f(-500,200,-2700);
	glTexCoord2f(0.0, 0.0);glVertex3f(-500,200,-3300);
	glTexCoord2f(0.0, 1.0);glVertex3f(-500,600,-3300);
	glTexCoord2f(1.0, 1.0);glVertex3f(-500,600,-2700);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);



	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	//Room4
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(2500,200,-2800);
	glTexCoord2f(1.0, 0.0);glVertex3f(2500,200,-2200);
	glTexCoord2f(1.0, 1.0);glVertex3f(2500,600,-2200);
	glTexCoord2f(0.0, 1.0);glVertex3f(2500,600,-2800);
	glEnd();
	glPopMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,-2800);
	glTexCoord2f(1.0, 0.0);glVertex3f(2500,200,-2800);
	glTexCoord2f(1.0, 1.0);glVertex3f(2500,600,-2800);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,-2800);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(1600,200,-2200);
	glTexCoord2f(1.0, 0.0);glVertex3f(2500,200,-2200);
	glTexCoord2f(1.0, 1.0);glVertex3f(2500,600,-2200);
	glTexCoord2f(0.0, 1.0);glVertex3f(1600,600,-2200);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);



	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	//Room5
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(2000,200,600);
	glTexCoord2f(1.0, 0.0);glVertex3f(3000,200,600);
	glTexCoord2f(1.0, 1.0);glVertex3f(3000,600,600);
	glTexCoord2f(0.0, 1.0);glVertex3f(2000,600,600);
	glEnd();
	glPopMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(1.0, 0.0);glVertex3f(2000,200,300);
	glTexCoord2f(0.0, 0.0);glVertex3f(2000,200,-400);
	glTexCoord2f(0.0, 1.0);glVertex3f(2000,600,-400);
	glTexCoord2f(1.0, 1.0);glVertex3f(2000,600,300);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(2000,200,-400);
	glTexCoord2f(1.0, 0.0);glVertex3f(3000,200,-400);
	glTexCoord2f(1.0, 1.0);glVertex3f(3000,600,-400);
	glTexCoord2f(0.0, 1.0);glVertex3f(2000,600,-400);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(3000,200,-400);
	glTexCoord2f(1.0, 0.0);glVertex3f(3000,200,600);
	glTexCoord2f(1.0, 1.0);glVertex3f(3000,600,600);
	glTexCoord2f(0.0, 1.0);glVertex3f(3000,600,-400);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();


	glEnable(GL_TEXTURE_2D);
	//Room6 (FINALROOM)
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(3.0, 0.0);glVertex3f(500,200,-9000);
	glTexCoord2f(0.0, 0.0);glVertex3f(500,200,-10500);
	glTexCoord2f(0.0, 1.0);glVertex3f(500,600,-10500);
	glTexCoord2f(3.0, 1.0);glVertex3f(500,600,-9000);
	glEnd();
	glPopMatrix();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(500,200,-8700);
	glTexCoord2f(3.0, 0.0);glVertex3f(500,200,-7200);
	glTexCoord2f(3.0, 1.0);glVertex3f(500,600,-7200);
	glTexCoord2f(0.0, 1.0);glVertex3f(500,600,-8700);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(500,200,-10500);
	glTexCoord2f(4.0, 0.0);glVertex3f(2500,200,-10500);
	glTexCoord2f(4.0, 1.0);glVertex3f(2500,600,-10500);
	glTexCoord2f(0.0, 1.0);glVertex3f(500,600,-10500);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(0.0, 0.0);glVertex3f(500,200,-7200);
	glTexCoord2f(4.0, 0.0);glVertex3f(2500,200,-7200);
	glTexCoord2f(4.0, 1.0);glVertex3f(2500,600,-7200);
	glTexCoord2f(0.0, 1.0);glVertex3f(500,600,-7200);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glTexCoord2f(6.0, 0.0);glVertex3f(2500,200,-7200);
	glTexCoord2f(0.0, 0.0);glVertex3f(2500,200,-10500);
	glTexCoord2f(0.0, 1.0);glVertex3f(2500,600,-10500);
	glTexCoord2f(6.0, 1.0);glVertex3f(2500,600,-7200);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
	glPushMatrix();
	for (int i = 0; i < numSnowMen; ++i)
	{

		Snowmen[i].Draw();
	}
	glPopMatrix();
}

void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *string) {

	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderStrokeFontString(
		float x,
		float y,
		float z,
		void *font,
		char *string) {  

	char *c;
	glPushMatrix();
	glTranslatef(x, y,z);
	glScalef(0.002f, 0.002f, 0.002f);
	for (c=string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}
	glPopMatrix();
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, windowWidth , windowHeight, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}void SnowMenCheck(){

	for (int i = 0; i < numSnowMen; ++i)
	{
	if(Snowmen[i].moveInX){
	if(Snowmen[i].x >= Snowmen[i].maxX || Snowmen[i].x <= Snowmen[i].minX){
		Snowmen[i].reverseX = !Snowmen[i].reverseX;
	}
	if(Snowmen[i].reverseX){
		Snowmen[i].x -= 2;
	}else{
		Snowmen[i].x += 2;
	}
	}else{
	if(Snowmen[i].z >= Snowmen[i].maxZ || Snowmen[i].z <= Snowmen[i].minZ){
		Snowmen[i].reverseZ = !Snowmen[i].reverseZ;
	}
	if(Snowmen[i].reverseZ){
		Snowmen[i].z -=2;
	}else{
		Snowmen[i].z +=2;
	}
	}
	if(Snowmen[i].aLive && Snowmen[i].fired == true){
		Snowmen[i].carrotPos +=10;	
	}
	
	


	
	

	for (int i = 0; i < numSnowMen; ++i)
	{
		for (int j = 0; j < NUM_BULLETS; ++j)
		{
			//if(Snowmen[i].fireInX){
			if(abs(actualBulletX[j] - Snowmen[i].x) <= 50 && abs(actualBulletZ[j]-Snowmen[i].z) <= 50){
				Snowmen[i].aLive = false;

			}
			/*else{
				if(abs(actualBulletX[j] - Snowmen[i].z) <= 100 && abs(actualBulletZ[j]-Snowmen[i].x) <= 100){
				Snowmen[i].aLive = false;
			}
			}*/
		}
		if(Snowmen[i].aLive){
		if(abs(Snowmen[i].actualCarrotPosX-camx)<= 50 && abs(Snowmen[i].lastZ - camz) <= 50){
			life -= 5;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			
		}else{
			if(abs(Snowmen[i].actualCarrotPosZ-camz)<= 50 && abs(Snowmen[i].lastX - camx) <= 50){
			life -= 5;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			
		}
		}
	}
		
		if(i == 0 || i ==1 || i ==2){
			if((!Snowmen[i].fireInX) &&(Snowmen[i].actualCarrotPosZ > -1050 || Snowmen[i].actualCarrotPosZ < -1550) ){
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door1State== OPENED && Snowmen[i].actualCarrotPosX < 150){
				//cout << Snowmen[i].actualCarrotPosX << "," << "OPENED" << endl;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door1State!= OPENED && Snowmen[i].actualCarrotPosX < 450){
				//cout << Snowmen[i].actualCarrotPosX << "," << "!OPENED" << endl;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
				
			}
		}

		if(i == 3 || i ==4 || i ==5){
			if((!Snowmen[i].fireInX) &&(Snowmen[i].actualCarrotPosZ > -2750 || Snowmen[i].actualCarrotPosZ < -3250) ){
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door2State== OPENED && Snowmen[i].actualCarrotPosX > 350){
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door2State!= OPENED && Snowmen[i].actualCarrotPosX > 50){
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
				
			}
		}
		//1600 2500 -2200 -2800
			if(i == 6 || i ==7 || i ==8){
			if((!Snowmen[i].fireInX) &&(Snowmen[i].actualCarrotPosZ > -2250 || Snowmen[i].actualCarrotPosZ < -2750) ){
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door4State== OPENED && Snowmen[i].actualCarrotPosX < 1350){
			//	cout << Snowmen[i].actualCarrotPosX << "," << "OPENED" << endl;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door4State!= OPENED && Snowmen[i].actualCarrotPosX < 1650){
			//	cout << Snowmen[i].actualCarrotPosX << "," << "!OPENED" << endl;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
				
			}
		}
		// 2000 3000 -400 600
			if(i == 9 || i ==10 || i ==11){
			if((!Snowmen[i].fireInX) &&(Snowmen[i].actualCarrotPosZ > 550 || Snowmen[i].actualCarrotPosZ < -350) ){
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door5State== OPENED && Snowmen[i].actualCarrotPosX < 1350){
				//cout << Snowmen[i].actualCarrotPosX << "," << "OPENED" << endl;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door5State!= OPENED && Snowmen[i].actualCarrotPosX < 2050){
				//cout << Snowmen[i].actualCarrotPosX << "," << "!OPENED" << endl;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
				
			}
		}
		// 500 2500 -7200 -10500
		if(i == 12 || i ==13 || i ==14 || i == 15 || i == 16 ){
			if((!Snowmen[i].fireInX) &&(Snowmen[i].actualCarrotPosZ > -7250 || Snowmen[i].actualCarrotPosZ < -10450) ){
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door6State== OPENED && Snowmen[i].actualCarrotPosX < - 1950){
				//cout << Snowmen[i].actualCarrotPosX << "," << "OPENED" << endl;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
			}
			if((Snowmen[i].fireInX) && door6State!= OPENED && Snowmen[i].actualCarrotPosX < 550){
				//cout << Snowmen[i].actualCarrotPosX << "," << "!OPENED" << endl;
			Snowmen[i].fired = false;
			Snowmen[i].carrotPos = 0;
			Snowmen[i].Draw();
			Snowmen[i].fired = true;
				
			}
		}
			
		
		if(life < 0){
			//GameOver
		}
		

	}
}
	
	
}
void DrawGun(){
GunShot();

	glPushMatrix();
	glTranslated(camx, 240 ,camz); 
	glRotatef(90+camangle,0,1,0);
	glColor3f(0,0,0);
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj,GLU_FILL);
	gluCylinder(qobj, 10, 10, 150, 8,8);
	for (int i = 0; i < NUM_BULLETS; ++i)
	{
		if(!gunFired[i]){

		gunFireAngle[i] = camangle;
		gunLastX[i] = camx;
		gunLastZ[i] = camz;
	}	
	}
	
	glutPostRedisplay();
	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i < NUM_BULLETS; ++i)
	{
		if(gunFired[i]){
		glColor3f(1,0,0);
		glColor3f(1,0,0);
		glTranslated(gunLastX[i], 280 ,gunLastZ[i]); 
		glRotatef(gunFireAngle[i],0,1,0);
		glTranslated(gunFireX[i],0,0);
		glutSolidSphere(5,5,5);
		cout << actualBulletX[i] << "," <<  actualBulletZ[i] <<"," << gunFireAngle[i] <<"Snowman 0 " << Snowmen[1].x <<","<<Snowmen[1].z << endl;
		/*glTranslated(actualBulletX[i],280,actualBulletZ[i]);*/
		glutSolidSphere(5,5,5);
	}
	}
	
	glPopMatrix();
}

void Display()
{
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	if(gameState==START){


		mciSendString(L"play laugh.mp3", NULL, 0, 0); //Change mp3 file

		setOrthographicProjection();
		void *font= GLUT_BITMAP_9_BY_15;
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1,1,0);
		
		

		char temp[]="Santa has kidnapped you and trapped you in his maze.";
		char temp1[]="You must find your way out without letting his evil ghost snowmen kill you.";
		char temp2[]="Press Page Down to begin...";
		renderBitmapString(420,360,0,font,temp);
		renderBitmapString(340,390,0,font,temp1);
		renderBitmapString(500,420,0,font,temp2);
		glPopMatrix();


	}

	if(gameState==PLAY)
	{
		if(firstTime)
	{
		firstTime=false;
		gameStartTime=time(NULL);
		mciSendString(L"stop laugh.mp3", NULL, 0, 0); //Change mp3 file
	}
		mciSendString(L"play Santa.mp3", NULL, 0, 0); //Change mp3 file
		mciSendString(L"setaudio Santa.mp3 volume to 200", NULL, 0, 0);

		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov,asp,near1,far1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(camx,camy,camz,
				  gazex,gazey,gazez,
				  0,		1,	0);	
		RotateRight();
		MoveForward();
		DrawWalls();
		DrawDoors();
		DrawRooms();
		if(gun){
		DrawGun();
		sprintf(bulletsLeftString,"bullets Left: %3.0i",
			bulletsLeft);	
		
		}
		DrawBoxes();

		sprintf(lifeString,"Energy level: %3.0f",
			life);
		setOrthographicProjection();
		void *font= GLUT_BITMAP_8_BY_13;
		glPushMatrix();
		glLoadIdentity();
		renderBitmapString(30,30,0,font,lifeString);
		if(gun){
		renderBitmapString(windowWidth/2-13,270,0,font,(char*)"[+]");
		if(bulletsLeft>0)
		renderBitmapString(30,50,0,font,bulletsLeftString);
		}
		glPopMatrix();
		restorePerspectiveProjection();
	}
	else
	if(gameState==LOST)
	{

		if(!LoseStart){
			startLose =  time(NULL);
			mciSendString(L"setaudio Santa.mp3 volume to 50", NULL, 0, 0);
			mciSendString(L"stop Viper.mp3", NULL, 0, 0);
			mciSendString(L"stop Heal.mp3", NULL, 0, 0);
			mciSendString(L"stop door.mp3", NULL, 0, 0);
			mciSendString(L"stop gun.mp3", NULL, 0, 0);
			mciSendString(L"play Orsi.mp3", NULL, 0, 0);
			mciSendString(L"setaudio Orsi.mp3 volume to 1000", NULL, 0, 0);

			LoseStart = true;
			SantaStart =  false;
			ViperStart =  false;
			HealStart = false;
			}

		setOrthographicProjection();
		void *font= GLUT_BITMAP_8_BY_13;
		glPushMatrix();
		glLoadIdentity();





	static GLuint eboxTexture1 = LoadTexture("assassin.bmp", 1366, 768, true);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, eboxTexture1);
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);glVertex3f(-20,0,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(-20,1000,0);
	glTexCoord2f(1.0, 0.0);glVertex3f(1300,1000,0);
	glTexCoord2f(1.0, 1.0);glVertex3f(1300,0,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();







		char temp[]="LOSAR";
		renderBitmapString(640,360,0,font,temp);
		glPopMatrix();
	}
	else
	if(gameState==WON)
	{
		if(!WinStart){
			startWin =  time(NULL);
			mciSendString(L"setaudio Santa.mp3 volume to 50", NULL, 0, 0);
			mciSendString(L"stop Viper.mp3", NULL, 0, 0);
			mciSendString(L"stop Heal.mp3", NULL, 0, 0);
			mciSendString(L"stop door.mp3", NULL, 0, 0);
			mciSendString(L"stop gun.mp3", NULL, 0, 0);
			mciSendString(L"play bloody.mp3", NULL, 0, 0);
			mciSendString(L"setaudio bloody.mp3 volume to 1000", NULL, 0, 0);
			WinStart = true;
			SantaStart =  false;
			ViperStart =  false;
			HealStart = false;
			}

		setOrthographicProjection();
		void *font= GLUT_BITMAP_8_BY_13;
		glPushMatrix();
		glLoadIdentity();
		if(!done)
		{
		lastTime=time(NULL);
		done=true;
		}
		static GLuint eboxTexture1 = LoadTexture("fireworks.bmp", 1280, 768, true);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, eboxTexture1);
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);glVertex3f(-20,0,0);
	glTexCoord2f(0.0, 0.0);glVertex3f(-20,1000,0);
	glTexCoord2f(1.0, 0.0);glVertex3f(1300,1000,0);
	glTexCoord2f(1.0, 1.0);glVertex3f(1300,0,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	}
	glutSwapBuffers();
}
void OpenDoor()
{
	switch(door)
	{
		case 1:if(door1State==CLOSED)door1State=OPENING;break;
		case 2:if(door2State==CLOSED)door2State=OPENING;break;
		case 4:if(door4State==CLOSED)door4State=OPENING;break;
		case 5:if(door5State==CLOSED)door5State=OPENING;break;
		case 6:if(door6State==CLOSED&&key)door6State=OPENING;break;
	}
}
void MyKeyboard(int thekey, int mouseX, int mouseY)
{
	switch(thekey)
	{
		case GLUT_KEY_LEFT: {CAMrot = 1;break;}
		case GLUT_KEY_RIGHT: {CAMrot = -1;break;}
		case GLUT_KEY_UP: {CAMStride = 5;break;}
		case GLUT_KEY_DOWN: {CAMStride = -5;break;}
		case GLUT_KEY_END: {OpenDoor();break;}
		case GLUT_KEY_HOME: {SwitchCAM();break;}
		case GLUT_KEY_PAGE_DOWN: {gameState = PLAY;break;}
		case GLUT_KEY_PAGE_UP: {if(bulletsLeft>0){ cout << bulletsLeft << endl; bulletsLeft = bulletsLeft-1;gunFired[bulletsLeft]= true;
							   
			if(!GunStart){
			startGun =  time(NULL);
			mciSendString(L"play gun.mp3", NULL, 0, 0); //Change mp3 file
			mciSendString(L"setaudio gun.mp3 volume to 1000", NULL, 0, 0);

			
			GunStart = true;
			SantaStart =  false;
			}
							   
							   }break;}
	}
}
void anim(int num)
{
			CheckHp();
			ResetGun();
			if(door1State==OPENING&&d1z1<d1z2)
				d1z1+=1;
			else
			{
				if(door1State==OPENING&&d1z1>=d1z2)
				{
					door1State=OPENED;
					time1Opened=time(NULL);	
				}
				if(door1State == OPENED){

					Snowmen[0].fired = true;
					Snowmen[1].fired = true;
					Snowmen[2].fired = true;
				}
				if((door1State==OPENED||door1State==CLOSING)&&time(NULL)-time1Opened>=10&&!Collided(camx,camz))
				{
					 if(d1z1>=d1temp)
					 {
					 	door1State=CLOSING;
					 	d1z1-=1;
					 }
					 else
					 {
						door1State=CLOSED;
						time1Opened=0;

					 }	
				}
			}
			if(door2State==OPENING&&d2z1<d2z2)
				d2z1+=1;
			else
			{
				if(door2State==OPENING&&d2z1>=d2z2)
				{
					door2State=OPENED;
					time2Opened=time(NULL);	
				}
				if(door2State==OPENED){
					Snowmen[3].fired = true;
					Snowmen[4].fired = true;
					Snowmen[5].fired = true;
				}
				if((door2State==OPENED||door2State==CLOSING)&&time(NULL)-time2Opened>=10&&!Collided(camx,camz))
				{
					 if(d2z1>=d2temp)
					 {
					 	door2State=CLOSING;
					 	d2z1-=1;
					 }
					 else
					 {
						door2State=CLOSED;
						time2Opened=0;

					 }	
				}
			}
			if(door4State==OPENING&&d4z1<d4z2)
				d4z1+=1;
			else
			{
				if(door4State==OPENING&&d4z1>=d4z2)
				{
					door4State=OPENED;
					time4Opened=time(NULL);	
				}
				if(door4State == OPENED ){
					Snowmen[6].fired = true;
					Snowmen[7].fired = true;
					Snowmen[8].fired = true;
				}
				if((door4State==OPENED||door4State==CLOSING)&&time(NULL)-time4Opened>=10&&!Collided(camx,camz))
				{
					 if(d4z1>=d4temp)
					 {
					 	door4State=CLOSING;
					 	d4z1-=1;
					 }
					 else
					 {
						door4State=CLOSED;
						time4Opened=0;

					 }	
				}
			}
			if(door5State==OPENING&&d5z1<d5z2)
				d5z1+=1;
			else
			{
				if(door5State==OPENING&&d5z1>=d5z2)
				{
					door5State=OPENED;
					time5Opened=time(NULL);	
				}
			if(door5State == OPENED ){
					Snowmen[9].fired = true;
					Snowmen[10].fired = true;
					Snowmen[11].fired = true;
				}
				if((door5State==OPENED||door5State==CLOSING)&&time(NULL)-time5Opened>=10&&!Collided(camx,camz))
				{
					 if(d5z1>=d5temp)
					 {
					 	door5State=CLOSING;
					 	d5z1-=1;
					 }

					 else
					 {
						door5State=CLOSED;
						time5Opened=0;

					 }	
				}
			}
			if(door6State==OPENING&&d6z1<d6z2)
				d6z1+=1;
			else
			{
				if(door6State==OPENING&&d6z1>=d6z2)
				{
					door6State=OPENED;
					time6Opened=time(NULL);	
				}
				if(door6State == OPENED ){
					Snowmen[12].fired = true;
					Snowmen[13].fired = true;
					Snowmen[14].fired = true;
					Snowmen[15].fired = true;
					Snowmen[16].fired = true;
				}
				if((door6State==OPENED||door6State==CLOSING)&&time(NULL)-time6Opened>=10&&!Collided(camx,camz))
				{
					 if(d6z1>=d6temp)
					 {
					 	d6z1-=1;
					 	door6State=CLOSING;
					 								
					 }
					 else
					 {
						door6State=CLOSED;
						time6Opened=0;

					 }	
				}
	}
	for (int i = 0; i < NUM_BULLETS; ++i)
	{
		if(gunFired[i]){
		gunFireX[i]+=40;
	}
	}

	SnowMenCheck();







	if(!SantaStart){

		if(ViperStart){

			if(time(NULL) - startViper > 3){
				mciSendString(L"stop Viper.mp3", NULL, 0, 0); //Change mp3 file
				mciSendString(L"setaudio Santa.mp3 volume to 200", NULL, 0, 0);
				ViperStart =  false;
				SantaStart =  true;
			}

		}

		if(HealStart){

			if(time(NULL) - startHeal > 4){
				mciSendString(L"stop Heal.mp3", NULL, 0, 0); //Change mp3 file
				mciSendString(L"setaudio Santa.mp3 volume to 200", NULL, 0, 0);
				HealStart =  false;
				SantaStart =  true;
			}

		}


		if(GunStart){
			if(time(NULL) - startGun > 1){
			mciSendString(L"stop gun.mp3", NULL, 0, 0);
			GunStart =  false;
			SantaStart =  true;
			}
		}

		if(KeyStart){
			if(time(NULL) - startKey > 9){
			mciSendString(L"stop door.mp3", NULL, 0, 0);
			mciSendString(L"setaudio Santa.mp3 volume to 200", NULL, 0, 0);
			KeyStart =  false;
			SantaStart =  true;
			}
		}



		if(WinStart){
			if(time(NULL) - startWin > 3){
			mciSendString(L"stop bloody.mp3", NULL, 0, 0);
			mciSendString(L"setaudio Santa.mp3 volume to 200", NULL, 0, 0);
			SantaStart =  true;
			}
		}


		if(LoseStart){
			if(time(NULL) - startLose > 8){
			mciSendString(L"stop Orsi.mp3", NULL, 0, 0);
			mciSendString(L"setaudio Santa.mp3 volume to 200", NULL, 0, 0);
			SantaStart =  true;
			}
		}


		


	}









	if(CAMStride == 0 && CAMrot == 0){
	mciSendString(L"pause walk.mp3", NULL, 0, 0);
	}
	else{
		mciSendString(L"play walk.mp3", NULL, 0, 0);
	}










	glutPostRedisplay();
	glutTimerFunc(30,anim,0);
}

void releaseKey(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT: {CAMrot = 0;break;}
		case GLUT_KEY_RIGHT: {CAMrot = 0;break;}
		case GLUT_KEY_UP: {CAMStride = 0;break;}
		case GLUT_KEY_DOWN: {CAMStride = 0;break;}
	}
}
void initializeSnowMen(){
	//room 1
	Snowmen[0].x= 825; 
	Snowmen[0].z= -1060;
	Snowmen[0].reverseX = false;
	Snowmen[0].maxX = 900;
	Snowmen[0].minX = 750;
	Snowmen[0].maxZ = -1060;
	Snowmen[0].minZ = -1500;
	Snowmen[0].moveInX = true;

	Snowmen[1].x = 600;
	Snowmen[1].z = -1300;
	Snowmen[1].reverseX = true;
	Snowmen[1].maxX = 750;
	Snowmen[1].minX = 500;
	Snowmen[1].maxZ = -1100;
	Snowmen[1].minZ = -1500;
	Snowmen[1].moveInX = true;
	Snowmen[1].fireInX = true;

	Snowmen[2].x = 825;
	Snowmen[2].z = -1540;
	Snowmen[2].reverseX = true;
	Snowmen[2].maxX = 900;
	Snowmen[2].minX = 750;
	Snowmen[2].maxZ = -1100;
	Snowmen[2].minZ = -1560;
	Snowmen[2].moveInX = true;

	//room2 

	Snowmen[3].x= -325; 
	Snowmen[3].z= -3200;
	Snowmen[3].reverseX = true;
	Snowmen[3].maxX = -250;
	Snowmen[3].minX = -400;
	Snowmen[3].maxZ = -2800;
	Snowmen[3].minZ = -3200;
	Snowmen[3].moveInX = true;
	
	Snowmen[4].x= -150; 
	Snowmen[4].z= -3000;
	Snowmen[4].reverseX = false;
	Snowmen[4].maxX = 0;
	Snowmen[4].minX = -250;
	Snowmen[4].maxZ = -2800;
	Snowmen[4].minZ = -3200;
	Snowmen[4].moveInX = true;
	Snowmen[4].fireInX = true;

	Snowmen[5].x= -325; 
	Snowmen[5].z= -2800;
	Snowmen[5].reverseX = false;
	Snowmen[5].maxX = -250;
	Snowmen[5].minX = -400;
	Snowmen[5].maxZ = -2800;
	Snowmen[5].minZ = -3200;
	Snowmen[5].moveInX = true;
	//room 3  1600 2500 -2200 -2800

	Snowmen[6].x= 2250; 
	Snowmen[6].z= -2300;
	Snowmen[6].reverseX = true;
	Snowmen[6].maxX = 2400;
	Snowmen[6].minX = 2100;
	Snowmen[6].maxZ = -2300;
	Snowmen[6].minZ = -2700;
	Snowmen[6].moveInX = true;

	Snowmen[7].x= 1800; 
	Snowmen[7].z= -2500;
	Snowmen[7].reverseX = false;
	Snowmen[7].maxX = 2000;
	Snowmen[7].minX = 1700;
	Snowmen[7].maxZ = -2300;
	Snowmen[7].minZ = -2700;
	Snowmen[7].moveInX = true;
	Snowmen[7].fireInX = true;

	Snowmen[8].x= 2250; 
	Snowmen[8].z= -2700;
	Snowmen[8].reverseX = false;
	Snowmen[8].maxX = 2400;
	Snowmen[8].minX = 2100;
	Snowmen[8].maxZ = -2300;
	Snowmen[8].minZ = -2700;
	Snowmen[8].moveInX = true;

	// room 4
	// 2000 3000 -400 600
	Snowmen[9].x= 2750; 
	Snowmen[9].z= -300;
	Snowmen[9].reverseX = false;
	Snowmen[9].maxX = 2900;
	Snowmen[9].minX = 2600;
	Snowmen[9].maxZ = 500;
	Snowmen[9].minZ = -300;
	Snowmen[9].moveInX = true;


	Snowmen[10].x= 2750; 
	Snowmen[10].z= 500;
	Snowmen[10].reverseX = true;
	Snowmen[10].maxX = 2900;
	Snowmen[10].minX = 2600;
	Snowmen[10].maxZ = 500;
	Snowmen[10].minZ = -300;
	Snowmen[10].moveInX = true;

	Snowmen[11].x= 2300; 
	Snowmen[11].z= 450;
	Snowmen[11].reverseX = false;
	Snowmen[11].maxX = 2400;
	Snowmen[11].minX = 2100;
	Snowmen[11].maxZ = 500;
	Snowmen[11].minZ = -300;
	Snowmen[11].moveInX = true;
	Snowmen[11].fireInX = true;

	// room 5
	// 500 2500 -7200 -10500
	Snowmen[12].x= 700; 
	Snowmen[12].z= -8850;
	Snowmen[12].reverseX = false;
	Snowmen[12].maxX = 900;
	Snowmen[12].minX = 600;
	Snowmen[12].maxZ = -7300;
	Snowmen[12].minZ = -10400;
	Snowmen[12].moveInX = true;
	Snowmen[12].fireInX = true;

	Snowmen[13].x= 1150; 
	Snowmen[13].z= -7300;
	Snowmen[13].reverseX = true;
	Snowmen[13].maxX = 1300;
	Snowmen[13].minX = 1000;
	Snowmen[13].maxZ = -7300;
	Snowmen[13].minZ = -10400;
	Snowmen[13].moveInX = true;

	Snowmen[14].x= 1150; 
	Snowmen[14].z= -10400;
	Snowmen[14].reverseX = false;
	Snowmen[14].maxX = 1300;
	Snowmen[14].minX = 1000;
	Snowmen[14].maxZ = -7300;
	Snowmen[14].minZ = -10400;
	Snowmen[14].moveInX = true;

	Snowmen[15].x= 1900; 
	Snowmen[15].z= -7300;
	Snowmen[15].reverseX = true;
	Snowmen[15].maxX = 2200;
	Snowmen[15].minX = 1600;
	Snowmen[15].maxZ = -7300;
	Snowmen[15].minZ = -10400;
	Snowmen[15].moveInX = true;

	Snowmen[16].x= 1900; 
	Snowmen[16].z= -10400;
	Snowmen[16].reverseX = false;
	Snowmen[16].maxX = 2200;
	Snowmen[16].minX = 1600;
	Snowmen[16].maxZ = -7300;
	Snowmen[16].minZ = -10400;
	Snowmen[16].moveInX = true;


	
	//rotations
	Snowmen[0].rotation = 90;
	Snowmen[1].rotation = 0;
	Snowmen[2].rotation = -90;
	Snowmen[3].rotation = -90;
	Snowmen[4].rotation = 180;
	Snowmen[5].rotation = 90;
	Snowmen[6].rotation = 90;
	Snowmen[7].rotation = 0;
	Snowmen[8].rotation = -90;
	Snowmen[9].rotation = -90;
	Snowmen[10].rotation = 90;
	Snowmen[11].rotation = 0;
	Snowmen[12].rotation = 0;
	Snowmen[13].rotation = 90;
	Snowmen[14].rotation = -90;
	Snowmen[15].rotation = 90;
	Snowmen[16].rotation = -90;
	
}
int main(int argc,char** argr)
{
	FillMap();

	glutInit(&argc,argr);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Maze");
	for (int i = 0; i < numSnowMen; ++i)
	{
		new (&Snowmen[i]) SnowMan(0,0,0,0);
	}

	initializeSnowMen();

	glutDisplayFunc(Display);
	glutTimerFunc(60,anim,0);


	glutSpecialFunc(MyKeyboard);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
	
	glEnable(GL_NORMALIZE);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glViewport(0,0,1280,900);
	glutMainLoop();
}