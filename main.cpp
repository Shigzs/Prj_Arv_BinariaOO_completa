#include "abb.h"
#include <conio.h>
using namespace std;

ArvBB tree; //instancia objeto conforme a classe, construtor faz root = NULL

void mensagem_arvore_vazia(bool t){
	cout << "Árvore está ";
	if(t)
		cout << "vazia\n";
	else
		cout << "não-vazia\n";
}
void printar_qtd_niveis(int t){
	t = tree.quantidadeNiveis();
	cout << t << "\n";;
}

void menu(){
	cout << "1 - Imprimir lista" << endl;
	cout << "2 - Inserir valor" << endl;
	cout << "3 - Imprimir Root" << endl;
	cout << "4 - Verificar se a árvore é vazia" << endl;
	cout << "5 - Reiniciar a árvore" << endl;
	cout << "6 - Destruir a árvore" << endl;
	cout << "7 - Buscar nó-dado" << endl;
	cout << "8 - Remover nó-dado" << endl;
	cout << "9 - Quantidade de Níveis" << endl;
	cout << "10 - Balancear a árvore" << endl;
	cout << "11 - Pre Ordem" << endl;
	cout << "12 - Em Ordem" << endl;
	cout << "13 - Pós Ordem" << endl;
	cout << "14 - Em nível" << endl;
	cout << "Escolha uma opção:  ";
}

int main(int argc, char** argv) {
	
	setlocale(LC_ALL, "Portuguese");
	cout<<"PROGRAMA ÁRVORE BINÁRIA DE BUSCA OO\n";

	
	int i,x;
	mensagem_arvore_vazia(tree.vazia());
	
	do{
		cout << endl << "=========================================================" << endl << endl;
		menu();
		cin >> i;
		switch(i){
			case 1:  //Imprime
				cout << "Mostrando estrutura de árvore:\n";
				tree.displayTree();
				break;
			case 2: //Inserir inicio
				cout << "Digite o valor a ser inserido: ";
				cin >> x;
				cout << "\nInserindo " << x << " na árvore...\n";
				tree.insere(x);
				break;
			case 3: // printar o root
				tree.displayRoot();
				break;
			case 4: //vazia
				mensagem_arvore_vazia(tree.vazia());
				break;
			case 5: //reiniciar a arvore
				cout << "Reiniciando a árvore!\n";
				tree.reiniciaTree();
				break;
			case 6:  //destrutor da árvore
				tree.~ArvBB();
				cout << "Árvore destruída (desalocada)\n";
				break;
			case 7: //
				cout << "Digite o valor a ser buscado: "; 
				cin >> x;
				cout << "\nBuscando " << x << " na árvore...\n";
				if(tree.abb_busca(x))
					cout << "Valor " << x << " encontrado!!\n";
				else
					cout << "Valor " << x << " não encontrado!!\n";
				break;
			case 8: // Remove um no dado
				cout << "Digite o valor a ser removido: "; 
				cin >> x;
				cout << "\nRemovendo " << x << " da árvore...\n";
				tree.retira(x);
				break;
			case 9: // Qtd Niveis
				cout << "Quantidade de níveis da árvore: ";
				printar_qtd_niveis(tree.quantidadeNiveis());
				break;
			case 10: // Balancear
				cout << "Balanceando a árvore... \n";
				tree.balancear();
				break;
			case 11: //
				tree.PreOrdem(tree.getRoot());
				break;
			case 12: //
				tree.EmOrdem(tree.getRoot());
				break;
			case 13: //
				tree.PosOrdem(tree.getRoot());
				break;
			case 14: //
				tree.EmNivel();
				break;
			default:
					cout << "Fim de programa!" << endl;
				break;
		}
	}while(i!=0);
	system("pause");
	return 0;
}


