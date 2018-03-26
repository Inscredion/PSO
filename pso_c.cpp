#include<iostream>
#include<cmath>
using namespace std;

#define MAX 100												//�������������� 
#define PNUM 50												//������Ⱥ���� 
#define get_rand(a,b) ((double)rand()/RAND_MAX)*(b-a) + a 	//��������� 
#define INF -99999999

double gbest = INF;												//������Ⱥ���Ž� 
double c1 = 0.5;												//����ѧϰ����c1 
double c2 = 0.5;												//����ѧϰ����c2 

struct pso{												
	double vel;												//���������ٶ� 
	double pos;												//��������λ�� 
	double pbest;											//�������Ž� 
};																	 
pso a[PNUM];												

double cal_v(double vel,double pos,double p);					//�ٶȸ���	
double func(double x);										//���	
double cal_p(double old_p,double v);							//λ�ø���	

int main(){	
	for(int i=0;i < PNUM ;i++){								//�����ʼ���������� 
		a[i].vel = get_rand(-1,1);
		a[i].pos = get_rand(0,20);
		a[i].pbest = func(a[i].pos);
 	}
	int index = 0;
	while(index<MAX)										//������ʼ 
	{
		for(int i=0;i < PNUM ;i++)							//Ѱ��ȫ�����Ž� 
		{
			if(gbest < func(a[i].pos))
				gbest = func(a[i].pos);
 		}
 		cout<<gbest<<endl;
 		for(int j=0;j <PNUM ;j++)							//�����ٶȸ��£�λ�ø��£�����ֵ���� 
	 	{
	 		a[j].vel = cal_v(a[j].vel,a[j].pos,a[j].pbest);
	 		a[j].pos = cal_p(a[j].pos,a[j].vel);
	 		if(a[j].pbest < func(a[j].pos))
 				a[j].pbest = func(a[j].pos);
	 	}
	 	index++;
 	}
 	cout<<gbest<<endl;										//������Ž� 
}
 
double cal_v(double vel,double pos,double p){            		//��Ȩ�ٶȸ��¹�ʽ,�ٶȱ߽硾-1,1�� �������߽������� 
	double nvel = vel*0.8+ c1*get_rand(0,1)*(p - pos)+c2*get_rand(0,1)*(gbest - pos);
	if(nvel>=1)
	 	return 1;
	else if(nvel <=-1)
 		return -1;
	else 
		return nvel;
}
double func(double x){										//����x*sin(x)*cos(2*x)-2*x*sin(3*x);
	return	x*sin(x)*cos(2*x)-2*x*sin(3*x);
}

double cal_p(double old_p,double v){							//����λ�ã������߽�������,λ��ȡֵ��Χ��0,20��
	double new_p = old_p + v;
	if(new_p >= 20)
		return 20;
	else if(new_p <= 0)
		return 0; 
	else
		return new_p;
}