#include<iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include "Grid.h"
using namespace std;

double** jacobian2d(Grid grid,int amount_of_elements);
double** matrixC(Grid grid,int amount_of_elements);
double** matrix_h_2d_bc(Grid grid, int amount_of_elements);
double*  matrix_p(Grid grid, int amount_of_elements);
double** aggregation(Grid grid, int amount_of_elements);
double* aggregation_vector_p(Grid grid, int amount_of_elements);
int main()
{
	string linia;
	fstream plik;
	int length;
	int heigth;
	double v[16][16];
	int tmp;
	int amount_of_elements;
	double **is_boundary_condition;
	is_boundary_condition = new double*[10];

	plik.open("Text.txt", ios::in);
	if (plik.good() == true)
	{
		getline(plik, linia);
		length = stoi(linia);
		tmp = length * 2;
		amount_of_elements = length/ 4;
		is_boundary_condition = new double*[amount_of_elements];
		for (int i = 0; i < tmp; i++)
		{
			getline(plik, linia);
			v[0][i] = stod(linia);
		}
			/*length = stoi(linia);
			getline(plik, linia);
			heigth = stoi(linia);*/

		for (int i = 0; i < amount_of_elements; i++)
		{
			is_boundary_condition[i] = new double[4];
		}
		double* tmpp = new double[length];

		for (int i = 0, j = 0; i < length; i++) {
			getline(plik, linia);
			tmpp[i] = stoi(linia);
		}
		//cout << "test" << endl;
		for (int i = 0, k=0; i < amount_of_elements; i++)
		{
			for (int j = 0; j < 4; j++,k++)
			{
				is_boundary_condition[i][j] = tmpp[k];
			//	cout << is_boundary_condition[i][j] << " ";
			}
			//cout << endl;
		}

		plik.close();
		//cout << "end of test" << endl;
	}

	for (int i = 0; i <tmp; i++)
	{
		//cout << v[0][i] << endl;
	}

	Grid grid(length-2,length-2);

	Element* elements = grid.get_element_array();
	Node* nodes = elements[0].get_array_node();
	elements[0].set_boundary_condition(is_boundary_condition[0]);
	//cout << "*****TEST*****" << endl;
	for (int i = 0,j=0; j < length; i++,j++)
	{
		nodes[j].set_x(v[0][i]);
		i += 1;
		nodes[j].set_y(v[0][i]);
		//cout << "node_id " << nodes[j].get_id() << endl;
		//cout << "node_id " << nodes[j].get_x()<<" "<< nodes[j].get_y() << endl;
	}

	//cout << "*****TEST*****" << endl;


	for (int i = 0; i < 1; i++)
	{
		//cout << "element_id " << elements[i].get_id() << endl;
		//cout << "element_nodes " << endl;
		Node* node_from_element = elements[i].get_array_node();
		//cout << node_from_element[0].get_id() << " " << node_from_element[1].get_id() << " " << node_from_element[2].get_id() << " " << node_from_element[3].get_id() << endl;

	}
	cout << "Matrix H" << endl;
	double** matrix=jacobian2d(grid,1);

/*	for (int i = 0; i < 4; i++)
	{
		cout << "matrix h ";
		for (int j = 0; j < 4; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	*/

	matrixC(grid, 1);
	matrix_h_2d_bc(grid, 1);
	matrix_p(grid, 1);
	aggregation(grid, 1);

	system("pause");
}

double** jacobian2d(Grid grid, int amount_of_elements)
{
	double e[4], n[4];
	n[0] = -0.57735;
	n[1] = -0.57735;
	n[2] = 0.57735;
	n[3] = 0.57735;
	e[0] = -0.57735;
	e[1] = 0.57735;
	e[2] = 0.57735;
	e[3] = -0.57735;

	double dnde[4][4],dndn[4][4];
	double jacobian[4][4];
	double** matrix_h;

	matrix_h = new double*[4];
	
	for (int i = 0; i < 4; i++)
	{
		dnde[i][0] = -0.25*(1 - n[i]);
		dnde[i][1] = 0.25*(1 - n[i]);
		dnde[i][2] = 0.25*(1 + n[i]);
		dnde[i][3] = -0.25*(1 + n[i]);

		dndn[i][0] = -0.25*(1 - e[i]);
		dndn[i][1] = -0.25*(1 + e[i]);
		dndn[i][2] = 0.25*(1 + e[i]);
		dndn[i][3] = 0.25*(1 - e[i]);
	}

	//for (int i = 0; i < 4; i++)
	//{
		//cout << dnde[i][0]<<" " << dnde[i][1]<<" " << dnde[i][2] << " " << dnde[i][3] << " " << dndn[i][0] << " " << dndn[i][1] << " " << dndn[i][2] << " " << dndn[i][3] << " " << endl;
	//}

	Element* element = grid.get_element_array();

	for (int i = 0; i < amount_of_elements; i++)
	{
		Node* node = element[i].get_array_node();
		double**jacobian = element[i].get_jacobian();
		double*det_jacobian = element[i].get_det_jacobian();
		double** det_divide_jacobian = element[i].get_det_divide_jacobian();
		double** dndx = element[i].get_dndx();
		double** dndy = element[i].get_dndy();
		double***dndx_multiply_dndx_t = element[i].get_dndx_multiply_dndx_t();
		double***dndy_multiply_dndy_t = element[i].get_dndy_multiply_dndy_t();
		double***det_multiply_dnmdx_t = element[i].get_det_multiply_dnmdx_t();
		double***det_multiply_dnmdy_t = element[i].get_det_multiply_dnmdy_t();
		double conductivity = 30;
		double*** matrix_multiply_conductivity = element[i].get_matrix_multiply_conductivity();
		double** final_matrix = element[i].get_final_matrix();

		for (int j = 0; j < 4; j++)
		{
			jacobian[j][0] = (dnde[j][0] * node[0].get_x()) + (dnde[j][1] * node[1].get_x()) + (dnde[j][2] * node[2].get_x()) + (dnde[j][3] * node[3].get_x());
			//cout << "kkkkkkk" << dnde[j][0] << " " << node[0].get_x() << " " << dnde[j][1] << " " << node[1].get_x() << " " << dnde[j][2] << " " << node[2].get_x() << " " << dnde[j][3] << " " << node[3].get_x() << endl;
			jacobian[j][1] = dnde[j][0] * node[0].get_y() + dnde[j][1] * node[1].get_y() + dnde[j][2] * node[2].get_y() + dnde[j][3] * node[3].get_y();
			jacobian[j][2] = dndn[j][0] * node[0].get_x() + dndn[j][1] * node[1].get_x() + dndn[j][2] * node[2].get_x() + dndn[j][3] * node[3].get_x();
			jacobian[j][3] = dndn[j][0] * node[0].get_y() + dndn[j][1] * node[1].get_y() + dndn[j][2] * node[2].get_y() + dndn[j][3] * node[3].get_y();
			//cout << jacobian[j][0] << " " << jacobian[j][1] << " " << jacobian[j][2] << " " << jacobian[j][3] << endl;
		}

		for (int i = 0; i < 4; i++)
		{
			det_jacobian[i] = jacobian[i][0] * jacobian[i][3] - jacobian[i][1] * jacobian[i][2];
			//cout << "det jacobian " << det_jacobian[i] << endl;
		}

		for (int i = 0; i < 4; i++)
		{
			//cout << "det divide jacobian ";
			for (int j = 0; j < 4; j++) {
				det_divide_jacobian[i][j] = jacobian[i][j] / det_jacobian[i];
				cout << det_divide_jacobian[i][j] << " ";
			}
			//cout << endl;
		}
		cout << endl;
		for (int i = 0; i < 4; i++)
		{
			//cout << "dndx ";
			//cout << "dndy";
			for (int j = 0; j < 4; j++)
			{
				dndx[i][j] = det_divide_jacobian[i][0] * dnde[i][j] + det_divide_jacobian[i][1] * dnde[i][j];
				dndy[i][j] = det_divide_jacobian[i][2] * dndn[i][j] + det_divide_jacobian[i][3] * dndn[i][j];
				//cout << dndx[i][j]<<" ";
				//cout << dndy[i][j] << " ";
			}
			//cout << endl;
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//cout << "dndx_multiply_dndx_t ";
				//cout << "dndy_multiply_dndy_t ";
				for (int k = 0; k < 4; k++)
				{
					dndx_multiply_dndx_t[i][j][k] = dndx[i][k] * dndx[i][j];
					//cout << dndx_multiply_dndx_t[i][j][k]<<" ";
					dndy_multiply_dndy_t[i][j][k] = dndy[i][k] * dndy[i][j];
					//cout << dndy_multiply_dndy_t[i][j][k] << " ";
				}
				//cout << endl;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//cout << "det_multiply_dndx_t" << " ";
				//cout << "det_multiply_dndy_t" << " ";
				for (int k = 0; k < 4; k++)
				{
					det_multiply_dnmdx_t[i][j][k] = dndx_multiply_dndx_t[i][j][k] * det_jacobian[j];
					//cout << det_multiply_dnmdx_t[i][j][k]<<" ";
					det_multiply_dnmdy_t[i][j][k] = dndy_multiply_dndy_t[i][j][k] * det_jacobian[j];
					//cout << det_multiply_dnmdy_t[i][j][k] << " ";
				}
				//cout << endl;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//cout << "matrix_multiply_conductivity ";
				for (int k = 0; k < 4; k++)
				{
					matrix_multiply_conductivity[i][j][k] = (det_multiply_dnmdx_t[i][j][k] + det_multiply_dnmdy_t[i][j][k])*conductivity;
					//cout << matrix_multiply_conductivity[i][j][k] << " ";
				}
				//cout << endl;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			//cout << "final matrix ";
			for (int j = 0; j < 4; j++)
			{
				final_matrix[i][j] = matrix_multiply_conductivity[0][i][j] + matrix_multiply_conductivity[1][i][j] + matrix_multiply_conductivity[2][i][j] + matrix_multiply_conductivity[3][i][j];
				//cout << final_matrix[i][j] << " ";
			}
			//cout << endl;
		}
		matrix_h = final_matrix;
	}
	return matrix_h;
}
double** matrixC(Grid grid,int amount_of_elements)
{
	double e[4], n[4];
	n[0] = -0.57735;
	n[1] = -0.57735;
	n[2] = 0.57735;
	n[3] = 0.57735;
	e[0] = -0.57735;
	e[1] = 0.57735;
	e[2] = 0.57735;
	e[3] = -0.57735;

	Element* element_array = grid.get_element_array();
	for (int i = 0; i < amount_of_elements; i++)
	{
		double c = 700.0;
		double ro = 7800.0;
		double* jacobian = element_array[i].get_det_jacobian();
		double** matrix_pc_n1n2n3n4 = element_array[i].get_matrix_pc_n1n2n3n4();
		double** final_matrix_c = element_array[i].get_final_matrix_c();
		double*** pc_matrix_n_multiply_nt = element_array[i].get_pc_matrix_n_multiply_nt();
		

		//matrix[pc][n1...n4] 
		//cout << "matrix_pc_n1n2n3n4: " << endl;
		for (int i = 0; i < 4; i++)
		{
			matrix_pc_n1n2n3n4[i][0] = 1.0 / 4.0 * (1.0 - (e[i]))*(1.0 - (n[i]));
			matrix_pc_n1n2n3n4[i][1] = 1.0 / 4.0 * (1.0 + (e[i]))*(1.0 - (n[i]));
			matrix_pc_n1n2n3n4[i][2] = 1.0 / 4.0 * (1.0 + (e[i]))*(1.0 + (n[i]));
			matrix_pc_n1n2n3n4[i][3] = 1.0 / 4.0 * (1.0 - (e[i]))*(1.0 + (n[i]));
			//cout << "ksi: " << e[i] << " " << "eta: " << n[i] << endl;
			//cout << matrix_pc_n1n2n3n4[i][0] << " " << matrix_pc_n1n2n3n4[i][1] << " " << matrix_pc_n1n2n3n4[i][2] << " " << matrix_pc_n1n2n3n4[i][3] << " " << endl;	
		}

		//matrix[pc][n1...n4][n1...n4]T

		for (int i = 0; i < 4; i++)
		{
			//cout << "pc: " << i << endl;
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					pc_matrix_n_multiply_nt[i][j][k] = matrix_pc_n1n2n3n4[i][k] * matrix_pc_n1n2n3n4[i][j]*c*ro*jacobian[i];
					//cout << pc_matrix_n_multiply_nt[i][j][k]<<" ";
				}
				//cout << endl;
			}
		}

		//final_matrix sum 

		//cout << "final c matrix: " << endl;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				final_matrix_c[i][j] = pc_matrix_n_multiply_nt[0][i][j] + pc_matrix_n_multiply_nt[1][i][j] + pc_matrix_n_multiply_nt[2][i][j] + pc_matrix_n_multiply_nt[3][i][j];
				//cout << final_matrix_c[i][j] << " ";
			}
			//cout << endl;
		}


		return final_matrix_c;

	}
}

double ** matrix_h_2d_bc(Grid grid, int amount_of_elements)
{
	Element* element_array = grid.get_element_array();
	for (int i = 0; i < amount_of_elements; i++)
	{
		double n[8], e[8];
		double convection = 25.0;
		double* jacobian_surface = element_array[i].get_jacobian_surface();
		double* det_jacobian_surface = new double[4];
		double* boundary_conditions = element_array[i].get_boundary_conditions();
		double** final_matrix_h_2d_bc = element_array[i].get_final_matrix_h_2d_bc();
		double*** n1n2n3n4 = element_array[i].get_n1n2n3n4();
		double*** sum_nnt = element_array[i].get_sum_nnt();
		double**** nnt = element_array[i].get_nnt();

		Node* nodes = element_array[i].get_array_node();

		n[0] = -0.57735;
		n[1] = 0.57735;
		e[0] = -1.0;
		e[1] = -1.0;

		//cout << "TEST" << endl;
		//cout << "e[0]: " << e[0] << " " << "n[0]: " << n[0] << endl;

		n[2] = 1.0;
		n[3] = 1.0;
		e[2] = -0.57735;
		e[3] = 0.57735;

		n[4] = 0.57735;
		n[5] = -0.57735;
		e[4] = 1.0;
		e[5] = 1.0;

		n[6] = -1.0;
		n[7] = -1.0;
		e[6] = 0.57735;
		e[7] = -0.57735;

		//n1n2n3n4[pow][pc][n1...n4]
		//cout << endl;
		//cout << "n1n2n3n4[pow][pc][n1...n4]" << endl<<endl;

		for (int i = 0,k=0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++,k++)
			{
	
					n1n2n3n4[i][j][0] = 0.25*(1 - (n[k]))*(1 - (e[k]));
					n1n2n3n4[i][j][1] = 0.25*(1 + (n[k]))*(1 - (e[k]));
					n1n2n3n4[i][j][2] = 0.25*(1 + (n[k]))*(1 + (e[k]));
					n1n2n3n4[i][j][3] = 0.25*(1 - (n[k]))*(1 + (e[k]));	
					//cout<<endl << "k: " <<k<<endl;
					//cout << "e["<<k<<"]: " << e[k] << endl;
					//cout << "n["<<k<<"]: " << n[k] << endl;
					//cout << n1n2n3n4[i][j][0] << " " << n1n2n3n4[i][j][1] << " " << n1n2n3n4[i][j][2] << " " << n1n2n3n4[i][j][3] << " "<<endl;
			}
			//cout << endl;
		}

		//nnt[pow][pc][n1..n4][n1..n4]t
		//cout<<endl<<"nnt[pow][pc][n1..n4][n1..n4]t"<<endl<<endl;

		for (int i = 0; i < 4; i++)
		{
			//cout << "pow: " << i+1 << endl;
			for (int j = 0; j < 2; j++)
			{
				//cout << "pc: " << j+1 << endl;
				for (int k = 0; k < 4; k++)
				{
					for (int l = 0; l < 4; l++)
					{
						nnt[i][j][k][l] = n1n2n3n4[i][j][l] * n1n2n3n4[i][j][k]*convection;
						//cout << nnt[i][j][k][l] << " ";
					}
					//cout << endl;
				}
				//cout << endl;
			}
			//cout << endl;
		}

		//jakobian powierzchni d�ugo�� odcinka mi�dzy pkt/2
		//cout << endl << "jacobian powierzchni" << endl;

		for (int i = 0,j=1; i < 4; i++,j++)
		{
			if (j == 4)
				j = 0;
			jacobian_surface[i]= sqrt(pow((nodes[i].get_x()-nodes[j].get_x()), 2)+ pow((nodes[i].get_y() - nodes[j].get_y()), 2))/2;
			//cout << "j: "<<j<<" "<<jacobian_surface[i] << endl;
			//cout << "nodes[i].get_x(): " << nodes[i].get_x()<<" " << "nodes[i].get_y(): " << nodes[i].get_y()<<"nodes[j].get_x(): "<< nodes[j].get_x() << " " << "nodes[j].get_y(): " << nodes[j].get_y() << endl;
		}

		//sum_nnt[pow][N1..N4][N1..N4]
		//cout << endl << "sum_nnt[pow][N1..N4][N1..N4]" << endl << endl;

		for (int i = 0; i < 4; i++)
		{
			//cout << "pow: " << i + 1 << endl;
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					sum_nnt[i][j][k] = (nnt[i][0][j][k] + nnt[i][1][j][k])*jacobian_surface[i];
					//cout <<"sum_nnt["<<i<<"]"<<"["<<j<<"]"<<"["<<k<<"]: "<< sum_nnt[i][j][k] <<" ";
					//cout << nnt[i][0][j][k] << " " << jacobian_surface[i]<<" ";
					//cout <<"i: "<<i<<" "<< jacobian_surface[i] << " ";
					//cout << sum_nnt[i][j][k] << " ";
				}
				//cout << endl;
			}
		}

		//final_matrix_h_2d_bc[N1..N4][N1..N4]
		//cout << endl << "final_matrix_h_2d_bc[N1..N4][N1..N4]" << endl;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				final_matrix_h_2d_bc[i][j] = sum_nnt[0][i][j] * boundary_conditions[0] + sum_nnt[1][i][j] * boundary_conditions[1] + sum_nnt[2][i][j] * boundary_conditions[2] + sum_nnt[3][i][j] * boundary_conditions[3];
				//cout << final_matrix_h_2d_bc[i][j] << " ";
			}
			//cout << endl;
		}

	}

	return nullptr;
}

double* matrix_p(Grid grid, int amount_of_elements) 
{
	Element* element_array = grid.get_element_array();
	double a = 85.23;
	double t_infinity = 40.0;

	for (int i = 0; i < amount_of_elements; i++)
	{
		double* matrix_p_1 = element_array[i].get_matrix_p();
		double* jacobian_surface = element_array[i].get_jacobian_surface();
		double** matrix_n_sum_n = element_array[i].get_matrix_n_sum_n();
		double*** ann= element_array[i].get_ann();
		double*** n1n2n3n4 = element_array[i].get_n1n2n3n4();
		double* boundary_conditions = element_array[i].get_boundary_conditions();
		
		//ann[pow][pc][N1..N4]
		//cout << endl << "ann[pow][pc][N1..N4]" << endl;

		for (int i = 0; i < 4; i++)
		{
			//cout << "pow: " << i << endl;
			for (int j = 0; j < 2; j++)
			{
				//cout << "pc: " << j << endl;
				for (int k = 0; k < 4; k++)
				{
					ann[i][j][k] = n1n2n3n4[i][j][k] * a * t_infinity;
					//cout << ann[i][j][k] << " ";
				}
				//cout << endl;
			}
		}
		//matrix_n_sum_n[pow][n1..n4]
		//cout << endl << "matrix_n_sum_n[pow][N]" << endl;
		for (int i = 0; i < 4; i++)
		{
			//cout << "pow: " << i << endl;
			for (int j = 0; j < 4; j++)
			{
				matrix_n_sum_n[i][j] = (ann[i][0][j]+ ann[i][1][j])*jacobian_surface[i];
				//cout << "ann["<<i<<"][0]["<<j<<"]: "<< ann[i][0][j]<<" ann["<<i<<"][1]["<<j<<"]: "<< ann[i][1][j]<<" ";
				//cout << matrix_n_sum_n[i][j] << " ";
				//cout << ann[i][0][j] << " ";
				//cout << ann[i][0][j] << " " << ann[i][1][j] << " ";
			}
			//cout << endl;
		}

		//matrix_p_1[pow]
		cout << "matrix_p_1[pow]" << endl;

		for (int i = 0; i < 4; i++)
		{
			matrix_p_1[i] = (matrix_n_sum_n[i][0] * boundary_conditions[i] + matrix_n_sum_n[i][1] * boundary_conditions[i] + matrix_n_sum_n[i][2] * boundary_conditions[i] + matrix_n_sum_n[i][3] * boundary_conditions[i])*(-1.0);
			cout << matrix_p_1[i] << " ";
		}	
		///////////////////////////////////////////////////////////////////////////////////////////

		double q = 200.33;
		double***qnn = element_array[i].get_qnn();
		double**matrix_p2_n_sum_n = element_array[i].get_matrix_p2_n_sum_n();
		double* matrix_p_2 = element_array[i].get_matrix_p_2();
		double* final_matrix_p = element_array[i].get_final_matrix_p();

		for (int i = 0; i < 4; i++)
		{
			//cout << "pow: " << i << endl;
			for (int j = 0; j < 2; j++)
			{
				//cout << "pc: " << j << endl;
				for (int k = 0; k < 4; k++)
				{
					qnn[i][j][k] = n1n2n3n4[i][j][k] * q;
					//cout << ann[i][j][k] << " ";
				}
				//cout << endl;
			}
		}
		//matrix_n_sum_n[pow][n1..n4]
		//cout << endl << "matrix_n_sum_n[pow][N]" << endl;
		for (int i = 0; i < 4; i++)
		{
			//cout << "pow: " << i << endl;
			for (int j = 0; j < 4; j++)
			{
				matrix_p2_n_sum_n[i][j] = (qnn[i][0][j] + qnn[i][1][j])*jacobian_surface[i];
				//cout << "ann["<<i<<"][0]["<<j<<"]: "<< ann[i][0][j]<<" ann["<<i<<"][1]["<<j<<"]: "<< ann[i][1][j]<<" ";
				//cout << matrix_n_sum_n[i][j] << " ";
				//cout << qnn[i][0][j] << " ";
				//cout << ann[i][0][j] << " " << ann[i][1][j] << " ";
			}
			//cout << endl;
		}

		//matrix_p_1[pow]
		//cout << "matrix_p_2[pow]" << endl;

		for (int i = 0; i < 4; i++)
		{
			matrix_p_2[i] = (matrix_p2_n_sum_n[i][0] * boundary_conditions[i] + matrix_p2_n_sum_n[i][1] * boundary_conditions[i] + matrix_p2_n_sum_n[i][2] * boundary_conditions[i] + matrix_p2_n_sum_n[i][3] * boundary_conditions[i]);
			//cout << matrix_p_2[i] << " ";
		}
		//cout << "final_matrix_p" << endl;
		for (int i = 0; i < 4; i++)
		{
			final_matrix_p[i] = matrix_p_1[i] + matrix_p_2[i];
			//cout << final_matrix_p[i] << " ";
		}
	}
	return nullptr;
}

double** aggregation(Grid grid, int amount_of_elements)
{
	int size = sqrt(amount_of_elements);
	size *= 4;

	//cout << endl << "size: " << size << endl;
	double** global_matrix_h = grid.get_global_matrix_h();

	 global_matrix_h= new double*[size];
	for (int i = 0; i < size; i++)
	{
		global_matrix_h[i] = new double[size];
	}

	Element* element_array = grid.get_element_array();
	
	//elements
	for (int i = 0; i < amount_of_elements; i++)
	{
		Node*nodes=element_array[i].get_array_node();
		double** local_matrix_h = element_array[i].get_final_matrix_h_2d_bc();

		//each
		//cout <<endl<< "aggregation: " << endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				global_matrix_h[nodes[i].get_id()-1][nodes[j].get_id()-1] = local_matrix_h[i][j];
				//cout << global_matrix_h[nodes[i].get_id()-1][nodes[j].get_id()-1] << " ";
			}
			//cout << endl;
		}
	}
	return global_matrix_h;
}

double* aggregation_vector_p(Grid grid, int amount_of_elements)
{
	int size = sqrt(amount_of_elements);
	size *= 4;
	double* matrix_global_p = grid.get_global_matrix_p();
	matrix_global_p = new double[size];
	Element* element_array = grid.get_element_array();

	for (int i = 0; i < amount_of_elements; i++)
	{
		Node* node_array=element_array[i].get_array_node();
		double* local_matrix_p = element_array[i].get_final_matrix_p();

		cout <<endl<< "matrix_global_p: " << endl;
		for (int i = 0; i < 4; i++)
		{
			matrix_global_p[node_array[i].get_id()] = local_matrix_p[i];
		}
	}

	return nullptr;
}