#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
public:	
	virtual void showMessage(void)const = 0;	//显示信息
	virtual void changeSelfKey(void) = 0;		//改自己的密码
	Person(std::string name="",char sex='m')	//有参构造
		:name(name),sex(sex),key("123"),is_first(true),flag(0){}
	virtual ~Person(){}							//析构
	
	int getID(void)
	{
		return this->id;
	}
	std::string& getName(void)
	{
		return this->name;
	}
	void setName(std::string& name)
	{
		this->name = name;
	}
	void setSex(char sex)
	{
		this->sex = sex;
	}
	void resetFlag(void)
	{
		this->flag = 0;
	}
	void resetKey(void)
	{
		key.assign("123");
	}
	std::string& getKey(void)
	{
		return key;
	}
protected:
	std::string name;	//姓名
	std::string key;	//密码
	char sex;			//性别
	bool is_first;		//是否第一次登录
	int id;				//工号/学号
	int flag;			//0-2表示输入错误了多少次，存档，三次锁定(flag==3)
};



#endif//PERSON_H
