#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

void PedirMatrixTransicion(int estados,int decisiones);
void PedirMatrizCostosMaximizar(int estados,int decisiones);
void PedirMatrizCostosMinimizar(int estados,int decisiones);
void ObtenerMatrizTransicion(int estados,int decisiones);
void ObtenerMatrizCostos(int estados,int decisiones);

int decisiones,estados;
int suma;
int i,j,k;
int N; // Numero maximo de iteraciones
int n;
long int numGrande = 9999999999;
long int numChico = -9999999999;
float matrizTransicion[100][100][100];
float matrizCostos[100][100];
float diferencia;
char Respuesta ;
char RespuestaCostos;

int main(){
		
	int numAlgoritmo;

	cout << "¿Desea Maximizar(+) o minimizar(-)?:";
	cin >> Respuesta;
	
	cout << "Ingrese la cantidad de estados:";
	cin >> estados;
	cout << "Ingresa la cantidad de decisiones:";
	cin >> decisiones;
	
	cout << " " << endl;

	
	PedirMatrixTransicion(estados,decisiones);
  

	if(Respuesta == '+'){
		PedirMatrizCostosMaximizar(estados,decisiones);
	}
	else if(Respuesta == '-' ){
		PedirMatrizCostosMinimizar(estados,decisiones);
	}
	
	ObtenerMatrizTransicion(estados,decisiones);
	cout << endl;
	ObtenerMatrizCostos(estados,decisiones);
	cout << endl;

	cout << "Elige alguno de los siguientes métodos:" << endl;
		

	do{	
		cout << "1. Enumeracion exhaustiva de politicas" << endl;
		cout << "2. Mejoramiento de politicas" << endl;
		cout << "3. Mejoramiento de politicas con descuento:" << endl;
		cout << "4. Aproximaciones sucesivas" << endl;
		cout << "Presione cualquier tecla para salir" << endl;
		cout << "Ingrese una opcion:";
		cin >> numAlgoritmo;
	
		if(numAlgoritmo == 1){
			cout << "Llama al programa Enumeracion exhaustiva de politicas" << endl;
			system("cls");	
		}	
		else if(numAlgoritmo == 2){
			cout << "Llama al programa Mejoramiento de politicas" << endl;
			system("cls");
		}
		else if(numAlgoritmo == 3){
			cout << "Llama al programa de Mejoramiento de politicas con descuento" << endl;
			system("cls");
		}
		else if(numAlgoritmo == 4){
			cout << "Llama al programa de Aproximaciones sucesivas" << endl;
			system("cls");
		}
		else{
			break;
			system("cls");
		}
	}while(numAlgoritmo == 1 || numAlgoritmo == 2 || numAlgoritmo == 3 || numAlgoritmo == 4);

return 0;
}



void PedirMatrixTransicion(int estados,int decisiones){


	cout << "Ingrese la matriz de transicion de estado a estado:" << endl; 
	
     for(k=0;k < decisiones;k++){
        for(i=0;i < estados;i++){
        	do{
              	suma=0;
                for(j=0;j < estados;j++){
                	cout << "Decision K = " << k+1 << " " << "[" << i+1 << "][" << j+1 << "]:";
                    cin >> matrizTransicion[i][j][k];
                    suma = suma + matrizTransicion[i][j][k];
                }
				if(suma!= 1 && suma !=0 && suma < 0.95){
					cout << "La suma por fila no es 1, ingresa tus datos de nuevo" << endl;
				}
            }while(suma!=1&&suma!=0&&suma<0.95);
        }
       system("cls");
   }
}

void PedirMatrizCostosMinimizar(int estados,int decisiones){

	cout << " " << endl;
	cout << "Ingrese la matriz de costos(Minimizar):" << endl;

		for(i = 0;i < estados;i++){
			for(j=0;j < decisiones;j++){
				cout << endl <<"Existe C[" << i << "][" << j+1 << "]?:" << endl;
				cout << "Si=s No=n:";
				cin >> RespuestaCostos;
				if(RespuestaCostos == 's' || RespuestaCostos == 'S'){
					cout << "Ingrese el costo:";
					cin >> matrizCostos[i][j];
				}
				else if(RespuestaCostos == 'n' || RespuestaCostos == 'N'){
					matrizCostos[i][j] = numGrande;
				}
			}
			system("cls");
		}		
}


void PedirMatrizCostosMaximizar(int estados,int decisiones){

	cout << " " << endl;
	cout << "Ingrese la matriz de costos(Maximizar):" << endl;

		for(i = 0;i < estados;i++){
			for(j=0;j < decisiones;j++){
				cout << endl <<"Existe C[" << i << "][" << j+1 << "]?:" << endl;
				cout << "Si=s No=n:";
				cin >> RespuestaCostos;
				if(RespuestaCostos == 's' || RespuestaCostos == 'S'){
					cout << "Ingrese el costo:";
					cin >> matrizCostos[i][j];
				}
				else if(RespuestaCostos == 'n' || RespuestaCostos == 'N'){
					matrizCostos[i][j] = numChico;
				}
			}
			system("cls");
		}			
}

void ObtenerMatrizTransicion(int estados,int decisiones){
	cout << "Matriz de transicion" << endl;
	for(k=0;k<decisiones;k++){
		cout << "Decision K = " << k+1 << endl;
		for(i=0;i<estados;i++){
			for(j=0;j<estados;j++){
				cout << matrizTransicion[i][j][k] << " ";
			}
			cout << endl;
		}
	}
}


void ObtenerMatrizCostos(int estados,int decisiones){
	cout << "Matriz de costos" << endl;
	for(i=0;i<estados;i++){
		for(k=0;k<decisiones;k++){
			cout << "C[" << i << "][" << k+1 << "]:" << matrizCostos[i][k] << endl;
		}
	}	
}


