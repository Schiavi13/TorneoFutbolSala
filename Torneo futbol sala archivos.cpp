#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

//Funciones prototipo
void menuPrincipal(void);
void menuSecundario(void);
void inicializarTorneo(void);
void ordenarJugadores(void);
void llenarGoleadores(void);
int buscarGoleador(string);
void ordenarGoleadores(void);
void definirEquipo(void);
void calcularPuntos(void);
void ordenarPosiciones(void);
void fixEmpate(void);
bool buscarID(string);
void modificarInformacionEquipo(void);
void modificarInformacionJugadores(void);
void mostrarEquipos(void);
void mostrarJugadores(void);
void mostrarJugadoresGol(void);
void mostrarPosiciones(void);
void mostrarGoleadores(void);
void llenarArchivoEquipos(FILE*);
void leerArchivoEquipos(FILE*);


//estructuras
struct jugador
{
	char nombre[16];
	char id[11];
	int edad;
	int goles;
	int amarillas;
	int rojas;
};

struct equipo
{
	char nombre[16];
	char dt[16];
	struct jugador jugadores[9];
	int jugados;
	int ganados;
	int perdidos;
	int empatados;
	int puntos;
	int goles;
	int amarillas;
	int rojas;	
};

struct torneo
{
	struct equipo equipos[3];
	struct jugador goleadores[27];
}torneo1;

FILE *arcTorneo;


int main()
{
	int opc=-1, opc2=-1;
	
	if ((arcTorneo = fopen("Torneo.txt","r+"))==NULL){       //Verifica  si existe el archivo del torneo, si es asi se conecta
	   inicializarTorneo();
	   calcularPuntos();
       printf("Archivo no existe, Se creará  en la dirección por defecto \n");
       arcTorneo  = fopen("Torneo.txt","w+");
       fclose(arcTorneo);
       llenarArchivoEquipos(arcTorneo);              //se crea el archivo     
       fclose(arcTorneo);
      }
    else
    leerArchivoEquipos(arcTorneo);
    
    
   
    
	 
      
	
	do{
		
		system("cls");
		menuPrincipal();
		scanf("%d",&opc);
		fflush(stdin);
		switch(opc){
			case 1:
						system("cls");
						menuSecundario();
						scanf("%d",&opc2);
						fflush(stdin);
						switch(opc2){
							case 1:
									system("cls");
									definirEquipo();
									calcularPuntos();
									llenarGoleadores();	
									ordenarGoleadores();
									ordenarPosiciones();
									fixEmpate();
									llenarGoleadores();
									arcTorneo=fopen("Torneo.txt","w+");
									fclose(arcTorneo);
									llenarArchivoEquipos(arcTorneo);
									break;
							case 2:
									system("cls");
									modificarInformacionEquipo();
									calcularPuntos();
									ordenarPosiciones();
									fixEmpate();
									arcTorneo=fopen("Torneo.txt","w+");
									fclose(arcTorneo);
									llenarArchivoEquipos(arcTorneo);		
									break;
							case 3:
									break;
						
							default:
									printf("Por favor ingrese una de las opciones disponibles en el menú.");
									system("pause");
									break;
						}
					
					break;
			case 2:
					system("cls");
					modificarInformacionJugadores();
					ordenarJugadores();
					ordenarGoleadores();
					fixEmpate();
					arcTorneo=fopen("Torneo.txt","w+");
					fclose(arcTorneo);
					llenarArchivoEquipos(arcTorneo);
					break;
			case 3:
					system("cls");
					mostrarEquipos();
					system("pause");
					break;
			case 4:
					system("cls");
					mostrarJugadores();
					system("pause");
					break;
			case 5:
					system("cls");
					mostrarJugadoresGol();
					system("pause");
					break;
			case 6:
					system("cls");
					mostrarPosiciones();
					system("pause");
					break;
			case 7:
					system("cls");
					mostrarGoleadores();
					system("pause");
					break;												
			case 8:
					break;
			default:
					printf("Por favor Ingrese una de las opciones disponibles en el menú.");
					system("pause"); 
					break;
		}
	}while(opc!=8);
	
	
	return 0;
	
}


void menuPrincipal()
{
	printf("\t\t\tT O R N E O    C H O R I S A L A\n\n\n");
	printf("1. Definir o modificar la información de un equipo.\n");
	printf("2. Modificar la información de los jugadores de un equipo.\n");
	printf("3. Mostrar información de los equipos (nombre y puntuación).\n");
	printf("4. Mostrar listado de jugadores de un equipo.\n");
	printf("5. Mostrar listado de jugadores ordenado por número de goles anotados.\n");
	printf("6. Mostrar tabla de posiciones.\n");
	printf("7. Mostrar tabla de goleadores.\n");
	printf("8. Salir.\n\n");
	printf("Ingrese la opción que desea -> ");
}

void menuSecundario()
{
	printf("1. Definir la información de un equipo.\n");
	printf("2. Modificar la información de un equipo.\n");
	printf("3. Atrás.\n\n");
	printf("Ingrese la opción que desea -> ");
}
//Función que inicializa los datos predeterminados del torneo
void inicializarTorneo()
{
	char aux[3]="no";
	//char aux2="no";
	for(int i=0;i<3;i++)
	{
		strcpy(torneo1.equipos[i].nombre,aux);	
		strcpy(torneo1.equipos[i].dt,aux);	
		torneo1.equipos[i].jugados=0;	
		torneo1.equipos[i].ganados=0;	
		torneo1.equipos[i].perdidos=0;
		torneo1.equipos[i].empatados=0;
		torneo1.equipos[i].puntos=0;
		torneo1.equipos[i].goles=0;
		torneo1.equipos[i].amarillas=0;
		torneo1.equipos[i].rojas=0;	
		for(int j=0;j<9;j++)
		{
			strcpy(torneo1.equipos[i].jugadores[j].nombre,aux);
			strcpy(torneo1.equipos[i].jugadores[j].id,aux);
			torneo1.equipos[i].jugadores[j].edad=0;
			torneo1.equipos[i].jugadores[j].goles=0;
			torneo1.equipos[i].jugadores[j].amarillas=0;
			torneo1.equipos[i].jugadores[j].rojas=0;
			strcpy(torneo1.goleadores[j+(i*9)].nombre,aux);
			strcpy(torneo1.goleadores[j+(i*9)].id,aux);
			torneo1.goleadores[j+(i*9)].goles=0;
		}
	}
}

//Función que ordenalos jugadores d eun equipo según los goles, implementando el algoritmo insertionsort
void ordenarJugadores()    
{
	for(int k=0;k<3;k++)
	{	
		for(int j=1;j<9;j++)
		{
			int clave=torneo1.equipos[k].jugadores[j].goles, i=j-1;	
			struct jugador aux=torneo1.equipos[k].jugadores[j];
			
			while(i>=0 && torneo1.equipos[k].jugadores[i].goles<clave)		//cambio para ordenarlos inversamente	que el anterior sea menor
			{                               
				torneo1.equipos[k].jugadores[i+1]=torneo1.equipos[k].jugadores[i];	 
								
				i=i-1;			
			}
			torneo1.equipos[k].jugadores[i+1]=aux;				
		}
	}
}


//Función que llena la tabla de goleadores
void llenarGoleadores()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<9;j++)
		{
			torneo1.goleadores[j+(i*9)]=torneo1.equipos[i].jugadores[j];
		}
	}
}

//Función que modifica los valores de la tabla de goleadores
int buscarGoleador(char * ident)
{
	for(int i=0;i<27;i++)
	{
		if(strcmp(torneo1.goleadores[i].id,ident)==0)
			return i;
	}
}

//Función que ordena la tabla de goleadores implementando el algoritmo insertionsort
void ordenarGoleadores()    
{
	for(int j=1;j<27;j++)
	{
		int clave=torneo1.goleadores[j].goles, i=j-1;	
		struct jugador aux=torneo1.goleadores[j];
		
		while(i>=0 && torneo1.goleadores[i].goles<clave)		//cambio para ordenarlos inversamente	que el anterior sea menor
		{                               
			torneo1.goleadores[i+1]=torneo1.goleadores[i];	 
							
			i=i-1;			
		}
		torneo1.goleadores[i+1]=aux;				
	}
}

//Función para verificar que un jugador no esté en más de un equipo
bool buscarID(char * identificacion)
{
	bool bandera=false;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(strcmp(torneo1.equipos[i].jugadores[j].id,identificacion)==0)
			return true;
		}
	}
	return false;
}


//Función para que permite definir todos los datos de un equipo por parte del usuario
void definirEquipo()
{
	
	int i;
	char aux[3]="no";
	int aux2=0;
	
	printf("¿ Qué equipo desea definir ?\n");
	if(strcmp(torneo1.equipos[0].nombre,aux)==0)
	{
		printf("1)....................\n");
	}
	else
	{
		printf("1) %s\n",torneo1.equipos[0].nombre);
	}
	if(strcmp(torneo1.equipos[1].nombre,aux)==0)
	{
		printf("2)....................\n");
	}
	else
	{
		printf("2) %s\n",torneo1.equipos[1].nombre);
	}
	if(strcmp(torneo1.equipos[2].nombre,aux)==0)
	{
		printf("3)....................\n");
	}
	else
	{
		printf("3) %s\n",torneo1.equipos[2].nombre);
	}
	printf("4) Atrás.\n");
	printf("Ingrese el número del equipo que desea definir ->");
	scanf("%d",&i);
	
	if(i==4)
		return;
	
	fflush(stdin);
	printf("\nNombre del equipo ->");
	gets(torneo1.equipos[i-1].nombre);
	fflush(stdin);
	printf("\nNombre del director técnico -> ");
	gets(torneo1.equipos[i-1].dt);
	fflush(stdin);
	torneo1.equipos[i-1].ganados=0;
	torneo1.equipos[i-1].jugados=0;
	torneo1.equipos[i-1].perdidos=0;
	printf("\nDatos jugadores\n\n");
	for(int j=0;j<9;j++)
	{
		char ident[11];
		bool bandera=false;
				
		printf("Jugador %d\n",j+1);
		printf("\nNombre -> ");
		gets(torneo1.equipos[i-1].jugadores[j].nombre);
		fflush(stdin);
		do{
			printf("\nIdentificación -> ");
			gets(ident);
			fflush(stdin);	
			bandera=buscarID(ident);
			if(bandera==false)
			{
				strcpy(torneo1.equipos[i-1].jugadores[j].id,ident);
			}
		}while(bandera==true);
		printf("\nEdad -> ");
		printf("\n");
		scanf("%d",&aux2);
		fflush(stdin);
		torneo1.equipos[i-1].jugadores[j].edad=aux2;
	}
	
}

//Función que calcula los puntos de cada equipo
void calcularPuntos()
{
	for(int i=0;i<3;i++)
	{
		torneo1.equipos[i].puntos=((torneo1.equipos[i].ganados*3)+torneo1.equipos[i].empatados);
	}
}

//Función que organiza la tabla de posiciones implementando el algoritmo insertionsort
void ordenarPosiciones()    
{
	for(int j=1;j<3;j++)
	{
		int clave=torneo1.equipos[j].puntos, i=j-1;	
		struct equipo aux=torneo1.equipos[j];
		
		while(i>=0 && torneo1.equipos[i].puntos<clave)		//cambio para ordenarlos inversamente	que el anterior sea menor
		{                               
			torneo1.equipos[i+1]=torneo1.equipos[i];	 
							
			i=i-1;			
		}
		torneo1.equipos[i+1]=aux;				
	}
}

//Función que organiza la tabla en caso de un empate en puntos
void fixEmpate()
{
	struct equipo auxiliar;
	
	int j=1;
	while(j<=2)
	{
	for(int i=0;i<2;i++)
	{
		if(torneo1.equipos[i].puntos==torneo1.equipos[i+1].puntos)
		{
			if(torneo1.equipos[i].goles<torneo1.equipos[i+1].goles)
			{
				auxiliar=torneo1.equipos[i];
				torneo1.equipos[i]=torneo1.equipos[i+1];
				torneo1.equipos[i+1]=auxiliar;
			}
			else if(torneo1.equipos[i].goles==torneo1.equipos[i+1].goles)
			{
				if(torneo1.equipos[i].rojas>torneo1.equipos[i+1].rojas)
				{
					auxiliar=torneo1.equipos[i];
					torneo1.equipos[i]=torneo1.equipos[i+1];
					torneo1.equipos[i+1]=auxiliar;
				}
				else if(torneo1.equipos[i].rojas==torneo1.equipos[i+1].rojas)
				{
					if(torneo1.equipos[i].amarillas>torneo1.equipos[i+1].amarillas)
					{
						auxiliar=torneo1.equipos[i];
						torneo1.equipos[i]=torneo1.equipos[i+1];
						torneo1.equipos[i+1]=auxiliar;
					}
				}
			}
		}
	}
	j++;
	}
}

//función que modifica los datos de un equipo
void modificarInformacionEquipo()
{	
	int opc=-1;
	int aux=0;
	char aux2[3]="no";
	bool bandera=false;
	
	printf("Indique el equipo al que desea adicionar información:\n\n");
	if(strcmp(torneo1.equipos[0].nombre,aux2)==0)
	{
		printf("1)....................\n");
	}
	else
	{
		printf("1) %s\n",torneo1.equipos[0].nombre);
	}
	if(strcmp(torneo1.equipos[1].nombre,aux2)==0)
	{
		printf("2)....................\n");
	}
	else
	{
		printf("2) %s\n",torneo1.equipos[1].nombre);
	}
	if(strcmp(torneo1.equipos[2].nombre,aux2)==0)
	{
		printf("3)....................\n");
	}
	else
	{
		printf("3) %s\n",torneo1.equipos[2].nombre);
	}
	printf("4) Atrás.\n");
	
	scanf("%d",&opc);
	fflush(stdin);
	
	if(opc==4)
		return;
	
	printf("Ingrese las cantidades que quiere adicionar:\n");
	printf("Partidos jugados -> ");
	scanf("%d",&aux);
	fflush(stdin);
	torneo1.equipos[opc-1].jugados+=aux;
	do{
		printf("\nPartidos ganados -> ");
		scanf("%d",&aux);
		fflush(stdin);
		if((torneo1.equipos[opc-1].ganados+torneo1.equipos[opc-1].perdidos+torneo1.equipos[opc-1].empatados+aux)<=torneo1.equipos[opc-1].jugados)
		{
			bandera=true;
			torneo1.equipos[opc-1].ganados+=aux;
		}
	}while(bandera==false);
	bandera=false;
	do{
		printf("\nPartidos perdidos -> ");
		scanf("%d",&aux);
		fflush(stdin);
		if((torneo1.equipos[opc-1].ganados+torneo1.equipos[opc-1].perdidos+torneo1.equipos[opc-1].empatados+aux)<=torneo1.equipos[opc-1].jugados)
		{
			bandera=true;
			torneo1.equipos[opc-1].perdidos+=aux;
		}
	}while(bandera==false);
	bandera=false;
	do{
		printf("\nPartidos empatados -> ");
		scanf("%d",&aux);
		fflush(stdin);
		if((torneo1.equipos[opc-1].ganados+torneo1.equipos[opc-1].perdidos+torneo1.equipos[opc-1].empatados+aux)==torneo1.equipos[opc-1].jugados)
		{
			bandera=true;
			torneo1.equipos[opc-1].empatados+=aux;
		}
	}while(bandera==false);
	
}



//Función que modifica la información de los jugadores
void modificarInformacionJugadores()
{
	int opc=-1;
	int opc2=-1;
	int aux=0;
	char aux2[3]="no";
	int goleador=0;
	
	printf("Indique el equipo al cual pertenecen los jugadores que desea modificar:\n\n");
	if(strcmp(torneo1.equipos[0].nombre,aux2)==0)
	{
		printf("1)....................\n");
	}
	else
	{
		printf("1) %s\n",torneo1.equipos[0].nombre);
	}
	if(strcmp(torneo1.equipos[1].nombre,aux2)==0)
	{
		printf("2)....................\n");
	}
	else
	{
		printf("2) %s\n",torneo1.equipos[1].nombre);
	}
	if(strcmp(torneo1.equipos[2].nombre,aux2)==0)
	{
		printf("3)....................\n");
	}
	else
	{
		printf("3) %s\n",torneo1.equipos[2].nombre);
	}
	printf("4) Atrás.\n");
	
	scanf("%d",&opc);
	fflush(stdin);
	
	if(opc==4)
		return;
		
	printf("¿Qué jugador desea modificar?\n\n");
	for(int i=0;i<9;i++)
	{
		printf("%d. %s\n",i+1,torneo1.equipos[opc-1].jugadores[i].nombre);
	}
	scanf("%d",&opc2);
	fflush(stdin);
	printf("\nIngrese las cantidades que desea adicionar:");
	printf("%s",torneo1.equipos[opc-1].jugadores[opc2-1].nombre);
	printf("\nGoles -> ");
	scanf("%d",&aux);
	fflush(stdin);
	torneo1.equipos[opc-1].jugadores[opc2-1].goles+=aux;
	torneo1.equipos[opc-1].goles+=aux;
	printf("\nAmarillas -> ");
	scanf("%d",&aux);
	fflush(stdin);
	torneo1.equipos[opc-1].jugadores[opc2-1].amarillas+=aux;
	torneo1.equipos[opc-1].goles+=aux;
	printf("\nRojas -> ");
	scanf("%d",&aux);
	fflush(stdin);
	torneo1.equipos[opc-1].jugadores[opc2-1].rojas+=aux;
	torneo1.equipos[opc-1].goles+=aux;
	
	goleador=buscarGoleador(torneo1.equipos[opc-1].jugadores[opc2-1].id);
	torneo1.goleadores[goleador]=torneo1.equipos[opc-1].jugadores[opc2-1];
}

void mostrarEquipos()
{
	printf("Lista de equipos y su puntuación:\n\n");
	for(int i=0;i<3;i++)
	{
		printf("%s\n",torneo1.equipos[i].nombre);
		printf("Director técnico: %s\n",torneo1.equipos[i].dt);
		printf("Puntos: %d\n\n",torneo1.equipos[i].puntos);
	}
}


//Función que muestra los jugadores de un equipo
void mostrarJugadores()
{
	int opc=-1;
	char aux[3]="no";
	
	printf("Indique el equipo al cual pertenecen los jugadores que desea ver:\n\n");
	if(strcmp(torneo1.equipos[0].nombre,aux)==0)
	{
		printf("1)....................\n");
	}
	else
	{
		printf("1) %s\n",torneo1.equipos[0].nombre);
	}
	if(strcmp(torneo1.equipos[1].nombre,aux)==0)
	{
		printf("2)....................\n");
	}
	else
	{
		printf("2) %s\n",torneo1.equipos[1].nombre);
	}
	if(strcmp(torneo1.equipos[2].nombre,aux)==0)
	{
		printf("3)....................\n");
	}
	else
	{
		printf("3) %s\n",torneo1.equipos[2].nombre);
	}
	printf("4) Atrás.\n\n");
	
	scanf("%d",&opc);
	fflush(stdin);
	
	if(opc==4)
		return;
	
	printf("Lista de jugadores del %s:\n\n",torneo1.equipos[opc-1].nombre);
	for(int i=0;i<9;i++)
	{
		printf("%s\n",torneo1.equipos[opc-1].jugadores[i].nombre);
		printf("Identificación: %s\n",torneo1.equipos[opc-1].jugadores[i].id);
		printf("Edad: %d\n",torneo1.equipos[opc-1].jugadores[i].edad);
		printf("Goles: %d\n",torneo1.equipos[opc-1].jugadores[i].goles);
		printf("Tarjetas amarillas: %d\n",torneo1.equipos[opc-1].jugadores[i].amarillas);
		printf("Tarjetas rojas: %d\n\n",torneo1.equipos[opc-1].jugadores[i].rojas);
	}
}


//función que muestra los jugadores de un equipo ordenados por gol
void mostrarJugadoresGol()
{
	int opc=-1;
	char aux[3]="no";
	
	printf("Indique el equipo al cual pertenecen los jugadores que desea ver:\n\n");
	if(strcmp(torneo1.equipos[0].nombre,aux)==0)
	{
		printf("1)....................\n");
	}
	else
	{
		printf("1) %s\n",torneo1.equipos[0].nombre);
	}
	if(strcmp(torneo1.equipos[1].nombre,aux)==0)
	{
		printf("2)....................\n");
	}
	else
	{
		printf("2) %s\n",torneo1.equipos[1].nombre);
	}
	if(strcmp(torneo1.equipos[2].nombre,aux)==0)
	{
		printf("3)....................\n");
	}
	else
	{
		printf("3) %s\n",torneo1.equipos[2].nombre);
	}
	printf("4) Atrás.\n\n");
	
	scanf("%d",&opc);
	fflush(stdin);
	
	if(opc==4)
		return;
	
	printf("Lista de jugadores del %s ordenada por goles:\n\n",torneo1.equipos[opc-1].nombre);
	for(int i=0;i<9;i++)
	{
		printf("%s\n",torneo1.equipos[opc-1].jugadores[i].nombre);
		printf("Identificación: %s\n",torneo1.equipos[opc-1].jugadores[i].id);		
		printf("Goles: %d\n",torneo1.equipos[opc-1].jugadores[i].goles);		
	}
}

//Función que muestra la tabla de posiciones
void mostrarPosiciones()
{
	printf("Tabla de posiciones:\n\n");

		for(int i=0;i<3;i++)
		{
			printf("%d. %s\n",i+1,torneo1.equipos[i].nombre);
		}
		printf("\n");
		printf("Estadísticas:\n\n");
		printf("Equipo    PJ    PG    PP    PE    Pts    Goles    TA    TR\n");
		for(int i=0;i<3;i++)
		{
			printf("  %d       %d     %d     %d     %d      %d        %d     %d     %d\n",i+1,torneo1.equipos[i].jugados,torneo1.equipos[i].ganados,torneo1.equipos[i].perdidos,
			torneo1.equipos[i].empatados,torneo1.equipos[i].puntos,torneo1.equipos[i].goles,torneo1.equipos[i].amarillas,torneo1.equipos[i].rojas);
			
		}

}


//Función que muestra la tabla de goleadores
void mostrarGoleadores()
{
	printf("Tabla de goleadores:\n\n");
	for(int i=0;i<27;i++)
	{
		printf("%d. %s %s: %d\n",i,torneo1.goleadores[i].nombre,torneo1.goleadores[i].id,torneo1.goleadores[i].goles);
	}
}


void llenarArchivoEquipos(FILE *arcTorneo)
{
	
	
	arcTorneo = fopen("Torneo.txt","r+");
	fseek (arcTorneo,0,0);
	for(int i=0;i<3;i++)
	{
		
		fwrite(&torneo1.equipos[i], sizeof(torneo),1,arcTorneo);
	}
	fclose(arcTorneo);
}

void leerArchivoEquipos(FILE*arcTorneo)
{
	arcTorneo=fopen("Torneo.txt","r+");
	fseek(arcTorneo,0,0);
	for(int i=0;i<3;i++)
	{
		fread(&torneo1.equipos[i],sizeof(torneo),1,arcTorneo);
	}
	fclose(arcTorneo);
}





