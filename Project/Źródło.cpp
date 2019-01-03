#include<iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream> 
#include "Grid.h"
using namespace std;

double** jacobian2d(Grid grid,int amount_of_elements);

int main()
{
	string linia;
	fstream plik;
	int length;
	int heigth;
	double v[16][16];
	int tmp;

	plik.open("plik.txt", ios::in);
	if (plik.good() == true)
	{
		getline(plik, linia);
		length = stoi(linia);
		tmp = length * 2;

		for (int i = 0; i < tmp; i++)
		{
			getline(plik, linia);


			v[0][i] = stod(linia);
		}
			/*length = stoi(linia);
			getline(plik, linia);
			heigth = stoi(linia);*/
		plik.close();
	}

	for (int i = 0; i <tmp; i++)
	{
		//cout << v[0][i] << endl;
	}

	Grid grid(length-2,length-2);

	Element* elements = grid.get_element_array();
	Node* nodes = elements[0].get_array_node();
	for (int i = 0,j=0; j < length; i++,j++)
	{
		nodes[j].set_x(v[0][i]);
		i += 1;
		nodes[j].set_y(v[0][i]);
		//cout << "node_id " << nodes[j].get_id() << endl;
		//cout << "node_id " << nodes[j].get_x()<<" "<< nodes[j].get_y() << endl;
	}



	for (int i = 0; i < 1; i++)
	{
		//cout << "element_id " << elements[i].get_id() << endl;
		//cout << "element_nodes " << endl;
		Node* node_from_element = elements[i].get_array_node();
		//cout << node_from_element[0].get_id() << " " << node_from_element[1].get_id() << " " << node_from_element[2].get_id() << " " << node_from_element[3].get_id() << endl;

	}
	cout << "Matrix H" << endl;
	double** matrix=jacobian2d(grid,1);

	for (int i = 0; i < 4; i++)
	{
		cout << "matrix h ";
		for (int j = 0; j < 4; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}


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
