/*Calcolo dei numeri primi in un dato intervallo suddividendo il lavoro tra n processi.
Si scriva un programma C/C++ che letto da input un intervallo nel formato MIN-MAX, 
calcoli il numero di numeri primi presenti nell'intervallo. 
Il programma dovrà utilizzare la funzione fork() per generare un numero di processi figli 
specificato dall'utente in input (numero max processi: 8). 
Ogni processo figlio dovrà calcolare il numero di numeri primi presenti in un sotto-intervallo dell'intervallo originale. 
Il processo padre dovrà attendere la terminazione di tutti i processi figli e stampare a video il numero totale di numeri primi presenti nell'intervallo.*/

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


using namespace std;


int numero_primo(int N){
    int contatore = 0;
    for(int i=1; i <= N; i++){
        if(N%i == 0){
            contatore++;
        }
    }
    if(contatore == 2){
        return 1;
    }
    return  0;
}


int processo(int Min, int Max){
    int contatore_n_primi=0;

    for(int i=Min; i<=Max; i++){
        if(numero_primo(i)==1){
            contatore_n_primi++;
        }
    }
    return contatore_n_primi;

}

int main(int argc, char const* argv[]){

    int Max, Min, N_processi,  exit_status=0;
    cout << "Gestione dei processi tramite funzioni fork() wait() ed exit()" << endl << endl;

    cout << "Inserire un'intervallo di numero specificando: " << endl;
    cout << "-inizio intervallo: ";
    cin >> Min;
    cout << "-fine intervallo: ";
    cin >> Max;

    while(Min >= Max){
        if(Max < Min){
        cout << "|la fine dell'intevallo è minore dell'inizio dell'intervallo" << endl;
        cout << "|inseire un numero maggiore dell'inizio dell'intervallo ";
        cin >> Max;           
        }else if (Max == Min){
        cout << "|la fine dell'intevallo è uguale all'inizio dell'intervallo" << endl;
        cout << "|inseire un numero maggiore dell'inizio dell'intervallo ";
        cin >> Max;
        }
    }

    cout << "-Inserire il numero di processi per i quale verrà suddiviso il programma (Massimo:8): ";
    cin >>  N_processi;

    while(N_processi <= 0 or N_processi > 8){
        if (N_processi < 0){
            cout << "|Il numero inserito è minore di 0, inserisci un'altro numero: ";
            cin >> N_processi;
        }else if (N_processi == 0){
            cout << "|Il numero inserito è uguale a 0, inserisci un'altro numero: ";
            cin >> N_processi;
        } else {
            cout << "|Il numero inserito è maggiore di 8, inserisci un'altro numero: ";
            cin >> N_processi;           
        }
    }

    int N_per_processo = (Max-Min+1)/N_processi;
    int N_per_processo1 = N_per_processo;
    int N_per_processo_cont=N_per_processo*N_processi;
    int From, To;

    for(int proces = 0; proces != N_processi; proces++){
        pid_t pid = fork();
        if(pid < 0){

            cout << "|Fork failed";
            exit(1);

        }else if(pid == 0){  
            //child

            From = Min+((N_per_processo)*proces);
            To = (From+N_per_processo)-1;
            N_per_processo_cont -= N_per_processo;


            if(proces == (N_processi-1) && (Max-Min+1)>(N_per_processo*N_processi)){

                N_per_processo1 = N_per_processo+(Max-Min+1)-(N_per_processo*N_processi);
                To = From-1+N_per_processo1;

            }else if ((Max-Min+1)<(N_per_processo*N_processi) && To == Max){
                From = 0;
                To = 0;
            }

            exit(processo(From, To));
           
        }else if (pid > 0){
            //parent

            for(int i=0; i < N_processi; i++){
                int status = 0;
            pid_t pid_terminated = wait(&status);
                if (WIFEXITED(status)) {
                    exit_status += WEXITSTATUS(status);
                }                
            }        
        }
    }
    cout << "-Nell'intervallo da " << Min << " a " << Max << " sono stati calcolati in totale " << exit_status << " numeri primi.";
    return 0;
}