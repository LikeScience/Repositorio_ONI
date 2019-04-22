/*
ano: 2014
fase: qualificação
problema: A
pontos: 72
autor: Nuno Teieira
linguafem: c++
tópicos: 

Adiciona/remove os elementos de um vector à medida que é lido o input. Quando é lida a pergunta ordena-se o vector antes de responder. 

A complexidade das operações são:
    INS - O(1)
    REM - O(N)
    PER - O(NlogN)

O boleano isSorted optimiza o caso em que são feitas várias perguntas consecutivamente. 
Não altera a complexidade temporal do algoritmo, mas é uma melhoria rápida que dá mais alguns pontos.

*/

#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

int main(){
        int n;
        vector<int> cards;
        cin >> n;

        bool isSorted = false;
        for(int i = 0; i < n; i++){
                string operation;
                int nr;

                cin >> operation;
                cin >> nr;

                if(operation == "INS") {
                        cards.push_back(nr);
                        isSorted = false;
                } else if(operation == "REM") {
                        vector<int>::iterator it = find(cards.begin(), cards.end(), nr);
                        if(it != cards.end())
                            cards.erase(it);
                        isSorted = false;
                } else {
                        if(!isSorted) {
                                sort(cards.begin(), cards.end(), greater<int>());
                                isSorted = true;
                        }
                        cout << cards[nr - 1] << endl;
                }
        }
}
