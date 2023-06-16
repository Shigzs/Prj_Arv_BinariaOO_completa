#include "abb.h"

//construtor
ArvBB::ArvBB(){
	this->root = abb_criavazia(); //construtor faz a inicializa��o de �rvore vazia
}

//destrutor
ArvBB::~ArvBB(){
	reiniciaTree(); //chama m�todo privado capaz de desalocar n�s-dado alocados e apontados por root
}

//insere novo n�-dado
void ArvBB::insere(int v){
	if (this->root != NULL) 
		abb_insere(this->root, v); //inser��o de demais n�s-dado ap�s root
	else
		this->root = abb_insere(this->root, v); //primeiro n�-dado inserido, root
}

//Desenha a �rvore para exibi��o de n�s-dados contidos
void ArvBB::displayTree(){ 
	no_dado* a = this->root; //inicia do root
	stack<no_dado*> globalStack; 
	globalStack.push(a);
	int nBlanks = 32;
	bool isRowEmpty = false;
	cout << "Vis�o encadeada de �rvore: " << endl;
	
	while (isRowEmpty == false){
		stack<no_dado*> localStack; 
		isRowEmpty = true;
	
		for (int j=0; j<nBlanks; j++)
			cout << " ";
	
		while (globalStack.empty()== false){
			no_dado* temp = globalStack.top(); //pega topo da pilha global e...
			globalStack.pop(); //...e o remove em seguida
			
			if (temp != NULL){
				cout << temp->info;
				localStack.push(temp->esq);
				localStack.push(temp->dir);
				
				if ((temp->esq != NULL) || (temp->dir != NULL)){
					isRowEmpty = false;
				}	
			}else{
				cout << "-";	
				localStack.push(NULL);
				localStack.push(NULL);	
			}
			int fim = nBlanks*2 - 1;
			for (int j=0; j<fim; j++)
				cout << " ";
		} //fim-while do globalStack n�o vazio
		cout << endl;
		nBlanks = nBlanks / 2;
		while (localStack.empty() == false){
			globalStack.push(localStack.top()); //pega topo da pilha local e...
			localStack.pop(); //...e o remove em seguida
		}
	} //fim-while do isRowEmpty � falso
	cout << endl;
}

//retorna o n�-dado root
no_dado* ArvBB::getRoot(){
	return this->root;	
}

//libera e desaloca todos os n�s da �rvore, reiniciando em Null o ponteiro root
void ArvBB::reiniciaTree(){
	this->root = abb_libera(this->root);
}

//retorna true/false se �rvore � vazia?
bool ArvBB::vazia(){
	return no_abb_vazio(this->root);
}

void ArvBB::displayRoot(){
	if (this->root != NULL) 
		cout << "Root -> info: " << this->root->info << endl;
	else
		cout << "�rvore vazia! \n";
}

//>>>>>>>>>> M�todos Privados - em apoio e execu��o interna (privada) <<<<<<<<<

// m�todo de inicializa��o: retorna n� nulo (vazio) 
no_dado* ArvBB::abb_criavazia(){
	return NULL;
}

// m�todo de cria��o: retorna n� criado (alocado)
no_dado* ArvBB::abb_cria(int c, no_dado* sae, no_dado* sad){
	no_dado* p=(no_dado*)malloc(sizeof(no_dado));
	if(p==NULL){
		cout << "FALHA DE ALOCA��O EM MEM�RIA!\n";
		exit(1);
	} 
	p->info = c;
	p->esq = sae;
	p->dir = sad;
	return p;
}

//M�todo de controle de inser��o de novo n�-dado - garante l�gica de inser��o de ABB
no_dado* ArvBB::abb_insere(no_dado* a, int v){
	if (a == NULL) //primeira inser��o, insira n� root
		a = abb_cria (v, NULL, NULL);
	else if (v < a->info)
		a->esq = abb_insere(a->esq,v); //insere como filho � esquerda
	else /*sen�o, temos: v >= a->info */
		a->dir = abb_insere(a->dir,v); //insere como filho � direita
	return a;
}

//M�todo recursivo que desaloca n�s-dado da �rvore, retornando NULL
no_dado* ArvBB::abb_libera(no_dado* a){
	if (!no_abb_vazio(a)){
		abb_libera(a->esq); /* libera sae */
		abb_libera(a->dir); /* libera sad */
		free(a); /* libera raiz */
	}
	return NULL;
}

//M�todo que verifica se um n�-dado � nulo?
bool ArvBB::no_abb_vazio(no_dado* a){
	return a == NULL;
}

bool ArvBB::abb_busca(int v) {
	no_dado* atual = root;
	while (atual != 0) {
		if (v == atual->info) {
			return true; // Encontrou o valor na �rvore
		}
		else if (v < atual->info) {
			atual = atual->esq; // Valor procurado � menor, ir para a esquerda
		}
		else {
			atual = atual->dir; // Valor procurado � maior, ir para a direita
		}
	}
	return false; // Valor n�o encontrado na �rvore
}

no_dado* ArvBB::abb_retira (no_dado* r, int v){
	if (r == NULL)	return NULL;
	
	else if (r->info > v)
		r->esq = abb_retira(r->esq, v);
		
	else if (r->info < v)
		r->dir = abb_retira(r->dir, v);
		
	else { /* achou o n� a remover */
		/* n� sem filhos */
		if (r->esq == NULL && r->dir == NULL) {
			free (r);
			r = NULL;
		}
		/* n� s� tem filho � direita */
		else if (r->esq == NULL) {
			no_dado* t = r;
			r = r->dir;
			free (t);
		}
		/* s� tem filho � esquerda */
		else if (r->dir == NULL) {
			no_dado* t = r;
			r = r->esq;
			free (t);	
		}
		/* n� tem os dois filhos */
		else {
			no_dado* f = r->esq;
			while (f->dir != NULL) {
			f = f->dir;
		}
		r->info = f->info; /* troca as informa��es */
		f->info = v;
		r->esq = abb_retira(r->esq,v);
		}
	}
 return r;
}

void ArvBB::retira(int v){
	if (this->root != NULL) 
		abb_retira(this->root, v); //inser��o de demais n�s-dado ap�s root
}

int ArvBB::qtdNiveis(no_dado* atual, int nivel) {
	if (atual == 0) {
		return nivel;
	}
	int nivel_esquerda = qtdNiveis(atual->esq, nivel + 1);
	int nivel_direita = qtdNiveis(atual->dir, nivel + 1);
	return max(nivel_esquerda, nivel_direita);
}

int ArvBB::quantidadeNiveis() {
	return qtdNiveis(root, 0);
}

void ArvBB::PreOrdem(no_dado* atual) {
	if (atual != 0) {
		cout << atual->info << " "; // Imprimir o valor do n� atual
		PreOrdem(atual->esq); // Percorrer a sub�rvore esquerda
		PreOrdem(atual->dir); // Percorrer a sub�rvore direita
	}
}

void ArvBB::EmOrdem(no_dado* atual) {
	if (atual != 0) {
		EmOrdem(atual->esq); // Percorrer a sub�rvore esquerda
		cout << atual->info << " "; // Imprimir o valor do n� atual
		EmOrdem(atual->dir); // Percorrer a sub�rvore direita
	}
}

void ArvBB::PosOrdem(no_dado* atual) {
	if (atual != 0) {
		PosOrdem(atual->esq); // Percorrer a sub�rvore esquerda
		PosOrdem(atual->dir); // Percorrer a sub�rvore direita
		cout << atual->info << " "; // Imprimir o valor do n� atual
	}
}

void ArvBB::EmNivel() {
	if (root == 0) {
		return;
	}

	queue<no_dado*> fila;
	fila.push(root);

	while (!fila.empty()) {
		no_dado* atual = fila.front();
		fila.pop();

		cout << atual->info << " "; // Imprimir o valor do n� atual

		if (atual->esq != 0) {
			fila.push(atual->esq); // Adicionar o filho esquerdo na fila
		}

		if (atual->dir != 0) {
			fila.push(atual->dir); // Adicionar o filho direito na fila
		}
	}
}


void ArvBB::balancear() {
	// Percorre a �rvore em ordem para obter uma lista de n�s
	vector<no_dado*> lista = percorrerEmOrdem(root);

	// Reconstr�i a �rvore a partir da lista
	root = listaParaArvore(lista, 0, lista.size() - 1);
}

no_dado* ArvBB::listaParaArvore(vector<no_dado*>& lista, int inicio, int fim) {
	if (inicio > fim) {
		return 0;
	}

	int meio = (inicio + fim) / 2;
	no_dado* raiz = lista[meio];

	raiz->esq = listaParaArvore(lista, inicio, meio - 1);
	raiz->dir = listaParaArvore(lista, meio + 1, fim);

	return raiz;
}

vector<no_dado*> ArvBB::percorrerEmOrdem(no_dado* atual) {
	vector<no_dado*> lista;
	stack<no_dado*> pilha;

	while (!pilha.empty() || atual != 0) {
		if (atual != 0) {
			pilha.push(atual);
			atual = atual->esq;
		}
		else {
			atual = pilha.top();
			pilha.pop();
			lista.push_back(atual);
			atual = atual->dir;
		}
	}

	return lista;
}

