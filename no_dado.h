class no_dado //defini��o struct para n�-dado de �rvore bin�ria de busca
{
	public:
		int info;
		no_dado* esq; //ponteiro para filho � esquerda
		no_dado* dir;
	public:	
		no_dado(int valor);
};
