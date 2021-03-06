// lab1_task16.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>

using namespace std;

const double p = 0.5;
const int max_level = 8;

struct node {
	int data;
	node **forward;
	node(int level, int& data)
	{
		forward = new node *[level + 1];
		memset(forward, 0, sizeof(node*)* (level + 1));
		this->data = data;
	}
	
	~node()
	{
		delete [] forward;
	}
};

struct skiplist
{
	node *root;
	int data;
	int level;

	skiplist()
	{
		root = new node(max_level, data);
		level = 0;
	}
	~skiplist()
	{
		delete root;
	}
	void print();
	void insert_element(int &);
	bool search(int &);
};
int main()
{
	skiplist test;
	int k , n;
	for (int i = 0; i < 10; i++)
	{
		cin >> n;
		test.insert_element(n);
	}

	test.print();
	cout << "Enter searching element: ";
	cin >> k; 
	if (test.search(k))
		cout << "Your element is in list!" << endl;
	else
		cout << "Eement not found!" << endl;
    return 0;
}

double frand()
{
	return (double) rand() / RAND_MAX;
}

int random_level()
{
	 static bool flag = true;
	if (flag)
	{
		srand((unsigned)time(NULL));
		flag = false;
	}
	int lvl = (int)(log(frand()) / log(1.-p));
	return lvl < max_level ? lvl : max_level;
}

void skiplist::insert_element(int &value)
{
	node *tmp = root;
	node *update[max_level + 1];
	memset(update, 0, sizeof(node*)* (max_level + 1));
	for (int i = level; i >=0 ; i--)
	{
		while (tmp->forward[i] != NULL && tmp->forward[i]->data < value)
		{
			tmp = tmp->forward[i];
		}
		update[i] = tmp;
	}

	tmp = tmp->forward[0];
	if (tmp == NULL || tmp->data != value)
	{
		int lvl = random_level();
		if (lvl > level)
		{
			for (int i = level + 1; i <= lvl; i++)
				update[i] = root;
			level = lvl;
		}

		tmp = new node(lvl, value);
		for (int i = 0; i <= lvl; ++i)
		{
			tmp->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = tmp;
		}
	}
}

void skiplist::print()
{
	const node * tmp = root->forward[0];
	while (tmp)
	{
		cout << tmp->data;
		tmp = tmp->forward[0];
		if (tmp != NULL)
			cout << " -> ";
	}
	cout << endl;
}

bool skiplist::search(int & value)
{
	node * tmp = root;
	for (int i = level; i >= 0; i--)
	{
		while (tmp->forward[i] != NULL && tmp->forward[i]->data < value)
			tmp = tmp->forward[i];
	}
	tmp = tmp->forward[0];
	return tmp != NULL && tmp->data == value;
}