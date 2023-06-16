//abb.h
//Define a classe e protótipo de métodos OO para biblioteca de árvore binária de busca (abb)
//Por Irineu Lima, ED2 - FeMASS

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <vector>
#include <queue>
#include <stack> //aplicada para função abb_displayTree - contâiner C++ LIFO
#include "no_dado.h"


using namespace std;

class ArvBB{
	
	private:
		no_dado* root; //controle de ponteiro para nó-dado raiz
	
	public:
		ArvBB(); //Construtor - método de mesmo nome da classe, não se usa a previsão de retorno
		~ArvBB(); //Destrutor - método executado ao fim ou término de uso do objeto de classe
		void insere(int v);
		void displayTree();
		no_dado* getRoot();
		void reiniciaTree();
		bool vazia();
		void displayRoot();
		bool abb_busca(int v);
		void retira(int v);
		int quantidadeNiveis();
		void balancear();
		void PreOrdem(no_dado* atual);
		void EmOrdem(no_dado* atual);
		void PosOrdem(no_dado* atual);
		void EmNivel();
		
		
	private:
		no_dado* abb_criavazia();
		no_dado* abb_cria (int c, no_dado* e, no_dado* d);
		no_dado* abb_insere(no_dado* a, int v);
		no_dado* abb_libera(no_dado* a);
		bool no_abb_vazio(no_dado* a);
		no_dado* abb_retira (no_dado* r, int v);
		int qtdNiveis(no_dado* atual, int nivel);
		no_dado* listaParaArvore(vector<no_dado*>& lista, int inicio, int fim);
		vector<no_dado*> percorrerEmOrdem(no_dado* atual);
		
};

