#include "abb.h"

//construtor
ArvBB::ArvBB(){
	this->root = abb_criavazia(); //construtor faz a inicialização de árvore vazia
}

//destrutor
ArvBB::~ArvBB(){
	reiniciaTree(); //chama método privado capaz de desalocar nós-dado alocados e apontados por root
}

//insere novo nó-dado
void ArvBB::insere(int v){
	if (this->root != NULL) 
		abb_insere(this->root, v); //inserção de demais nós-dado após root
	else
		this->root = abb_insere(this->root, v); //primeiro nó-dado inserido, root
}

//Desenha a árvore para exibição de nós-dados contidos
void ArvBB::displayTree(){ 
	no_dado* a = this->root; //inicia do root
	stack<no_dado*> globalStack; 
	globalStack.push(a);
	int nBlanks = 32;
	bool isRowEmpty = false;
	cout << "Visão encadeada de árvore: " << endl;
	
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
		} //fim-while do globalStack não vazio
		cout << endl;
		nBlanks = nBlanks / 2;
		while (localStack.empty() == false){
			globalStack.push(localStack.top()); //pega topo da pilha local e...
			localStack.pop(); //...e o remove em seguida
		}
	} //fim-while do isRowEmpty é falso
	cout << endl;
}

//retorna o nó-dado root
no_dado* ArvBB::getRoot(){
	return this->root;	
}

//libera e desaloca todos os nós da árvore, reiniciando em Null o ponteiro root
void ArvBB::reiniciaTree(){
	this->root = abb_libera(this->root);
}

//retorna true/false se árvore é vazia?
bool ArvBB::vazia(){
	return no_abb_vazio(this->root);
}

void ArvBB::displayRoot(){
	if (this->root != NULL) 
		cout << "Root -> info: " << this->root->info << endl;
	else
		cout << "Árvore vazia! \n";
}

//>>>>>>>>>> Métodos Privados - em apoio e execução interna (privada) <<<<<<<<<

// método de inicialização: retorna nó nulo (vazio) 
no_dado* ArvBB::abb_criavazia(){
	return NULL;
}

// método de criação: retorna nó criado (alocado)
no_dado* ArvBB::abb_cria(int c, no_dado* sae, no_dado* sad){
	no_dado* p=(no_dado*)malloc(sizeof(no_dado));
	if(p==NULL){
		cout << "FALHA DE ALOCAÇÃO EM MEMÓRIA!\n";
		exit(1);
	} 
	p->info = c;
	p->esq = sae;
	p->dir = sad;
	return p;
}

//Método de controle de inserção de novo nó-dado - garante lógica de inserção de ABB
no_dado* ArvBB::abb_insere(no_dado* a, int v){
	if (a == NULL) //primeira inserção, insira nó root
		a = abb_cria (v, NULL, NULL);
	else if (v < a->info)
		a->esq = abb_insere(a->esq,v); //insere como filho à esquerda
	else /*senão, temos: v >= a->info */
		a->dir = abb_insere(a->dir,v); //insere como filho à direita
	return a;
}

//Método recursivo que desaloca nós-dado da árvore, retornando NULL
no_dado* ArvBB::abb_libera(no_dado* a){
	if (!no_abb_vazio(a)){
		abb_libera(a->esq); /* libera sae */
		abb_libera(a->dir); /* libera sad */
		free(a); /* libera raiz */
	}
	return NULL;
}

//Método que verifica se um nó-dado é nulo?
bool ArvBB::no_abb_vazio(no_dado* a){
	return a == NULL;
}

bool ArvBB::abb_busca(int v) {
	no_dado* atual = root;
	while (atual != 0) {
		if (v == atual->info) {
			return true; // Encontrou o valor na árvore
		}
		else if (v < atual->info) {
			atual = atual->esq; // Valor procurado é menor, ir para a esquerda
		}
		else {
			atual = atual->dir; // Valor procurado é maior, ir para a direita
		}
	}
	return false; // Valor não encontrado na árvore
}

no_dado* ArvBB::abb_retira (no_dado* r, int v){
	if (r == NULL)	return NULL;
	
	else if (r->info > v)
		r->esq = abb_retira(r->esq, v);
		
	else if (r->info < v)
		r->dir = abb_retira(r->dir, v);
		
	else { /* achou o nó a remover */
		/* nó sem filhos */
		if (r->esq == NULL && r->dir == NULL) {
			free (r);
			r = NULL;
		}
		/* nó só tem filho à direita */
		else if (r->esq == NULL) {
			no_dado* t = r;
			r = r->dir;
			free (t);
		}
		/* só tem filho à esquerda */
		else if (r->dir == NULL) {
			no_dado* t = r;
			r = r->esq;
			free (t);	
		}
		/* nó tem os dois filhos */
		else {
			no_dado* f = r->esq;
			while (f->dir != NULL) {
			f = f->dir;
		}
		r->info = f->info; /* troca as informações */
		f->info = v;
		r->esq = abb_retira(r->esq,v);
		}
	}
 return r;
}

void ArvBB::retira(int v){
	if (this->root != NULL) 
		abb_retira(this->root, v); //inserção de demais nós-dado após root
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
		cout << atual->info << " "; // Imprimir o valor do nó atual
		PreOrdem(atual->esq); // Percorrer a subárvore esquerda
		PreOrdem(atual->dir); // Percorrer a subárvore direita
	}
}

void ArvBB::EmOrdem(no_dado* atual) {
	if (atual != 0) {
		EmOrdem(atual->esq); // Percorrer a subárvore esquerda
		cout << atual->info << " "; // Imprimir o valor do nó atual
		EmOrdem(atual->dir); // Percorrer a subárvore direita
	}
}

void ArvBB::PosOrdem(no_dado* atual) {
	if (atual != 0) {
		PosOrdem(atual->esq); // Percorrer a subárvore esquerda
		PosOrdem(atual->dir); // Percorrer a subárvore direita
		cout << atual->info << " "; // Imprimir o valor do nó atual
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

		cout << atual->info << " "; // Imprimir o valor do nó atual

		if (atual->esq != 0) {
			fila.push(atual->esq); // Adicionar o filho esquerdo na fila
		}

		if (atual->dir != 0) {
			fila.push(atual->dir); // Adicionar o filho direito na fila
		}
	}
}


void ArvBB::balancear() {
	// Percorre a árvore em ordem para obter uma lista de nós
	vector<no_dado*> lista = percorrerEmOrdem(root);

	// Reconstrói a árvore a partir da lista
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

