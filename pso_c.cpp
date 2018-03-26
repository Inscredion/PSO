#include<iostream>
#include<cmath>
using namespace std;

#define MAX 100												//定义最大迭代次数 
#define PNUM 50												//定义种群个数 
#define get_rand(a,b) ((double)rand()/RAND_MAX)*(b-a) + a 	//随机生成数 
#define INF -99999999

double gbest = INF;												//定义种群最优解 
double c1 = 0.5;												//定义学习因子c1 
double c2 = 0.5;												//定义学习因子c2 

struct pso{												
	double vel;												//粒子自身速度 
	double pos;												//粒子自身位置 
	double pbest;											//自身最优解 
};																	 
pso a[PNUM];												

double cal_v(double vel,double pos,double p);					//速度更新	
double func(double x);										//求解	
double cal_p(double old_p,double v);							//位置更新	

int main(){	
	for(int i=0;i < PNUM ;i++){								//随机初始化粒子属性 
		a[i].vel = get_rand(-1,1);
		a[i].pos = get_rand(0,20);
		a[i].pbest = func(a[i].pos);
 	}
	int index = 0;
	while(index<MAX)										//迭代开始 
	{
		for(int i=0;i < PNUM ;i++)							//寻找全局最优解 
		{
			if(gbest < func(a[i].pos))
				gbest = func(a[i].pos);
 		}
 		cout<<gbest<<endl;
 		for(int j=0;j <PNUM ;j++)							//粒子速度更新，位置更新，自身极值更新 
	 	{
	 		a[j].vel = cal_v(a[j].vel,a[j].pos,a[j].pbest);
	 		a[j].pos = cal_p(a[j].pos,a[j].vel);
	 		if(a[j].pbest < func(a[j].pos))
 				a[j].pbest = func(a[j].pos);
	 	}
	 	index++;
 	}
 	cout<<gbest<<endl;										//输出最优解 
}
 
double cal_v(double vel,double pos,double p){            		//加权速度更新公式,速度边界【-1,1】 ，超出边界做处理 
	double nvel = vel*0.8+ c1*get_rand(0,1)*(p - pos)+c2*get_rand(0,1)*(gbest - pos);
	if(nvel>=1)
	 	return 1;
	else if(nvel <=-1)
 		return -1;
	else 
		return nvel;
}
double func(double x){										//函数x*sin(x)*cos(2*x)-2*x*sin(3*x);
	return	x*sin(x)*cos(2*x)-2*x*sin(3*x);
}

double cal_p(double old_p,double v){							//更新位置，超过边界做处理,位置取值范围【0,20】
	double new_p = old_p + v;
	if(new_p >= 20)
		return 20;
	else if(new_p <= 0)
		return 0; 
	else
		return new_p;
}