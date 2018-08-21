#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 
using namespace std;

double shengmingli = 2000;//定义主角初始生命力 
int gongjili = 150;//定义主角初始攻击力 
int fangyuli = 200;//定义主角初始防御力 
int money = 100;//定义主角初始金钱数量 
int fight = 0; //标记是否处于战斗状态
bool guoguan = false;//定义是否通关判定 

void init()
{
	shengmingli = 2000;
	gongjili = 150;
	fangyuli = 200;
	money = 100;
	fight = 0; 
	guoguan = false;
}

void wuqidian();//定义武器店函数 
void yaodian();//定义药店函数 
void guaiwu1();//定义小怪物函数 
void guaiwu2();//定义大怪物函数 

void menu()
{
	cout << "----欢迎回到小镇，请选择你接下来要选择的操作----" << endl;
	cout << "------------------ 1.去武器店 ------------------" << endl;
	cout << "------------------ 2.去药品店 ------------------" << endl;
	cout << "------------------ 3.打小怪物 ------------------" << endl;
	cout << "------------------ 4.打大怪物 ------------------" << endl;
	cout << "------------------ 5.当前状态 ------------------" << endl;
	cout << "------------------ 0.退出游戏 ------------------" << endl;
}

void zhuangtai()
{
	cout << "当前生命力:" << shengmingli << endl;
	cout << "当前攻击力:" << gongjili << endl;
	cout << "当前防御力:" << fangyuli << endl;
	cout << "当前拥有的money:" << money << endl;
	menu();
}
int main()
{
	cout << "欢迎你开始玩打怪物小游戏！\n";
	cout << "小镇\n";
	cout << "一个1000年的小镇。周围有一条河，有一片树林，很多房子和很多人。\n有一家药店" << endl;
	cout << "和一家武器店。\n";
	menu();
	int xiaozhen;//定义选择项目 	
	cin >> xiaozhen;
	while (xiaozhen != 0)//输入0时退出游戏 
	{
		switch (xiaozhen)
		{
			case 1:
				system("cls");
				wuqidian(); //武器店
				break;
			case 2:
				system("cls");
				yaodian(); //药店
				break;
			case 3:
				system("cls");
				guaiwu1(); //小怪物
				break;
			case 4:
				system("cls");
				guaiwu2(); //大怪物
				break;
			case 5:
				zhuangtai();//显示当前状态
				break;
			default: 
				cout << "选择无效，请重选！" << endl; 
				menu();
				break;
		}
		if (shengmingli <= 0 || guoguan)//主角生命力小于等于0时游戏结束 
		{
			int choose;
			cout << "请选择 1、再来一局  0、退出游戏" << endl;
			cin >> choose;
			switch (choose)
			{
			case 1:
				init();
				menu();
				break;
			case 0:
				xiaozhen = 0;
				break;
			}
			if (choose == 1)
				continue;
			else
				break;
		}
		else
			cin >> xiaozhen;
	}
	if (xiaozhen == 0)
	{
		cout << "正在退出游戏……" << endl;
	}
	cin.get();
	cin.get();
	return 0;
}
void wuqidian()
{
	cout << "************** 欢迎来到武器店！*************" << endl;
	cout << "******* 1、买小刀（10￥ 加15攻击力）********" << endl;
	cout << "******* 2、买短剑（20￥ 加30攻击力）********" << endl;
	cout << "******* 3、买砍刀（30￥ 加50攻击力) ********" << endl;
	cout << "******* 4、买弓箭（35￥ 加60攻击力）********" << endl;
	cout << "******* 5、买盾牌（10￥ 加30防御力）********" << endl;
	cout << "******* 6、买铠甲（60￥ 加60防御力）********" << endl;
	cout << "*************** 0、离开武器店 **************" << endl;
	int wuqidian;
	cin >> wuqidian;
	while (wuqidian != 0)//输入0时结束函数 
	{
		switch (wuqidian)
		{
		case 1: 
			if (money < 10) //买小刀
			{
				cout << "你的钱不够 小刀需要10￥，当前只有" << money << "￥" << endl;//钱不够时返回Flase
				break;
			}
			else
				cout << "购买成功！" << endl;//钱足够时返回True 
			gongjili += 15;
			money -= 10;
			break;
		case 2: 
			if (money < 20)//买短剑
			{
				cout << "你的钱不够 小刀需要20￥，当前只有" << money << "￥" << endl;
				break;
			}
			else
				cout << "购买成功！" << endl;
			gongjili += 40;
			money -= 30;
			break;
		case 3: 
			if (money < 30)//买砍刀
			{
				cout << "你的钱不够 小刀需要20￥，当前只有" << money << "￥" << endl;
				break;
			}
				else
					cout << "购买成功！" << endl;
			gongjili += 50;
			money -= 30;
			break;
		case 4: 
			if (money < 35)//买弓箭
			{
				cout << "你的钱不够 小刀需要35￥，当前只有" << money << "￥" << endl;
				break;
			}
				else
					cout << "购买成功！" << endl;
			gongjili += 60;
			money -= 35;
			break;
		case 5: 
			if (money < 10)//买盾牌
			{
				cout << "你的钱不够 小刀需要10￥，当前只有" << money << "￥" << endl;
				break;
			}
				else
					cout << "购买成功！" << endl;
			fangyuli += 30;
			money -= 10;
			break;
		case 6:
			if (money < 60)//买砍刀
			{
				cout << "你的钱不够 小刀需要20￥，当前只有" << money << "￥" << endl;
				break;
			}
			fangyuli += 60;
			money -= 60;
			break;
		case 0:
			break;
		default: cout << "选择错误，请重选" << endl;
			break;
		}
		cin >> wuqidian;
	}
	if (wuqidian == 0)
	{	  //返回游戏主界面 
		cout << "欢迎下次再来！" << endl;
		system("cls");
		menu();
	}
}
/*
yaodian()的设置与wuqidian()相同,可参照阅读.
*/
void yaodian()
{
	cout << "***************** 欢迎来到药品店！******************" << endl;
	cout << "******* 1、买1号补血药（10￥ 加200生命力）**********" << endl;
	cout << "******* 2、买2号补血药（50￥ 加1000生命力）*********" << endl;
	cout << "******* 3、买3号补血药（80￥ 加2200生命力) *********" << endl;
	cout << "******************* 4、返回战斗 ********************" << endl;
	cout << "******************* 0、离开武器店 ******************" << endl;
	int yaodian;
	int flag = 0;
	cin >> yaodian;
	while (yaodian != 0)
	{
		switch (yaodian)
		{
		case 1: 
			if (money < 10)
			{
				cout << "你的钱不够 1号补血药需要10￥ 你当前拥有" << money << "￥" << endl;
				break;
			}
			else
			{
				cout << "购买成功！生命力增加200 当前生命力为："<<shengmingli << endl;
			}
			shengmingli += 200;
			money -= 10;
			break;
		case 2: 
			if (money < 50)
			{
				cout << "你的钱不够 2号补血药需要50￥ 你当前拥有" << money << "￥" << endl;
				break;
			}
			else
			{
				cout << "购买成功！生命力增加1000 当前生命力为：" << shengmingli << endl;
			}
			shengmingli += 1000;
			money -= 50;
			break;
		case 3: 
			if (money < 80)
			{
				cout << "你的钱不够 1号补血药需要80￥ 你当前拥有" << money << "￥" << endl;
				break;
			}
			else
			{
				cout << "购买成功！生命力增加2200 当前生命力为：" << shengmingli << endl;
			}
			shengmingli += 2200;
			money -= 80;
			break;
		case 4:
			if (fight == 0)
			{
				cout << "你还没有开始任何的战斗" << endl;
			}
			else//正在与怪兽战斗
			{
				flag = 1;
			}			
		default: cout << "无" << endl;
			break;
		}
		if (flag == 1)
			break;
		cin >> yaodian;	
	}
	if (yaodian == 0)
	{
		cout << "欢迎下次再来！" << endl;
		system("cls");
		menu();
	}
}
/*这里是两个战斗函数,使用指针来处理.避免造成内存崩溃.*/
void guaiwu1()
{
	cout << "开始与小怪物战斗！！！" << endl;
	double* g_shengmingli = new double;//定义怪物生命 
	int* g_gongjili = new int;//定义怪物攻击力 
	int* g_fangyuli = new int;//定义怪物防御力 
	int* g_money = new int;//定义怪物金钱 
	*g_shengmingli = 200;
	*g_gongjili = 5;
	*g_fangyuli = 3;
	*g_money = 50;
	double* tongji1 = new double;//用来计算主角对怪物的杀伤 
	double* tongji2 = new double;//用来计算怪物对主角的杀伤 
	*tongji1 = 0;
	*tongji2 = 0;
	int* huihe = new int;//定义回合数 
	*huihe = 1;
	int flag = 0;
	cout << "你开始对小怪物进行攻击！" << endl;
	int* xuanze = new int;
	/*
	攻击计算公式
	杀伤=攻击力*2-防御力
	玩家每回合可以选择攻击与逃跑
	*/
	while ((*g_shengmingli)>0 && shengmingli>0 && (*xuanze) != 3)
	{	
		cout << "现在是" << "第" << *huihe << "回合！" << endl;
		zhuangtai();
		cout << "请选择你的动作:\n";
		cout << "1、攻击\n 2、回血\n 3、逃跑\n ";
		cin >> *xuanze;
		switch ((*xuanze))
		{
			system("cls");
		case 1: cout << "你对小怪物发动了攻击！" << endl;
			*g_shengmingli -= gongjili * 2 - (*g_fangyuli);
			*tongji1 = gongjili - (*g_fangyuli);
			cout << "你打掉了小怪物" << *tongji1 << "的生命！获得5￥" << endl;
			money += 5;
			cout << "小怪物还剩" << (*g_shengmingli) - (*tongji1) << "点生命" << endl;
			shengmingli -= (*g_gongjili) * 2 - fangyuli;
			*tongji2 = (*g_gongjili) * 2 - fangyuli;
			cout << "小怪物对你发动了攻击！" << endl;
			cout << "小怪物打掉了你" << *tongji2 << "的生命！" << endl;
			cout << "你还剩" << shengmingli - (*tongji2) << "点生命" << endl; 
			cout << "请选择:\n 1、攻击\n2、逃跑\n" << endl;
			break;
		case 2:
			yaodian();
			break;
		case 3: 
			cout << "你决定逃跑！" << endl;
			cout << "逃跑成功！" << endl; 
			flag = 1;
			break;
		default: cout << "选择无效，请重选" << endl;
		}
		if (flag == 1)
			break;
		(*huihe)++;
	}
	if ((*g_shengmingli) <= 0)
	{//杀死怪物后的返回 
		cout << "成功击败小怪兽，获得50￥" << endl;
		flag = 0;
		guoguan = 1;
		money += (*g_money);
	}
	if (shengmingli <= 0)
	{//被怪物杀死后的返回 
		cout << "你被小怪兽击败了！游戏结束！！！" << endl;
	}
	if ((*xuanze) == 3)
	{//逃跑的返回 
		cout << "你逃回了小镇！" << endl;
		system("cls");
		menu();
	}
	delete g_shengmingli;
	delete g_gongjili;
	delete g_fangyuli;
	delete g_money;
	delete tongji1;
	delete tongji2;
}
/*
设置均与void函数guaiwu1()相同,可参照上例阅读.
*/
void guaiwu2()
{
	cout << "开始与大怪物战斗！！！" << endl;
	double* g_shengmingli = new double;
	int* g_gongjili = new int;
	int* g_fangyuli = new int;
	*g_shengmingli = 3600;
	*g_gongjili = 500;
	*g_fangyuli = 500;
	double* tongji1 = new double;
	double* tongji2 = new double;
	*tongji1 = 0;
	*tongji2 = 0;
	int* huihe = new int;
	*huihe = 1;
	cout << "你开始对大怪物进行攻击！" << endl;
	int* xuanze = new int;
	while ((*g_shengmingli)>0 && shengmingli>0 && (*xuanze) != 2)
	{
		cout << "现在是" << "第" << *huihe << "回合！" << endl;
		cout << "请选择你的动作:\n";
		cout << "1、攻击\n2、逃跑\n";
		cin >> *xuanze;
		switch ((*xuanze))
		{
		case 1: cout << "你对大怪物发动了攻击！" << endl;
			*g_shengmingli -= gongjili * 2 - (*g_fangyuli);
			*tongji1 = gongjili * 2 - (*g_fangyuli);
			cout << "你打掉了大怪物" << *tongji1 << "的生命！" << endl;
			cout << "大怪物还剩" << (*g_shengmingli) - (*tongji1) << "点生命" << endl;
			shengmingli -= (*g_gongjili) * 2 - fangyuli;
			*tongji2 = (*g_gongjili) * 2 - fangyuli;
			cout << "大怪物对你发动了攻击！" << endl;
			cout << "大怪物打掉了你" << *tongji2 << "的生命！" << endl;
			cout << "你还剩" << shengmingli - (*tongji2) << "点生命" << endl; break;
		case 2: cout << "你决定逃跑！" << endl;
			cout << "逃跑成功！" << endl; continue;
		default: cout << "请不要乱选！" << endl;
		}
		(*huihe)++;
	}
	if ((*g_shengmingli) <= 0)
	{
		cout << "大怪物被你杀死了！你真厉害！！！" << endl;
		guoguan = true;
		system("cls");
		menu();
	}
	else
	if (shengmingli <= 0)
	{
		cout << "你被大怪物杀死了！游戏结束！！！" << endl;
	}
	else
	if ((*xuanze) == 2)
	{
		cout << "你逃回了小镇！" << endl;
		menu();
	}
	delete g_shengmingli;
	delete g_gongjili;
	delete g_fangyuli;
	delete tongji1;
	delete tongji2;
}
