#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <climits>
#include <list>
#include <cstdlib>
#include "principal.h"

//获取low和high之间的一个整数数据
int getIntCMD(int low=INT_MIN,int high=INT_MAX);

//获取一个string	
std::string getStringCMD(void);	

double getDouble(void);

//按任意键继续					
void anyKeyContinue(void);

//登录功能
template <typename T>
T signIn(const std::list<T>& vt)
{
	using namespace std;
	string id;
	string sec;
	
	while(true)
	{
		system("clear");
		T obj = NULL;
		//输入帐号存储，判断是否退出指令
		cout << "请输入帐号(q退出)："<<endl;
		id = getStringCMD();
		if(string("q") == id)	return nullptr;
		//输入密码
		cout << "请输入密码："<<endl;
		sec = getStringCMD();
		
		//查找对应的id帐号
		for(T p:vt)
		{
			if(std::to_string(p->id) == id)
			{
				obj = p;
				break;
			}
		}
		//没有查找到帐号，继续登录操作
		if(NULL == obj)
		{
			cout << "帐号不存在，";
			anyKeyContinue();
			continue;
		}
		//查找到帐号，对比密码正确
		if(sec == obj->key)
		{
			obj->flag = 0;
			return obj;
		}
		else//没有查找到帐号，于是可以尝试的次数减一
		{
			obj->flag++;
			cout << "你还有"<<3-obj->flag<<"次机会尝试登录"<<endl;
			if(obj->flag == 3)
			{
				cout << "帐号已锁定，请找上一级解锁"<<endl;
				anyKeyContinue();
				return nullptr;
			}
			anyKeyContinue();
		}
	}
}



#endif
