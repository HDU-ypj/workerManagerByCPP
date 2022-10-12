#ifndef STUDENT_H
#define STUDENT_H

#include <list>
#include <string>
#include <fstream>
#include "person.h"

//信息存放文件路径
#define STU_ON_PATH 	"./source/stu_on.txt"
#define STU_OFF_PATH 	"./source/stu_off.txt"

enum subject{ENGLISH,CHINESE,MATH};
class Student:public Person
{
public:
	Student(std::string name="",char sex='m'):Person(name,sex),isAtSchool(true)
	{
		id = id_max++;
	}
	Student(const Student& that) = delete;
	Student& operator=(const Student& that) = delete;
	
	void showMessage(void)const;//显示学生信息
	void changeSelfKey(void);	//改密码
	void showScore(void);		//查询成绩
	bool atSchool(void)
	{
		return isAtSchool;
	}
	void setIsAtSchool(bool flag)
	{
		isAtSchool = flag;
	}
	void setScore(double& eng,double& math,double& chin)
	{
		score[ENGLISH] = eng;
		score[MATH] = math;
		score[CHINESE] = chin;
	}
	static void setIDMax(int id)
	{
		id_max = id;
	}
	static int getIDMax(void)
	{
		return id_max;
	}
	static void writeStudentFile(void);//将学生信息写入文件
	static void loadStudentFile(void);	//将学生信息导入系统
	
	friend std::ostream& operator<<(std::ostream& ofs,const Student& stu);
	friend std::istream& operator>>(std::istream& ifs, Student& stu);
	template <typename T> friend T signIn(const std::list<T>& vt);
	
private:
	static int id_max;			//维护一个最大id用来自动生成学生的学号
	double score[3];			//语文数学英语的成绩
	bool isAtSchool;			//是否在校
};

extern std::list<Student*> g_student;
Student* findStuByID(int id);
void mainStudent(void);

#endif//STUDENT_H
