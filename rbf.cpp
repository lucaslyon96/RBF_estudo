#include <iostream>
#include <cmath>
#include <math.h>

#define passo_aprendizagem 0.4 
#define Num_pont 10 //Número de pontos utilizados no treinamento
#define rad_base 0.5 //variância das funções radiais de base

using namespace std;

float rbf1(float (&entrada)[Num_pont][2], int cont);
float rbf2(float (&entrada)[Num_pont][2], int cont);
void out(float (&W)[3][3], float (&saida)[3], float (&var_rbf)[3]);
void error(float (&errvec)[3], float (&saida)[3], float (&d)[Num_pont][3], int cont);
void wUpdate(float (&W)[3][3], float (&errvec)[3], float (&var_rbf)[3]);

int main(){

	float entrada[Num_pont][2] = {{0.9,0.8},{0.2,1.3},{0.3,0.5},{0.2,1.5},{0.4,0.2},{0.4,1.2},{0.5,0.6},{0.7,1.0},{0.4,1.4},{0.7,1.2}};
	float d[Num_pont][3] = {{1,0,0},{0,1,0},{1,0,0},{0,0,1},{1,0,0},{0,1,0},{1,0,0},{0,1,0},{0,0,1},{0,0,1}};

	float W[3][3] = {{0.7,0.4,0.2},{0.9,0.3,0.8},{0.4,0.9,0.6}};

	float errvec[3] = {1,1,1};
	float var_rbf[3];
	float saida[3];

	var_rbf[0] = -1;

	int cont = 0;
	int epoch = 0;
		while(epoch < 1000000){
		cont = cont%Num_pont;

		var_rbf[1] = rbf1(entrada,cont);
		var_rbf[2] = rbf2(entrada,cont);

		out(W, saida, var_rbf);
		error(errvec, saida, d, cont);
		wUpdate(W,errvec,var_rbf);

		if (epoch % 100000 == 0)
		{
			for (int i = 0; i < 3; ++i)
			{
				cout << "Saida " << (i+1) << "= " << saida[i] << endl;
			}
			cout << endl;

			for (int i = 0; i < 3; ++i)
			{
				cout << "Erro " << (i+1) << "= " << errvec[i] << endl;
			}
			cout << endl;
			for (int i = 0; i < 3; ++i)
			{
				cout << "| " << W[i][0] << ", " << W[i][1] << ", " << W[i][2] << " |" << endl;
			}
			cout << endl << endl;
		}

		cont++;
		epoch++;
	}
	return 0;
}
float rbf1(float (&entrada)[Num_pont][2], int cont){ //função radial de base 1 - centros[0.3 0.5]
	float modulo;
	float cent1[2] = {0.3, 0.5};
	modulo = sqrt( pow(entrada[cont][0] - cent1[0],2) + pow(entrada[cont][1] - cent1[1],2));

	return exp((-1/(2*rad_base))*modulo);
}

float rbf2(float (&entrada)[Num_pont][2], int cont){ //função radial de base 1 - centros[0.7 1.2]
	float modulo;
	float cent1[2] = {0.7, 1.2};
	modulo = sqrt( pow(entrada[cont][0] - cent1[0],2) + pow(entrada[cont][1] - cent1[1],2));

	return exp((-1/(2*rad_base))*modulo);
}

void out(float (&W)[3][3], float (&saida)[3], float (&var_rbf)[3]){
	for (int i = 0; i < 3; ++i)
	{
		saida[i] = W[i][0]*var_rbf[0] + W[i][1]*var_rbf[1] + W[i][2]*var_rbf[2];
	}
}

void error(float (&errvec)[3], float (&saida)[3], float (&d)[Num_pont][3], int cont){
	for (int i = 0; i < 3; ++i)
	{
		errvec[i] = d[cont][i] - saida[i];
	}
}

void wUpdate(float (&W)[3][3], float (&errvec)[3], float (&var_rbf)[3]){
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			W[i][j] = W[i][j] + passo_aprendizagem*errvec[i]*var_rbf[j];
		}
	}
}
