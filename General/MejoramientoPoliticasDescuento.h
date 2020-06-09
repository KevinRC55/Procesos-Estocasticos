#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<math.h>


using namespace std;

void mejorPoliDiscMax(long double **C,float M[100][100][100],int Stat, int Desic){

	int i,j,k,Total;
	char opc;

		
	system("clear");
	cout<<"\n\t\t\tPROCESOS MARKOVIANOS DE DESICION";
	cout<<"\n\t\tMejoramiento de Politicas con Descuento";
	cout<<"\n\t\tMaximizacion";
	
	long int Pol[Stat];
	long int nPol[Stat];
	long int dec,ii,jj;
	double Vi[Stat];
	double alpha;

	//Elección de la política arbitraria
	cout<<"\n\n\tPolitica Arbitraria";
	for(i=0;i<=Stat-1;i++){
		do{
			cout<<"\n\tIngrese el elemento "<<i+1<<" del vector de la política arbitraria:";
			cin>>Pol[i];
			Pol[i]=Pol[i]-1;
		}while(Pol[i]<0 || Pol[i]>=Stat);
	}	
	
	system("clear");
	//Impresión de la política arbitraria
	cout<<"\n\tLa politica arbitraria es: (";
	for(i=0;i<=Stat-1;i++){
		if(i<=Stat-1){
			cout<<Pol[i]<<",";	
		}
		else{
			cout<<Pol[i];
		}
	}cout<<")";
	
	cout<<"\n\n\tIngrese el valor de alfa: ";cin>>alpha;
	
	int Final=0;
	
	//ITERACIÓN DE POLÍTICAS
	do{
		system("clear");
		//MATRIZ DE LA POLÍTICA
		cout<<"\n\n\tEl sistema de ecuaciones quedaría de la siguiente manera\n";
		
		k=0;
		for(i=0;i<=Stat-1;i++){
			cout<<"\n\tV"<<i+1<<" = "<<C[i][dec]<<" + "<<alpha<<" * (";
			for(j=0;j<=Stat-1;j++){
				dec = Pol[k];
				if(j<=Stat-2){
					cout<<M[i][j][dec]<<" + ";
				}
				else{
					cout<<M[i][j][dec];	
				}	
			}
			cout<<")\n";
			k+=1;
		}
		
		//MATRIZ DE COSTO PROMEDIO
		k=0;
		float GR[Stat][Stat];
		float B[Stat];
		
		for(i=0;i<=Stat-1;i++){
			GR[i][0]=1;
		}
		
		for(i=0;i<=Stat-1;i++){
			for(j=1;j<=Stat-1;j++){
				if(i==j-1){
					GR[i][j]=alpha*(1-M[i][j-1][Pol[k]]);
				}else{
					GR[i][j]=alpha*(-M[i][j-1][Pol[k]]);
				}
			}
			k+=1;
		}
		
		k=0;
		for(i=0;i<=Stat-1;i++){
			B[i]=C[Pol[k]][i];
			k+=1;
		}
		//system("pause");
		system("clear");
		
		cout<<"\n\n\tGauss-Jordan\n\n";
		cout<<"\n\nMatriz de Costos Promedio\n";
		for(i=0;i<=Stat-1;i++){
			for(j=0;j<=Stat-1;j++){
				cout<<alpha*(GR[i][j])<<"	";
			}
			cout<<B[i];
			cout<<"\n";
		}
		cout<<"\n\n";
		
		
		//GAUSS
		k=0;
		float piv;
		while(k<=Stat-1){
			for(i=k;i<=Stat-1;i++){
				for(j=k;j<=Stat-1;j++){
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
							if(j==Stat-1){
								B[i]=B[i]*piv;
							}		
						}else{
							GR[i][j]*=piv;
							if(j==Stat-1){
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
						if(j==Stat-1){
							B[i]=B[i]+(B[k]*piv);
						}
					}
				}
			}
			//IMPRESION
			for(ii=0;ii<=Stat-1;ii++){
				for(jj=0;jj<=Stat-1;jj++){
					cout<<GR[ii][jj]<<"	";
				}
				cout<<B[ii];
				cout<<"\n";
			}
			cout<<"\n\n";
			k+=1;
		}
		//JORDAN
		k=Stat-1;
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
			for(ii=0;ii<=Stat-1;ii++){
				for(jj=0;jj<=Stat-1;jj++){
					cout<<GR[ii][jj]<<"	";
				}
				cout<<B[ii];
				cout<<"\n";
			}
			cout<<"\n\n";
			k-=1;
		}
		//system("pause");
		system("clear");
		
		//MEJORAMIENTO DE LA POLÍTICA
		cout<<"\n\n\tMejoramiento de la politica\n\n";
		long int decs[Stat];
		double cost_p[Stat][Stat];
		
		for(i=0;i<=Stat-1;i++){
			decs[i]=0;
		}
		
		for(i=0;i<=Stat-1;i++){
			for(j=0;j<=Stat-1;j++){
				if(C[i][j]!=-1){
					decs[j]+=1;
				}
			}
		}
		for(i=0;i<=Stat-1;i++){
			for(j=0;j<=Stat-1;j++){
				cost_p[i][j]=0;
			}
		}
		
		//CÁLCULO DE COSTOS PROMEDIOs
		for(i=0;i<=Stat-1;i++){
			if(decs[i]==1){
				cout<<"Estado "<<i+1<<":\n\n";
				cout<<"\tDecision unica"<<"\n\n";
				nPol[i]=Pol[i];
			}else{
				cout<<"Estado "<<i+1<<":\n\n";
				for(ii=0;ii<=Stat-1;ii++){
					if(C[ii][i]!=-1){
						cost_p[ii][i]+=C[ii][i];
						for(j=0;j<=Stat-2;j++){
							cost_p[ii][i]+=M[i][j][ii]*B[j+1];
						}
						cost_p[ii][i]-=B[i+1];
						cout<<"\tDecision "<< ii+1<<"\t";
						cout<<cost_p[ii][i]<<"\n";
					}
				}
				cout<<"\n";
			}
		}
		int max=0;
		int min=10000;
		
		//DETERMINACIÓN DE NUEVA POLÍTICA
		
		for(i=0;i<=Stat-1;i++){
			max=0;
			for(j=0;j<=Stat-1;j++){
				if(cost_p[j][i]>max){
					nPol[i]=j;
					max=cost_p[j][i];
				}
			}
		}
		
		int ind=0;
		for(i=0;i<=Stat-1;i++){
			if(Pol[i]==nPol[i]){
				ind+=1;
			}
		}
		
		if(ind==Stat){//FIN
			cout<<"\n\n\tLA POLITICA ES OPTIMA\n\n";
			for(i=0;i<=Stat-1;i++){
				cout<<"Tomar la decision "<<nPol[i]+1<<" en el estado "<<i+1<<"\n";
			}
			Final=1;
		}else{//NUEVA POLÍTICA
			cout<<"\n\n\tLA POLITICA NO ES OPTIMA. NUEVA POLITICA:\n\n";
			for(i=0;i<=Stat-1;i++){
				cout<<"Tomar la decision "<<nPol[i]+1<<" en el estado "<<i+1<<"\n";
			}
			for(i=0;i<=Stat-1;i++){
				Pol[i]=nPol[i];
			}
		}
		//system("pause");
	}while(Final==0);
}

void mejorPoliDiscMin(long double **C,float M[100][100][100],int Stat, int Desic){
	
	int i,j,k,Total;
	char opc;

		
	system("clear");
	cout<<"\n\t\t\tPROCESOS MARKOVIANOS DE DESICION";
	cout<<"\n\t\tMejoramiento de Politicas con Descuento";
	cout<<"\n\t\tMinimzacion";
	
	//long int Pol[Stat];
	//long int nPol[Stat];
	long int dec,ii,jj;
	//double Vi[Stat];
	double alpha;
	
	long int Pol[100];
	long int nPol[100];
	double Vi[100];
	
	//Elección de la política arbitraria
	cout<<"\n\n\tPolitica Arbitraria";
	for(i=0;i<=Stat-1;i++){
		do{
			cout<<"\n\tIngrese el elemento "<<i+1<<" del vector de la politica arbitraria:";
			cin>>Pol[i];
			Pol[i]=Pol[i]-1;
		}while(Pol[i]<0 || Pol[i]>=Stat);
	}	
	
	system("clear");
	//Impresión de la política arbitraria
	cout<<"\n\tLa politica arbitraria es: (";
	for(i=0;i<=Stat-1;i++){
		if(i<=Stat-1){
			cout<<Pol[i]<<",";	
		}
		else{
			cout<<Pol[i];
		}
	}cout<<")";
	
	cout<<"\n\n\tIngrese el valor de alfa: ";cin>>alpha;
	
	int Final=0;
	
	//ITERACIÓN DE POLÍTICAS
	do{
		system("clear");
		//MATRIZ DE LA POLÍTICA
		cout<<"\n\n\tEl sistema de ecuaciones quedaria de la siguiente manera\n";
		
		k=0;
		for(i=0;i<=Stat-1;i++){
			cout<<"\n\tV"<<i+1<<" = "<<C[i][dec]<<" + "<<alpha<<" * (";
			for(j=0;j<=Stat-1;j++){
				dec = Pol[k];
				if(j<=Stat-2){
					cout<<M[i][j][dec]<<" + ";
				}
				else{
					cout<<M[i][j][dec];	
				}	
			}
			cout<<")\n";
			k+=1;
		}
		
		//MATRIZ DE COSTO PROMEDIO
		k=0;
		double GR[Stat][Stat];
		double B[Stat];
		
		for(i=0;i<=Stat-1;i++){
			GR[i][0]=1;
		}
		
		for(i=0;i<=Stat-1;i++){
			for(j=1;j<=Stat-1;j++){
				if(i==j-1){
					GR[i][j]=alpha*(1-M[i][j-1][Pol[k]]);
				}else{
					GR[i][j]=alpha*(-M[i][j-1][Pol[k]]);
				}
			}
			k+=1;
		}
		
		k=0;
		for(i=0;i<=Stat-1;i++){
			B[i]=C[Pol[k]][i];
			k+=1;
		}
		//system("pause");
		system("clear");
		
		cout<<"\n\n\tGauss-Jordan\n\n";
		cout<<"\n\nMatriz de Costos Promedio\n";
		for(i=0;i<=Stat-1;i++){
			for(j=0;j<=Stat-1;j++){
				cout<<alpha*(GR[i][j])<<"	";
			}
			cout<<B[i];
			cout<<"\n";
		}
		cout<<"\n\n";
		
		
		//GAUSS
		k=0;
		double piv;
		while(k<=Stat-1){
			for(i=k;i<=Stat-1;i++){
				for(j=k;j<=Stat-1;j++){
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
							if(j==Stat-1){
								B[i]=B[i]*piv;
							}		
						}else{
							GR[i][j]*=piv;
							if(j==Stat-1){
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
						if(j==Stat-1){
							B[i]=B[i]+(B[k]*piv);
						}
					}
				}
			}
			//IMPRESION
			for(ii=0;ii<=Stat-1;ii++){
				for(jj=0;jj<=Stat-1;jj++){
					cout<<GR[ii][jj]<<"	";
				}
				cout<<B[ii];
				cout<<"\n";
			}
			cout<<"\n\n";
			k+=1;
		}
		//JORDAN
		k=Stat-1;
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
			for(ii=0;ii<=Stat-1;ii++){
				for(jj=0;jj<=Stat-1;jj++){
					cout<<GR[ii][jj]<<"	";
				}
				cout<<B[ii];
				cout<<"\n";
			}
			cout<<"\n\n";
			k-=1;
		}
		//system("pause");
		system("clear");
		
		//MEJORAMIENTO DE LA POLÍTICA
		cout<<"\n\n\tMejoramiento de la politica\n\n";
		long int decs[Stat];
		double  cost_p[Stat][Stat];
		
		for(i=0;i<=Stat-1;i++){
			decs[i]=0;
		}
		
		for(i=0;i<=Stat-1;i++){
			for(j=0;j<=Stat-1;j++){
				if(C[i][j]!=-1){
					decs[j]+=1;
				}
			}
		}
		for(i=0;i<=Stat-1;i++){
			for(j=0;j<=Stat-1;j++){
				cost_p[i][j]=0;
			}
		}
		
		//CÁLCULO DE COSTOS PROMEDIOs
		for(i=0;i<=Stat-1;i++){
			if(decs[i]==1){
				cout<<"Estado "<<i+1<<":\n\n";
				cout<<"\tDecision unica"<<"\n\n";
				nPol[i]=Pol[i];
			}else{
				cout<<"Estado "<<i+1<<":\n\n";
				for(ii=0;ii<=Stat-1;ii++){
					if(C[ii][i]!=-1){
						cost_p[ii][i]+=C[ii][i];
						for(j=0;j<=Stat-2;j++){
							cost_p[ii][i]+=M[i][j][ii]*B[j+1];
						}
						cost_p[ii][i]-=B[i+1];
						cout<<"\tDecision "<< ii+1<<"\t";
						cout<<cost_p[ii][i]<<"\n";
					}
				}
				cout<<"\n";
			}
		}
		int max=0;
		int min=10000;
		
		//DETERMINACIÓN DE NUEVA POLÍTICA
		
		for(i=0;i<=Stat-1;i++){
			min=0;
			for(j=0;j<=Stat-1;j++){
				if(cost_p[j][i]<min){
					nPol[i]=j;
					min=cost_p[j][i];
				}
			}
		}
		
		int ind=0;
		for(i=0;i<=Stat-1;i++){
			if(Pol[i]==nPol[i]){
				ind+=1;
			}
		}
		
		if(ind==Stat){//FIN
			cout<<"\n\n\tLA POLITICA ES OPTIMA\n\n";
			for(i=0;i<=Stat-1;i++){
				cout<<"Tomar la decision "<<nPol[i]+1<<" en el estado "<<i+1<<"\n";
			}
			Final=1;
		}else{//NUEVA POLÍTICA
			cout<<"\n\n\tLA POLITICA NO ES OPTIMA. NUEVA POLITICA:\n\n";
			for(i=0;i<=Stat-1;i++){
				cout<<"Tomar la decision "<<nPol[i]+1<<" en el estado "<<i+1<<"\n";
			}
			for(i=0;i<=Stat-1;i++){
				Pol[i]=nPol[i];
			}
		}
		//system("pause");
	}while(Final==0);
}
	
