#include <iostream>

using namespace std;
	
	
void MinimizarAproximacionSucesiva(float matrizTransicion[100][100][100],long double matrizCostos[100][100],int estados,int decisiones){
	
	int i,j,k;
	int N; // Numero maximo de iteraciones
	int n;
	long int numeros[100];
	long int temp;
	long int politicaTemporal;
	double numGrande = 9999999999;
	float alfa;
	float epsilon;
	char Respuesta ;
	

	// i = estados
	// j = estados ya que j va de 0 hasta m y m son los estados   
	// k = decisiones
	cout << endl;
	cout << "Ingrese el numero maximo de iteraciones:";
	cin >> N;	

	cout << "Ingresa el valor de tu error:";
	cin >> epsilon;

	cout << "Ingresa el factor de descuento:";
	cin >> alfa;
	

 //limpiamos buffer con funcion cls

    // Mostramos el contenido de la matriz de transicion
	cout << endl << "Matrices de transicion:" << endl;
	for(k= 0;k < decisiones;k++){
		cout << "Decision K = " << " "  << k+1 << endl;
		for(i=0;i < estados;i++){
			for(j=0;j<estados;j++){
				cout << matrizTransicion[i][j][k] << " ";
			}
		   cout << endl;	
		}
	}


	
    cout << endl << "Matriz de costos:"<< endl;
	for(i=0;i<decisiones;i++){
			for(k=0;k<estados;k++){
				if(matrizCostos[i][k] < numGrande ){
					cout << "C[" << i+1 << "][" << k+1 << "]:" << matrizCostos[i][k] << endl;					
				}
		 	}
      }

	cout << endl;
	
// MINIMIZAR

	n = 0; 
	cout << "n = " << n+1 << endl;	
	// Calcular  V_{i}^{n} = min_{k} {C_{ik}}	 
	
	//Calculo de elementos más chicos por fila	

	long V[N][estados];
	
	for(i=0;i<N;i++){
		for(j=0;j<estados;j++){
			V[i][j] = 0;
		}
	}

	
	int P[estados];

	for(i=0;i<estados;i++){
		P[i] = 0;
	}	

	for(i=0;i<estados;i++){
			float Vminimo = matrizCostos[i][0];
			int  Pminimo = 0;

			for(k=0;k<decisiones;k++){
					if(matrizCostos[i][k] < Vminimo ){
							Vminimo = matrizCostos[i][k];
							Pminimo = k;
					//Sacar el valor de los k para obtener P
					}
				}
			V[0][i] = Vminimo;
			P[i] = Pminimo+1;
			Pminimo = 0;	
		}
	
	
	cout << "Minimizando" << endl; 
	cout << "Primera iteracion" << endl;
	cout << "Costos minimos: [";

	for(i=0;i< estados;i++){
		cout << V[0][i]  << ",";
	}

	cout << "]" << endl;
	
	cout << "Politica aproximada: [";

	for(i=0;i<estados;i++){
		cout << P[i] << ",";
	}
	cout << "]" << endl;
	cout << endl;
	// 
	float suma = 0;

	while(n < N-1){
		
		cout << "n = " << n+2 << endl;
		for(i=0;i<estados;i++){
			temp = numGrande;
			for(k=0;k<decisiones;k++){
					for(j=0;j< estados;j++){
						suma = suma +(matrizTransicion[i][j][k] * V[n][j]);
					}
				
				V[n+1][i] = matrizCostos[i][k] + alfa*suma;
				
				numeros[k] = V[n+1][i];
				
				
				if(temp > numeros[k]){
					temp = numeros[k];
					politicaTemporal = k+1;
				}		
				

				//cout << "V["<< n+1<< "][" << i << "]:"<<  V[n+1][i] << " " << "K=" << k+1 << " " << endl; 
				//crear un arreglo temporal al alamcene los minimos de V[n+1][i] con tamaño i
				suma = 0;	
			}
			// Aqui ya traeria el valor minimo de cada V[n+1][i]
			
			V[n+1][i] = temp;
			cout << "V["<< n+2<< "][" << i << "]:"<<  V[n+1][i]  << "\t" << "K = " << politicaTemporal<< endl;

			}
			n++;
			cout << endl;
		}

}


void MaximizarAproximacionSucesiva(float matrizTransicion[100][100][100],long double matrizCostos[100][100],int estados,int decisiones){
	
	int i,j,k;
	int N; // Numero maximo de iteraciones
	int n;
	long int numeros[100];
	long int temp;
	long int politicaTemporal;
	double numChico = -9999999999;
	float alfa;
	float epsilon;
	char Respuesta ;
	

	// i = estados
	// j = estados ya que j va de 0 hasta m y m son los estados   
	// k = decisiones
	
	cout << endl;
	cout << "Ingrese el numero maximo de iteraciones:";
	cin >> N;	

	cout << "Ingresa el valor de tu error:";
	cin >> epsilon;

	cout << "Ingresa el factor de descuento:";
	cin >> alfa;
	
 
// Se pedia matriz de costos
 
 //limpiamos buffer con funcion cls

    // Mostramos el contenido de la matriz de transicion
	cout << endl << "Matrices de transicion:" << endl;
	for(k= 0;k < decisiones;k++){
		cout << "Decision K = " << " "  << k+1 << endl;
		for(i=0;i < estados;i++){
			for(j=0;j<estados;j++){
				cout << matrizTransicion[i][j][k] << " ";
			}
		   cout << endl;	
		}
	}


    cout << endl << "Matriz de costos:"<< endl;
	for(i=0;i<decisiones;i++){
			for(k=0;k<estados;k++){
				if(matrizCostos[i][k] > numChico ){
					cout << "C[" << i+1 << "][" << k+1 << "]:" << matrizCostos[i][k] << endl;
					
				}
		 	}
      }

	cout << endl;
	
// MAXIMIZAR

	n = 0; 
	cout << "n = " << n+1 << endl;	
	// Calcular  V_{i}^{n} = min_{k} {C_{ik}}	 
	
	//Calculo de elementos más grandes por fila	

	long V[N][estados];
	
	for(i=0;i<N;i++){
		for(j=0;j<estados;j++){
			V[i][j] = 0;
		}
	}

	
	int P[estados];
	for(i=0;i<estados;i++){
		P[i] = 0;
	}
	
	for(i=0;i<estados;i++){
			float Vminimo = matrizCostos[i][0];
			int  Pminimo = 0;

			for(k=0;k<decisiones;k++){
					if(matrizCostos[i][k] > Vminimo ){
							Vminimo = matrizCostos[i][k];
							Pminimo = k;
					//Sacar el valor de los k para obtener P
					}
				}
			V[0][i] = Vminimo;
			P[i] = Pminimo+1;
			Pminimo = 0;	
		}
	
	
	cout << "Maximizando" << endl; 
	cout << "Primera iteracion" << endl;
	cout << "Costos minimos: [";

	for(i=0;i< estados;i++){
		cout << V[0][i]  << ",";
	}

	cout << "]" << endl;
	
	cout << "Politica aproximada: [";

	for(i=0;i<estados;i++){
		cout << P[i] << ",";
	}
	cout << "]" << endl;
	cout << endl;
	// 
	float suma = 0;

	while(n < N-1){
		
		cout << "n = " << n+2 << endl;
		for(i=0;i<estados;i++){
			temp = numChico;
			for(k=0;k<decisiones;k++){
					for(j=0;j< estados;j++){
						suma = suma +(matrizTransicion[i][j][k] * V[n][j]);
					}
				
				V[n+1][i] = matrizCostos[i][k] + alfa*suma;
				
				numeros[k] = V[n+1][i];
				
				
				if(temp < numeros[k]){
					temp = numeros[k];
					politicaTemporal = k+1;
				}		
				

				//cout << "V["<< n+1<< "][" << i << "]:"<<  V[n+1][i] << " " << "K=" << k+1 << " " << endl; 
				//crear un arreglo temporal al alamcene los minimos de V[n+1][i] con tamaño i
				suma = 0;	
			}
			// Aqui ya traeria el valor minimo de cada V[n+1][i]
			
			V[n+1][i] = temp;
			cout << "V["<< n+2<< "][" << i << "]:"<<  V[n+1][i]  << "\t" << "K = " << politicaTemporal<< endl;

			}
			n++;
			cout << endl;
		}

}

