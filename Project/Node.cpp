#include "Node.h"



Node::Node()
{
}


Node::~Node()
{
}

int Node::get_id()
{
	return this->id;
}

double Node::get_y()
{
	return this->y;
}

double Node::get_x()
{
	return this->x;
}


void Node :: set_x(double x)
{
	this->x = x;
}
void Node :: set_y(double y)
{
	this->y = y;
}
void Node::set_t(double t)
{
	this->t = t;
}

void Node::set_id(int id)
{
	this->id = id;
}

