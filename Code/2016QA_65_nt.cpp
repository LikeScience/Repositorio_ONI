/*
ano: 2016
fase: qualificação
problema: A
pontos: 65
autor: Nuno Teixeira
linguagem: c++
tópicos: 
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

/*
* Percorrer a linha de 0 até n, cada vez que encontramos um homem verificar quantas mulheres existem nas últimas k posições
* O(NK)
*/

int combinations(string line, int k, int n) {
	int acc = 0;
	for(int i = 0; i < n; i++) {
		if(line[i] == 'H') {
			for(int j = i -1; j >= 0 && j >= i - k; j--) {
				if(line[j] == 'M') acc++;
			}
		}
	}
	
	return acc;
}


int main() {

	int k, n;
	string line;
	cin >> n;
	cin >> k;
	cin.ignore();

        getline(cin, line);
	cout << combinations(line, k, n) <<endl;
	return 0;
}
