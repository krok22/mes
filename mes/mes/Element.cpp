#include "Element.h"

Element::Element()
{
	array_node = new Node[4];
	jacobian = new double*[4];
	det_jacobian = new double[4];
	boundary_conditions = new double[4];
	det_divide_jacobian = new double*[4];
	dndx = new double*[4];
	dndy = new double*[4];
	final_matrix_c = new double*[4];
	final_matrix = new double*[4];
	matrix_pc_n1n2n3n4 = new double*[4];
	dndx_multiply_dndx_t = new double**[4];
	dndy_multiply_dndy_t = new double**[4];
	det_multiply_dnmdx_t = new double**[4];
	det_multiply_dnmdy_t = new double**[4];
	n1n2n3n4 = new double**[4];
	matrix_multiply_conductivity = new double**[4];
	pc_matrix_n_multiply_nt = new double**[4];
	sum_nnt = new double**[4];
	nnt = new double***[4];

	for (int i = 0; i < 4; i++)
	{
		boundary_conditions[i] = 0.0;
		jacobian[i] = new double[4];
		det_divide_jacobian[i] = new double[4];
		dndx[i] = new double[4];
		dndy[i] = new double[4];
		final_matrix[i] = new double[4];
		final_matrix_c[i] = new double[4];
		matrix_pc_n1n2n3n4[i] = new double[4];
		dndx_multiply_dndx_t[i] = new double*[4];
		dndy_multiply_dndy_t[i] = new double*[4];
		det_multiply_dnmdx_t[i] = new double*[4];
		det_multiply_dnmdy_t[i] = new double*[4];
		matrix_multiply_conductivity[i] = new double*[4];
		pc_matrix_n_multiply_nt[i] = new double*[4];
		n1n2n3n4[i] = new double*[2];
		sum_nnt[i] = new double*[4];
		nnt[i] = new double**[2];
		
		for (int j = 0; j < 4; j++)
		{
			dndx_multiply_dndx_t[i][j] = new double[4];
			dndy_multiply_dndy_t[i][j] = new double[4];
			det_multiply_dnmdx_t[i][j] = new double[4];
			det_multiply_dnmdy_t[i][j] = new double[4];
			matrix_multiply_conductivity[i][j] = new double[4];
			pc_matrix_n_multiply_nt[i][j] = new double[4];
			n1n2n3n4[i][j] = new double[4];
			sum_nnt[i][j] = new double[4];
			nnt[i][j] = new double*[4];

			for (int k = 0; k < 4; k++)
			{
				nnt[i][j][k] = new double[4];
			}
		}
	}
	
}


Element::~Element()
{
	
}
void Element::set_array_node(Node* array_node)
{
	this->array_node = array_node;
}
Node* Element::get_array_node()
{
	return this->array_node;
}
void Element::set_id(int id) {
	this->id = id;
}

int Element::get_id()
{
	return this->id;
}

double* Element::get_boundary_conditions()
{
	return this->boundary_conditions;
}

void Element::set_boundary_condition(double * boundary_condition)
{
	this->boundary_conditions = boundary_condition;
}

void Element::set_jacobian(double** jacobian)
{
	this->jacobian = jacobian;
}

double** Element::get_jacobian()
{
	return this->jacobian;
}

void Element::set_det_jacobian(double* det_jacobian)
{
	this->det_jacobian = det_jacobian;
}

double* Element::get_det_jacobian()
{
	return this->det_jacobian;
}

void Element::set_det_divide_jacobian(double ** det_divide_jacobian)
{
	this->det_divide_jacobian = det_divide_jacobian;
}

double ** Element::get_det_divide_jacobian()
{
	return this->det_divide_jacobian;
}

double ** Element::get_dndx()
{
	return this->dndx;
}

double ** Element::get_dndy()
{
	return this->dndy;
}

void Element::set_dnde(double ** dnde)
{
	this->dnde = dnde;
}

void Element::set_dndn(double ** dndn)
{
	this->dndn = dndn;
}

double ** Element::get_dnde()
{
	return this->dnde;
}

double ** Element::get_dndn()
{
	return this->dndn;
}

double ** Element::get_final_matrix_c()
{
	return this->final_matrix_c;
}

double ** Element::get_final_matrix()
{
	return this->final_matrix;
}

double** Element::get_matrix_pc_n1n2n3n4()
{
	return this->matrix_pc_n1n2n3n4;
}

double *** Element::get_dndx_multiply_dndx_t()
{
	return this->dndx_multiply_dndx_t;
}

double *** Element::get_dndy_multiply_dndy_t()
{
	return this->dndy_multiply_dndy_t;
}

double *** Element::get_det_multiply_dnmdx_t()
{
	return this->det_multiply_dnmdx_t;
}

double *** Element::get_det_multiply_dnmdy_t()
{
	return this->det_multiply_dnmdy_t;
}

double *** Element::get_matrix_multiply_conductivity()
{
	return this->matrix_multiply_conductivity;
}

double *** Element::get_pc_matrix_n_multiply_nt()
{
	return this->pc_matrix_n_multiply_nt;
}

double *** Element::get_n1n2n3n4()
{
	return this->n1n2n3n4;
}

double *** Element::get_sum_nnt()
{
	return this->sum_nnt;
}

double **** Element::get_nnt()
{
	return this->nnt;
}