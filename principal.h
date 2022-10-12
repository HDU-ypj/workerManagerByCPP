#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <pthread.h>
#include "person.h"
#include "tools.h"

//信息存放文件路径
#define PRIN_PATH 	"./source/prin.txt"

class Principal:public Person
{
	static Principal* admin;			//单例模式，懒汉模式
	static pthread_mutex_t lock;		//加锁实现线程安全
	Principal():Person("admin")
	{
		id = 0;	
	}
	Principal(const Principal& that) = delete;
	Principal& operator=(const Principal& that) = delete;
public:

	void showMessage(void)const;
	void changeSelfKey(void);		//改密码
	void resetSelfKey(void);		//重置自己的密码
	void resetTeacherKey(void);		//重置教师密码
	void addTeacher(void);			//添加教师
	void delTeacher(void);			//删除教师
	void showTeacherOn(void);		//显示所有在校教师
	void showTeacherOff(void);		//显示所有离职教师
	void unlockTeacher(void);		//解锁教师帐号（解锁不是重置密码）
	
	static void writeAdminFile(void);		//将校长信息写入文件
	static void loadAdminFile(void);		//将校长信息导入系统
	static Principal& getAdmin(void);		//获取校长（超级管理员）对象
	
	friend std::ostream& operator<<(std::ostream& os,const Principal& prin);
	friend std::istream& operator>>(std::istream& is, Principal& prin);
	template <typename T> friend T signIn(const std::list<T>& vt);
	
	//重载校长登录
	static Principal* signIn(Principal& prin);
};

extern std::list<Principal*> g_principal;
void mainPrincipal(void);
#endif//PRINCIPAL_H
