#include<iostream>
#include<wchar.h>
#include<locale.h>

using std::cout;
using std::cin;

int num_edos,num_dec;
int i,j,ii,jj,k,a,b,c,dec;
float suma;
char op;

void MaximizarMP(float Prob[10][10][10],float Costos[10][10],int num_edos,int num_dec){
//MATRICES
	system("cls");
	cout<<"\n\n\tMatrices de transición y Costos\n\n";
	for(k=0;k<=num_dec-1;k++){
		cout<<"Decisión "<<k+1<<"\n";
		for(i=0;i<=num_edos-1;i++){
			for(j=0;j<=num_edos-1;j++){
				cout<<Prob[i][j][k]<<"	";
			}
			cout<<"\n";
		}
		cout<<"\n\n";
	}
	//COSTOS
	cout<<"Costos"<<"\n";
	for(i=0;i<=num_dec-1;i++){
		for(j=0;j<=num_edos-1;j++){
			cout<<Costos[i][j]<<"	";
		}
		cout<<"\n";
	}
	system("pause");
	
	//--------------------------------------------
	//--------------------------------------------
	//INICIO DE PROGRAMA USANDO LAOS VALORES DADOS
	//--------------------------------------------
	//--------------------------------------------
	
	//Prob			Matriz de probabilidades por decisión
	//Costos 		Matriz de costos
	//num_edos		Número de estados
	//num_dec		Número de decisiones
	//op			Maximizar o minimizar	
	
	//POLITICA INICIAL
	system("cls");
	cout<<"\n\n\tPolítica Inicial\n\n";
	int Pol[num_edos];
	int nPol[num_edos];
	for(i=0;i<=num_edos-1;i++){
		do{
			cout<<"Decisión a tomar en el estado "<<i+1<<":	";
			cin>>Pol[i];
			Pol[i]=Pol[i]-1;
		}while(Pol[i]<0 || Pol[i]>=num_dec);
	}
	
	int Final=0;
	
	//ITERACIÓN DE POLÍTICAS
	do{
		system("cls");
		//MATRIZ DE LA POLÍTICA
		cout<<"\n\n\tMatriz de la política\n";
		k=0;
		for(i=0;i<=num_edos-1;i++){
			for(j=0;j<=num_edos-1;j++){
				dec=Pol[k];
				cout<<Prob[i][j][dec]<<"	";
			}
			cout<<"\n";
			k+=1;
		}
		
		//MATRIZ DE COSTO PROMEDIO
		k=0;
		float GR[num_edos][num_edos];
		float B[num_edos];
		for(i=0;i<=num_edos-1;i++){
			GR[i][0]=1;
		}
		for(i=0;i<=num_edos-1;i++){
			for(j=1;j<=num_edos-1;j++){
				if(i==j-1){
					GR[i][j]=1-Prob[i][j-1][Pol[k]];
				}else{
					GR[i][j]=-Prob[i][j-1][Pol[k]];
				}
			}
			k+=1;
		}
		
		k=0;
		for(i=0;i<=num_edos-1;i++){
			B[i]=Costos[Pol[k]][i];
			k+=1;
		}
		system("pause");
		system("cls");
		
		cout<<"\n\n\tGauss-Jordan\n\n";
		cout<<"\n\nMatriz de Costos Promedio\n";
		for(i=0;i<=num_edos-1;i++){
			for(j=0;j<=num_edos-1;j++){
				cout<<GR[i][j]<<"	";
			}
			cout<<B[i];
			cout<<"\n";
		}
		cout<<"\n\n";
		//GAUSS
		k=0;
		float piv;
		while(k<=num_edos-1){
			for(i=k;i<=num_edos-1;i++){
				for(j=k;j<=num_edos-1;j++){
					//FILA PIVOTE
					if(k==i){
						if(k==j){
							if(GR[i][j]>0){
								if(GR[i][j]==1){
									piv=1;
								}else{
								piv=1/(GR[i][j]);
								}
							}else if(GR[i][j]<0){
								if(GR[i][j]==-1){
									piv=-1;
								}else{
								piv=1/(GR[i][j]);
								}
							}
							GR[i][j]=1;
							if(j==num_edos-1){
								B[i]=B[i]*piv;
							}		
						}else{
							GR[i][j]*=piv;
							if(j==num_edos-1){
								B[i]=B[i]*piv;
							}
						}
					}
					//RESTAS
					if(k!=i){
						if(k==j){
							piv=-(GR[i][j]);
						}
						GR[i][j]=GR[i][j]+(GR[k][j]*piv);
						if(j==num_edos-1){
							B[i]=B[i]+(B[k]*piv);
						}
					}
				}
			}
			//IMPRESION
			for(ii=0;ii<=num_edos-1;ii++){
				for(jj=0;jj<=num_edos-1;jj++){
					cout<<GR[ii][jj]<<"	";
				}
				cout<<B[ii];
				cout<<"\n";
			}
			cout<<"\n\n";
			k+=1;
		}
		//JORDAN
		k=num_edos-1;
		while(k>=0){
			for(i=k;i>=0;i--){
				for(j=k;j>=0;j--){
					//FILA PIVOTE
					if(k==i){
						if(k==j){
							if(GR[i][j]>0){
								if(GR[i][j]==1){
									piv=1;
								}else{
								piv=1/(GR[i][j]);
								}
							}else if(GR[i][j]<0){
								if(GR[i][j]==-1){
									piv=-1;
								}else{
								piv=1/(GR[i][j]);
								}
							}
							GR[i][j]=1;
							if(j==0){
								B[i]=B[i]*piv;
							}		
						}else{
							GR[i][j]*=piv;
							if(j==0){
								B[i]=B[i]*piv;
							}
						}
					}
					//RESTAS
					if(k!=i){
						if(k==j){
							piv=-(GR[i][j]);
						}
						GR[i][j]=GR[i][j]+(GR[k][j]*piv);
						if(j==0){
							B[i]=B[i]+(B[k]*piv);
						}
					}
				}
			}
			//IMPRESION
			for(ii=0;ii<=num_edos-1;ii++){
				for(jj=0;jj<=num_edos-1;jj++){
					cout<<GR[ii][jj]<<"	";
				}
				cout<<B[ii];
				cout<<"\n";
			}
			cout<<"\n\n";
			k-=1;
		}
		system("pause");
		system("cls");
		
		//MEJORAMIENTO DE LA POLÍTICA
		cout<<"\n\n\tMejoramiento de la política\n\n";
		int decs[num_edos];
		float cost_p[num_dec][num_edos];
		for(i=0;i<=num_edos-1;i++){
			decs[i]=0;
		}
		for(i=0;i<=num_dec-1;i++){
			for(j=0;j<=num_edos-1;j++){
				if(Costos[i][j]!=-1 && Costos[i][j]<99999 && Costos[i][j]>-99999){
					decs[j]+=1;
				}
			}
		}
		for(i=0;i<=num_dec-1;i++){
			for(j=0;j<=num_edos-1;j++){
				cost_p[i][j]=0;
			}
		}
		
		//CÁLCULO DE COSTOS PROMEDIOs
		for(i=0;i<=num_edos-1;i++){
			if(decs[i]==1){
				cout<<"Estado "<<i+1<<":\n\n";
				cout<<"\tDecisión única"<<"\n\n";
				nPol[i]=Pol[i];
			}else{
				cout<<"Estado "<<i+1<<":\n\n";
				for(ii=0;ii<=num_dec-1;ii++){
					if(Costos[ii][i]!=-1 && Costos[ii][i]<99999 && Costos[ii][i]>-99999){
						cost_p[ii][i]+=Costos[ii][i];
						for(j=0;j<=num_edos-2;j++){
							cost_p[ii][i]+=Prob[i][j][ii]*B[j+1];
						}
						cost_p[ii][i]-=B[i+1];
						cout<<"\tDecisión "<< ii+1<<"\t";
						cout<<cost_p[ii][i]<<"\n";
					}
				}
				cout<<"\n";
			}
		}
		int max=0;
		
		//DETERMINACIÓN DE NUEVA POLÍTICA
		for(i=0;i<=num_edos-1;i++){
			max=0;
			for(j=0;j<=num_dec-1;j++){
				if(cost_p[j][i]>max){
					nPol[i]=j;
					max=cost_p[j][i];
				}
			}
		}
		int ind=0;
		for(i=0;i<=num_edos-1;i++){
			if(Pol[i]==nPol[i]){
				ind+=1;
			}
		}
		
		if(ind==num_edos){//FIN
			cout<<"\n\n\tLA POLÍTICA ES ÓPTIMA\n\n";
			for(i=0;i<=num_edos-1;i++){
				cout<<"Tomar la decisión "<<nPol[i]+1<<" en el estado "<<i+1<<"\n";
			}
			Final=1;
		}else{//NUEVA POLÍTICA
			cout<<"\n\n\tLA POLÍTICA NO ES ÓPTIMA. NUEVA POLÍTICA:\n\n";
			for(i=0;i<=num_edos-1;i++){
				cout<<"Tomar la decisión "<<nPol[i]+1<<" en el estado "<<i+1<<"\n";
			}
			for(i=0;i<=num_edos-1;i++){
				Pol[i]=nPol[i];
			}
		}
		system("pause");
	}while(Final==0);
}	

void MinimizarMP(float Prob[10][10][10], float Costos[10][10], int num_edos, int num_dec){
	//MATRICES
	system("cls");
	cout<<"\n\n\tMatrices de transición y Costos\n\n";
	for(k=0;k<=num_dec-1;k++){
		cout<<"Decisión "<<k+1<<"\n";
		for(i=0;i<=num_edos-1;i++){
			for(j=0;j<=num_edos-1;j++){
				cout<<Prob[i][j][k]<<"	";
			}
			cout<<"\n";
		}
		cout<<"\n\n";
	}
	//COSTOS
	cout<<"Costos"<<"\n";
	for(i=0;i<=num_dec-1;i++){
		for(j=0;j<=num_edos-1;j++){
			cout<<Costos[i][j]<<"	";
		}
		cout<<"\n";
	}
	system("pause");
	
	//--------------------------------------------
	//--------------------------------------------
	//INICIO DE PROGRAMA USANDO LAOS VALORES DADOS
	//--------------------------------------------
	//--------------------------------------------
	
	//Prob			Matriz de probabilidades por decisión
	//Costos 		Matriz de costos
	//num_edos		Número de estados
	//num_dec		Número de decisiones
	//op			Maximizar o minimizar	
	
	//POLITICA INICIAL
	system("cls");
	cout<<"\n\n\tPolítica Inicial\n\n";
	int Pol[num_edos];
	int nPol[num_edos];
	for(i=0;i<=num_edos-1;i++){
		do{
			cout<<"Decisión a tomar en el estado "<<i+1<<":	";
			cin>>Pol[i];
			Pol[i]=Pol[i]-1;
		}while(Pol[i]<0 || Pol[i]>=num_dec);
	}
	
	int Final=0;
	
	//ITERACIÓN DE POLÍTICAS
	do{
		system("cls");
		//MATRIZ DE LA POLÍTICA
		cout<<"\n\n\tMatriz de la política\n";
		k=0;
		for(i=0;i<=num_edos-1;i++){
			for(j=0;j<=num_edos-1;j++){
				dec=Pol[k];
				cout<<Prob[i][j][dec]<<"	";
			}
			cout<<"\n";
			k+=1;
		}
		
		//MATRIZ DE COSTO PROMEDIO
		k=0;
		float GR[num_edos][num_edos];
		float B[num_edos];
		for(i=0;i<=num_edos-1;i++){
			GR[i][0]=1;
		}
		for(i=0;i<=num_edos-1;i++){
			for(j=1;j<=num_edos-1;j++){
				if(i==j-1){
					GR[i][j]=1-Prob[i][j-1][Pol[k]];
				}else{
					GR[i][j]=-Prob[i][j-1][Pol[k]];
				}
			}
			k+=1;
		}
		
		k=0;
		for(i=0;i<=num_edos-1;i++){
			B[i]=Costos[Pol[k]][i];
			k+=1;
		}
		system("pause");
		system("cls");
		
		cout<<"\n\n\tGauss-Jordan\n\n";
		cout<<"\n\nMatriz de Costos Promedio\n";
		for(i=0;i<=num_edos-1;i++){
			for(j=0;j<=num_edos-1;j++){
				cout<<GR[i][j]<<"	";
			}
			cout<<B[i];
			cout<<"\n";
		}
		cout<<"\n\n";
		//GAUSS
		k=0;
		float piv;
		while(k<=num_edos-1){
			for(i=k;i<=num_edos-1;i++){
				for(j=k;j<=num_edos-1;j++){
					//FILA PIVOTE
					if(k==i){
						if(k==j){
							if(GR[i][j]>0){
								if(GR[i][j]==1){
									piv=1;
								}else{
								piv=1/(GR[i][j]);
								}
							}else if(GR[i][j]<0){
								if(GR[i][j]==-1){
									piv=-1;
								}else{
								piv=1/(GR[i][j]);
								}
							}
							GR[i][j]=1;
							if(j==num_edos-1){
								B[i]=B[i]*piv;
							}		
						}else{
							GR[i][j]*=piv;
							if(j==num_edos-1){
								B[i]=B[i]*piv;
							}
						}
					}
					//RESTAS
					if(k!=i){
						if(k==j){
							piv=-(GR[i][j]);
						}
						GR[i][j]=GR[i][j]+(GR[k][j]*piv);
						if(j==num_edos-1){
							B[i]=B[i]+(B[k]*piv);
						}
					}
				}
			}
			//IMPRESION
			for(ii=0;ii<=num_edos-1;ii++){
				for(jj=0;jj<=num_edos-1;jj++){
					cout<<GR[ii][jj]<<"	";
				}
				cout<<B[ii];
				cout<<"\n";
			}
			cout<<"\n\n";
			k+=1;
		}
		//JORDAN
		k=num_edos-1;
		while(k>=0){
			for(i=k;i>=0;i--){
				for(j=k;j>=0;j--){
					//FILA PIVOTE
					if(k==i){
						if(k==j){
							if(GR[i][j]>0){
								if(GR[i][j]==1){
									piv=1;
								}else{
								piv=1/(GR[i][j]);
								}
							}else if(GR[i][j]<0){
								if(GR[i][j]==-1){
									piv=-1;
								}else{
								piv=1/(GR[i][j]);
								}
							}
							GR[i][j]=1;
							if(j==0){
								B[i]=B[i]*piv;
							}		
						}else{
							GR[i][j]*=piv;
							if(j==0){
								B[i]=B[i]*piv;
							}
						}
					}
					//RESTAS
					if(k!=i){
						if(k==j){
							piv=-(GR[i][j]);
						}
						GR[i][j]=GR[i][j]+(GR[k][j]*piv);
						if(j==0){
							B[i]=B[i]+(B[k]*piv);
						}
					}
				}
			}
			//IMPRESION
			for(ii=0;ii<=num_edos-1;ii++){
				for(jj=0;jj<=num_edos-1;jj++){
					cout<<GR[ii][jj]<<"	";
				}
				cout<<B[ii];
				cout<<"\n";
			}
			cout<<"\n\n";
			k-=1;
		}
		system("pause");
		system("cls");
		
		//MEJORAMIENTO DE LA POLÍTICA
		cout<<"\n\n\tMejoramiento de la política\n\n";
		int decs[num_edos];
		float cost_p[num_dec][num_edos];
		for(i=0;i<=num_edos-1;i++){
			decs[i]=0;
		}
		for(i=0;i<=num_dec-1;i++){
			for(j=0;j<=num_edos-1;j++){
				if(Costos[i][j]!=-1 && Costos[i][j]<99999 && Costos[i][j]>-99999){
					decs[j]+=1;
				}
			}
		}
		for(i=0;i<=num_dec-1;i++){
			for(j=0;j<=num_edos-1;j++){
				cost_p[i][j]=0;
			}
		}
		
		//CÁLCULO DE COSTOS PROMEDIOs
		for(i=0;i<=num_edos-1;i++){
			if(decs[i]==1){
				cout<<"Estado "<<i+1<<":\n\n";
				cout<<"\tDecisión única"<<"\n\n";
				nPol[i]=Pol[i];
			}else{
				cout<<"Estado "<<i+1<<":\n\n";
				for(ii=0;ii<=num_dec-1;ii++){
					if(Costos[ii][i]!=-1 && Costos[ii][i]<99999 && Costos[ii][i]>-99999){
						cost_p[ii][i]+=Costos[ii][i];
						for(j=0;j<=num_edos-2;j++){
							cost_p[ii][i]+=Prob[i][j][ii]*B[j+1];
						}
						cost_p[ii][i]-=B[i+1];
						cout<<"\tDecisión "<< ii+1<<"\t";
						cout<<cost_p[ii][i]<<"\n";
					}
				}
				cout<<"\n";
			}
		}
		int min=10000;
		
		//DETERMINACIÓN DE NUEVA POLÍTICA
		for(i=0;i<=num_edos-1;i++){
			min=0;
			for(j=0;j<=num_dec-1;j++){
				if(cost_p[j][i]<min){
					nPol[i]=j;
					min=cost_p[j][i];
				}
			}
		}
		
		
		
		int ind=0;
		for(i=0;i<=num_edos-1;i++){
			if(Pol[i]==nPol[i]){
				ind+=1;
			}
		}
		
		if(ind==num_edos){//FIN
			cout<<"\n\n\tLA POLÍTICA ES ÓPTIMA\n\n";
			for(i=0;i<=num_edos-1;i++){
				cout<<"Tomar la decisión "<<nPol[i]+1<<" en el estado "<<i+1<<"\n";
			}
			Final=1;
		}else{//NUEVA POLÍTICA
			cout<<"\n\n\tLA POLÍTICA NO ES ÓPTIMA. NUEVA POLÍTICA:\n\n";
			for(i=0;i<=num_edos-1;i++){
				cout<<"Tomar la decisión "<<nPol[i]+1<<" en el estado "<<i+1<<"\n";
			}
			for(i=0;i<=num_edos-1;i++){
				Pol[i]=nPol[i];
			}
		}
		system("pause");
	}while(Final==0);
}

int main(){
	setlocale(LC_CTYPE,"Spanish");
	
	cout<<"\n";
	cout<<"\t\tMejoramiento de Políticas\n\n";

	do{
		cout<<"Maximizar(+) o Minimizar(-):		";
		cin>>op;
		if(op!='+' && op!='-'){
			cout<<"		Signo incorrecto.Intente nuevamente\n\n";
		}
    }while(op!='+' && op!='-');
    cout<<"\nCantidad de estados:			";
    cin>>num_edos;
    cout<<"\nCantidad de decisiones: 		";
    cin>>num_dec;
    float Prob[10][10][10];
    system("cls");
    
    //ASIGNACIÓN DE VALORES A MATRICES DE TRANSICIÓN
    for(k=0;k<=num_dec-1;k++){
    	cout<<"\n\n\tDecisión "<<k+1<<"\n\n";
    	cout<<"Probabilidades de estado a estado:\n";
		for(i=0;i<=num_edos-1;i++){
			do{
		   		suma=0;
		   		for(j=0;j<=num_edos-1;j++){
		   			cout<<i+1<<" a "<<j+1<<"	";
		   			cin>>Prob[i][j][k];
		   			suma=suma+Prob[i][j][k];
				}
				cout<<"\n";
				if(suma!=1&&suma!=0&&suma<0.95){
					cout<<"		Los valores no suman 1, ingrese los valores nuevamente\n\n";
				}
			}while(suma!=1&&suma!=0&&suma<0.95);	
		}
		system("cls");
	}
	
	//ASIGNACIÓN DE COSTOS
	
	system("cls");
	cout<<"\n\n\tCostos\n";
	cout<<"NOTA: Si la decisión no se toma, escribir -1\n\n";
	float Costos[10][10];
	for(i=0;i<=num_dec-1;i++){
		for(j=0;j<=num_edos-1;j++){
			cout<<"Ganancia de tomar la decisión "<<i+1<<" en el estado "<<j+1<<"	";
			cin>>Costos[i][j];
		}
	}
    
    if(op=='+'){
    	MaximizarMP(Prob,Costos,num_edos,num_dec);
	}else{
		MinimizarMP(Prob,Costos,num_edos,num_dec);
	}
}
