#include <iostream>
#include <getch.h>
#include <list>
#include <string>
#include "tools.h"
#include "principal.h"

using namespace std;

int getIntCMD(int low,int high)
{
	int cmd;
	while(true)
	{
		cin>>cmd;
		if(cin.fail() || cmd<low || cmd>high)
		{
			cout << "input error! try again" << endl;
			cin.clear();
		}
		else
		{
			break;
		}
	}
	return cmd;
}
string getStringCMD(void)
{
	string cmd;
	while(true)
	{
		cin >> cmd;
		if(cin.fail())
		{
			cout << "input error!try again" << endl;
			cin.clear();
		}
		else
			break;
	}
	return cmd;
}
//这里也是发现有点冗余了，可以考虑创造一个模板类
double getDouble(void)
{
	double cmd;
	while(true)
	{
		cin >> cmd;
		if(cin.fail())
		{
			cout << "input error!try again" << endl;
			cin.clear();
		}
		else
			break;
	}
	return cmd;
}
void anyKeyContinue(void)
{
	cout << "按任意键继续"<< endl;
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	getch();
	stdin->_IO_read_ptr = stdin->_IO_read_end;
}



