#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <unistd.h>
#include "teacher.h"
#include "student.h"
#include "tools.h"
using namespace std;

int Teacher::id_max = 90000000;
list<Teacher*> g_teacher;

void Teacher::showMessage(void)const
{
	cout << "name:" << name << ' '
		 << "sex:" << sex << ' '
		 << "id:" << id << ' '
		 << "status:"<< (isAtSchool?"on":"off")
		 << endl;
}

void Teacher::changeSelfKey(void)
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

void Teacher::singleAddStu(void)
{
	char ssex;
	string sname;
	cout << "请输入学生姓名：";
	sname = getStringCMD();
	cout << "请输入学生性别：";
	cin >> ssex;
	if(cin.good())
	{
		Student* stu = new Student(sname,ssex);
		g_student.push_back(stu);
		cout << "添加成功"<<endl;
		return;
	}
	cout << "添加失败"<<endl;
	
}

void Teacher::batchAddStu(void)
{
	system("ls");
	string path;
	double score[3];
	int _id;
	cout << "请输入导入文件的路径：";
	path = getStringCMD();
	//创建文件io对象
	ifstream ifs(path);
	if(ifs.fail())
	{
		cout << "文件打开失败，批量添加失败"<<endl;
		return;
	}
	while(!ifs.eof())
	{
		ifs >>_id >> score[0] >> score[1] >> score[2];
		if(ifs.good())
		{
			Student* stu = findStuByID(_id);
			if(nullptr != stu)
			{
				stu->setScore(score[0],score[1],score[2]);
			}
		}
		else
		{
			break;
		}
	}
	cout << "添加成功" <<endl;
	ifs.close();
}

void Teacher::addStu(void)
{
	int cmd;
	cout << "1、单个添加"<<endl;
	cout << "2、批量添加"<<endl;
	cout << "please enter your choise:";
	cmd = getIntCMD(1,2);
	switch(cmd)
	{
		case 1:singleAddStu();break;	//单个添加
		case 2:batchAddStu();break;		//批量添加
	}
}
	

void Teacher::del(void)
{
	int delid;
	cout << "请输入需要删除的学生id编号"<<endl;
	delid = getIntCMD();
	for(list<Student*>::iterator it=g_student.begin(); it!=g_student.end(); it++)
	{
		if((*it)->getID() == delid)
		{
			(*it)->setIsAtSchool(false);
			cout << "删除成功"<<endl;
			return;
		}
	}
	cout << "删除失败"<<endl;
}

void Teacher::searchName(void)
{
	string _name;
	cout << "请输入搜索的学生姓名：";
	_name = getStringCMD();
	for(auto stu:g_student)
	{
		//采用找字串的方式进行查找，即模糊查找
		if((stu->getName()).find(_name) != -1)
		{
			stu->showMessage();
		}
	}
}
	
void Teacher::searchID(void)
{
	int _id;
	cout << "请输入搜索的学生ID：";
	_id = getIntCMD();
	for(auto stu:g_student)
	{
		//id比对
		if(stu->getID() == _id)
		{
			stu->showMessage();
		}
	}
}

void Teacher::seacher(void)
{
	int cmd;
	cout << "1、按照名字搜索"<<endl;
	cout << "2、按照ID搜索"<<endl;
	cout << "please enter your choise:";
	cmd = getIntCMD(1,2);
	switch(cmd)
	{
		case 1:searchName();break;		//按照名字搜索
		case 2:searchID();break;		//按照ID搜索
	}
}
	
		
void Teacher::modifyMessage(void)
{
	int resid;
	cout << "请输入学生的ID号：";
	resid = getIntCMD();
	//查找学生
	Student* stu = findStuByID(resid);
	//如果学生ID查找失败
	if(NULL == stu)
	{
		cout << "学生ID不存在，修改失败"<<endl;
		return;
	}
	//修改姓名性别
	string _name;
	char _sex;
	cout << "请输入修改后的姓名：";
	_name = getStringCMD();
	cout << "请输入修改后的性别：";
	cin >> _sex;
	stu->setName(_name);
	stu->setSex(_sex);
	cout << "修改成功"<<endl;
}
	
void Teacher::modifyScore(void)
{
	
	int resid;
	cout << "请输入学生的ID号：";
	resid = getIntCMD();
	//查找学生
	Student* stu = findStuByID(resid);
	//如果学生ID查找失败
	if(NULL == stu)
	{
		cout << "学生ID不存在，修改失败"<<endl;
		return;
	}
	double score[3];
	cout << "请输入修改后的语文成绩：";
	score[CHINESE] = getDouble();
	cout << "请输入修改后的数学成绩：";
	score[MATH] = getDouble();
	cout << "请输入修改后的英语成绩：";
	score[ENGLISH] = getDouble();
	
	stu->setScore(score[ENGLISH],score[MATH],score[CHINESE]);
}

void Teacher::modify(void)
{
	int cmd;
	cout << "1、修改基本信息"<<endl;
	cout << "2、修改成绩信息"<<endl;
	cout << "please enter your choise:";
	cmd = getIntCMD(1,2);
	switch(cmd)
	{
		case 1:modifyMessage();break;	//修改基本信息
		case 2:modifyScore();break;		//修改成绩信息
	}
}

void Teacher::importSingleScore(void)
{
	int resid;
	cout << "请输入学生的ID号：";
	resid = getIntCMD();
	//查找学生
	Student* stu = findStuByID(resid);
	//如果学生ID查找失败
	if(NULL == stu)
	{
		cout << "学生ID不存在，修改失败"<<endl;
		return;
	}
	
	double score[3];
	cout << "请输入语文成绩：";
	score[CHINESE] = getDouble();
	cout << "请输入数学成绩：";
	score[MATH] = getDouble();
	cout << "请输入英语成绩：";
	score[ENGLISH] = getDouble();
	stu->setScore(score[ENGLISH],score[MATH],score[CHINESE]);
	cout << "导入成绩成功"<<endl;
}


void Teacher::importScore(void)
{
	system("ls");
	
	//文件操作
	string path;
	cout << "请输入导入成绩路径(每行格式：id 英语 数学 语文)：";
	path = getStringCMD();
	ifstream ifs(path);
	if(ifs.fail())
	{
		cout << "文件打开失败，批量导入成绩失败"<<endl;
		return;
	}
	
	double score[3];
	int id;
	while(!ifs.eof() && !ifs.fail())
	{
		ifs >> id
			>> score[0]
			>> score[1]
			>> score[2];
		//查找学生
		Student* stu = findStuByID(id);
		//如果学生ID查找失败
		if(NULL != stu)
		{
			stu->setScore(score[0],score[1],score[1]);
		}
		else
		{
			cout << "id:"<<id<<"not found!"<<endl;
		}
	}
	cout << "导入完成"<<endl;
}

//导入成绩
void Teacher::inputScore(void)
{
	int cmd;
	cout << "1、单个添加成绩"<<endl;
	cout << "2、批量添加成绩"<<endl;
	cout << "please enter your choise:";
	cmd = getIntCMD(1,2);
	switch(cmd)
	{
		case 1:importSingleScore();break;//单个添加成绩
		case 2:importScore();break;		 //批量添加成绩
	}
}

void Teacher::resetStuKey(void)
{
	int resid;
	cout << "请输入学生的ID号：";
	resid = getIntCMD();
	//查找学生
	Student* stu = findStuByID(resid);
	//如果学生ID查找失败
	if(NULL == stu)
	{
		cout << "学生ID不存在，重置失败"<<endl;
		return;
	}
	//重置学生密码
	stu->resetKey();
	cout << "重置密码成功"<<endl;
}

void Teacher::showOnStu(void)
{
	for(auto stu:g_student)
	{
		if(stu->atSchool())
		{
			stu->showMessage();
		}
	}
}

void Teacher::showOffStu(void)
{
	for(auto stu:g_student)
	{
		if(!stu->atSchool())
		{
			stu->showMessage();
		}
	}
}

ostream& operator<<(ostream& os,const Teacher& tch)
{
	return os << tch.name << ' '
		 << tch.id << ' '
		 << tch.is_first << ' '
		 << tch.flag << ' '
		 << tch.sex << ' '
		 << tch.isAtSchool << ' '
		 << tch.key
		 << endl;
}
istream& operator>>(istream& is, Teacher& tch)
{
	return is >> tch.name
		>> tch.id
		>> tch.is_first
		>> tch.flag
		>> tch.sex
		>> tch.isAtSchool
		>> tch.key;
}
	
void Teacher::writeTeacherFile(void)
{
	//打开文件
	ofstream ofs_on(TCH_ON_PATH);
	ofstream ofs_off(TCH_OFF_PATH);
	//写入最大id值
	ofs_on << Teacher::getIDMax()<<endl;
	//导入数据
	for(auto tch:g_teacher)
	{
		if(tch->atSchool())
		{
			ofs_on << *tch;
		}
		else
		{
			ofs_off << *tch;
		}
	}
	ofs_on.close();
	ofs_off.close();
}
void Teacher::loadTeacherFile(void)
{
	//判断文件是否存在,初始化系统文件
	if(access(TCH_ON_PATH,F_OK))
	{
		cout << "init tch_on.txt"<<endl;
		//写方式打开文件，创建文件
		ofstream ofs(TCH_ON_PATH);
		if(ofs.fail())
		{
			cout << "init fail"<<endl;
			return;
		}
		ofs.close();
	}
	if(access(TCH_OFF_PATH,F_OK))
	{
		cout << "init tch_off.txt"<<endl;
		//写方式打开文件，创建文件
		ofstream ofs(TCH_OFF_PATH);
		if(ofs.fail())
		{
			cout << "init fail"<<endl;
			return;
		}
		ofs.close();
	}
	
	//读入在校学生数据
	ifstream ifs(TCH_ON_PATH);
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
			Teacher *tch = new Teacher;
			ifs >> *tch;
			if(ifs.fail())
			{
				ifs.close();
				break;
			}
			g_teacher.push_back(tch);
		}
	}
	
	//读入离校学生数据
	ifs.open(TCH_OFF_PATH);
	if(ifs.fail())
	{
		cout << "文件打开失败"<<endl;
	}
	else
	{
		//读入员工到系统
		while(!ifs.eof())
		{
			Teacher *tch = new Teacher;
			ifs >> *tch;
			if(ifs.fail())
			{
				ifs.close();
				break;
			}
			g_teacher.push_back(tch);
		}
	}
	Teacher::setIDMax(idtemp);
}
	

Teacher* findTchByID(int id)
{
	for(auto s:g_teacher)
	{
		if(s->getID() == id)	return s;
	}
	return nullptr;
}


void teacherInterface(void)
{
	system("clear");
	puts("教师端系统");
	puts("0、退出登录");
	puts("1、添加学生");
	puts("2、删除学生");
	puts("3、查找学生");
	puts("4、修改学生信息");
	puts("5、录入学生成绩");
	puts("6、重置学生密码");
	puts("7、显示在校学生信息");
	puts("8、显示离校学生信息");
	puts("9、更改帐号密码");
	cout << "please enter your choise:";
}
void mainTeacher(void)
{
	system("clear");
	Teacher* tch = signIn<Teacher*>(g_teacher);
	//登录失败，直接返回
	if(nullptr == tch)	return;

	while(true)
	{
		teacherInterface();
		int cmd = getIntCMD(0,9);
		if(0 == cmd)	break;
		switch(cmd)
		{
			case 1:tch->addStu();break;
			case 2:tch->del();break;
			case 3:tch->seacher();break;
			case 4:tch->modify();break;
			case 5:tch->inputScore();break;
			case 6:tch->resetStuKey();break;
			case 7:tch->showOnStu();break;
			case 8:tch->showOffStu();break;
			case 9:tch->changeSelfKey();break;
		}
		anyKeyContinue();
	}
}
