#include <iostream>
#include "AproximacionSucesiva.h"

using namespace std;

int main(){

	int i,j,k;
	int estados,decisiones;	
	char DecisionMaxMin;
	char Respuesta;
	double numChico = -9999999999;
	double numGrande = 9999999999;
	float matrizTransicion[100][100][100];	
	
	cout << "Maximizar(+) Minimizar(-):";
	cin >> DecisionMaxMin;
	
	cout << "Digite el numero de decisiones:";
   	cin  >> decisiones ;
	
	cout << "Digite el numero de estados:";
	cin >> estados;

	//Hacemos referencia a la matriz de transiciones
		cout << endl;
		//Se ingresa la matriz de transicion
		cout << "Ingresa la matriz de transicion" << endl;
		for(k=0;k < decisiones;k++){
			for(i=0;i<estados;i++){
				for(j=0;j<estados;j++){
					cout << "Decision K =  " << k+1 << " " << "P[" << i << "][" << j << "]:";
					cin >> matrizTransicion[i][j][k];
				}
			}
		cout << endl;
		}	
	

	// Hacemos referencia a la matriz de costos
	long int** matrizCostos = new long int*[estados];
	for(i=0;i<estados;i++){
		matrizCostos[i] = new long int[decisiones];
	}
	
	if(DecisionMaxMin == '-'){
		
		cout << "Se minimizara" << endl;
		cout << endl;
		//Se ingresa la matriz de costos
		cout << "Ingresa los costos:" << endl;
	
		for(i = 0;i<estados;i++){
			for(j=0;j < decisiones;j++){
				cout << endl <<"Existe C[" << i << "][" << j+1 << "]?:" << endl;
				cout << "Si=s No=n:";
				cin >> Respuesta;
				if(Respuesta == 's' || Respuesta == 'S'){
					cout << "Ingrese el costo:";
					cin >> matrizCostos[i][j];
				}
				else if(Respuesta == 'n' || Respuesta == 'N'){
					matrizCostos[i][j] = numGrande;
				}
			}
		}
		MinimizarAproximacionSucesiva(matrizTransicion,matrizCostos,estados,decisiones);
		cout << endl;
	}
	else if(DecisionMaxMin == '+'){
		cout << endl;
		cout << "Se maximizara" << endl;
		cout << endl;
		cout << "Ingresa los costos:" << endl;

		for(i = 0;i<estados;i++){
			for(j=0;j < decisiones;j++){
				cout << endl <<"Existe C[" << i+1 << "][" << j+1 << "]?:" << endl;
				cout << "Si=s No=n:";
				cin >> Respuesta;
				if(Respuesta == 's' || Respuesta == 'S'){
					cout << "Ingrese el costo:";
					cin >> matrizCostos[i][j];
				}
				else if(Respuesta == 'n' || Respuesta == 'N'){
					matrizCostos[i][j] = numChico;
				}
			}
		}
		MaximizarAproximacionSucesiva(matrizTransicion,matrizCostos,estados,decisiones);
		cout << endl;
	}



return 0;
}

