#include "iostream"
#include "string"
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;

const int height = 50;
const int width = 20;

struct position {
	int x,y;
};

position generate_random()
{
	position p;
	srand(time(NULL));
	p.x = (rand() % (width - 2)) + 1;
	p.y = (rand() % (height - 2)) + 1;
	return p;
}

class point {
	position p;
	char x;
public:
	point(){}
	point(position p1, char x1 = 'O')
	{
		p = p1;
		x = x1;
	}
	void set_char(char b)
	{
		x = b;
	}
	void set_position(position p)
	{
		this->p = p;
	}
	void set_position(int x, int y)
	{
		this->p.x = x;
		this->p.y = y;
	}
	position get_position()
	{
		return p;
	}
	char get_char()
	{
		return x;
	}
	void generate_fruit()
	{
		
		this->set_position(generate_random());
		this->set_char('@');
	}
};

void swap(point&a, point&b)
{
	point temp = a;
	a = b;
	b = temp;
}

class snake {
	point head;
	point tail[9*width*height/10];
	int count;
public:
	snake()
	{
		count = 0;
	}
	int get_count()
	{
		return count;
	}
	position get_head_position()
	{
		return head.get_position();
	}
	void increase_count()
	{
		count++;
	}
	char get_head_char()
	{
		return head.get_char();
	}
	void set_head_position(position p1)
	{
		head.set_position(p1);
	}
	point* get_tail()
	{
		return tail;
	}
	void set_head(point p)
	{
		head = p;
	}
	void move (string x)
	{
		position p = this->get_head_position();
		if (count > 1)
		{
			for(int i = count; i >= 1; i--)
			{
				tail[i] = tail[i-1]; 
			}
		}
		tail[0].set_position(p);
		if (x == "Up")
		{
			p.y--;
			head.set_position(p);
		}
		else if (x == "Down")
		{
			p.y++;
			head.set_position(p);
		}
		else if (x == "Right")
		{
			p.x++;
			head.set_position(p);
		}
		else if (x == "Left")
		{
			p.x--;
			head.set_position(p);
		}
	}
};

class map {
	snake s;
	point fruit;
	point arr[width][height];
	void draw()
	{
		system("cls");
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < height; j++)
			{
				if (i == 0 || i == width-1 || j == 0 || j == height-1)
					arr[i][j].set_char('*');
				else if (i == s.get_head_position().x && j == s.get_head_position().y)
					arr[i][j].set_char(s.get_head_char());
				else if (i == fruit.get_position().x && j == fruit.get_position().y)
					arr[i][j].set_char(fruit.get_char());
				else
					arr[i][j].set_char(' ');
				for(int k = 0; k < s.get_count(); k++)
				{
					if(i == s.get_tail()[k].get_position().x && j == s.get_tail()[k].get_position().y)
					{		
						arr[i][j].set_char('o');
						break;
					}
				}
				cout << arr[i][j].get_char();
			}
			cout<<endl;
		}
		cout<<"\t\t   Score = "<<s.get_count()<<endl;
	}
public:
	map()
	{
		point p1;
		position x = {width/2, height/2};
		p1.set_char('O');
		p1.set_position(x);
		s.set_head(p1);
		fruit.generate_fruit();
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < height; j++)
			{
				if (i == 0 || i == width-1 || j == 0 || j == height-1)
					arr[i][j].set_char('*');
				else if (i == s.get_head_position().x && j == s.get_head_position().y)
					arr[i][j].set_char(s.get_head_char());
				else if (i == fruit.get_position().x && j == fruit.get_position().y)
					arr[i][j].set_char(fruit.get_char());
				else
					arr[i][j].set_char(' ');
				for(int k = 0; k < s.get_count(); k++)
				{
					if(i == s.get_tail()[k].get_position().x && j == s.get_tail()[k].get_position().y)
						arr[i][j].set_char('o');
				}
			}
		}
	}
	void play(){
		while(1)
		{
			this->draw();
			string move;
			position n;
			int y1 = s.get_head_position().y;
			int x1 = s.get_head_position().x;
			if(_kbhit())
			{
				char c = _getch();
				switch(c) {
				case 75:
					move = "Up";
					s.move(move);
					break;
				case 77:
					move = "Down";
					s.move(move);
					break;
				case 80:
					move = "Right";
					s.move(move);
					break;
				case 72:
					move = "Left";
					s.move(move);
					break;
				case 'x':
					exit(0);
				}
				if (s.get_head_position().x == fruit.get_position().x && s.get_head_position().y == fruit.get_position().y)
				{
					while(1)
					{
						fruit.generate_fruit();
						int i = 0;
						if(s.get_head_position().x == fruit.get_position().x && s.get_head_position().y == fruit.get_position().y)
							i++;
						for(int k = 0; k < s.get_count(); k++)
						{
							if(fruit.get_position().x == s.get_tail()[k].get_position().x && fruit.get_position().y == s.get_tail()[k].get_position().y)
							{		
								i++;
								break;
							}
						}
						if(i==0)
							break;
					}
					s.increase_count();
				}
				if (s.get_head_position().x <= 0 || s.get_head_position().x >= width-1 || s.get_head_position().y <= 0 || s.get_head_position().y >= height-1)
				{
					break;
				}
			}
			if (s.get_head_position().x <= 0 || s.get_head_position().x >= width-1 || s.get_head_position().y <= 0 || s.get_head_position().y >= height-1)
			{
				break;
			}
			for (int i = 0; i < s.get_count(); i++)
			{
				if(s.get_tail()[i].get_position().x == s.get_head_position().x && s.get_tail()[i].get_position().y == s.get_head_position().y)
				{
					system("pause");
					exit(0);
				}
			}
			while(!(_kbhit()))
			{
				s.move(move);
				this->draw();
				if (s.get_head_position().x == fruit.get_position().x && s.get_head_position().y == fruit.get_position().y)
				{
					while(1)
					{
						fruit.generate_fruit();
						int i = 0;
						if(s.get_head_position().x == fruit.get_position().x && s.get_head_position().y == fruit.get_position().y)
							i++;
						for(int k = 0; k < s.get_count(); k++)
						{
							if(fruit.get_position().x == s.get_tail()[k].get_position().x && fruit.get_position().y == s.get_tail()[k].get_position().y)
							{		
								i++;
								break;
							}
						}
						if(i==0)
							break;
					}
					s.increase_count();
				}
				if (s.get_head_position().x <= 0 || s.get_head_position().x >= width-1 || s.get_head_position().y <= 0 || s.get_head_position().y >= height-1)
				{
					break;
				}
				for (int i = 0; i < s.get_count(); i++)
				{
					if(s.get_tail()[i].get_position().x == s.get_head_position().x && s.get_tail()[i].get_position().y == s.get_head_position().y)
					{
						system("pause");
						exit(0);
					}
				}
				Sleep(30);
			}
			Sleep(30);
		}
	}
};


int main()
{
	map m;
	m.play();
	system("pause");
	return 0;
}