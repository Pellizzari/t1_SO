#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

int ls(){

	int var, j;
	struct dirent **d;
	struct stat status;
	struct tm * t;
	
	var=scandir(".", &d, 0, alphasort);//Ordena los archivos del directorio con alphasort.
		
	for (j=0; j<var; j++){
		
		char nombre[1000];
		stat(nombre, &status);
		strcpy(nombre,d[j]->d_name);//Asigna el nombre del archivo a la variable nombre.
		if ((strncmp(nombre, "..",2) != 0)&&(strncmp(nombre, ".",1) != 0)){
		t= localtime (&(status.st_mtime));//Asigna a t la hora local

		printf("%s\n%s", nombre, asctime(t));//Entrega la fecha y el nombre de los archivos.

		switch(status.st_mode & S_IFMT){ 
			case S_IFBLK: printf("Block Special Device");break;
			case S_IFIFO: printf("FIFO");break;
			case S_IFCHR: printf("Character Device");break;
			case S_IFLNK: printf("Link");break;
			case S_IFSOCK: printf("Socket");break;
			case S_IFREG: printf("File");break;
			case S_IFDIR: printf("Directory");break;
			default: printf("Unknown");
		}//Entrega el tipo del archivo.
		printf("\n\n");
		}
        free(d[j]);

	}

	free(d);
	
	return 0;

}


//Main para el manejo de las funciones.
int main(){
	char d[1024];
	char l[1024];
	int n=1;
	while(n){
		int var;
		getcwd(d,sizeof(d)); 
		printf("%s\\$",d);
		scanf("\n %[^\n]",l); 
		if(strncmp(l,"ls n",4)==0){
			ls();
		}
		//Aplicacion de la funcion open, quedara en un while esperando a que el usuario ingrese close.
		else if(strncmp(l,"open",4)==0){
			FILE *ff;
			ff=fopen(&l[5],"r");
			while(fgets(&l[5],sizeof &l[5],ff)!= NULL){		
      				fprintf(stdout,"%s",&l[5]);							
			}
			fclose(ff);
			while (strncmp(l, "close",5) != 0){
				printf("$");
				scanf("%s", l);
			}

		}
		//Aplicacion de la funcion cd chdir(&l[3]) llevara al directorio indicado por el comando considerando el caso "..".
		//Se verifica el valor de chdir(&l[3] asignandolo a una variable, si su valor es 0, la direccion será valida.
		else if(strncmp(l,"cd",2)==0){
			var=chdir(&l[3]);
			if (var==0){
				chdir(&l[3]);
			}

		}
		
		//En caso de que el comando ingresado por el usuario no sea ninguno de los pedidos en la tarea se mostrara 
		//en pantalla el pantalla "comando no valido"
		else{
			printf("Comando no valido");
			
		}

	}

}
