/*
(david n)

Para resolver este problema basta saber usar a fun��o sort que est� no algorithm:
    - Para cada concorrente guardamos o seu nome e a sua pontua��o num struct.
    - Guardamos todos os concorrentes numa lista de N elementos
    - Ordenamos a lista usando sort, de acordo com uma fun��o de compara��o costumizada para a struct dos concorrentes:
      essa fun��o ordena os concorrentes por n�mero de pontos, caso o n�mero de pontos seja diferente. Caso contr�rio ordena por ordem alfab�tica.
    - Agora s� falta imprimir a lista, que j� est� ordenada

    Complexidade: O(NP+Nlog N)
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

struct Concorrente{
	string nome;
	int pontos;
};

bool compare(Concorrente lhs, Concorrente rhs) {
	if(lhs.pontos!=rhs.pontos){
		return lhs.pontos>rhs.pontos;
	}else{
		return lhs.nome<rhs.nome;
	}
}

int main(){
	int n,p;
	scanf("%d %d", &n, &p);
	Concorrente lista[n];
	for(int i=0;i<n;i++){
		cin >> lista[i].nome;
		int l = 0;
		for(int j=0;j<p;j++){
			int k;
			scanf("%d", &k);
			l += k;
		}
		lista[i].pontos = l;
	}
	sort(lista, lista+n, compare);
	for(int k=0;k<n;k++){
		cout << lista[k].nome << " " << lista[k].pontos << endl;
	}
	return 0;
}
