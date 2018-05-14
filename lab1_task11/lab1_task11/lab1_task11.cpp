// lab1_task11.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <cstring>

using namespace std;



struct node {
	int exp;
	int coef;
	node *next;
};

node *fill(node *root ,int e, int c)
{	
	node *temp = new node();
	temp->coef = c;
	temp->exp = e;
	temp->next = NULL;

	if (root)	
	{
		node *cur = root;
		cur = root;
		while (cur->next)
			cur = cur->next;
		cur->next = temp;
	}
	else
	{
		root = temp;
	}
	return root;
}
node *DeleteZeros(node *root)
{
	node * tmp = root;
	node *prev = NULL;
	while (tmp)
	{
		if (tmp->coef == 0)
		{
			if (prev != NULL)
			{
				prev->next = tmp->next;
				delete tmp;
				tmp = prev;
			}
			else
			{
				root = tmp->next;
				delete tmp;
				tmp = root;
			}
		}

		prev = tmp;
		tmp = tmp->next;
	}
	return root;
}
void output(node *Root)
{
	while (Root) {
		cout << Root->coef << "x^" << Root->exp;
		if(Root->next) 
			cout << " + ";
		Root = Root->next;
	}
	cout << endl;
}
node *adding_polinoms(node* root)
{
	int n;
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int c = 0;
		int e = 0;
		cin >> c;
		cin >> e;
		root = fill(root, e, c);
	}
	return root;
}
node *addition_polinoms(node *p1, node *p2)
{
	node *result = NULL;
	node *tmp = NULL,*temp_p2 = p2;

	tmp = p1;
	while (tmp)
	{
		result = fill(result, tmp->exp, tmp->coef);
		tmp = tmp->next;
	}

	while (temp_p2)
	{
		bool flag = false;
		tmp = result;
		while (tmp)
		{
			if (tmp->exp == temp_p2->exp)
			{
				tmp->coef += temp_p2->coef;
				flag = true;
				break;
			}
			tmp = tmp->next;
		}
		if (!flag)
		{
			result = fill(result, temp_p2->exp, temp_p2->coef);
			flag = false;
		}
		temp_p2 = temp_p2->next;
	}
	return result;
}
node *substraction(node *p1, node *p2)
{
	node *result = NULL;
	node *tmp = NULL, *temp_p2 = p2;

	tmp = p1;
	while (tmp)
	{
		result = fill(result, tmp->exp, tmp->coef);
		tmp = tmp->next;
	}

	while (temp_p2)
	{
		bool flag = false;
		tmp = result;
		while (tmp)
		{
			if (tmp->exp == temp_p2->exp)
			{
				tmp->coef -= temp_p2->coef;
				flag = true;
				break;
			}
			tmp = tmp->next;
		}
		if (!flag)
		{
			result = fill(result, temp_p2->exp, -temp_p2->coef);
			flag = false;
		}
		temp_p2 = temp_p2->next;
	}
	return result;
}
node *multiplication(node *p1, node *p2)
{
	node *result = NULL,*main_p1 = p1,*temp_p1 = p1,*temp_p2 = p2;
	node *tmp = NULL;
	while (temp_p2)
	{
		temp_p1 = main_p1;
		while (temp_p1)
		{
			bool flag = false;
			result = tmp;
			while (result)
			{
				if (result->exp == temp_p1->exp+temp_p2->exp)
				{
					result->coef += temp_p1->coef * temp_p2->coef;
					flag = true;
					break;
				}				
				result = result->next;
			}
			if (!flag)
				tmp = fill(tmp, temp_p1->exp+temp_p2->exp, temp_p1->coef*temp_p2->coef);
			temp_p1 = temp_p1->next;
		}
		temp_p2 = temp_p2->next;
	}
	return tmp;
}

node *SortedInsert(node *root, node *newnode)
{
	if (root==NULL || newnode->exp > root->exp)
	{
		newnode->next = root;
		root = newnode;
		return root;
	}
	else
	{
		node *current = root;
		while (current->next && !(newnode->exp > current->next->exp))
			current = current->next;
		newnode->next = current->next;
		current->next = newnode;
	}
	return root;
}

node *InsertSort(node *root)
{
	node *result = NULL;
	while (root)
	{
		node *newnode = root;
		root = root->next;
		result = SortedInsert(result, newnode);
	}
	return result;
}
node *division(node *p1, node *p2)
{
	node *result = NULL, *main_p1 = p1, *main_p2 = p2, *temp_p1 = p1;
	result->coef = temp_p1->coef / main_p2->coef;
	result->exp = temp_p1->exp - main_p2->exp;
	result->next = NULL;
	while (temp_p1->exp >= main_p2->exp && temp_p1->coef / main_p2->coef != 0)
	{
		temp_p1 = InsertSort(DeleteZeros(substraction(temp_p1, multiplication(main_p2, result))));
		result = fill(result, temp_p1->exp - main_p2->exp, temp_p1->coef/main_p2->coef);
	}

	return result;
}

int main()
{
	node *p1 = NULL;
	node *p2 = NULL;
	cout << "first: " << endl;
	p1 = adding_polinoms(p1);
	cout << "second: " << endl;
	p2 = adding_polinoms(p2);
	
	output(p1);
	output(p2);
	output(InsertSort(addition_polinoms(p1, p2)));
	output(DeleteZeros(substraction(p1, p2)));
	output(InsertSort(multiplication(p1, p2)));
	p1 = InsertSort(p1);
	p2 = InsertSort(p2);
	//output(InsertSort(division(p1, p2)));
    return 0;
}

