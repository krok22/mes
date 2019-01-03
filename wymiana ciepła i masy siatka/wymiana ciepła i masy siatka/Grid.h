#pragma once
#include "Element.h"
class Grid
{
private:
	int id=0;
	int length, heigth;
	Element *element_array;
	Node *node_array;	
	void initialize(int,int);
public:
	Grid(int,int);
	~Grid();
	Element* get_element_array();
	Node* get_node_array();
};

