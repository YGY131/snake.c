#include<graphics.h>
#include<conio.h>
#include<stdio.h>


#define MAXSIZE_1 100
#define MAXSIZE_2 200
#define MAXSIZE_3 300
#define WIDTH 1280
#define HEIGHT 960

char sign[40] = "GAME OVER PLEASE PASSURE ESC TO END";


//方向的枚举
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT

};



//食物的结构体
struct food {
	int x;
	int y;
	DWORD color;
	bool flag;
}food;


//蛇的身体的结构体
struct node
{
	int x;
	int y;
	DWORD color;

};


//创建蛇的结构体，创建整条蛇，包括蛇的速度、节数、SIZE、分数
 struct Snake
{
	 int size;//宽高
	 int num;//身体节数
	 int dir;//方向
	 int speed;//速度
	 int score;//分数
	 //蛇的每节身体，包括颜色、位置
	 struct node nodes[MAXSIZE_1];
	
}snake;

//游戏的初始化
void Initgame()
{
	
	srand(GetTickCount());
	snake.num = 3;
	snake.dir = RIGHT;
	snake.score = 0;
	snake.size = 10;
	snake.speed = 10;

	snake.nodes[0].x = 20;
	snake.nodes[0].y = 0;
	snake.nodes[0].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	snake.nodes[1].x = 10;
	snake.nodes[1].y = 0;
	snake.nodes[1].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	snake.nodes[2].x = 0;
	snake.nodes[2].y = 0;
	snake.nodes[2].color = RGB(rand() % 256, rand() % 256, rand() % 256);

	//初始化食物

	food.x = rand() % (WIDTH/10) *10;
	food.y = rand() % (HEIGHT / 10) * 10;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.flag = true;

}

//绘制
void Drawsnake()
{
	cleardevice();
	setfillcolor(snake.nodes[0].color);//？？？
	for (int i = 0; i < snake.num; i++)
	{
		//填充三色
		setfillcolor(snake.nodes[i].color);
		fillrectangle(snake.nodes[i].x, snake.nodes[i].y, snake.nodes[i].x + 10, snake.nodes[i].y + 10);

	}
	//food

	
	if (food.flag)
	{
		setfillcolor(food.color);
		solidellipse(food.x, food.y, food.x + 10, food.y + 10);
	}

	char temp[20] = "";
	sprintf(temp, "分数: %d", snake.score);
	outtextxy(10, 10, temp);
}


//判断蛇有没有撞到自己
void Dead()
{
	char k = 30;
	for (int i = 4; i < snake.num; i++)
	{
		if (snake.nodes[0].x == snake.nodes[i].x && snake.nodes[0].y == snake.nodes[i].y)
		{
			
			while (1)
			{				
				outtextxy(500, 450, sign);
				k = _getch();
				
				if (k == 27)
				{
					exit(0);
				}
				
			}
		}
	}
}


//判断蛇有没有碰到墙边缘
void Edge()
{
	
	if (snake.nodes[0].x < 0)
	{
		snake.nodes[0].x += 1280;
	}
	if (snake.nodes[0].x > 1280)
	{
		snake.nodes[0].x -= 1280;
	}
	if (snake.nodes[0].y < 0)
	{
		snake.nodes[0].y += 960;
	}
	if (snake.nodes[0].y > 960)
	{
		snake.nodes[0].y -= 960;
	}
}


//让蛇移动
void Movesnake()
{
	//让蛇的x、y轴发生变化
	for (int i = snake.num - 1; i > 0; i--)//？？？
	{
		snake.nodes[i].x = snake.nodes[i - 1].x;
		snake.nodes[i].y = snake.nodes[i - 1].y;
	}

	switch (snake.dir)
	{
		case UP:
			snake.nodes[0].y -= snake.speed;
			break;
		case DOWN:
			snake.nodes[0].y += snake.speed;
			break;
		case LEFT:
			snake.nodes[0].x -= snake.speed;
			break;
		case RIGHT:
			snake.nodes[0].x += snake.speed;
			break;
	}


}


//读取键盘
void Controlsnake()
{
	char key = _getch();
	switch (key)
	{
		case 72:
			if (snake.dir == DOWN) 
			{
				snake.dir = DOWN;
				break;
			}
			snake.dir = UP;
			break;
		case 80:
			if (snake.dir == UP)
			{
				snake.dir = UP;
				break;
			}
			snake.dir = DOWN;
			break;
		case 75:
			if (snake.dir == RIGHT)
			{
				snake.dir = RIGHT;
				break;
			}
			snake.dir = LEFT;
			break;
		case 77:
			if (snake.dir == LEFT)
			{
				snake.dir = LEFT;
				break;
			}
			snake.dir = RIGHT;
			break;
	}
}


//创建食物
void Creatfood()
{
	if (!food.flag)
	{
		food.x = rand() % (WIDTH / 10) * 10;
		food.y = rand() % (HEIGHT / 10) * 10;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.flag = true;
	}
}


//蛇吃食物
void Eat()
{
	if(food.flag)
	if (snake.nodes[0].x == food.x && snake.nodes[0].y == food.y)
	{
		food.flag = false;
		snake.num++;
		snake.score += 10;
		snake.nodes[snake.num-1].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		Creatfood();
	}
}

//主程序入口
int main()
{
	initgraph(WIDTH, HEIGHT);
	setbkcolor(GREEN);
	cleardevice();

	Initgame();

	

	while (1) 
	{
		Drawsnake();
		Movesnake();
		//BeginBatchDraw();
		if (_kbhit())
		{
			Controlsnake();
		}
		Edge();
		Dead();
		FlushBatchDraw();
		Eat();
		Sleep(10);



	}
	return 0;
}