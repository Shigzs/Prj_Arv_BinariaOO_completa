class no_dado //definição struct para nó-dado de árvore binária de busca
{
	public:
		int info;
		no_dado* esq; //ponteiro para filho à esquerda
		no_dado* dir;
	public:	
		no_dado(int valor);
};
