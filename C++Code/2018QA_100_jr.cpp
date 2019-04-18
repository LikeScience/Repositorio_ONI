/*
(joaorico)

Explicacao mais detalhada no loop:
http://oni.dcc.fc.up.pt/loop/solucoes/2018/qualificacao/prob_a.html

Quardamos as paginas num vector. O(n)
Ordenamos esse vector O(n log n).
Somamos as paginas dos primeiros livros ate termos o numero necessario O(n)


Complexidade: O(n logn)
*/

#include <stdio.h>
#include <vector>
#include <algorithm> // sort()

using namespace std;

int main() {
    int n, z;
    scanf("%d %d", &n, &z);

    int livro;
    vector<int> livros;

    for (int i = 0; i < n; i++) {
        scanf("%d", &livro);
        livros.push_back(livro); // inicialmente nao lemos nenhum
    }

    sort(livros.begin(), livros.end()); // ordenar livros por numero crescente de paginas

    int soma = 0;
    int lidos = 0;
    while(soma < z){
        soma += livros[lidos];
        lidos++;
    }

    printf("%d\n", lidos); // imprimir a resposta

    return 0;
}
