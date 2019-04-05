#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct No{
     int altura;
     int chave;
     struct No *pai;
     struct No *esq;
     struct No *dir;
     
}No;
/*
Criado pelo aluno João Marcelo Ravache Fernandes da Silva
Matricula: 403849
*/



/* Função que retorna a quantidade dos nos*/
int quantidadeNos(No *raiz){
  if(raiz == NULL){
    return 0;
  }else{
    int direita = quantidadeNos(raiz->dir);
    int esquerda = quantidadeNos(raiz->esq);
    return ((direita+esquerda)+1);
  }
}

/* Função que retorna o minimo valor da arvore*/
int minimo(No* raiz){
    if(raiz->esq == NULL){
        return raiz->chave;
    }else{
        return minimo(raiz->esq);
    }
}

/*Função que retorna o valor maximo da arvore*/
int maximo(No* raiz){
    if(raiz->dir == NULL){
        return raiz->chave;
    }else{
        return maximo(raiz->dir);
    }
}

/*Função de maximo entre dois inteiros*/
int max(int valor1, int valor2){
    if(valor1 > valor2){
        return valor1;
    }else{
        return valor2;
    }
}

/*Função que retorna a altura de um no*/
int alturaNo(No *raiz){
  if(raiz == NULL){
    return 0;
  }else{
    return (raiz->altura);
  }
}

/*Função que retorna o balaceamento do no*/
int balancearNo(No *raiz){
  
  int alturaDireita,alturaEsquerda;
  alturaEsquerda = alturaNo(raiz->esq);
  alturaDireita = alturaNo(raiz->dir);
  return (alturaEsquerda - alturaDireita);
}

/*Rotação a Direita*/
void rotacaoDireita(No *raiz){
  
  int chaveRaiz = raiz->chave;
  raiz->chave = raiz->esq->chave;
  raiz->esq->chave = chaveRaiz;


    No *y;

    y = raiz->esq;
    raiz->esq = y->esq;
    y->esq = y->dir;
    y->dir = raiz->dir;
    raiz->dir = y;
  raiz->altura = (max(alturaNo(raiz->esq),alturaNo(raiz->dir))+1);
  raiz->dir->altura = (max(alturaNo(raiz->dir->esq),alturaNo(raiz->dir->dir))+1);
}

/*Rotação a Esquerda*/
void rotacaoEsquerda(No *raiz){
  
  int chaveRaiz = raiz->chave;
  raiz->chave = raiz->dir->chave;
  raiz->dir->chave = chaveRaiz;

  No *y;

  y = raiz->dir;
  raiz->dir = y->dir;
  y->dir = y->esq;
  y->esq = raiz->esq;
  raiz->esq = y;

  raiz->altura = (max(alturaNo(raiz->esq),alturaNo(raiz->dir))+1);
  raiz->esq->altura = (max(alturaNo(raiz->esq->esq),alturaNo(raiz->esq->dir))+1);

}

/*Dupla Rotação a Direita*/
void duplaRotacaoDireita(No* raiz){
  rotacaoEsquerda(raiz->esq);
  rotacaoDireita(raiz);
}

/*Dupla Rotação a Esquerda*/
void duplaRotacaoEsquerda(No* raiz){
  rotacaoDireita(raiz->dir);
  rotacaoEsquerda(raiz);
}

/*Função retorna quando ja existir valor na arvore*/
No *retorna(No *raiz){
  if(raiz->pai != NULL){
    return retorna(raiz->pai);
  }else{
    return raiz;
  }
}

/*Função que balancea a arvore subindo a mesma*/
No *balancear(No *raiz){
  int alturaL = alturaNo(raiz->esq);
  int alturaR = alturaNo(raiz->dir);
  raiz->altura = (max(alturaL,alturaR)+1);
  if(raiz != NULL){
    if((balancearNo(raiz)) == 2){
      if((balancearNo(raiz->esq) == -1)){
        duplaRotacaoDireita(raiz);
      }else{
        rotacaoDireita(raiz);
      }
    }else if((balancearNo(raiz)) == -2){
      if((balancearNo(raiz->dir)) == 1){
        duplaRotacaoEsquerda(raiz);
      }else{
        rotacaoEsquerda(raiz);
      }
    }
    
    if(raiz->pai != NULL){
      
      balancear(raiz->pai);
    }
  }
  return raiz;
}

/*Função Inserir na arvore*/
No *inserir(No *raiz, int valor){
  if(raiz == NULL){
      No *novo = (No*)malloc(sizeof(No));
      novo->altura = 1;
      novo->chave = valor;
      novo->dir = NULL;
      novo->esq = NULL;
      novo->pai = NULL;
      
      raiz = novo;
  }else{
    if(raiz->chave == valor){
      cout<<"valor ja existe!"<<endl;
      return retorna(raiz);
    }else{
      if(raiz->chave > valor){
        if(raiz->esq == NULL){
          No *novo = (No*)malloc(sizeof(No));
          novo->altura = 1;
          novo->chave = valor;
          novo->dir = NULL;
          novo->esq = NULL;
          novo->pai = raiz;
          raiz->esq = novo;
          raiz->altura = (2-alturaNo(raiz->dir));
        }else{
          inserir(raiz->esq,valor);
        }
      }else{
        if(raiz->dir == NULL){
          No *novo = (No*)malloc(sizeof(No));
          novo->altura = 1;
          novo->chave = valor;
          novo->dir = NULL;
          novo->esq = NULL;
          novo->pai = raiz;
          raiz->dir = novo;
          raiz->altura = (alturaNo(raiz->esq)-2);
        }else{
          inserir(raiz->dir,valor);
        }
      }
    }
  }
  return balancear(raiz);
}

/*Função imprime em Ordem*/
void emOrdem(No *raiz){
  if(raiz != NULL){
    emOrdem(raiz->esq);
    cout<<raiz->chave<<endl;
    emOrdem(raiz->dir);
  }
}

/*Função imprime em pre Ordem*/
void preOrdem(No *raiz){
  if(raiz != NULL){
    cout<<raiz->chave<<endl;
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
  }
}

/*Função imprime em pos Ordem*/
void posOrdem(No *raiz){
  if(raiz != NULL){
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    cout<<raiz->chave<<endl;
  }
}

/*Objeto contendo o no raiz da Arvore*/
class Arvore{
  public:
    No *raiz = NULL;
    void inserirAVL(int valor);
    void emOrdemAVL();
    void preOrdemAVL();
    void posOrdemAVL();
    int minimoAVL();
    int maximoAVL();
    int alturaAVL();
    int quantidadeNosAVL();
};

void Arvore::inserirAVL(int valor){
  raiz = inserir(raiz,valor);
}

void Arvore::emOrdemAVL(){
  emOrdem(raiz);
}

void Arvore::preOrdemAVL(){
  preOrdem(raiz);
}

void Arvore::posOrdemAVL(){
  posOrdem(raiz);
}

int Arvore::minimoAVL(){
  return minimo(raiz);
}

int Arvore::maximoAVL(){
  return maximo(raiz);
}

int Arvore::alturaAVL(){
  return alturaNo(raiz);
}

int Arvore::quantidadeNosAVL(){
  return quantidadeNos(raiz);
}

int main(){

  Arvore raiz;
  int opcao = 0;
  while(opcao != 8){
    cout<<"-----------------------------------------"<<endl;
    cout<<"Imprementação da Arvore AVL"<<endl;
    cout<<"-----------------------------------------"<<endl;
    cout<<"1. Inserir na arvore."<<endl;
    cout<<"2. percurso pre-ordem."<<endl;
    cout<<"3. percurso em-ordem."<<endl;
    cout<<"4. percurso pos-ordem."<<endl;
    cout<<"5. altura da Arvore."<<endl;
    cout<<"6. numero de folhas da Arvore."<<endl;
    cout<<"7. valor maximo e minimo da Arvore."<<endl;
    cout<<"8. Sair."<<endl;
    cout<<"Digite sua opção:"<<endl;
    cin>>opcao;
    switch (opcao)
    {
      case 1:
        cout<<"digite o valor..."<<endl;
        int valor;
        cin>>valor;
        raiz.inserirAVL(valor);
        break;
      case 2:
        cout<<"percurso em pre-ordem..."<<endl;
        raiz.preOrdemAVL();
        break;
      case 3:
        cout<<"percurso em em-ordem..."<<endl;
        raiz.emOrdemAVL();
        break;
      case 4:
        cout<<"percurso em pos-ordem..."<<endl;
        raiz.posOrdemAVL();
        break;
      case 5:
        cout<<"altura da arvore..."<<endl;
        cout<<raiz.alturaAVL()<<endl;
        break;
      case 6:
        cout<<"numero de folhas da arvore:"<<endl;
        cout<<raiz.quantidadeNosAVL()<<endl;  
        break;
      case 7:
        cout<<"valor maximo da arvore:"<<endl;
        cout<<raiz.maximoAVL()<<endl;
        cout<<"valor minimo da arvore:"<<endl;
        cout<<raiz.minimoAVL()<<endl;
        break;
      case 8:
        cout<<"Saindo..."<<endl;
        break;
      default:
        cout<<"Numero Invalido!"<<endl;
        break;
    }
  }
}