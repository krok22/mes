#pragma once
#include "Node.h"
class Element
{
private:
    int id;
	double* boundary_conditions;
	Node* array_node;
	double* det_jacobian;
	double* jacobian_surface;
	double* matrix_p;
	double* matrix_p_2;
	double* final_matrix_p;
	double** jacobian;
	double** det_divide_jacobian;
	double** dndx;
	double** dndy;
	double** dnde;
	double** dndn;
	double** matrix_pc_n1n2n3n4;
	double** final_matrix_c;
	double** final_matrix;
	double** final_matrix_h_2d_bc;
	double** matrix_n_sum_n;
	double** matrix_p2_n_sum_n;
	double*** ann;
	double*** qnn;
	double*** dndx_multiply_dndx_t;
	double*** dndy_multiply_dndy_t;
	double*** det_multiply_dnmdx_t;
	double*** det_multiply_dnmdy_t;
	double*** matrix_multiply_conductivity;
	double*** pc_matrix_n_multiply_nt;
	double*** n1n2n3n4;
	double*** sum_nnt;
	double**** nnt;
public:
	void set_array_node(Node* array_node);
	void set_id(int id);
	Node* get_array_node();
	int get_id();
	double* get_boundary_conditions();
	double* get_jacobian_surface();
	void set_boundary_condition(double* boundary_condition);
	void set_jacobian(double** jacobian);
	double** get_jacobian();
	void set_det_jacobian(double* det_jacobian);
	double* get_det_jacobian();
	double* get_matrix_p();
	double* get_matrix_p_2();
	double* get_final_matrix_p();
	void set_det_divide_jacobian(double** det_divide_jacobian);
	double** get_matrix_n_sum_n();
	double** get_det_divide_jacobian();
	double** get_dndx();
	double** get_dndy();
	void set_dnde(double** dnde);
	void set_dndn(double** dndn);
	double** get_dnde();
	double** get_dndn();
	double** get_final_matrix_c();
	double** get_final_matrix();
	double** get_matrix_pc_n1n2n3n4();
	double** get_final_matrix_h_2d_bc();
	double** get_matrix_p2_n_sum_n();
	double*** get_ann();
	double*** get_qnn();
	double*** get_dndx_multiply_dndx_t();
	double*** get_dndy_multiply_dndy_t();
	double*** get_det_multiply_dnmdx_t();
	double*** get_det_multiply_dnmdy_t();
	double*** get_matrix_multiply_conductivity();
	double*** get_pc_matrix_n_multiply_nt();
	double*** get_n1n2n3n4();
	double*** get_sum_nnt();
	double**** get_nnt();

	Element();
	~Element();
};

