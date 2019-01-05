#pragma once
class Node
{private:
	double x, y, t;
	int id;
	
public:
	void set_x(double x);
	void set_y(double y);
	void set_t(double t);
	void set_id(int id);
	double get_x();
	double get_y();
	double get_t();

	int get_id();
	Node();
	~Node();
};

