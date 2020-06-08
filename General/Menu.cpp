#include <iostream>
#include <math.h>

#include "EnumeracionExhaustiva.h"
//#include "MejoramientoPoliticas.h"
#include "MejoramientoPoliticasDescuento.h"
#include "AproximacionSucesiva.h"

using namespace std;

int main(){

	int i,j,k;
	int estados,decisiones;	
	char DecisionMaxMin;
	char Respuesta;
	int Algoritmo;
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
		cout << endl;
		cout << "Procesos Markoviano de decisiones:" << endl;
	do{
		cout << "1. Enumeracion Exhaustiva de politicas" << endl;
		cout << "2. Mejoramiento de politicas" << endl;
		cout << "3. Mejoramiento de politicas con descuentos" << endl;
		cout << "4. Aproximaciones sucesivas" << endl;
		cout << "Para salir presione cualquier tecla" << endl;
		cout << endl;
		cout << "Seleccione una opcion:";
		cin >> Algoritmo;
	

			if(Algoritmo == 1){
				cout << endl;
				MinimizarEnumeracionExhaustiva(matrizTransicion,matrizCostos,estados,decisiones);
				cout << endl;
			}
			else if(Algoritmo == 2){
				cout << endl;
				//MinimizarMP(matrizTransicion,matrizCostos,estados,decisiones);		
				cout << endl;
			}
			else if(Algoritmo == 3){
				cout << endl;
				cout << "Minimizar Mejoramiento de politicas con descuento" << endl;
				cout << endl;
			}
			else if(Algoritmo == 4){
				MinimizarAproximacionSucesiva(matrizTransicion,matrizCostos,estados,decisiones);
				cout << endl;
			}
			else{
				break;
			}	

		}while(Algoritmo == 1 || Algoritmo==2 || Algoritmo == 3 || Algoritmo == 4);
		

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


		cout << endl;
		cout << "Procesos Markoviano de decisiones:" << endl;
		do{
			cout << "1. Enumeracion Exhaustiva de politicas" << endl;
			cout << "2. Mejoramiento de politicas" << endl;
			cout << "3. Mejoramiento de politicas con descuentos" << endl;
			cout << "4. Aproximaciones sucesivas" << endl;
			cout << "Para salir presione cualquier tecla" << endl;
			cout << endl;
			cout << "Seleccione una opcion:";
			cin >> Algoritmo;

				if(Algoritmo == 1){
					cout << endl;
					MaximizarEnumeracionExhaustiva(matrizTransicion,matrizCostos,estados,decisiones);
					cout << endl;
				}
				else if(Algoritmo == 2){
					cout << endl;
					//MaximizarMP(matrizTransicion,matrizCostos,estados,decisiones);
					cout << endl;
				}
				else if(Algoritmo == 3){
					cout << endl;
					cout << "Maximizar Mejoramiento de politicas con descuento" << endl;
					cout << endl;
				}
				else if(Algoritmo == 4){
					MaximizarAproximacionSucesiva(matrizTransicion,matrizCostos,estados,decisiones);
					cout << endl;
				}	

		}while(Algoritmo == 1 || Algoritmo==2 || Algoritmo == 3 || Algoritmo == 4);

	}

	
return 0;
}

