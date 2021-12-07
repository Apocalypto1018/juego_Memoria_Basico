//proyecto Memoria

//librerias
#include <stdio.h> //libria principal
#include <stdlib.h> //libreria para las funciones de system, rand()
#include <time.h> //libreria que sirve para tomar la hora del sistema para resetear la semilla srand()
#include <windows.h>  //libreria que sirve para usar la funcion sleep (dormir sistema)

//prototimos de las funciones
void generarLetras(int tam, char matriz[tam][tam]); 
void mostrarPosicion(int tam, char matriz[tam][tam], int posAcertadas[36]); 
void mostrar(int tam, char matriz[tam][tam]); 
void intercambioAleatorio(int tam, char matriz[tam][tam]);
int mostrarLetra(int tam,char matriz[tam][tam],int pos1,int pos2);
void coordenada(int*f,int*c, int pos, int tam);
void vaciar(int posAcertadas[36]);
int ocupado(int, int, int, int[36]);
int posValidas(int, int, int[36], int);

//funcion principal
int main(){
	srand(time(0)); //sereteando la semilla 
	
	//variables locales
	int posAcertadas[36]; //vector que almacena las posiciones acertadas
	int opc=0;   
	int salir=0; // var condicional 
	int jugar=0;  //var condicional
	int tam=0;  //controla el tamanio de la matriz y por lo tanto la dificultad del nivel elegido
	int pos1=0; 
	int pos2=0;
	int generar=0; //variable condicional sobre la previsualizacion
	int intentos=0;
	int intentosMaximos=0;
	int fin=0; //var condicional
	int aciertos=0;
	int pos=0;
	int correcto=0;


	do{  //ciclo que controla el uego total (si se queire cambiar de nivel o salir)
		//menu de eleccion de nivel
		printf("      BIENVENIDO A MEMORICHAR!!\n\n");
		printf("*Ingrese 1 para jugar en modo MUY FACIL (PRACTICA)\n\n");	
		printf("*Ingrese 2 para jugar en modo FACIL\n\n");	
		printf("*Ingrese 3 para jugar en modo NORMAL\n\n");
		printf("*Ingrese 4 para visualizar las intrucciones\n\n");
		printf("*Ingrese 0 para salir del juego\n\n->");
		scanf("%i", &opc);
		
		system("cls"); //limpiar pantalla
		
		switch(opc){ //estudio de casos de la opcion que eleigio el usuario
			
			case 0:{
				salir=1;
				break;
			}
			case 1:{
				tam=2;
				jugar=1;
				generar=1;
				intentos=0;
				intentosMaximos=2;
				fin=0;
				pos=0;
				aciertos=0;
				break;
			}
			case 2:{
				tam=4;
				jugar=1;
				generar=1;
				intentos=0;
				intentosMaximos=12;
				fin=0;
				pos=0;
				aciertos=0;
				break;
			}
			case 3:{
				tam=6;
				jugar=1;
				generar=1;
				intentos=0;
				intentosMaximos=26;
				fin=0;
				pos=0;
				aciertos=0;
				break;
			}
			case 4:{
				//instrucciones
				printf("*Debera elegir el nivel de dificultad en el menu principal\n\n");
				printf("*Se dispondra de 4 segundos para previzualizar la ubicacion de las letras\n\n");
				printf("*Pasado el tiempo, podra elegir 2 posiciones diferentes para intentar acertar el par\n\n");
				printf("*Se define si gano o no, en funcion de la cantidad de intentos para encontrar   todas las parejas.\n\n");
				printf("-Para el nivel muy facil tabla de critertio:\n2 intentos gana de manera Excelente\n3 intentos completado de manera Normal\n4 intentos completado de manera regular\nMas intentos completado de manera Mal\n\n");
				printf("-Para el nivel facil tabla de critertio:\n12 intentos gana de manera Excelente\n16 intentos completado de manera Normal\n18 intentos completado de manera regular\nMas intentos completado de manera Mal\n\n");
				printf("-Para el nivel normal tabla de critertio:\n26 intentos gana de manera Excelente\n30 intentos completado de manera Normal\n34 intentos completado de manera regular\nMas intentos completado de manera Mal\n\n");
				printf("*Podra elegir cambiar de modo o salir luego de realizar un intento...\n\n");
				system("pause");
				system("cls");
				break;
			}
			default:{
				printf("*Error!! Parametro ingresado no valido...Volviendo al menu principal.\n\n");
				
				system("pause");
				system("cls");
				break;
			}
			
		}
		
		char matriz[tam][tam]; //inicializacion de la matriz con la dificultad (tamanio) correspondiente al nivel elejido
		
		while(jugar==1){
			
			if(generar==1){
				
				generarLetras(tam, matriz); //invocacion de la funcion que general la matriz
				
				mostrar(tam, matriz); //mostrar
				printf("\nTiempo de previsualizacion: 4s\n");	
				Sleep(1000); //pausa por 1 segundos
				system("cls"); //borrar pantalla
				
				mostrar(tam, matriz);
				printf("\nTiempo de previsualizacion: 3s\n");
				Sleep(1000); //pausa por 1 segundos
				system("cls"); //borrar pantalla
							
				mostrar(tam, matriz);
				printf("\nTiempo de previsualizacion: 2s\n");
				Sleep(1000); //pausa por 1 segundos
				system("cls"); //borrar pantalla
				
				mostrar(tam, matriz);
				printf("\nTiempo de previsualizacion: 1s\n");
				Sleep(1000); //pausa por 1 segundos
				system("cls"); //borrar pantalla
				
				generar++;
				vaciar(posAcertadas);
				
			}
				
			do{
				printf("Cargando posiciones...\n");
				Sleep(1000);
				system("cls");
				mostrarPosicion(tam, matriz, posAcertadas); //se invoca la funcion que mostrara las posiciones
				//solicitud de las posiciones
				Sleep(100);
				
				printf("\n*Ingrese la primera posicion\n->");
				scanf("%i",&pos1);
				
				printf("\n*Ingrese la segunda posicion\n->");
				scanf("%i",&pos2);
				printf("\n\n");
			}while(posValidas(pos1, pos2, posAcertadas, pos)!=1); //ciclo que asegura que las opsiciones ingresadas no sean iguales a las ya acertadas
			
		    correcto=mostrarLetra(tam,matriz,pos1,pos2);
			intentos++;
			printf("/---------------------------------------/\n");
			
			if(correcto==1){
				printf("\n*Posiciones ingresadas: %i y %i\n", pos1, pos2);
				printf("\n*Has acertado!!\n\n");
				aciertos++;
				
				posAcertadas[pos]=pos1;
				pos++;
				posAcertadas[pos]=pos2;
				pos++;

				//Sistema de aciertos por nivel para saber cuando finaliza el uego
				if(tam==2 && aciertos==2){
					fin=1;
				}else if(tam==4 && aciertos==8){
					fin=1;
				}else if(tam==6 && aciertos==18){
					fin=1;
				}
			}else{
				printf("\n*Posiciones ingresadas: %i y %i\n", pos1, pos2);
				printf("\n*Lo siento. No has acertado!!\n\n");
			}
			printf("\n*Cantidad de intentos: %i de %i maximos para ganar este nivel\n", intentos, intentosMaximos);
			system("pause");
			system("cls");
			
			do{
				if(fin!=1){
					
					printf("*Ingrese 1 para CONTINUAR jugando\n\n");
					printf("*Ingrese 0 para SALIR  al menu principal\n\n->");
					fflush(stdin); //funcion que limpia el buffer
					scanf("%i", &jugar);
					
					system("cls");
				}
				
			}while(jugar<0 || jugar>1);	
			
			if(fin==1){ //si terminar el usuario de descubirir los pares...
				
				if(tam==2 ){ //validacion de tabla de criterio para nivel muy facil
					if(intentos<=2){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("*Felicidades Has ganado el nivel muy facil de forma Excelente!!.\n*Descubriste las parejas en %i Intentos\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}else if(intentos<=3){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("*Felicidades Has ganado el nivel muy facil de forma Normal!!.\n*Descubriste las parejas en %i Intentos\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}else if(intentos<=4){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("*Has completado el nivel muy facil de forma Regular!!.\n*Descubriste las parejas en %i Intentos\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}else if(intentos>4){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("Has completado el nivel muy facil de forma Mal!!.\n*Descubriste las parejas en %i Intentos\n*Te recomendamos practicar.\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}
						
				}else if(tam==4){ //validacion de tabla de criterio para nivel facil
					if(intentos<=12){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("*Felicidades Has ganado el nivel facil de forma Excelente!!.\n*Descubriste las parejas en %i Intentos\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}else if(intentos<=16){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("*Felicidades Has ganado el nivel facil de forma Normal!!.\n*Descubriste las parejas en %i Intentos\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}else if(intentos<=18){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("*Has completado el nivel facil de forma Regular!!.\n*Descubriste las parejas en %i Intentos\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}else if(intentos>18){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("Has completado el nivel facil de forma Mal!!.\n*Descubriste las parejas en %i Intentos\n*Te recomendamos practicar.\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}
				
					
				}else if(tam==6 ){ //validacion de tabla de criterio para nivel normal
					if(intentos<=26){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("*Felicidades Has ganado el nivel normal de forma Excelente!!.\n*Descubriste las parejas en %i Intentos\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}else if(intentos<=30){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("*Felicidades Has ganado el nivel normal de forma Normal!!.\n*Descubriste las parejas en %i Intentos\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}else if(intentos<=34){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("*Has completado el nivel normal de forma Regular!!.\n*Descubriste las parejas en %i Intentos\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}else if(intentos>34){
						system("cls");
						printf("/------------------------------------------------------------------------------/\n");
						printf("Has completado el nivel normal de forma Mal!!.\n*Descubriste las parejas en %i Intentos\n*Te recomendamos practicar.\n\n", intentos);
						printf("/------------------------------------------------------------------------------/\n");
						system("pause");
						system("cls");
						jugar=0;
					}
				}		
			}
		}
			
	}while(salir!=1);
	
	printf("/---------------------------------------/\n");
	printf("\n*SALIENDO... GRACIAS POR jUGAR MEMORICHAR\n*LA PRACTICA HACE AL MAESTRO!!\n\n");
	printf("/---------------------------------------/\n");
	system("pause");
	system("cls");
	
	return 0;
}

//funcion que llenara la matriz y la mostrara las letras al principio por 4 segundos al inicio
void generarLetras(int tam, char matriz[tam][tam]){
	char letra=' ';
	int correcto=0;
	int pos=0;
	
	int nroElemento = (tam*tam)/2; //esto seria n^2/2
	int numAleatorio[50];
	
	//lenamos el vector con pares de letras aleatorias
	while(nroElemento)
	{
		numAleatorio[nroElemento-1] = rand()%25+65;
		nroElemento--;
	}
	
	int k=0,cont;
	//asigncion del vector numAleatorio a la matriz
	for(int i=0;i<tam;i++)
	{
		for(int j=0;j<tam;j++)
		{
			matriz[i][j] = numAleatorio[k];
			cont++;
			if(cont % 2 == 0){k++;}
		}
	}
	
	intercambioAleatorio(tam, matriz); //invocamos la funcion que intercambiara aleatoriamentente las pareas generadas
	
}

//funcion que imprime la matriz en la consola
void mostrar(int tam, char matriz[tam][tam]){
	//recorrer la matriz e imprimir sus elementos
	for(int i=0;i<tam;i++){
		
		for(int j=0;j<tam;j++){
			//muestra el elemento en la posicion en que este durante el recorrido
			printf("[ %c ]\t", matriz[i][j]);
		}
		
		printf("\n\n");
	}
}

//intercambio de forma aleatoria los elementos
void intercambioAleatorio(int tam, char matriz[tam][tam])
{
	int tempI,tempJ,temp;
	//recorremos la matriz
	for (int i=0;i<tam;i++)
	{
		for(int j=0;j<tam;j++)
		{
			//asigna aleatoriamente valores de la matriz durante el recorrido
			tempI = rand() % tam;
			tempJ = rand() % tam;
			temp = matriz[i][j];
			matriz[i][j] = matriz[tempI][tempJ];
			matriz[tempI][tempJ] = temp;
		}
	}
}

// funcion que muestra las posiciones elegidas
int mostrarLetra(int tam,char matriz[tam][tam],int pos1,int pos2){
	int posicion=1;
	int coincidencia=0;
	int aux=0, aux2=0;
	int f1, c1, f2,	 c2; //almacenan las filas y las columnas de las posiciones en la matriz
	
	coordenada(&f1,&c1, pos1, tam); //invocacion de la funcion que convierte la posicion a coordenada de la primera posicion ingresada
	coordenada(&f2,&c2, pos2, tam);//invocacion de la funcion que convierte la posicion a coordenada de la primera posicion ingresada
	
	system("cls");
	
	for(int i=0;i<tam;i++){
		
		for(int j=0;j<tam;j++){
			
			if(i==f1 && j==c1){
				aux=matriz[i][j];
				printf("[ %c ]\t",matriz[i][j]);
				posicion++;	
			}else if(i==f2 && j==c2){
				aux2=matriz[i][j];
				printf("[ %c ]\t",matriz[i][j]);	
				posicion++;
			}else{
				printf("[ %i ]\t",posicion);	
				posicion++;
			}
				
		}
		
		printf("\n\n");
	}
	
	if(aux==aux2){
		return 1;
	}else{
		return 0;
	}
	
}

//funcion que imprime las posiciones de la matriz
void mostrarPosicion(int tam, char matriz[tam][tam], int posAcertadas[36]){
	//variables locales
	int posicion=1;
	int control=0;
	
	for(int i=0;i<tam;i++){
		
		for(int j=0;j<tam;j++){
			//recorre la matriz y muestra la variable posicion que se aumenta por cada iteracion, mostrando asi cada posicion
			control=ocupado(i, j, tam, posAcertadas); //invocacion de la funcion que valida si hubo coincidencia de una posicion acertada
			
			//de existir una posicion acertada, se muestra la letra
			if(control==1){
				printf("[ %c ]\t",matriz[i][j]);	
			}else{ //de no existir coincidencia, solo se muestra la posicion
				printf("[ %i ]\t", posicion);
			}
			
			posicion++;			
		}
		
		printf("\n\n");
	}
	
}

//funcion que valida si la posicion ya esta ocupada
int ocupado(int i, int j, int tam, int posAcertadas[36]){
	int f1, c1, f2,	 c2; //almacenan las filas y las columnas de las posiciones en la matriz
	int m=0;
	//se recorre la matriz
	for(int k=0;k<tam;k++){
		
		for(int l=0;l<tam;l++){
			//se llama a la funcion que retornara las coordenadas de las posiciones acertadas almacenadas en el vector de posiciones acertadas
			coordenada(&f1, &c1,posAcertadas[m],tam);
			
			//se valida si existe coincidencia entre las coordenadas de la matriz y las coordenadas de la posicion del vector durante la iteracion
			if(f1==i && c1==j && posAcertadas[m]!=0)
				return 1;
						
			m++;	
		}

	}
	
	return 0;
}

//vaciar array
void vaciar(int posAcertadas[36]){
	for(int i=0;i<36;i++){
		posAcertadas[i]=0;
	}
}

//funcion que determina si las posiciones ingresadas son validas
int posValidas(int pos1, int pos2, int posAcertadas[36], int pos){

	for(int i=0;i<pos;i++){
		if(pos1==posAcertadas[i]){
			system("cls");
			printf("*La posicion %i ya ha sido descubierta\n", pos1);
			system("pause");
			system("cls");
			return 0;
		}
		if(pos2==posAcertadas[i]){
			system("cls");
			printf("*La posicion %i ya ha sido descubierta\n", pos2);
			system("pause");
			system("cls");
			return 0;
		}
	}
	
	return 1;
}

//funcion que cambiara la posicion ingresada por el usuario a coordenada
void coordenada(int *f,int *c, int pos, int tam){
	//sistemas de condicional anidados para validar que coordenada corresponde de acuerdo a la posicion ingresada
	if(tam==2){ 
		
		if(pos==1){
			*f=0; *c=0;
		}
			
		else if(pos==2){
			*f=0; *c=1;	
		}
			
		else if(pos==3){
			*f=1; *c=0;
		}
		else if(pos==4){
			*f=1; *c=1;
		}
	}
	
	else if(tam==4){
		
		if(pos==1){
			*f=0; *c=0;
		}
			
		else if(pos==2){
			*f=0; *c=1;	
		}
			
		else if(pos==3){
			*f=0; *c=2;
		}
		else if(pos==4){
			*f=0; *c=3;
		}
		else if(pos==5){
			*f=1; *c=0;
		}
			
		else if(pos==6){
			*f=1; *c=1;	
		}
			
		else if(pos==7){
			*f=1; *c=2;
		}
		else if(pos==8){
			*f=1; *c=3;
		}
		else if(pos==9){
			*f=2; *c=0;
		}
			
		else if(pos==10){
			*f=2; *c=1;	
		}
			
		else if(pos==11){
			*f=2; *c=2;
		}
		else if(pos==12){
			*f=2; *c=3;
		}
		else if(pos==13){
			*f=3; *c=0;
		}
			
		else if(pos==14){
			*f=3; *c=1;	
		}
			
		else if(pos==15){
			*f=3; *c=2;
		}
		else if(pos==16){
			*f=3; *c=3;
		}
	}
	
	else if(tam==6){
		
		if(pos==1){
			*f=0; *c=0;
		}
			
		else if(pos==2){
			*f=0; *c=1;	
		}
			
		else if(pos==3){
			*f=0; *c=2;
		}
		else if(pos==4){
			*f=0; *c=3;
		}
		else if(pos==5){
			*f=0; *c=4;
		}
			
		else if(pos==6){
			*f=0; *c=5;	
		}
		
		else if(pos==7){
			*f=1; *c=0;
		}
			
		else if(pos==8){
			*f=1; *c=1;	
		}
			
		else if(pos==9){
			*f=1; *c=2;
		}
		else if(pos==10){
			*f=1; *c=3;
		}
		else if(pos==11){
			*f=1; *c=4;
		}
			
		else if(pos==12){
			*f=1; *c=5;	
		}
		else if(pos==13){
			*f=2; *c=0;
		}
			
		else if(pos==14){
			*f=2; *c=1;	
		}
			
		else if(pos==15){
			*f=2; *c=2;
		}
		else if(pos==16){
			*f=2; *c=3;
		}
		else if(pos==17){
			*f=2; *c=4;
		}
			
		else if(pos==18){
			*f=2; *c=5;	
		}
		
		else if(pos==19){
			*f=3; *c=0;
		}
			
		else if(pos==20){
			*f=3; *c=1;	
		}
			
		else if(pos==21){
			*f=3; *c=2;
		}
		else if(pos==22){
			*f=3; *c=3;
		}
		else if(pos==23){
			*f=3; *c=4;
		}
			
		else if(pos==24){
			*f=3; *c=5;	
		}
		
		
		else if(pos==25){
			*f=4; *c=0;
		}
			
		else if(pos==26){
			*f=4; *c=1;	
		}
			
		else if(pos==27){
			*f=4; *c=2;
		}
		else if(pos==28){
			*f=4; *c=3;
		}
		else if(pos==29){
			*f=4; *c=4;
		}
			
		else if(pos==30){
			*f=4; *c=5;	
		}
		
		
		else if(pos==31){
			*f=5; *c=0;
		}
			
		else if(pos==32){
			*f=5; *c=1;	
		}
			
		else if(pos==33){
			*f=5; *c=2;
		}
		else if(pos==34){
			*f=5; *c=3;
		}
		else if(pos==35){
			*f=5; *c=4;
		}
			
		else if(pos==36){
			*f=5; *c=5;	
		}	
		
	}
	
}
