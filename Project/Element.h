#pragma once
#include "Node.h"
class Element
{
private:
    int id;
	Node* array_node;
	double** jacobian;
	double* det_jacobian;
	double** det_divide_jacobian;
	double** dndx;
	double** dndy;
	double** dnde;
	double** dndn;
	double*** dndx_multiply_dndx_t;
	double*** dndy_multiply_dndy_t;
	double*** det_multiply_dnmdx_t;
	double*** det_multiply_dnmdy_t;
	double*** matrix_multiply_conductivity;
	double** final_matrix;
public:
	void set_array_node(Node* array_node);
	void set_id(int id);
	Node* get_array_node();
	int get_id();
	void set_jacobian(double** jacobian);
	double** get_jacobian();
	void set_det_jacobian(double* det_jacobian);
	double* get_det_jacobian();
	void set_det_divide_jacobian(double** det_divide_jacobian);
	double** get_det_divide_jacobian();
	double** get_dndx();
	double** get_dndy();
	void set_dnde(double** dnde);
	void set_dndn(double** dndn);
	double** get_dnde();
	double** get_dndn();
	double*** get_dndx_multiply_dndx_t();
	double*** get_dndy_multiply_dndy_t();
	double*** get_det_multiply_dnmdx_t();
	double*** get_det_multiply_dnmdy_t();
	double*** get_matrix_multiply_conductivity();
	double** get_final_matrix();
	Element();
	~Element();
};

