/*
ano: 2014
fase: qualificação
problema: C
pontos: 100
autor: João Rico
linguagem: c++
tópicos: programação dinâmica

Programacao dinamica. 
(segundo as solucoes oficiais, com a mesma notacao em geral)

Comecamos por reparar que, saindo da loja,
        nao faz sentido passar por uma casa sem entregar a pizza.
Assim o estado depende do numero de casas a esquerda (n_esq)
        e o numero de casas a direita (n_dir) que ja visitamos.

Mas precisamos de mais um dado: o sentido em que vinhamos.
Por exemplo, se inicialmente houver 2 casas a esquerda e duas a direita,
        se o estado actual for (n_esq=1,n_dir=1),
        nao sabemos se estamos na primeira casa a direita ou a esquerda.
Precisamos de saber se estavamos a ir para a esquerda ou a direita.
Representamos S=0 para o sentido para a esquerda, S=1, para o sentido a direita.

Entao temos que o estado e definido por 3 parametros, (S, E, D). 
Temos, no maximo, 2*1500*1500 estados = 4 500 000.
(mas a matriz em top-down DP definimos como 2*3000*3000, 
        ja que nao sabemos como e a distribuicao de casas esquerda-direita)

A solucao passa pelas duas fases usuais de DP:
        1. estabelecer as relacoes de transicao de estados,  (ver solucoes oficiais)
        2. ter cuidado a definir os estados base (iniciais, finais e edge)


Complexidade: O(N^2) porque ha O(N^2) estados e cada um demora O(1)

NOTA:
A solucao oficial tem uma gralha no site das oni:

"e entre: abs(seq_dir[n_direita] ­- seq_esq[n_esquerda ­- 1])"
->
"e entre: abs(seq_dir[n_direita] ­+ seq_esq[n_esquerda ­- 1])"

*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath> //abs
#include<cstring> // memset

using namespace std;

int N, total_esq = 0, total_dir = 0;
int x;
int s;
vector<int> seq_esq, seq_dir;
int memo[2][3010][3010];


int DP(int s, int n_esq, int n_dir){
        // caso final
        if (n_esq == total_esq && n_dir == total_dir){
                return 0;
        }
        // casos iniciais
        if (n_esq == 0 && n_dir == 0){
                return min( DP(0, 1, 0) + seq_esq[0]*N,
                            DP(1, 0, 1) + seq_dir[0]*N
                );
        }
        if (memo[s][n_esq][n_dir] != -1){ // DP
                return memo[s][n_esq][n_dir];   
        }     
        if (s == 0){
                if (n_esq == total_esq){
                        return memo[s][n_esq][n_dir] = abs(seq_dir[n_dir] + seq_esq[n_esq-1])*(total_esq-n_esq+total_dir-n_dir) 
                               + DP(1, n_esq, n_dir+1);
                }
                if (n_dir == total_dir){
                        return memo[s][n_esq][n_dir] = abs(seq_esq[n_esq] - seq_esq[n_esq-1])*(total_esq-n_esq+total_dir-n_dir)
                            + DP(0, n_esq+1, n_dir);
                        // atencao: fiquei uma hora em debug, porque achei inicialmente que nunca chegavamos a este caso...
                }
                return memo[s][n_esq][n_dir] = min( abs(seq_esq[n_esq] - seq_esq[n_esq-1])*(total_esq-n_esq+total_dir-n_dir)
                            + DP(0, n_esq+1, n_dir),
                            //conforme nota acima a linha abaixo tem uma gralha na solucao oficial das ONI
                            abs(seq_dir[n_dir] + seq_esq[n_esq-1])*(total_esq-n_esq+total_dir-n_dir) 
                            + DP(1, n_esq, n_dir+1)
                );
        } else {
                if (n_esq == total_esq){
                        return memo[s][n_esq][n_dir] = abs(seq_dir[n_dir] - seq_dir[n_dir-1])*(total_esq-n_esq+total_dir-n_dir)
                            + DP(1, n_esq, n_dir+1);
                        // atencao: fiquei uma hora em debug, porque achei inicialmente que nunca chegavamos a este caso...
                }
                if (n_dir == total_dir){
                        return memo[s][n_esq][n_dir] = abs(seq_dir[n_dir-1] + seq_esq[n_esq])*(total_esq-n_esq+total_dir-n_dir) 
                               + DP(0, n_esq+1, n_dir);
                }
                return memo[s][n_esq][n_dir] = min( abs(seq_dir[n_dir] - seq_dir[n_dir-1])*(total_esq-n_esq+total_dir-n_dir)
                            + DP(1, n_esq, n_dir+1),
                            abs(seq_dir[n_dir-1] + seq_esq[n_esq])*(total_esq-n_esq+total_dir-n_dir) 
                            + DP(0, n_esq+1, n_dir)
                );
        }
}

int main(){

        cin >> N;

        memset(memo, -1, sizeof memo);

        // criacao das duas listas com as posicoes das casas
        for(int i = 0; i < N; i++){
                cin >> x;
                if (x < 0){
                        seq_esq.push_back(-x); // tornar positivo
                        total_esq++;    // numero de casas a esquerda
                } else {
                        seq_dir.push_back(x);
                        total_dir++;    // numero de casas a direita
                }
                sort(seq_esq.begin(), seq_esq.end());  // inverter ordem para ficar crescente
        }
        

        // se so tivermos casas de um lado, fazemos de forma diferente,
        // porque a funcao DP() conta com as listas seq_* nao serem vazias
        int d = 0;
        if (total_dir == 0){                    // caso em que so ha casas a esquerda
                for(int i = 0; i < total_esq; i++){
                        d += seq_esq[i];
                }
                cout << d << endl;
        } else if (total_esq == 0){             // caso em que so ha casas a direita
                for(int i = 0; i < total_dir; i++){
                        d += seq_dir[i];
                }
                cout << d << endl;
        } else{
                cout << DP(0, 0, 0) << endl;    // caso em que ha casas em ambos os lados
       }        
}
