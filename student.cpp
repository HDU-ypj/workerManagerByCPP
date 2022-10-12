#include <iostream>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "student.h"
#include "tools.h"

using namespace std;

//静态成员的定义
int Student::id_max = 10000000;
//采用List容器存储数据
list<Student*> g_student;

void Student::showMessage(void) const
{
	cout << "name:" << name << ' '
		 << "id:" << id << ' '
		 << "sex:" << sex << ' '
		 << "English:" << score[ENGLISH] << ' '
		 << "Chinese:" << score[CHINESE] << ' '
		 << "Math:" << score[MATH] << ' '
		 << "status:"<< (isAtSchool?"on":"off")
		 << endl;
}
void Student::changeSelfKey(void)
{
	string keyOld,keyNew;
	cout << "请输入你的原密码：";
	keyOld = getStringCMD();
	cout << "请输入你的新密码：";
	keyNew = getStringCMD();
	if(keyOld == this->key)
	{
		this->key = keyNew;
		cout << "更改成功！"<<endl;
	}
	else
	{
		cout << "更改失败！"<<endl;
	}
}
void Student::showScore(void)
{
	cout << "show Score"<<endl;
}

Student* findStuByID(int id)
{
	for(auto s:g_student)
	{
		if(s->getID() == id)	return s;
	}
	return nullptr;
}

void Student::writeStudentFile(void)
{
	//打开文件
	ofstream ofs_on(STU_ON_PATH);
	ofstream ofs_off(STU_OFF_PATH);
	//写入最大id值
	ofs_on << Student::getIDMax()<<endl;
	//导入数据
	for(auto stu:g_student)
	{
		if(stu->atSchool())
		{
			ofs_on << *stu;
		}
		else
		{
			ofs_off << *stu;
		}
	}
	ofs_on.close();
	ofs_off.close();
}

void Student::loadStudentFile(void)
{
	//判断文件是否存在,初始化系统文件
	if(access(STU_ON_PATH,F_OK))
	{
		cout << "init stu_on.txt"<<endl;
		//写方式打开文件，创建文件
		ofstream ofs(STU_ON_PATH);
		if(ofs.fail())
		{
			cout << "init fail"<<endl;
			return;
		}
		ofs.close();
	}
	if(access(STU_OFF_PATH,F_OK))
	{
		cout << "init stu_off.txt"<<endl;
		//写方式打开文件，创建文件
		ofstream ofs(STU_OFF_PATH);
		if(ofs.fail())
		{
			cout << "init fail"<<endl;
			return;
		}
		ofs.close();
	}
	
	//读入在校学生数据
	ifstream ifs(STU_ON_PATH);
	int idtemp;
	if(ifs.fail())
	{
		cout << "文件打开失败"<<endl;
	}
	else
	{
		//读入最大员工id号
		ifs >> idtemp;
		if(ifs.fail())
		{
			ifs.close();
			return;
		}
		//读入员工到系统
		while(!ifs.eof())
		{
			Student *stu = new Student;
			ifs >> *stu;
			if(ifs.fail())
			{
				ifs.close();
				break;
			}
			g_student.push_back(stu);
		}
	}
	
	//读入离校学生数据
	ifs.open(STU_OFF_PATH);
	if(ifs.fail())
	{
		cout << "文件打开失败"<<endl;
	}
	else
	{
		//读入员工到系统
		while(!ifs.eof())
		{
			Student *stu = new Student;
			ifs >> *stu;
			if(ifs.fail())
			{
				ifs.close();
				break;
			}
			g_student.push_back(stu);
		}
	}
	Student::setIDMax(idtemp);
}

ostream& operator<<(ostream& os,const Student& stu)
{
	return os << stu.name << ' '
		 << stu.id << ' '
		 << stu.is_first << ' '
		 << stu.flag << ' '
		 << stu.sex << ' '
		 << stu.score[ENGLISH] << ' '
		 << stu.score[CHINESE] << ' '
		 << stu.score[MATH] << ' '
		 << stu.isAtSchool << ' '
		 << stu.key
		 << endl;
}
istream& operator>>(istream& is, Student& stu)
{
	return is >> stu.name
		>> stu.id
		>> stu.is_first
		>> stu.flag
		>> stu.sex
		>> stu.score[ENGLISH]
		>> stu.score[CHINESE]
		>> stu.score[MATH]
		>> stu.isAtSchool
		>> stu.key;
}

void studentInterface(void)
{
	system("clear");
	puts("学生端系统");
	puts("0、退出登录");
	puts("1、查询成绩");
	puts("2、修改密码");
	puts("3、查看个人信息");
	cout << "please enter your choise:";
}


void mainStudent(void)
{
	system("clear");
	Student* stu = signIn<Student*>(g_student);
	//登录失败，直接返回
	if(nullptr == stu)	return;

	while(true)
	{
		studentInterface();
		int cmd = getIntCMD(0,3);
		if(0 == cmd)	break;
		switch(cmd)
		{
			case 1:stu->showScore();break;
			case 2:stu->changeSelfKey();break;
			case 3:stu->showMessage();break;
		}
		anyKeyContinue();
	}
}

