#include <iostream>
using namespace std;

int main(){
    
    int N, contatore = 0, N_primo = 0;
    for(int i=1; i <= N; i++){
        if(N%i == 0){
            contatore++;
        }
    }

    if(contatore==2){
        N_primo = 1;
    }
    return N_primo;
}