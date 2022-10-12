#include <iostream>
#include <fstream>
#include <unistd.h>
#include "principal.h"
#include "teacher.h"
#include "tools.h"

using namespace std;

Principal* Principal::admin = nullptr;
pthread_mutex_t Principal::lock = PTHREAD_MUTEX_INITIALIZER;

list<Principal*> g_principal;

void Principal::showMessage(void)const
{
	cout << "name:" << name << ' '
		 << "sex:" << sex << ' '
		 <<endl;
}

void Principal::changeSelfKey(void)
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

void Principal::resetTeacherKey(void)
{
	int resid;
	cout << "请输入老师的ID号：";
	resid = getIntCMD();
	//查找老师
	Teacher* tch = findTchByID(resid);
	//如果老师ID查找失败
	if(NULL == tch)
	{
		cout << "老师ID不存在，重置失败"<<endl;
		return;
	}
	//重置老师密码
	tch->resetKey();
	cout << "重置密码成功"<<endl;
}

void Principal::resetSelfKey(void)
{
	resetKey();
	cout << "重置成功"<<endl;
}
void Principal::addTeacher(void)
{
	string _name;
	char _sex;
	cout << "请输入教师姓名："<<endl;
	_name = getStringCMD();
	cout << "请输入教师性别："<<endl;
	cin >> _sex;	
	//可以优化，封装函数，判断输入，懒得做了	
	if(cin.good())
	{
		Teacher* tch = new Teacher(_name,_sex);
		g_teacher.push_back(tch);
		cout << "添加成功"<<endl;
		return;
	}
	cout << "添加失败"<<endl;
}

void Principal::delTeacher(void)
{
	int delid;
	cout << "请输入需要删除的老师id编号"<<endl;
	delid = getIntCMD();
	for(list<Teacher*>::iterator it=g_teacher.begin(); it!=g_teacher.end(); it++)
	{
		if((*it)->getID() == delid)
		{
			delete *it;
			g_teacher.erase(it);
			cout << "删除成功"<<endl;
			return;
		}
	}
	cout << "删除失败"<<endl;
}

void Principal::showTeacherOn(void)
{
	for(auto tch:g_teacher)
	{
		if(tch->atSchool())
		{
			tch->showMessage();
		}
	}
}

void Principal::showTeacherOff(void)
{
	for(auto tch:g_teacher)
	{
		if(!tch->atSchool())
		{
			tch->showMessage();
		}
	}
}

void Principal::unlockTeacher(void)
{
	int resid;
	cout << "请输入教师的ID号：";
	resid = getIntCMD();
	//查找教师
	Teacher* tch = findTchByID(resid);
	//如果教师ID查找失败
	if(NULL == tch)
	{
		cout << "教师ID不存在，解锁帐号失败"<<endl;
		return;
	}
	//重置学生密码
	tch->resetFlag();
	cout << "解锁帐号成功"<<endl;
}

void Principal::writeAdminFile(void)
{
	Principal& prin = getAdmin();
	//打开文件
	ofstream ofs(PRIN_PATH);
	//导入数据
	ofs << prin;
	ofs.close();
}

void Principal::loadAdminFile(void)
{
	//判断文件是否存在,初始化系统文件
	if(access(PRIN_PATH,F_OK))
	{
		cout << "init prin_on.txt"<<endl;
		//写方式打开文件，创建文件
		ofstream ofs(PRIN_PATH);
		if(ofs.fail())
		{
			cout << "init fail"<<endl;
			return;
		}
		ofs.close();
		return;
	}
	
	Principal& prin = getAdmin();
	//读入数据
	ifstream ifs(PRIN_PATH);
	if(ifs.fail())
	{
		cout << "文件打开失败"<<endl;
	}
	else
	{
		ifs >> prin;
		if(ifs.fail())
		{
			cout << "导入失败"<<endl;
			ifs.close();
			return;
		}
		cout << "导入成功"<<endl;
	}
	ifs.close();
	
}

ostream& operator<<(ostream& os,const Principal& prin)
{
	return os << prin.name << ' '
		 << prin.id << ' '
		 << prin.key
		 << endl;
}
istream& operator>>(istream& is, Principal& prin)
{
	return is >> prin.name
		>> prin.id
		>> prin.key;
}

Principal& Principal::getAdmin(void)
{
	pthread_mutex_lock(&lock);
	if(NULL == admin)
	{
		admin = new Principal();
	}
	pthread_mutex_unlock(&lock);
	return *admin;
}

//重载校长登录
Principal* Principal::signIn(Principal& prin)
{
	string _id;
	string _key;
	while(true)
	{
		cout << "请输入帐号(q退出)：";
		_id = getStringCMD();
		if(_id == string("q"))	break;
		cout << "请输入密码：";
		_key = getStringCMD();
		
		if(to_string(prin.getID()) == _id && prin.getKey() == _key)
		{
			return &prin;
		}
		cout << "密码错误……"<<endl;
		anyKeyContinue();
	}
	return nullptr;
}


void principalInterface(void)
{
	system("clear");
	puts("校长端系统");
	puts("0、退出登录");
	puts("1、更改自己的密码");
	puts("2、重置教师密码");
	puts("3、添加教师");
	puts("4、删除教师");
	puts("5、显示在职教师");
	puts("6、显示离职教师");
	puts("7、解锁教师帐号");
	puts("8、重置自己的密码");
	cout << "please enter your choise:";
}

void mainPrincipal(void)
{
	system("clear");
	//获取超级管理员对象
	Principal& principal = Principal::getAdmin();
	Principal* prin = Principal::signIn(principal);
	//登录失败，直接返回
	if(nullptr == prin)	return;

	while(true)
	{
		principalInterface();
		int cmd = getIntCMD(0,8);
		if(0 == cmd)	break;
		switch(cmd)
		{
			case 1:prin->changeSelfKey();break;
			case 2:prin->resetTeacherKey();break;
			case 3:prin->addTeacher();break;
			case 4:prin->delTeacher();break;
			case 5:prin->showTeacherOn();break;
			case 6:prin->showTeacherOff();break;
			case 7:prin->unlockTeacher();break;
			case 8:prin->resetSelfKey();break;
		}
		anyKeyContinue();
	}
}
	
