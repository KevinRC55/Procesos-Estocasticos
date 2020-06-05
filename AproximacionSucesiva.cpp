#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


void PedirDatosMatrizTransicion();


int main(){
	
	int decisiones,estados;
	int i,j,k;
	int N; // Numero maximo de iteraciones
	int n;
	long int numGrande = 9999999999;
	float matrizTransicion[100][100][100];
	float matrizCostos[100][100];
	float alfa;
	float epsilon;
	char Respuesta ;
	
	
	
	// i = estados
	// j = estados ya que j va de 0 hasta m y m son los estados   
	// k = decisiones
	cout << "Digite el numero de decisiones:";
   	cin  >> decisiones ;
	
	cout << "Digite el numero de estados:";
	cin >> estados;

	cout << "Ingrese el numero maximo de iteraciones:";
	cin >> N;	

	cout << "Ingresa el valor de tu error:";
	cin >> epsilon;

	cout << "Ingresa el factor de descuento:";
	cin >> alfa;
	

	 // Se ingresa la matriz de transicion
	cout << "Matriz de transicion" << endl;

	for(i=0;i < decisiones;i++){
		for(j=0;j<decisiones;j++){
			for(k=0;k<estados;k++){
			cout << "Decision K =  " << i+1 << " " << "P[" << j << "][" << k+1 << "]:";
			cin >> matrizTransicion[i][j][k];
			}
		}
	cout << endl;
	}



	cout << "Ingresa los costos:" << endl;
	cout << "Para cada estado ingresa su decision correspondiente:" << endl;
	

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
	

 //limpiamos buffer con funcion cls

    // Mostramos el contenido de la matriz de transicion
	cout << endl << "Matrices de transicion:" << endl;
	for(i= 0;i < decisiones;i++){
		cout << "Decision K = " << " "  << i+1 << endl;
		for(j=0;j < decisiones;j++){
			for(k=0;k<estados;k++){
				cout << matrizTransicion[i][j][k] << " ";
			}
		   cout << endl;	
		}
	}


	
    cout << endl << "Matriz de costos:"<< endl;
	for(i=0;i<estados;i++){
			for(k=0;k<decisiones;k++){
				if(matrizCostos[i][k] >= 0 ){
					cout << "C[" << i << "][" << k+1 << "]:" << matrizCostos[i][k] << endl;
					
				}
		 	}
      }
	
	cout << endl;
	
	n = 1; 
	
	// Calcular  V_{i}^{n} = min_{k} {C_{ik}}	 
	
	//Calculo de elementos más chicos por fila	

	float V[estados];
	int P[estados];
	
	for(i=0;i<estados;i++){
			float Vminimo = matrizCostos[i][0];
			int  Pminimo;

			for(k=0;k<decisiones;k++){
					if(matrizCostos[i][k] < Vminimo ){
							Vminimo = matrizCostos[i][k];
							Pminimo = k;
					//Sacar el valor de los k para obtener P
					}
				}
			V[i] = Vminimo;
			P[i] = Pminimo+1;

		}
	
	

	cout << "Primera iteracion" << endl;
	cout << "Costos minimos: [";

	for(i=0;i< estados;i++){
		cout << V[i]  << ",";
	}

	cout << "]" << endl;
	
	cout << "Politica aproximada: [";

	for(i=0;i<estados;i++){
		cout << P[i] << ",";
	}
	cout << "]" << endl;

	
	



return 0;	
}

