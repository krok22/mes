#include "Grid.h"



Grid::Grid(int length,int heigth)
{
	initialize(length,heigth);
}


Grid::~Grid()
{
	
}

Element* Grid::get_element_array()
{
	return this->element_array;

}
Node* Grid::get_node_array()
{
	return this->node_array;
}

double ** Grid::get_global_matrix_h()
{
	return this->global_matrix_h;
}

double * Grid::get_global_matrix_p()
{
	return this->global_matrix_p;
}

void Grid::initialize(int length, int heigth)
{
	int size_node_array = length * heigth;
	node_array = new Node[size_node_array];
	for (int i = 0; i < size_node_array; i++)
		node_array[i].set_id(i + 1);

	element_array = new Element[(length - 1)*(heigth - 1)];
	
	for (int i = 0,index=0; i <length-1; i++)
	{
		for (int j = 0; j < heigth-1; j++,index++)
		{
			element_array[index].set_id(index + 1);
			Node *array_from_node = element_array[index].get_array_node();

				array_from_node[0] = node_array[index + i];
				array_from_node[1] = node_array[index +i+ heigth];
				array_from_node[2] = node_array[index + i+ heigth +1];
				array_from_node[3] = node_array[index + i+1];
			
		}
	}

	

}