#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

time_t t1;
time_t t2;
int tempo_total;

typedef struct {
  int eBomba;
  int foiAberta;
  int vizinhos;
  int bandeira;
} celula;

typedef struct {
  int tempo;
  string nome;
} jogador;

celula jogo [15][30];
int taml, tamc;
int l;
int c;
int contatempo = 0;
int modoAnterior;
jogador recordistas[5];
jogador atual;

void records(){
  jogador aux;
  jogador aux2;
  int i = 0;
  int j = 0;

  for(i = 0; i < 5; i++){
    if(recordistas[i].tempo > 0) {
      if(atual.tempo < recordistas[i].tempo){
        aux = recordistas[i];
        recordistas[i] = atual;
        break;
        }
      } else {
      recordistas[i] = atual;
      i = 5;
      }
      }
    
      for(j = i; j < 4; j++){
          aux2 = recordistas[j+1];
          recordistas[j+1] = aux;
          aux = aux2;
        }
}

void inicializarJogo (){
  for(l = 0; l < taml; l++){
    for(c = 0; c < tamc; c++){
      jogo[l][c].eBomba = 0;
      jogo[l][c].foiAberta = 0;
      jogo[l][c].vizinhos = 0;
      jogo[l][c].bandeira = 0;
    }  
  }  
}


// procedimento para sortear n bombas
void sortearBombas(int n){
  int i;
  srand(time(NULL));
  for(i = 1; i <= n; i++){
    l = rand() % taml;
    c = rand() % tamc;
    if(jogo[l][c].eBomba == 0)
      jogo[l][c].eBomba = 1;
    else
      i--;
  }
}
int coordenadaValida (int l, int c){
  if (l >= 0 && l < taml && c >= 0 && c < tamc){
    return 1;
  }
  else {
    return 0;
  } 
}

int quantbombasVizinhas (int l, int c){
  int quantidade = 0;

  if (coordenadaValida (l - 1, c) && jogo[l-1][c].eBomba){
    quantidade++;  
  }
  if (coordenadaValida (l + 1, c) && jogo[l+1][c].eBomba){
    quantidade++;  
  }
  if (coordenadaValida (l, c + 1) && jogo[l][c+1].eBomba){
    quantidade++;  
  }
  if (coordenadaValida (l, c - 1) && jogo[l][c-1].eBomba){
    quantidade++;  
  }
  if (coordenadaValida (l - 1, c - 1) && jogo[l-1][c-1].eBomba){
    quantidade++;  
  }
  if (coordenadaValida (l - 1, c + 1) && jogo[l-1][c+1].eBomba){
    quantidade++;  
  }
  if (coordenadaValida (l + 1, c - 1) && jogo[l+1][c-1].eBomba){
    quantidade++;  
  }
  if (coordenadaValida (l + 1, c + 1) && jogo[l+1][c+1].eBomba){
    quantidade++;  
  }

  return quantidade;
  
}

void contarBombas () {
  for(l = 0; l < taml; l++){
    for(c = 0; c < tamc; c++){
      jogo[l][c].vizinhos = quantbombasVizinhas (l, c);
    }  
  }  
  
}

void imprimir(){

  cout << "\n\n\t  ";
  if (tamc > 10){
    cout << "\t";
  }
  for(c = 0; c < tamc; c++){
    cout << " " << c << " "; 
  }
  
  cout << "\n\t";

  //Quando for no modo fácil
    if(tamc == 10){
      for(c = 0; c < tamc+1; c++){
        cout << "---"; 
      }
    }
    
    //Quando for no modo intermediário
    if(tamc == 15){
      for(c = 0; c < tamc+3; c++){
        cout << "---"; 
      }
    }
    //Quando for no modo difícil
    if(tamc == 30){
      for(c = 0; c < tamc+8; c++){
        cout << "---"; 
    }
  }
  
  cout << "\n";
  
  for(l = 0; l < taml; l++){

    if(tamc > 10 && l < 10){
      cout << "\t" << l << "  |";
    }else{
       cout << "\t" << l << " |";
    }
    
    
    for(c = 0; c < tamc; c++){
      
      if(jogo[l][c].foiAberta == 0){
         if(jogo[l][c].bandeira == 1) 
            cout << "P";
      }
      
      if(jogo[l][c].foiAberta){
        if(jogo[l][c].eBomba){
           cout << "*";
        }else {
        cout << jogo[l][c].vizinhos;
        } 
      }else {
        cout << " ";
      } 
    
      if(c > 9){
        cout << "  |";
      }else
        cout << " |";
      
    } 
    //Quando for no modo fácil
    if(tamc == 10){
      cout << "\n\t";
      for(c = 0; c < tamc+1; c++){
        cout << "---"; 
      }
      cout << "\n";
    }
    
    //Quando for no modo intermediário
    if(tamc == 15){
      cout << "\n\t";
      for(c = 0; c < tamc+3; c++){
        cout << "---"; 
      }
      cout << "\n";
    }
    //Quando for no modo difícil
    if(tamc == 30){
      cout << "\n\t";
      for(c = 0; c < tamc+8; c++){
        cout << "---"; 
    }
    cout << "\n";
  }
    //cout << "\n\t---------------------------------\n";
  }  
  
}

void abrirCelula(int l, int c){
  if(coordenadaValida(l,c) == 1 && jogo[l][c].foiAberta == 0){
    jogo[l][c].foiAberta = 1;
    if(jogo[l][c].vizinhos == 0 && jogo[l][c].eBomba == 0){
      
      abrirCelula(l-1, c);
      abrirCelula(l+1, c);
      abrirCelula(l, c+1);
      abrirCelula(l, c-1);
      abrirCelula(l-1, c-1);
      abrirCelula(l-1, c+1);
      abrirCelula(l+1, c-1);
      abrirCelula(l+1, c+1);
      
    }
  }
}

int ganhou(){
  int quantidade = 0;
  
  for(l = 0; l < taml; l++){
    for(c = 0; c < tamc; c++){
      if((jogo[l][c].foiAberta == 0 && jogo[l][c].eBomba == 0) || (jogo[l][c].eBomba == 1 && jogo[l][c].foiAberta == 0))
        quantidade++;
    }  
  } 
  return quantidade;
}

void jogar(){
  int linha, coluna, acao;
  int  BandeiraCerta = 0;
 
  do{

    if(contatempo == 1){
      time(&t1);
    }
    
    imprimir();
    cout << "Digite 1 para abrir uma célula ou 2 para inserir uma bandeira: ";
    cin >> acao;
    
    if(acao == 1){
      do {
        cout << "Digite as coordenadas de linha e coluna para abrir uma celula: ";
        cin >> linha  >> coluna;
        contatempo++;
    
        if(coordenadaValida(linha, coluna) == 0 || jogo[linha][coluna].foiAberta == 1)
          cout << "Coordenada invalida ou ja aberta! \n";
        
      }while(coordenadaValida(linha, coluna) == 0 || jogo[linha][coluna].foiAberta == 1);
      
    abrirCelula(linha, coluna);
      
    }else if(acao == 2){
      do {
        cout << "Digite as coordenadas de linha e coluna da bandeira: ";
        cin >> linha  >> coluna;
    
        if(coordenadaValida(linha, coluna) == 0 || jogo[linha][coluna].foiAberta == 1 || jogo[linha][coluna].bandeira == 1)
          cout << "Coordenada invalida ou ja possui uma bandeira! \n";
        else {
          jogo[linha][coluna].bandeira = 1;
          jogo[linha][coluna].foiAberta = 0;
        }    
      }while(coordenadaValida(linha, coluna) == 0 || jogo[linha][coluna].bandeira == 0);

      if(jogo[linha][coluna].bandeira == 1 && jogo[linha][coluna].eBomba == 1 ){
        BandeiraCerta++;
      }
      
    }

    if(jogo[linha][coluna].foiAberta == 1 && jogo[linha][coluna].eBomba == 1)
      break;

    if(BandeiraCerta == 10)
      break;
    //}while(jogo[linha][coluna].eBomba != 1 && jogo[linha][coluna].foiAberta == 0 || BandeiraCerta == 10);
     //}while(ganhou() != 0 && jogo[linha][coluna].eBomba == 0 || BandeiraCerta != 10 || (jogo[linha][coluna].eBomba == 1 && jogo[linha][coluna].foiAberta == 1));
      }while((jogo[linha][coluna].foiAberta == 1 && jogo[linha][coluna].eBomba == 0) || (jogo[linha][coluna].foiAberta == 0 && jogo[linha][coluna].eBomba == 1) || (jogo[linha][coluna].bandeira == 1 && jogo[linha][coluna].foiAberta == 0) || (BandeiraCerta < 
 11) || ganhou() != 0 && jogo[linha][coluna].eBomba == 0);

  imprimir() ;
     
  if(jogo[linha][coluna].eBomba == 1 && jogo[linha][coluna].foiAberta == 1){
    cout << "\n\t------------------------------------------\n";
    cout << "\n\t " << "AH, NÃO...UMA BOMBA. VOCÊ PERDEU! :(\n";
    cout << "\n\t------------------------------------------\n";
    
    //time(&t2);
    //tempo_total = t2 - t1;
    //cout << "\n tempo 1: "<< t1 << "\n tempo 2: " << t2 << "\n tempo total: " << tempo_total << endl; 
    
    }
  if (ganhou() == 0 || BandeiraCerta == 10){
    cout << "\n\t---------------------------------\n";
    cout << "\t\t\nPARABÉNS! VOCÊ GANHOU! :D \n";
    cout << "\n\t---------------------------------\n";

    time(&t2);
    tempo_total = t2 - t1;
    cout << "\n tempo total: " << tempo_total << endl; 
    }
  

  
}

int main(int argc, char *argv[ ]) {
  /*
  //ponteiro para struct que armazena data e hora  
  struct tm *data_hora_atual;     
  
  //variável do tipo time_t para armazenar o tempo em segundos  
  time_t segundos;
  
  //obtendo o tempo em segundos  
  time(&segundos);   
  
  //para converter de segundos para o tempo local  
  //utilizamos a função localtime  
  data_hora_atual = localtime(&segundos);

  /*Printa a hora atual
  cout << data_hora_atual->tm_hour << ":" << data_hora_atual->tm_min << ":" << data_hora_atual->tm_sec;
  */
  int opcao;
  char *modo;
  //int modoAnterior;
  //int *ptr;
  recordistas[5].tempo = 0;

  modo = argv[1];

  if (strcmp(modo, "-d <b") == 0 || strcmp(modo,"--difficulty <beginner") == 0){
    modoAnterior = 1;
    //ptr = &modoAnterior
    taml = 10;
    tamc = 10;
    jogo [10][10];
    l = 10;
    c = 10;
      
    do{
    inicializarJogo();
    sortearBombas(10);
    contarBombas();
    cout << "CAMPO MINADO \n";
    jogar();

    cout << "Digite 1 para jogar novamente neste modo ou 0 para sair: ";
    cin >> opcao;
    }while(opcao == 1);

    opcao == 0;
  }

  if (strcmp(modo, "-d <i") == 0 || strcmp(modo,"--difficulty <intermediary") == 0){
    modoAnterior = 2;
    taml = 15;
    tamc = 15;
    jogo [15][15];
    l = 15;  
    c = 15;
      
    do{
    inicializarJogo();
    sortearBombas(40);
    contarBombas();
    cout << "CAMPO MINADO \n";
    jogar();

    cout << "Digite 1 para jogar novamente neste modo ou 0 para sair: ";
    cin >> opcao;
    }while(opcao == 1);

    opcao == 0;
  }
  if (strcmp(modo, "-d <a") == 0 || strcmp(modo,"--difficulty <advanced") == 0){
    modoAnterior = 3;
    taml = 15;
    tamc = 30;
    jogo [15][30];
    l = 15;
    c = 30;
      
    do{
    inicializarJogo();
    sortearBombas(100);
    contarBombas();
    cout << "CAMPO MINADO \n";
    jogar();

    cout << "Digite 1 para jogar novamente neste modo ou 0 para sair: ";
    cin >> opcao;
    }while(opcao == 1);

    opcao == 0;
  }
  if (strcmp(modo, "-h") == 0 ||strcmp(modo,"--help") == 0){
    cout << "\n\n\t\t\t\t\tOLÁ! SEJA BEM-VIND@ A SESSÃO DE AJUDA! :D\n";
    cout << "\t\t\t\t\t\t-----------------------------------\n";
    cout << "\t\t\t\t\t\t\t\tPRIMEIROS PASSOS:\n";
    cout << "\t\t\t\t\t\t-----------------------------------\n\n";
    cout << "Para dar innício ao jogo, escolha qual modo deseja jogar (beginner, intermediary ou advanced) digitando entre áspas os seguintes comandos e teclando enter em seguida:\n\n";
    cout << "-d <b ou --difficulty <beginner (para iniciar no modo iniciante, com uma área que possui 10 linhas e 10 colunas com um total de 10 minas);\n\n";
    cout << "-d <i ou --difficulty <intermediary (para iniciar no modo intermediário, com uma área que possui 15 linhas e 15 colunas com um total de 40 minas e a primeira ação revelar sempre revela uma posição vazia);\n\n";
cout << "-d <a ou --difficulty <advanced (para iniciar no modo avançado, com uma área que possui 15 linhas e 30 colunas com um total de 100 minas e a primeira ação revelar sempre revela um número).\n\n";
    cout << "\n\t\t\t\t\t\t-----------------------------------\n";
    cout << "\t\t\t\t\t\t\t\tREGRAS DO JOGO:\n";
    cout << "\t\t\t\t\t\t-----------------------------------\n\n";
    cout << "-> Para revelear um espaço ou marcar o espaço com uma bandeira, digite as coordenadas de  linha e coluna do espaço desejado (necessariamente nessa ordem);\n\n";
    cout << "-> Caso revele todos os espaços que não possuem minas ou marque com uma bandeira a posição de todas as minas existentes, você vence o jogo;\n\n";
    cout << "-> Caso revele a posição de uma bomba, você perde o jogo;\n\n";
    cout << "-> Para jogar novamente no mesmo modo, digite 1. Mas, caso queira sair do jogo, mudar de modo, ver as regras novamente (-h ou --help), ou acessar os records (comando: -r ou --records, entre áspas), clique 0.\n\n";
    cout << "\t\t\t\t\t\t\t-----------------------------\n";
    cout << "\t\t\t\t\t\t\t\tBOM JOGO! SE DIVIRTA! :D\n";
    
  }
  if (strcmp(modo, "-r") == 0 || strcmp(modo,"--records") == 0){
    if (modoAnterior == 1){
      cout << "------------------------------------\n";
      cout << "RECORDISTAS DO MODO INICIANTE:\n";
      cout << "------------------------------------\n";
    }
    if (modoAnterior == 2){
      cout << "------------------------------------\n";
      cout << "RECORDISTAS DO MODO INTERMEDIÁRIO:\n";
      cout << "------------------------------------\n";
    }
    if (modoAnterior == 3){
      cout << "------------------------------------\n";
      cout << "RECORDISTAS DO MODO AVANÇADO:\n";
      cout << "------------------------------------\n";
    } else {
      cout << "------------------------------------\n";
      cout << ":\n";
      cout << "------------------------------------\n";
    }
    
  }
  
  
 
  return 0;
}
