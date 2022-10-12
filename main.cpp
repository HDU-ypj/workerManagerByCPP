/**************************************************
>	作	  者：杭电羊皮卷
>	邮	  箱：2997675141@qq.com
>   文件名称: main.cpp
>   创建日期：2022年10月03日
>   描    述：
**************************************************/

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "student.h"
#include "teacher.h"
#include "tools.h"
#include "principal.h"


using namespace std;

void sys_config(void)
{
	Student::loadStudentFile();
	Teacher::loadTeacherFile();
	Principal::loadAdminFile();
}

void sys_release(int num)
{
	Student::writeStudentFile();
	Teacher::writeTeacherFile();
	Principal::writeAdminFile();
	exit(0);
}
void run(void)
{
	signal(SIGINT,sys_release);	//注册信号，ctrl+c保存后退出
	sys_config();				//加载文件
	while(true)
	{
		system("clear");
		cout << "欢迎使用本系统" << endl;
		cout << "1、学生端登录" << endl;
		cout << "2、教师端登录" << endl;
		cout << "3、校长端登录" << endl;
		cout << "0、退出系统" << endl;
		cout << "please enter your choise:";
		int cmd;
		cmd = getIntCMD(0,3);
		if(0 == cmd)	break;
		if(1 == cmd)	mainStudent();
		if(2 == cmd)	mainTeacher();
		if(3 == cmd)	mainPrincipal();
	}
	sys_release(0);				//写入文件
	cout << "欢迎下次使用……"<<endl;
}


int main(int argc,const char* argv[])
{
	run();
	return 0;
}
