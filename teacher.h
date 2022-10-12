#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"

//信息存放文件路径
#define TCH_ON_PATH 	"./source/tch_on.txt"
#define TCH_OFF_PATH 	"./source/tch_off.txt"

class Teacher:public Person
{
	static int id_max;			//维护一个最大id用来自动生成老师的工号
public:
	Teacher(std::string name="",char sex='m'):Person(name,sex),isAtSchool(true)
	{
		id = id_max++;
	}
	Teacher(const Teacher& that) = delete;
	Teacher& operator=(const Teacher& that) = delete;
	

	void showMessage(void)const;//显示信息
	void changeSelfKey(void);	//改密码
	void addStu(void);			//添加学生
	void del(void);				//删除学生
	void seacher(void);			//搜索
	void modify(void);			//修改
	void inputScore(void);		//导入成绩
	void resetStuKey(void);		//重置学生密码
	void showOnStu(void);		//显示在校学生信息
	void showOffStu(void);		//显示离校学生信息
	
	static void writeTeacherFile(void);	//将教师信息写入文件
	static void loadTeacherFile(void);	//将教师信息导入系统

	bool atSchool(void)
	{
		return isAtSchool;
	}
	void setIsAtSchool(bool flag)
	{
		isAtSchool = flag;
	}
	static void setIDMax(int id)
	{
		id_max = id;
	}
	static int getIDMax(void)
	{
		return id_max;
	}
	
	friend std::ostream& operator<<(std::ostream& os,const Teacher& tch);
	friend std::istream& operator>>(std::istream& is, Teacher& tch);
	template <typename T> friend T signIn(const std::list<T>& vt);

private:
	void singleAddStu(void);	//单个添加学生
	void batchAddStu(void);		//批量添加
	void searchName(void);		//按名字搜索
	void searchID(void);		//按学号搜索
	void modifyMessage(void);	//修改信息
	void modifyScore(void);		//修改成绩
	void importSingleScore(void);//导入单个成绩
	void importScore(void);		//批量导入成绩

	bool isAtSchool;			//是否在校
};

extern std::list<Teacher*> g_teacher;

void mainTeacher(void);			//老师子模块系统入口
Teacher* findTchByID(int id);	//通过id查找老师

#endif//TEACHER_H
