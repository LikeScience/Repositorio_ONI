#include <iostream>
#include <stack>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

/*
* Para optimizar a solução anterior para O(N) basta guardar um contador com o número de mulheres vistas
* Incrementar se a posição i for uma mulher e decrementar se a posição i - k for uma mulher
*/

int combinations(string line, int k, int n) {
	int acc = 0;
	int sequentialWomen = 0;

	if(line[0] == 'M') {
		sequentialWomen = 1;
	}

	for(int i = 1; i < n; i++) {
		if(line[i] == 'M') {
			sequentialWomen++;
		} else {
			acc += sequentialWomen;
		}
		if(i - k >= 0 && line[i - k] == 'M') sequentialWomen--;
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
