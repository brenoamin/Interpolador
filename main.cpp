#include <iostream>
using namespace std;
#define TAM 10
int opcMetodo, k, n;
double dd[TAM][TAM], tab[TAM][TAM]; // dd(ordem)(i)

double fat(int x) {
  if (x==0) return 1;
  else if (x==1) return 1;
  else return x*fat(x-1); 
}

void salvarDif() {
  for(int i=0; i<=n; i++) dd[0][i]=tab[i][1];
  for(int i=1; i<=n; i++) { 
    for(int j=0; j<=n; j++) { 
      if (j<=n-i) {
        if(opcMetodo==1) dd[i][j]=(dd[i-1][j+1]-dd[i-1][j])/(tab[j+i][0]-tab[j][0]);
        else dd[i][j]=(dd[i-1][j+1]-dd[i-1][j]);
      }
      else dd[i][j]=0;
    }
  }
}

double fdd(double x, int n) {
  double sum = tab[0][1];
  for(int i=1; i<=n; i++) {
    double p=1.0;
    for(int j=0; j<=i-1; j++) p*=x-tab[j][0];
    sum+=p*dd[i][0];
  }
  return sum;
}

double fdf(double x, int n) {
  double z=(x-tab[0][0])/(tab[1][0]-tab[0][0]);
  double sum = tab[0][1];
  for(int i=1; i<=n; i++) {
    double p=1.0;
    for(int j=0; j<=i-1; j++) p*=z-j;
    sum+=p*dd[i][0]/fat(i);
  }
  return sum;
}

bool notCanUse() {
  bool aux;
  for(int i=2; i<k-1; i++) {
      if(tab[i][0]-tab[i-1][0]==tab[i-1][0]-tab[i-2][0]) {
        aux = false;
      } else if (opcMetodo==2) {
        cout<<"Erro 1"<<endl;
        aux=true;
        break;
      } 
      if (tab[i-1][0]<=tab[i-2][0]) {
        cout<<"Erro 2"<<endl;
        aux=true;
        break;
      }
    }
  return aux;
}

void debug(double a, double b, double p) {
  cout<<"\n\n------ DEBBUG PARA DESMOS ------"<<endl;
  double i=a;
  p=(b-a)/p;
  while (i<=b+1) {
    //cout<<"f("<<i<<") = "; // Bonitinho
    cout<<i<<";"; // Para colocar no Desmos
    if (opcMetodo==1) cout<<fdd(i,n)<<endl;
    else cout<<fdf(i,n)<<endl;
    i+=p;
  }
  cout<<"---------- FIM DO DEBBUGER ----------"<<endl;
}

int main() {
  // Parte 1 - Escolher o método
  do {
    cout<<"Escolha o método: \n1. Método de Newton com uso de Diferenças Divididas \n2. Método de Gregory-Newton com uso de Diferenças Finitas\nOpção: ";
    cin>>opcMetodo;
    cout<<endl;
  } while (opcMetodo!=1 && opcMetodo!=2);
  
  // Parte 2 - Quantidade de pontos
  do {
    cout<<"Digite a quantidade de pontos para a interpolação\nn = ";
    cin>>k;
  } while (k<3);
  cout<<endl;
  
  // Parte 3 - Escolha de pontos
  do {
    cout<<"Insira os pontos:"<<endl;
    for (int i=0; i<k; i++) {
      cout<<"x"<<i<<" = ";
      cin>>tab[i][0];
      cout<<"y"<<i<<" = ";
      cin>>tab[i][1];
      cout<<endl;
    }
  } while(notCanUse());

  // Parte 4 - Escolhe o grau do polinômio 
  cout<<"O grau máximo do polinômio é de: "<<k-1<<endl;
  do {
    cout<<"\nInsira o grau do polinômio: ";
    cin>>n;
  } while(n>k-1 || n<=0);
  salvarDif();

  // Parte 5 - Debug para o Desmos
  debug(0,8,100);
  cout<<"\n"<<endl;
}