#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <ctime>
#include <sys/stat.h>

// Desarrollado por Camilo Esteban Mora Gómez

using namespace std;


struct stuOfertaEmpleo{
    char correoEmpl[50] = "";
    char Nombre[50] = "";
    char Cargo[50] = "";
    char Profesion[60] = "";
    char Descripcion[500] = "";
    int Salario = 0;
    int NumPostulantes=0;
};

struct stuHojaVida{
    char Nombres[50] = "";
    char Apellidos[50] = "";
    char Email[50] = "";
    char Profesion[50] = "";
    char Descripcion [400] = "";
    int NumPostulaciones=0;
};

struct stuEmpl{
    char Nombres[50] = "";
    char Apellidos[50] = "";
    char Email[50] = "";
    int NumPostulantes = 0;
};

struct stuPostulacion{
    char fecha[10] = "";
    int AspSalario = 0;
    stuOfertaEmpleo Ofer;
    stuHojaVida HojaVida;
};

void SelecUsuario();
void MenuSol();
void NuevoSol();
void BuscarSol();
void MenuSolRes(stuHojaVida HojaVida);
void BuscarOferta(stuHojaVida HojaVida);
void AddOfer(stuOfertaEmpleo Ofer, char **array, stuOfertaEmpleo *&Ofers, int &n, int as);
void Ordenar(stuOfertaEmpleo *&Ofers, int size);
void ReporteOfers(stuOfertaEmpleo *Ofers, int size, stuHojaVida HojaVida);
void ReporteOfer(stuOfertaEmpleo Ofer, stuHojaVida HojaVida);
void AddPostu(stuOfertaEmpleo Ofer, stuHojaVida HojaVida, int sal);
void MenuEmpl();
void NuevoEmpl();
void BuscarEmpl();
void MenuEmplRes(stuEmpl Empl);
void NuevoOfe(stuEmpl Empl);
void ReporteOferEmpl(stuEmpl Empl);
void ReportePost(stuHojaVida HojaVida);
void BorrarOfer(stuEmpl Empl, int size, stuOfertaEmpleo *array);
bool cmpStructOfer(stuOfertaEmpleo ofer1, stuOfertaEmpleo ofer2);
void ExaminarOfer(stuEmpl Empl);
void OrdenarPostu(stuPostulacion *&Posts, int size);
void EliminarPost(stuPostulacion Post);

int main(int argc, char** argv){
    SelecUsuario();
    return 0;
}

void SelecUsuario(){
    /*
  	  Nombre : SelecUsuario
  	  Objetivo: Mostrar el primer menu donde se elige entre empleador y solicitante
  	  Entradas: Ninguna
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    int a;
    cout << "--------------Seleccion de Usuario--------------" <<endl<<endl;
    cout << "Seleccione 1 si desea ingresar como solicitante" <<endl;
    cout << "Seleccione 2 si desea ingresar como empleador" <<endl;
    cout << "Seleccione otro numero para salir" <<endl;
    cin>>a;
    switch(a){
        case 1:
            MenuSol();
            break;
        case 2:
            MenuEmpl(); 
            break;
    }
}

void MenuSol(){
    /*
  	  Nombre : MenuSol
  	  Objetivo: Mostrar menu de ingreso a solicitante
  	  Entradas: Ninguna
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    int op;
    cout << "--------------Ingreso Solicitante--------------" <<endl<<endl;
    cout << "Seleccione 1 si ya esta registrado" <<endl;
    cout << "Seleccione 2 si no esta registrado" <<endl;
    cout << "Seleccione 3 si quiere volver a la seleccion de usuario" <<endl;
    cout << "Seleccione otro numero para salir" <<endl;
    cin>>op;
    switch(op){
        case 1:
            BuscarSol();
            break;
        case 2:
            NuevoSol();
            MenuSol();
            break;
        case 3:
            SelecUsuario(); 
            break;
    }
}

void BuscarSol(){
    /*
  	  Nombre : BuscarSol
  	  Objetivo: Buscar un solicitante segun un correo ingresado
  	  Entradas: Ninguna
  	  Salidas: Ninguna, funcion void
	*/
    stuHojaVida HojaVD;
    char correo[50];
    bool Encontro=false;
    cout << "" <<endl<<endl;
    cin.ignore();
    cout << "Ingrese su correo" <<endl;
    cin.getline(correo, sizeof(correo));
    ifstream archSol("Solicitantes.dat",ios::binary);
    if (archSol){
      while (!archSol.eof() && !Encontro){
        if (archSol.read((char *)&HojaVD, sizeof(HojaVD)))
          if (strcmp(correo, HojaVD.Email)==0)
            Encontro=true;
      }
      if (!Encontro){
        cout << "El solicitante no existe" << endl;
        system("pause");
        MenuSol();
        }else
            MenuSolRes(HojaVD);
      archSol.close();
	}else{
	  cout << "No se pudo abrir el archivo" << endl;
      system("pause");
      MenuSol();
      }
}

void MenuSolRes(stuHojaVida HojaVida){
    /*
  	  Nombre : MenuSolRes
  	  Objetivo: Mostrar el menu de un solicitante registrado
  	  Entradas: Un struct de Hoja de Vida
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    int op;
    cout << "------------------Menu Solicitante------------------" <<endl<<endl;
    cout << "Bienvenido "<<HojaVida.Nombres<<" "<<HojaVida.Apellidos <<endl;
    cout << setw(70) << setfill('-') << '\n' << setfill(' ');
    cout << "Seleccione 1 si quiere buscar una oferta de empleo" <<endl;
    cout << "Seleccione 2 para ver el reporte de las postulaciones" <<endl;
    cout << "Seleccione 3 para volver a la seleccion de usuario" <<endl;
    cout << "Seleccione otro numero para salir" <<endl;
    cin>>op;
    switch(op){
        case 1:
            BuscarOferta(HojaVida);
            break;
        case 2:
            if(HojaVida.NumPostulaciones>0)
                ReportePost(HojaVida);
            else{
                cout<<"Usted no tiene postulaciones a ver"<<endl;
                system("pause");
                MenuSolRes(HojaVida);
            }
            break;
        case 3:
            SelecUsuario(); 
            break;
    }
}

void NuevoSol(){
    /*
  	  Nombre : NuevoSol
  	  Objetivo: Crear y registrar un nuevo solicitante
  	  Entradas: Ninguna
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    stuHojaVida NHojaVida;
    cout << "----------Registro de nuevo Solicitante----------" <<endl<<endl;
    cin.ignore();
    cout << "Digite sus nombres "<<endl;
	cin.getline(NHojaVida.Nombres, sizeof(NHojaVida.Nombres));
	cout << "Digite sus apellidos "<<endl;
	cin.getline(NHojaVida.Apellidos,sizeof(NHojaVida.Apellidos));
	cout << "Digite su correo "<<endl;
	cin.getline(NHojaVida.Email,sizeof(NHojaVida.Email));
	cout << "Digite su profesion"<<endl;
	cin.getline(NHojaVida.Profesion,sizeof(NHojaVida.Profesion));
    cout << "Digite una descripcion laboral"<<endl;
	cin.getline(NHojaVida.Descripcion,sizeof(NHojaVida.Descripcion));
    ofstream archSol("Solicitantes.dat",ios::binary|ios::app);
    archSol.write((char *)&NHojaVida, sizeof(NHojaVida));
	archSol.close();
    cout << "Solicitante registrado exitosamente"<<endl;
    system("pause");
}

void BuscarOferta(stuHojaVida HojaVida){
    /*
  	  Nombre : BuscarOferta
  	  Objetivo: Buscar entre las ofertas registradas segun palabras claves
  	  Entradas: Un struct con la Hoja de Vida
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    stuOfertaEmpleo Ofer;
    char palabras[100], *p, **array, **temp;
    int i=0, k;
    cout << "----------Busqueda de Ofertas----------" <<endl<<endl;
    cout<<"Digite las palabras clave a buscar separadas por comas"<<endl;
    cin.ignore();
    cin.getline(palabras, sizeof(palabras));
    for (int i=0; i<strlen(palabras);i++)
		palabras[i] = tolower(palabras[i]);
    p=strtok(palabras," ,.;:");
	while (p!=NULL){
        temp = new char*[i+1];
        for(k=0;k<i;k++)
            *(temp+k)=*(array+k);
        *(temp+k) = p;
        if(i>0)
            delete[]array;
        array=temp;
        i++;
	    p=strtok(NULL," ,.;:");
    }
    fstream archOfer("Ofertas.dat",ios::binary|ios::in|ios::out);
    int n=0;
    stuOfertaEmpleo *Ofers;
    if(archOfer){
        while(!archOfer.eof()){
            if (archOfer.read((char *)&Ofer, sizeof(Ofer))){
                AddOfer(Ofer, array, Ofers, n, i);
            }
        }
    archOfer.close();
    }
    Ordenar(Ofers, n);
    ReporteOfers(Ofers, n, HojaVida);
}

void AddOfer(stuOfertaEmpleo Ofer, char **array, stuOfertaEmpleo *&Ofers, int &n, int as){
    /*
  	  Nombre : AddOfer
  	  Objetivo: Añadir una oferta que contiene una de las palabras claves al arreglo de ofertas
  	  Entradas: Un struct con la oferta a analizar, un arreglo de char con las palabras claves, 
        un arreglo de structs de ofertas, un entero (n) que representa la extension
        del arreglo, y un entero (as) que es la extension del arreglo de palabras clave
  	  Salidas: Ninguna, funcion void
	*/
    char *p, *q, text[500], prof[60];
    bool existe = false;
    stuOfertaEmpleo *temp;
    int k, j;
    strcpy(text, Ofer.Descripcion);
    strcpy(prof, Ofer.Profesion);
    for (int i=0; i<strlen(text);i++)
		text[i] = tolower(text[i]);
    for (int i=0; i<strlen(prof);i++)
		prof[i] = tolower(prof[i]);
    p = strtok(text," ,.;:");
    while(p!=NULL && !existe){
        for(k=0;k<as;k++){
            if(strcmp(p, *(array+k))==0){
                temp = new stuOfertaEmpleo[n+1];
                for(j=0;j<n;j++)
                    *(temp+j)=*(Ofers+j);
                *(temp+j)=Ofer;
                if(n>0)
                    delete[]Ofers;
                n++;
                Ofers = temp;
                existe = true;
                break;
            }
        }
        p=strtok(NULL," ,.;:");
    }
    if(!existe){
        q = strtok(prof," ,.;:");
        while(q!=NULL && !existe){
            for(k=0;k<as;k++)
                if(strcmp(q, *(array+k))==0){
                    temp = new stuOfertaEmpleo[n+1];
                    for(j=0;j<n;j++)
                        *(temp+j)=*(Ofers+j);
                    *(temp+j)=Ofer;
                    if(n>0)
                        delete[]Ofers;
                    n++;
                    Ofers = temp;
                    existe = true;
                    break;
                }
            q=strtok(NULL," ,.;:");
        }
    }
}

void Ordenar(stuOfertaEmpleo *&Ofers, int size){
    /*
  	  Nombre : Ordenar
  	  Objetivo: Ordenar un arreglo de ofertas por salario
  	  Entradas: Un arreglo de structs de ofertas y un entero con su tamaño
  	  Salidas: Ninguna, funcion void
	*/
    stuOfertaEmpleo temp;
    for (int i = 0; i<size;i++){
		for (int k=i+1;k<size;k++){
			if((Ofers+i)->Salario < (Ofers+k)->Salario){
			    temp = *(Ofers+i);
			    *(Ofers+i) = *(Ofers+k);
			    *(Ofers+k) = temp;
			}
		}
	}
}

void ReporteOfers(stuOfertaEmpleo *Ofers, int size, stuHojaVida HojaVida){
    /*
  	  Nombre : ReporteOfers
  	  Objetivo: Mostrar las ofertas filtradas por las palabras clave y dar
        la opcion de postularse
  	  Entradas: Un arreglo de structs de ofertas, un entero con su tamaño y
        la hoja de vida del solicitante
  	  Salidas: Ninguna, funcion void
	*/
    int i=1;
    stuOfertaEmpleo Ofer;
    if(size>0){
        for(int k=0;k<size;k++){
            cout<<"\n#: "<<i<<endl;
            cout<<"Nombre de la empresa: "<<(Ofers+k)->Nombre<<endl;
            cout<<"Cargo ofrecido: "<<(Ofers+k)->Cargo<<endl;
            cout<<"Salario: "<<(Ofers+k)->Salario<<endl;
            i++;
        }
        int op;
        cout << "\nDigite 0 si quiere volver al inicio"<< endl;
        cout << "Ingrese el numero de la oferta a la que desea aplicar"<< endl;
        cin>>op;
        if(op>size && op!=0){
            cout<<"Opcion mayor a la cantidad de opciones"<<endl;
            system("pause");
        }else if(op==0){
            MenuSolRes(HojaVida);
        }else{
            cout<<"Usted ha elegido la opcion "<<op<<endl<<endl;
            ReporteOfer(*(Ofers+op-1), HojaVida);
        }
    }else{
        cout<<"No hay ofertas con tales terminos"<<endl;
        MenuSolRes(HojaVida);
    }

}

void ReporteOfer(stuOfertaEmpleo Ofer, stuHojaVida HojaVida){
    /*
  	  Nombre : ReporteOfer
  	  Objetivo: Mostrar una oferta de forma más detallada y poder postularse
  	  Entradas: Un struct de la oferta y la hoja de vida del solicitante
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    cout<<"Nombre: "<<Ofer.Nombre<<endl;
    cout<<"Cargo: "<<Ofer.Cargo<<endl;
    cout<<"Profesion(es): "<<Ofer.Profesion<<endl;
    cout<<"Descripcion: "<<Ofer.Descripcion<<endl;
    cout<<"Salario: "<<Ofer.Salario<<endl;
    int op;
    cout<<"\nDigite 1 para postular a la oferta"<<endl;
    cout<<"\nDigite 2 para volver a la busqueda de ofertas"<<endl;
    cin>>op;
    switch(op){
        case 1:
            int sal;
            cout<<"Ingrese el salario que le gustaria tener"<<endl;
            cin>>sal;
            AddPostu(Ofer, HojaVida, sal);
            HojaVida.NumPostulaciones++;
            MenuSolRes(HojaVida);
            break;
        case 2:
            BuscarOferta(HojaVida);
            break;
    }

}

void AddPostu(stuOfertaEmpleo Ofer, stuHojaVida HojaVida, int sal){
    /*
  	  Nombre : AddPostu
  	  Objetivo: Crear y agregar una postulacion a una oferta
  	  Entradas: Un struct de la oferta, de la hoja de vida del solicitante y
        un entero del salario esperado
  	  Salidas: Ninguna, funcion void
	*/
    bool encontro=false;
    stuPostulacion Post;
    Post.HojaVida=HojaVida;
    Post.Ofer=Ofer;
	time_t curr_time;
	tm * curr_tm;
	char fecha[10];
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(fecha, 20, "%d/%m/%Y", curr_tm);
    strcpy(Post.fecha, fecha);
    Post.AspSalario=sal;
    ofstream archPosts("Postulaciones.dat",ios::binary|ios::app);
    if(archPosts){
        archPosts.write((char *)&Post, sizeof(Post));
        archPosts.close();
    }
    stuEmpl Ex;
    fstream archEmpl("Empleadores.dat",ios::binary|ios::in|ios::out);
    if(archEmpl){
        while (!archEmpl.eof() && !encontro){
            if (archEmpl.read((char *)&Ex, sizeof(Ex)))
                if(strcmp(Ex.Email, Ofer.correoEmpl)==0){
                    encontro = true;
                    Ex.NumPostulantes++;
                    archEmpl.seekg((int)((-1)*sizeof(Ex)),ios::cur);
                    archEmpl.write((char *)&Ex, sizeof(Ex));
                }
        }
        archEmpl.close();
    }
    encontro = false;
    stuHojaVida Ej;
    fstream archSol("Solicitantes.dat",ios::binary|ios::in|ios::out);
    if(archSol){
        while (!archSol.eof() && !encontro){
            if (archSol.read((char *)&Ej, sizeof(Ej)))
                if(strcmp(Ej.Email, Post.HojaVida.Email)==0){
                    encontro = true;
                    Ej.NumPostulaciones++;
                    archSol.seekg((int)((-1)*sizeof(Ej)),ios::cur);
                    archSol.write((char *)&Ej, sizeof(Ej));
                }
        }
        archSol.close();
    }  
    encontro = false;
    stuOfertaEmpleo Of;
    fstream archOfer("Ofertas.dat",ios::binary|ios::in|ios::out);
    if(archOfer){
        while (!archOfer.eof() && !encontro){
            if (archOfer.read((char *)&Of, sizeof(Of))){
                if(cmpStructOfer(Ofer, Of))
                    encontro = true;
                    Of.NumPostulantes++;
                    archOfer.seekg((int)((-1)*sizeof(Of)),ios::cur);
                    archOfer.write((char *)&Of, sizeof(Of));
                }
        }
        archOfer.close();
    } 
}

void ReportePost(stuHojaVida HojaVida){
    /*
  	  Nombre : ReportePost
  	  Objetivo: Mostrar las postulaciones hechas por un solicitante
  	  Entradas: Un struct de la hoja de vida del solicitante
  	  Salidas: Ninguna, funcion void
	*/
    stuHojaVida datHV;
    stuPostulacion Post, *Posts = new stuPostulacion[HojaVida.NumPostulaciones];
    bool encontro = false;
    ifstream archSol("Postulaciones.dat",ios::binary);
    int i=0;
    if(archSol){
        while (!archSol.eof() && !encontro){
            if (archSol.read((char *)&Post, sizeof(Post)))
                if(strcmp(Post.HojaVida.Email, HojaVida.Email)==0){
                    *(Posts+i) = Post;
                    cout<<"\n# "<<i+1<<endl;
                    cout<<"Nombre de la empresa: "<<Post.Ofer.Nombre<<endl;
                    cout<<"Cargo:  "<<Post.Ofer.Cargo<<endl;
                    cout<<"Fecha de postulacion:  "<<Post.fecha<<endl;
                    cout<<"Salario esperado:  "<<Post.AspSalario<<endl;
                    i++;
                }
        }
        archSol.close();
        int op;
        cout<<"\nDigite 1 si quiere volver al menu de solicitante"<<endl;
        cout<<"Digite 2 si retirar una postulacion"<<endl;
        cin>>op;
        switch(op){
            case 1:
                MenuSolRes(HojaVida);
                break;
            case 2:
                int p;
                cout<<"Ingrese el numero de la postulacion a retirar"<<endl;
                cin>>p;
                if(p<=0||p>HojaVida.NumPostulaciones){
                    cout<<"Opcion no valida"<<endl;
                    MenuSolRes(HojaVida);
                }else
                    EliminarPost(*(Posts+p-1));
                    HojaVida.NumPostulaciones--;
                    MenuSolRes(HojaVida);
                break;
        }
        delete[] Posts;
    }
}

void MenuEmpl(){
    /*
  	  Nombre : MenuEmpl
  	  Objetivo: Mostrar el menu de ingreso para empleador
  	  Entradas: Ninguna
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    int op;
    cout << "--------------Ingreso Empleador--------------" <<endl<<endl;
    cout << "Seleccione 1 si ya esta registrado" <<endl;
    cout << "Seleccione 2 si no esta registrado" <<endl;
    cout << "Seleccione 3 si quiere volver a la seleccion de usuario" <<endl;
    cout << "Seleccione otro numero para salir" <<endl;
    cin>>op;
    switch(op){
        case 1:
            BuscarEmpl();
            break;
        case 2:
            NuevoEmpl();
            MenuEmpl();
            break;
        case 3:
            SelecUsuario(); 
            break;
    }
}

void NuevoEmpl(){
    /*
  	  Nombre : NuevoEmpl
  	  Objetivo: Crear un nuevo empleador y registrarlo
  	  Entradas: Ninguna
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    stuEmpl Empl;
    cout << "----------Registro de nuevo Empleador----------" <<endl<<endl;
    cin.ignore();
    cout << "Digite sus nombres"<<endl;
	cin.getline(Empl.Nombres, sizeof(Empl.Nombres));
	cout << "Digite sus apellidos"<<endl;
	cin.getline(Empl.Apellidos,sizeof(Empl.Apellidos));
	cout << "Digite su correo"<<endl;
	cin.getline(Empl.Email,sizeof(Empl.Email));
    ofstream archSol("Empleadores.dat",ios::binary|ios::app);
    archSol.write((char *)&Empl, sizeof(Empl));
	archSol.close();
    cout << "Empleador registrado exitosamente"<<endl;
    system("pause");
}

void BuscarEmpl(){
    /*
  	  Nombre : BuscarEmpl
  	  Objetivo: Buscar un empleador por un correo ingresado
  	  Entradas: Ninguna
  	  Salidas: Ninguna, funcion void
	*/
    stuEmpl Empl;
    char correo[50];
    bool Encontro=false;
    cout << "" <<endl<<endl;
    cin.ignore();
    cout << "Ingrese su correo" <<endl;
    cin.getline(correo, sizeof(correo));
    ifstream archSol("Empleadores.dat",ios::binary);
    if (archSol){
      while (!archSol.eof() && !Encontro){
        if (archSol.read((char *)&Empl, sizeof(Empl)))
          if (strcmp(correo, Empl.Email)==0){
            Encontro=true;
            MenuEmplRes(Empl);
          }
      }
      if (!Encontro){
        cout << "El empleador no existe no existe" << endl;
        system("pause");
        MenuEmpl();
        }
      archSol.close();
	}else{
	  cout << "No se pudo abrir el archivo" << endl;
      system("pause");
      MenuEmpl();
      }
}

void MenuEmplRes(stuEmpl Empl){
    /*
  	  Nombre : MenuEmplRes
  	  Objetivo: Mostrar el menu de un empleador registrado
  	  Entradas: El struct de un empleador
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    int op;
    cout << "------------------Menu Empleador------------------" <<endl<<endl;
    cout << "Bienvenido "<<Empl.Nombres<<" "<<Empl.Apellidos <<endl;
    cout << setw(70) << setfill('-') << '\n' << setfill(' ');
    cout << "Seleccione 1 si agregar una oferta" <<endl;
    cout << "Seleccione 2 para ver un reporte y/o eliminar una oferta" <<endl;
    cout << "Seleccione 3 para volver a la seleccion de usuario" <<endl;
    cout << "Seleccione otro numero para salir" <<endl;
    cin>>op;
    switch(op){
        case 1:
            NuevoOfe(Empl);
            break;
        case 2:
            ReporteOferEmpl(Empl);
            break;
        case 3:
            SelecUsuario(); 
            break;
    }
}

void NuevoOfe(stuEmpl Empl){
    /*
  	  Nombre : NuevoOfe
  	  Objetivo: Crear y registrar una nueva oferta
  	  Entradas: El struct de un empleador
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    stuOfertaEmpleo NOfEmpl;
    cout << "----------Nueva Oferta----------" <<endl<<endl;
    strcpy(NOfEmpl.correoEmpl, Empl.Email);
    cin.ignore();
    cout << "Digite el nombre de la empresa"<<endl;
	cin.getline(NOfEmpl.Nombre, sizeof(NOfEmpl.Nombre));
	cout << "Digite el cargo ofrecido"<<endl;
	cin.getline(NOfEmpl.Cargo,sizeof(NOfEmpl.Cargo));
	cout << "Digite la(s) profesion(es) solicitada(s), si es mas de una separelas por comas"<<endl;
	cin.getline(NOfEmpl.Profesion,sizeof(NOfEmpl.Profesion));
	cout << "Digite la descripcion de las oferta"<<endl;
	cin.getline(NOfEmpl.Descripcion,sizeof(NOfEmpl.Descripcion));
    cout << "Digite el salario ofrecido"<<endl;
	cin>>NOfEmpl.Salario;
    ofstream archSol("Ofertas.dat",ios::binary|ios::app);
    archSol.write((char *)&NOfEmpl, sizeof(NOfEmpl));
	archSol.close();
    cout << "Nueva oferta registrada exitosamente"<<endl;
    system("pause");
    MenuEmplRes(Empl);
}


void ReporteOferEmpl(stuEmpl Empl){
    /*
  	  Nombre : ReporteOferEmpl
  	  Objetivo: Mostrar las ofertas hechas por un empleador y crear un arreglo
        de ofertas por si se busca eliminar una oferta
  	  Entradas: El struct de un empleador
  	  Salidas: Ninguna, funcion void
	*/
    system("cls");
    int i = 1, n=0, k;
    stuOfertaEmpleo OfEmpl, *array, *temp;
    fstream archOfer("Ofertas.dat",ios::binary|ios::in|ios::out);
    cout << "----------Reporte de Ofertas----------" <<endl<<endl;
    if(archOfer){
        while (!archOfer.eof()){
            if (archOfer.read((char *)&OfEmpl, sizeof(OfEmpl))){
                if(strcmp(OfEmpl.correoEmpl, Empl.Email)==0){
                    cout<<"\n#: "<<i<<endl;
                    cout<<"Nombre de la empresa: "<<OfEmpl.Nombre<<endl;
                    cout<<"Cargo ofrecido: "<<OfEmpl.Cargo<<endl;
                    cout<<"Salario: "<<OfEmpl.Salario<<endl;
                    n++;
                    temp = new stuOfertaEmpleo[n];
                    for(k=0;k<n-1;k++)
                        *(temp+k) = *(array+k);
                    *(temp+k) = OfEmpl;
                    if(n>1)
                        delete[] array;
                    array = temp;
                    i++;
                }
            }
        }
        archOfer.close();
    }
    if(n==0){
        cout<<"No hay ofertas creadas"<<endl;
        system("pause");
        MenuEmplRes(Empl);
    }else{
        int op;
        cout << setw(70) << setfill('-') << '\n' << setfill(' ');
        cout<<"\nSi quiere borrar una oferta de empleo, digite 1"<<endl;
        cout<<"Si quiere ver candidatos, digite 2"<<endl;
        cout<<"Si quiere volver, digite 3"<<endl;
        cin>>op;
        switch(op){
            case 1:
                BorrarOfer(Empl, n, array);
                break;
            case 2:
                if (Empl.NumPostulantes>0)
                    ExaminarOfer(Empl);
                else{
                    cout<<"No hay postulantes actualmente a sus ofertas"<<endl;
                    system("pause");
                    ReporteOferEmpl(Empl);
                }
                break;
            case 3:
                MenuEmplRes(Empl);
                break;
        }
    }

}

void BorrarOfer(stuEmpl Empl, int size, stuOfertaEmpleo *array){
    /*
  	  Nombre : BorrarOfer
  	  Objetivo: Borrar una oferta hecha por un empleador, y si la oferta tiene
        postulantes, eliminar estas postulaciones también
  	  Entradas: El struct de un empleador, un entero del tamaño del arreglo
        de ofertas, y un arreglo con structs de ofertas del empleador
  	  Salidas: Ninguna, funcion void
	*/
    int op;
    cout<<"Digite el numero de la oferta a borrar"<<endl;
    cin>>op;
    if(op-1>size){
        cout<<"El numero es mayor a la cantidad de ofertas"<<endl;
    }else{
        stuOfertaEmpleo Obj = *(array+op-1), rec;
        cout<<"Usted ha elegido la oferta de la empresa: "<<Obj.Nombre<<" para el cargo de "
        <<Obj.Cargo<<" con un salario de "<<Obj.Salario<<endl;
        ifstream archOfertas("Ofertas.dat",ios::binary);
	    ofstream archOfertasTemp("OfertasTemp.dat",ios::binary);
        if (archOfertas){
            while (!archOfertas.eof()){
                if (archOfertas.read((char *)&rec, sizeof(rec)))
                    if (!cmpStructOfer(Obj, rec)){
          	            archOfertasTemp.write((char *)&rec, sizeof(rec));
                    }
                }
            archOfertas.close();
            archOfertasTemp.close();
            remove("Ofertas.dat");
            rename("OfertasTemp.dat","Ofertas.dat");
        }
        cout<<"Oferta borrada exitosamente"<<endl;
        if(Obj.NumPostulantes>0){
            int i=0;
            stuPostulacion *Posts = new stuPostulacion[Obj.NumPostulantes], Post;
            ifstream archPosts("Postulaciones.dat",ios::binary);
            if(archPosts){
                while(!archPosts.eof()){
                    if(archPosts.read((char *)&Post, sizeof(Post))){
                        if(cmpStructOfer(Obj, Post.Ofer)){
                            *(Posts+i)=Post;
                            i++;
                        }
                    }
                }
                archPosts.close();
            }
            int k;
            for(k=0;k<Obj.NumPostulantes;k++)
                EliminarPost(*(Posts+k));
            delete[]Posts;
        }
    }
    Empl.NumPostulantes-=(array+op-1)->NumPostulantes;
    ReporteOferEmpl(Empl);
}

bool cmpStructOfer(stuOfertaEmpleo ofer1, stuOfertaEmpleo ofer2){
    /*
  	  Nombre : cmpStructOfer
  	  Objetivo: Comparar dos structs de ofertas
  	  Entradas: Dos structs de ofertas
  	  Salidas: Bool
	*/
    if (strcmp(ofer1.Cargo, ofer2.Cargo)!=0)
        return false;
    if (strcmp(ofer1.Nombre, ofer2.Nombre)!=0)
        return false;
    if (strcmp(ofer1.Profesion, ofer2.Profesion)!=0)
        return false;
    if (strcmp(ofer1.Descripcion, ofer2.Descripcion)!=0)
        return false;
    if (ofer1.Salario!=ofer2.Salario)
        return false;
    return true;
}

void ExaminarOfer(stuEmpl Empl){
    /*
  	  Nombre : ExaminarOfer
  	  Objetivo: Mostrar los postulantes a ofertas de un empleador
  	  Entradas: Un struct de un empleador
  	  Salidas: Ninguna, funcion void
	*/
    int i, k, n=0;
    stuOfertaEmpleo datOfer, *Ofers, *temp;
    stuPostulacion Post, *Posts = new stuPostulacion[Empl.NumPostulantes];;
    fstream arch("Postulaciones.dat",ios::binary|ios::in|ios::out);
    if(arch){
        while(!arch.eof()){
            if (arch.read((char *)&Post, sizeof(Post)))
                if(strcmp(Empl.Email, Post.Ofer.correoEmpl)==0){
                    *(Posts+n) = Post;
                    n++;
                }
        }
        arch.close();
        OrdenarPostu(Posts, Empl.NumPostulantes);
        cout<<"----------Lista de Postulantes----------"<<endl;
        for(i=0;i<Empl.NumPostulantes;i++){
            cout<<"\n#"<<i+1<<endl;
            cout<<"Cargo Ofrecido: "<<(Posts+i)->Ofer.Cargo<<endl;
            cout<<"Nombre(s) del postulantes: "<<(Posts+i)->HojaVida.Nombres<<endl;
            cout<<"Profesion del postulante: "<<(Posts+i)->HojaVida.Profesion<<endl;
            cout<<"Salario esperado: "<<(Posts+i)->AspSalario<<endl;
        }
        int op;
        cout<<"\nDigite 1 para volver al reporte de sus ofertas"<<endl;
        cout<<"Digite 2 para descartar a un postulante"<<endl;
        cin>>op;
        switch(op){
            case 1:
                ReporteOferEmpl(Empl);
                break;
            case 2:
                int p;
                cout<<"Ingrese el numero del postulante a descartar"<<endl;
                cin>>p;
                if(p<=0||p>Empl.NumPostulantes){
                    cout<<"Numero invalido"<<endl;
                    MenuEmplRes(Empl);
                }else{
                    EliminarPost(*(Posts+p-1));
                    Empl.NumPostulantes--;
                    MenuEmplRes(Empl);
                }
                break;
        }
        delete[] Posts;
    }
}

void OrdenarPostu(stuPostulacion *&Posts, int size){
    /*
  	  Nombre : OrdenarPostu
  	  Objetivo: Ordenar una arreglo de postulaciones por cargo y luego por salario
  	  Entradas: Un arreglo de structs de postulaciones y un entero que es el 
        tamaño del arreglo
  	  Salidas: Ninguna, funcion void
	*/
    stuPostulacion temp;
    for (int i = 0; i<size;i++){
		for (int k=i+1;k<size;k++){
			if((Posts+i)->AspSalario > (Posts+k)->AspSalario){
			    temp = *(Posts+i);
			    *(Posts+i) = *(Posts+k);
			    *(Posts+k) = temp;
			}
		}
	}
    for (int i = 0; i<size;i++){
		for (int k=i+1;k<size;k++){
			if((Posts+i)->Ofer.Cargo > (Posts+k)->Ofer.Cargo){
			    temp = *(Posts+i);
			    *(Posts+i) = *(Posts+k);
			    *(Posts+k) = temp;
			}
		}
	}    
}

void EliminarPost(stuPostulacion Post){
    /*
  	  Nombre : EliminarPost
  	  Objetivo: Eliminar una postulacion
  	  Entradas: Un struct de la postulacion
  	  Salidas: Ninguna, funcion void
	*/
    stuHojaVida HJ;
    stuOfertaEmpleo TOfer;
    stuPostulacion TPost;
    stuEmpl TEmpl;
    int i=0;
    ofstream archTemp("PostulacionesTemp.dat",ios::binary);
    ifstream archPosts("Postulaciones.dat",ios::binary);
    if(archPosts){
        while(!archPosts.eof()){
            if(archPosts.read((char *)&TPost, sizeof(TPost))){
                if(TPost.AspSalario!=Post.AspSalario || strcmp(Post.fecha, TPost.fecha)!=0
                || strcmp(TPost.HojaVida.Email, Post.HojaVida.Email)!=0 || 
                !cmpStructOfer(TPost.Ofer, Post.Ofer))
                    archTemp.write((char *)&Post, sizeof(Post));
            }
        }
        archPosts.close();
        archTemp.close();
        remove("Postulaciones.dat");
        rename("PostulacionesTemp.dat","Postulaciones.dat");
    }
    bool encontro=false;
    fstream archEmpl("Empleadores.dat",ios::binary|ios::in|ios::out);
    if(archEmpl){
        while(!archEmpl.eof() && !encontro){
            if (archEmpl.read((char *)&TEmpl, sizeof(TEmpl))){
                if(strcmp(Post.Ofer.correoEmpl, TEmpl.Email)==0){
                    TEmpl.NumPostulantes--;
                    archEmpl.seekg((int)((-1)*sizeof(TEmpl)),ios::cur);
                    archEmpl.write((char *)&TEmpl, sizeof(TEmpl));
                    encontro=true;
                }
            }
        }
        archEmpl.close();
    }
    encontro=false;
    fstream archSol("Solicitantes.dat",ios::binary|ios::in|ios::out);
    if(archSol){
        while(!archSol.eof()&& !encontro){
            if (archSol.read((char *)&HJ, sizeof(HJ))){
                if(strcmp(Post.HojaVida.Email, HJ.Email)==0){
                    HJ.NumPostulaciones--;
                    archSol.seekg((int)((-1)*sizeof(HJ)),ios::cur);
                    archSol.write((char *)&HJ, sizeof(HJ));
                    encontro=true;
                }
            }
        }
        archSol.close();
    }
    encontro=false;
    fstream archOfer("Ofertas.dat",ios::binary|ios::in|ios::out);
    if(archOfer){
        while(!archOfer.eof()&& !encontro){
            if (archOfer.read((char *)&TOfer, sizeof(TOfer))){
                if(cmpStructOfer(Post.Ofer, TOfer)){
                    TOfer.NumPostulantes--;
                    archOfer.seekg((int)((-1)*sizeof(TOfer)),ios::cur);
                    archOfer.write((char *)&TOfer, sizeof(TOfer));
                    encontro=true;
                }
            }
        }
        archOfer.close();
    }
}
