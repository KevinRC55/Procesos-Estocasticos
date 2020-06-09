#include<iostream>
#include<math.h>

using namespace std;

void MaximizarEnumeracionExhaustiva(float mt[100][100][100], long double **csts, int stds, int dcsns){
    int i,j,k,l,kk,cntdr,pp;

    pp = pow(dcsns,stds);
	int pltcs[pp][stds];
	
	i=0;
	j=0;
	//Politicas posibles
	switch(stds){
		case 2:
			for(int a=1;a<=dcsns;a++){
				for(int b=1;b<=dcsns;b++){
					j=0;
					pltcs[i][j]=a;
					j=j+1;
					pltcs[i][j]=b;
					i=i+1;
				}
			}
			break;
		case 3:
			for(int a=1;a<=dcsns;a++){
				for(int b=1;b<=dcsns;b++){
					for(int c=1;c<=dcsns;c++){
						j=0;
						pltcs[i][j]=a;
						j=j+1;
						pltcs[i][j]=b;
						j=j+1;
						pltcs[i][j]=c;
						i=i+1;
					}
				}
			}
			break;
		case 4:
			for(int a=1;a<=dcsns;a++){
				for(int b=1;b<=dcsns;b++){
					for(int c=1;c<=dcsns;c++){
						for(int d=1;d<=dcsns;d++){
							j=0;
							pltcs[i][j]=a;
							j=j+1;
							pltcs[i][j]=b;
							j=j+1;
							pltcs[i][j]=c;
							j=j+1;
							pltcs[i][j]=d;
							i=i+1;
						}
					}
				}
			}
			break;
		case 5:
			for(int a=1;a<=dcsns;a++){
				for(int b=1;b<=dcsns;b++){
					for(int c=1;c<=dcsns;c++){
						for(int d=1;d<=dcsns;d++){
							for(int e=1;e<=dcsns;e++){
								j=0;
								pltcs[i][j]=a;
								j=j+1;
								pltcs[i][j]=b;
								j=j+1;
								pltcs[i][j]=c;
								j=j+1;
								pltcs[i][j]=d;
								i=i+1;
							}
						}
					}
				}
			}
			break;
	}


	//Matriz de transicion de politica
	float aux[stds][stds][dcsns];
	cntdr = 0;

	float cap[pp];
	int pos=0;
	float mayor = -999999; 

	system("clear");
	for(k=0;k<=dcsns-1;k++){
		for(i=0;i<=stds-1;i++){
            for(j=0;j<=stds-1;j++){
                aux[i][j][k] = mt[i][j][k];
            }	
		}
	}

	for(kk=0;kk<=pp-1;kk++){

		for(k=0;k<=dcsns-1;k++){
			for(i=0;i<=stds-1;i++){
				for(j=0;j<=stds-1;j++){
					mt[i][j][k] = aux[i][j][k];
				}	
			}
		}

		cout<<"\n\n\n ||POLITICA R(";

		for(i=0;i<=stds-1;i++){
			cout<<pltcs[kk][i]<<",";
		}	

		cout<<") ||\n\n";

		cout<<"\n\t\t ||Matriz de transicion de politica||\n\n\t\t";
		for(i=0;i<=stds-1;i++){
			k = pltcs[kk][i]-1;
			cout<<"|";
			for(j=0;j<=stds-1;j++){
				cout<<mt[i][j][k]<<" ";
			}	
		cout<<"|\n\t\t";
		}

		cout<<"\n";
		
		//Sistema de ecuaciones-vector de distribucion estacionaria 
		float sstm[stds][stds];
		float v[stds];

		for(i=0;i<=stds-1;i++){
			for(j=0;j<=stds-1;j++){
				k = pltcs[kk][j]-1;
				mt[j][i][k] = (-1)*(mt[j][i][k]);
				if (i==j){
					mt[j][i][k] = 1 + mt[j][i][k];
				}
				if (i == stds-1){
					mt[j][i][k] = 1;
				}
				sstm[i][j] = mt[j][i][k];
			}	
		}

		/*cout<<"\n\t\t ||Sistema de ecuaciones||\n\n";
		for(i=0;i<=stds-1;i++){
			for(j=0;j<=stds-1;j++){
				cout<<sstm[i][j]<<" ";
			}	
		cout<<"\n";
		}*/

		for(i=0;i<=stds-1;i++){
			v[i] = 0;
			if (i == stds-1){
				v[i] = 1;
			}
		}	

		//Resolver sistema por GAUSS-JORDAN
		//GAUSS
		k=0;
		float piv;
		while(k<=stds-1){
			for(i=k;i<=stds-1;i++){
				for(j=k;j<=stds-1;j++){
					//FILA PIVOTE
					if(k==i){
						if(k==j){
							if(sstm[i][j]>0){
								if(sstm[i][j]==1){
									piv=1;
								}else{
								piv=1/(sstm[i][j]);
								}
							}else if(sstm[i][j]<0){
								if(sstm[i][j]==-1){
									piv=-1;
								}else{
								piv=1/(sstm[i][j]);
								}
							}
							sstm[i][j]=1;
							if(j==stds-1){
								v[i]=v[i]*piv;
							}		
						}else{
							sstm[i][j]*=piv;
							if(j==stds-1){
								v[i]=v[i]*piv;
							}
						}
					}
					//RESTAS
					if(k!=i){
						if(k==j){
							piv=-(sstm[i][j]);
						}
						sstm[i][j]=sstm[i][j]+(sstm[k][j]*piv);
						if(j==stds-1){
							v[i]=v[i]+(v[k]*piv);
						}
					}
				}
			}
			/*IMPRESION
			for(int ii=0;ii<=stds-1;ii++){
				for(int jj=0;jj<=stds-1;jj++){
					cout<<sstm[ii][jj]<<"	";
				}
				cout<<v[ii];
				cout<<"\n";
			}
			cout<<"\n\n";*/
			k+=1;
		}
		//JORDAN
		k=stds-1;
		while(k>=0){
			for(i=k;i>=0;i--){
				for(j=k;j>=0;j--){
					//FILA PIVOTE
					if(k==i){
						if(k==j){
							if(sstm[i][j]>0){
								if(sstm[i][j]==1){
									piv=1;
								}else{
								piv=1/(sstm[i][j]);
								}
							}else if(sstm[i][j]<0){
								if(sstm[i][j]==-1){
									piv=-1;
								}else{
								piv=1/(sstm[i][j]);
								}
							}
							sstm[i][j]=1;
							if(j==0){
								v[i]=v[i]*piv;
							}		
						}else{
							sstm[i][j]*=piv;
							if(j==0){
								v[i]=v[i]*piv;
							}
						}
					}
					//RESTAS
					if(k!=i){
						if(k==j){
							piv=-(sstm[i][j]);
						}
						sstm[i][j]=sstm[i][j]+(sstm[k][j]*piv);
						if(j==0){
							v[i]=v[i]+(v[k]*piv);
						}
					}
				}
			}
			/*IMPRESION
			for(int ii=0;ii<=stds-1;ii++){
				for(int jj=0;jj<=stds-1;jj++){
					cout<<sstm[ii][jj]<<"	";
				}
				cout<<v[ii];
				cout<<"\n";
			}
			cout<<"\n\n";*/
			k-=1;
		}

		cout<<"\n\t\t ||Vector de de distribucion estacionaria||\n\n";
		cout<<"\t\t(";
		for(i=0;i<=stds-1;i++){
			cout<<v[i]<<" ";
		}
		cout<<")";
		//Calculo de costo asociado E(c)
		float e=0;
		for(i=0;i<=stds-1;i++){
			j = pltcs[kk][i]-1;
			e+=csts[i][j]*v[i]; 
		}

		cout<<"\n\n\n\t\t ||Costo asociado a la politica||\n\n";
		cout<<"\t\tE(c) = "<<e;
		
		cap[kk] = e;

        if(cap[kk] > mayor){
            mayor = cap[kk];
            pos = kk; 
        }		
	}

	cout<<"\n\n";
	//system("pause");
	system("clear");
	
    cout<<"\n\n"<<"El costo asociado mayor es E(c)= "<<mayor;

	cout<<"\n\n\n\t\t ||Politica optima||\n\t\tP(";

	for(j=0;j<=stds-1;j++){
		cout<<pltcs[pos][j]<<",";
	}
	cout<<")";

	for(k=0;k<=dcsns-1;k++){
			for(i=0;i<=stds-1;i++){
				for(j=0;j<=stds-1;j++){
					mt[i][j][k] = aux[i][j][k];
				}	
			}
		}

	cout<<"\n\n";
	//system("pause");
}

void MinimizarEnumeracionExhaustiva(float mt[100][100][100], long double **csts, int stds,int dcsns){
    int i,j,k,l,kk,cntdr,pp;
    pp = pow(dcsns,stds);
	int pltcs[pp][stds];
	
	i=0;
	j=0;
	//Politicas posibles
	switch(stds){
		case 2:
			for(int a=1;a<=dcsns;a++){
				for(int b=1;b<=dcsns;b++){
					j=0;
					pltcs[i][j]=a;
					j=j+1;
					pltcs[i][j]=b;
					i=i+1;
				}
			}
			break;
		case 3:
			for(int a=1;a<=dcsns;a++){
				for(int b=1;b<=dcsns;b++){
					for(int c=1;c<=dcsns;c++){
						j=0;
						pltcs[i][j]=a;
						j=j+1;
						pltcs[i][j]=b;
						j=j+1;
						pltcs[i][j]=c;
						i=i+1;
					}
				}
			}
			break;
		case 4:
			for(int a=1;a<=dcsns;a++){
				for(int b=1;b<=dcsns;b++){
					for(int c=1;c<=dcsns;c++){
						for(int d=1;d<=dcsns;d++){
							j=0;
							pltcs[i][j]=a;
							j=j+1;
							pltcs[i][j]=b;
							j=j+1;
							pltcs[i][j]=c;
							j=j+1;
							pltcs[i][j]=d;
							i=i+1;
						}
					}
				}
			}
			break;
		case 5:
			for(int a=1;a<=dcsns;a++){
				for(int b=1;b<=dcsns;b++){
					for(int c=1;c<=dcsns;c++){
						for(int d=1;d<=dcsns;d++){
							for(int e=1;e<=dcsns;e++){
								j=0;
								pltcs[i][j]=a;
								j=j+1;
								pltcs[i][j]=b;
								j=j+1;
								pltcs[i][j]=c;
								j=j+1;
								pltcs[i][j]=d;
								i=i+1;
							}
						}
					}
				}
			}
			break;
	}


	//Matriz de transicion de politica
	float aux[stds][stds][dcsns];
	cntdr = 0;

	float cap[pp];
	int pos=0;
	float mayor = -999999;
	float menor = 999999; 

	system("clear");
	for(k=0;k<=dcsns-1;k++){
		for(i=0;i<=stds-1;i++){
            for(j=0;j<=stds-1;j++){
                aux[i][j][k] = mt[i][j][k];
            }	
		}
	}

	for(kk=0;kk<=pp-1;kk++){

		for(k=0;k<=dcsns-1;k++){
			for(i=0;i<=stds-1;i++){
				for(j=0;j<=stds-1;j++){
					mt[i][j][k] = aux[i][j][k];
				}	
			}
		}

		cout<<"\n\n\n ||POLITICA R(";

		for(i=0;i<=stds-1;i++){
			cout<<pltcs[kk][i]<<",";
		}	

		cout<<") ||\n\n";

		cout<<"\n\t\t ||Matriz de transicion de politica||\n\n\t\t";
		for(i=0;i<=stds-1;i++){
			k = pltcs[kk][i]-1;
			cout<<"|";
			for(j=0;j<=stds-1;j++){
				cout<<mt[i][j][k]<<" ";
			}	
		cout<<"|\n\t\t";
		}

		cout<<"\n";
		
		//Sistema de ecuaciones-vector de distribucion estacionaria 
		float sstm[stds][stds];
		float v[stds];

		for(i=0;i<=stds-1;i++){
			for(j=0;j<=stds-1;j++){
				k = pltcs[kk][j]-1;
				mt[j][i][k] = (-1)*(mt[j][i][k]);
				if (i==j){
					mt[j][i][k] = 1 + mt[j][i][k];
				}
				if (i == stds-1){
					mt[j][i][k] = 1;
				}
				sstm[i][j] = mt[j][i][k];
			}	
		}

		/*cout<<"\n\t\t ||Sistema de ecuaciones||\n\n";
		for(i=0;i<=stds-1;i++){
			for(j=0;j<=stds-1;j++){
				cout<<sstm[i][j]<<" ";
			}	
		cout<<"\n";
		}*/

		for(i=0;i<=stds-1;i++){
			v[i] = 0;
			if (i == stds-1){
				v[i] = 1;
			}
		}	

		//Resolver sistema por GAUSS-JORDAN
		//GAUSS
		k=0;
		float piv;
		while(k<=stds-1){
			for(i=k;i<=stds-1;i++){
				for(j=k;j<=stds-1;j++){
					//FILA PIVOTE
					if(k==i){
						if(k==j){
							if(sstm[i][j]>0){
								if(sstm[i][j]==1){
									piv=1;
								}else{
								piv=1/(sstm[i][j]);
								}
							}else if(sstm[i][j]<0){
								if(sstm[i][j]==-1){
									piv=-1;
								}else{
								piv=1/(sstm[i][j]);
								}
							}
							sstm[i][j]=1;
							if(j==stds-1){
								v[i]=v[i]*piv;
							}		
						}else{
							sstm[i][j]*=piv;
							if(j==stds-1){
								v[i]=v[i]*piv;
							}
						}
					}
					//RESTAS
					if(k!=i){
						if(k==j){
							piv=-(sstm[i][j]);
						}
						sstm[i][j]=sstm[i][j]+(sstm[k][j]*piv);
						if(j==stds-1){
							v[i]=v[i]+(v[k]*piv);
						}
					}
				}
			}
			/*IMPRESION
			for(int ii=0;ii<=stds-1;ii++){
				for(int jj=0;jj<=stds-1;jj++){
					cout<<sstm[ii][jj]<<"	";
				}
				cout<<v[ii];
				cout<<"\n";
			}
			cout<<"\n\n";*/
			k+=1;
		}
		//JORDAN
		k=stds-1;
		while(k>=0){
			for(i=k;i>=0;i--){
				for(j=k;j>=0;j--){
					//FILA PIVOTE
					if(k==i){
						if(k==j){
							if(sstm[i][j]>0){
								if(sstm[i][j]==1){
									piv=1;
								}else{
								piv=1/(sstm[i][j]);
								}
							}else if(sstm[i][j]<0){
								if(sstm[i][j]==-1){
									piv=-1;
								}else{
								piv=1/(sstm[i][j]);
								}
							}
							sstm[i][j]=1;
							if(j==0){
								v[i]=v[i]*piv;
							}		
						}else{
							sstm[i][j]*=piv;
							if(j==0){
								v[i]=v[i]*piv;
							}
						}
					}
					//RESTAS
					if(k!=i){
						if(k==j){
							piv=-(sstm[i][j]);
						}
						sstm[i][j]=sstm[i][j]+(sstm[k][j]*piv);
						if(j==0){
							v[i]=v[i]+(v[k]*piv);
						}
					}
				}
			}
			/*IMPRESION
			for(int ii=0;ii<=stds-1;ii++){
				for(int jj=0;jj<=stds-1;jj++){
					cout<<sstm[ii][jj]<<"	";
				}
				cout<<v[ii];
				cout<<"\n";
			}
			cout<<"\n\n";*/
			k-=1;
		}

		cout<<"\n\t\t ||Vector de de distribucion estacionaria||\n\n";
		cout<<"\t\t(";
		for(i=0;i<=stds-1;i++){
			cout<<v[i]<<" ";
		}
		cout<<")";
		//Calculo de costo asociado E(c)
		float e=0;
		for(i=0;i<=stds-1;i++){
			j = pltcs[kk][i]-1;
			e+=csts[i][j]*v[i]; 
		}

		cout<<"\n\n\n\t\t ||Costo asociado a la politica||\n\n";
		cout<<"\t\tE(c) = "<<e;
		
		cap[kk] = e;

        if(cap[kk] < menor){
            menor = cap[kk];
            pos = kk; 
        }
		
	}
	cout<<"\n\n";
	//system("pause");
	system("clear");
	
    cout<<"\n\n"<<"El costo asociado menor es E(c)= "<<menor;
	
	cout<<"\n\n\n\t\t ||Politica optima||\n\t\tP(";

	for(j=0;j<=stds-1;j++){
		cout<<pltcs[pos][j]<<",";
	}
	cout<<")";

	for(k=0;k<=dcsns-1;k++){
			for(i=0;i<=stds-1;i++){
				for(j=0;j<=stds-1;j++){
					mt[i][j][k] = aux[i][j][k];
				}	
			}
		}

	cout<<"\n\n";
	//system("pause");
}

