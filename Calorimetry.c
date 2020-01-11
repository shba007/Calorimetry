#include <stdio.h>
#include <stdlib.h>

int sign(float value);
int Lheat(float value, int n);
int Sheat(float value, int n);
int condition(float q, int n);

const char phase_name[][8] = {"Solid", "Liquid", "Gas"};

struct Thermal
{
	char name[16];
	float spc_heat[3];
	float lat_heat[2];
	float thm_point[4];
	float mass[2];
	float temp;
	int phase; //For Solid 0, Liquid 1, Gas 2;
};

struct Thermal obj[] = {{"Water", {0.5, 1, 0.47}, {80, 540}, {-273.15, 0, 100, 10000}}};

int main()
{

	int n = 0;
	float Q, q, max_heat;

	/* printf("\nChoose Element:-\n\n1.Water\n\nEnter option: ");
	scanf("%d", &n);
	n -= 1; */
	printf("\nEnter the Mass of %s(in gram): ", obj[n].name);
	scanf("%f", &obj[n].mass[0]);
	printf("\nEnter the phase of %s(1.Solid/2.Liquid/3.Gas): ", obj[n].name);
	scanf("%d", &obj[n].phase);
	obj[n].phase -= 1;
	printf("\nEnter the Temperature of %s(In Celsius): ", obj[n].name);
	scanf("%f", &obj[n].temp);
	printf("\nEnter the amount of heat to give(in Calorie)[+ve to give -ve to take]: ");
	scanf("%f", &q);
	Q = q;

	while (q)
	{
		switch (condition(q, n))
		{
		//Latent Heat Conversation
		case 1:
			max_heat = obj[n].mass[0] * obj[n].lat_heat[Lheat(q, n)] * sign(q);
			if ((q > 0 && q >= max_heat) || (q < 0 && q <= max_heat))
			{
				q -= max_heat;
				obj[n].phase += sign(q);
			}
			else
			{
				obj[n].mass[1] = (q / obj[n].lat_heat[Lheat(q, n)]) * sign(q);
				obj[n].mass[0] -= obj[n].mass[1];
				q = 0;
			}
			break;
		//Specific Heat conversation
		case 2:
			max_heat = obj[n].mass[0] * obj[n].spc_heat[obj[n].phase] * (obj[n].thm_point[Sheat(q, n)] - obj[n].temp);
			if ((q > 0 && q >= max_heat) || (q < 0 && q <= max_heat))
			{
				q -= max_heat;
				obj[n].temp = obj[n].thm_point[Sheat(q, n)];
			}
			else
			{
				obj[n].temp += q / (obj[n].mass[0] * obj[n].spc_heat[obj[n].phase]);
				q = 0;
			}
			break;
		}
		printf("\nTemperature is %.2f phase %s Heat remaining %.2f\n", obj[n].temp, phase_name[obj[n].phase], q);
		system("pause");
	}
	//Phase
	printf("\nThe final temperature of %s is %.2f%cC %s remaining %.2fg and transferred to %s is %.2f\n", obj[n].name, obj[n].temp, 248, phase_name[obj[n].phase], obj[n].mass[0], phase_name[obj[n].phase + sign(Q)], obj[n].mass[1]);
	getchar();
	return 0;
}

int sign(float value)
{
	if (value >= 0)
		return (1);
	else
		return (-1);
}

int Lheat(float value, int n)
{
	if (value >= 0)
		return (obj[n].phase);
	else
		return (obj[n].phase - 1);
}

int Sheat(float value, int n)
{
	if (value >= 0)
		return (obj[n].phase + 1);
	else
		return (obj[n].phase);
}

int condition(float q, int n)
{
	if (obj[n].temp == obj[n].thm_point[1] && q > 0 && obj[n].phase == 0)
		return 1;
	else if (obj[n].temp == obj[n].thm_point[2] && q > 0 && obj[n].phase == 1)
		return 1;
	else if (obj[n].temp == obj[n].thm_point[1] && q < 0 && obj[n].phase == 1)
		return 1;
	else if (obj[n].temp == obj[n].thm_point[2] && q < 0 && obj[n].phase == 2)
		return 1;
	else
		return 2;
}