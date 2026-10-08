bool ordenado(int v[], int n) {
  for (int i = 1; i < n; i++) {
    if (v[i] <= v[i - 1])
      return false;
  }
  return true;
}

#include <iostream>

using namespace std;

int main() {
  int vet[10] {
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10
  };
  if (ordenado(vet, 10)) {
    cout << "O vetor esta ordenado";
  } else {
    cout << "O vetor nao esta ordenado";
  }
  return 0;
}
