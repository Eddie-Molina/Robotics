/*
 \file		Project2.c
 \author	Peter Dang, Eddie Molina, Roberto Villazana, Van Ta
 \date		11/28/18
 \brief		Project 2 candle 
*/

#include <ev3.h>

void Forward();
void Stop();
void Right();
void Left();
void Rightq();
void Leftq();
void Reverse();
void endSong();


int x = 0;


int main(void)
{

	InitEV3();
	setAllSensorMode(TOUCH_PRESS,TOUCH_PRESS,US_DIST_MM,COL_COLOR);
	Forward();
	Stop();
	endSong();
	FreeEV3();
	return 0;
}

void Right()
{
	OnFwdReg(OUT_A,0);
	OnRevReg(OUT_D,46);
	Wait(MS_500);
	OnFwdReg(OUT_A,39);
	OnRevReg(OUT_D,0);
	Wait(MS_400);
}

void Left()
{
	OnFwdReg(OUT_D,0);
	OnRevReg(OUT_A,46);
	Wait(MS_500);
	OnFwdReg(OUT_D,41);
	OnRevReg(OUT_A,0);
	Wait(MS_400);

}

void Rightq()
{
	OnFwdReg(OUT_A,0);
	OnRevReg(OUT_D,20);
	Wait(MS_600);
	OnFwdReg(OUT_A,20);
	OnRevReg(OUT_D,0);
	Wait(MS_700);
}

void Leftq()
{
	OnFwdReg(OUT_D,0);
	OnRevReg(OUT_A,20);
	Wait(MS_300);
	OnFwdReg(OUT_D,20);
	OnRevReg(OUT_A,0);
	Wait(MS_100);
}

void Forward()
{

	int a = 0;

	double old = 0;
	double new = 0;
	int flag = 0;

	while(1)
	{


		if (readSensor(IN_1) == 1 && readSensor(IN_2) != 1)
		{
			a++;

			if (a == 50)
			{
				Reverse();
				Reverse();
				Right();
				a = 0;
			}
		}

		if (readSensor(IN_2) == 1 && readSensor(IN_1) != 1)
		{
			a++;

			if (a == 30)
			{
				Reverse();
				Reverse();
				Right();
				a = 0;
			}
		}

		if (readSensor(IN_1) == 1 && readSensor(IN_2) == 1)
		{
			Reverse();
			Reverse();
			Right();
		}

		if (readSensor(IN_3) <= 100)
		{
			OnFwdReg(OUT_A,19);
			OnFwdReg(OUT_D,18);
			Wait(MS_100);
			x = 0;
		}
		else if (readSensor(IN_3) >= 103 && readSensor(IN_3) < 200)
		{
			OnFwdReg(OUT_A,18);
			OnFwdReg(OUT_D,19);
			Wait(MS_100);

		}
		else if (readSensor(IN_3) > 100 && (readSensor(IN_3) < 103))
		{
			OnFwdReg(OUT_A,18);
			OnFwdReg(OUT_D,18);
			Wait(MS_100);
		}

		if (readSensor(IN_3) > 200)
		{
			OnFwdReg(OUT_A,18);
			OnFwdReg(OUT_D,18);
			Wait(SEC_1);
			Wait(MS_200);
			Left();
			OnFwdReg(OUT_A,18);
			OnFwdReg(OUT_D,18);
			Wait(SEC_3);
		}

		if (readSensor(IN_4) == 2)		//	break once robot reaches destination
		{
			break;
		}

	}
}

void Reverse()
{
	OnRevReg(OUT_A,15);
	OnRevReg(OUT_D,15);
	Wait(MS_300);
}

void Stop()
{
	OnFwdReg(OUT_A,0);
	OnFwdReg(OUT_D,0);
	Wait(MS_100);
}

void endSong()
{
	double c5 = 523.25;
	double e5 = 659.25;
	double g5 = 783.99;
	double d5 = 587.33;
	double f5 = 698.46;
	double bf5 = 932.33;
	double b5 = 987.77;
	double a5 = 880;
	double af5 = 830.61;
	double gf5 = 739.99;
	double ef5 = 622.25;


	double c = 1046.50;


	PlayTone(c,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(b5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(bf5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(b5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(bf5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(a5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(bf5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(a5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(af5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(a5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(af5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(g5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(af5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(g5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(gf5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(g5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(gf5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(f5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(gf5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(f5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(e5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(ef5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(e5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(ef5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(d5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(ef5,NOTE_EIGHT);
	Wait(MS_100);


}
