#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int somma(){
    int S;
    for(int i=1; i<=10; i++){
        S += i;
    }
    return S;
}

int prodotto(){
    int M=1;
    for(int i=1; i<=5; i++){
        M *= i;
    }    

    return M;

}

void processi(){
    pid_t pid1 = fork();
    if (pid1 < 0){

        cout << "fork failed";
        exit(1);

    }else if(pid1 == 0){
        //child1
        exit(somma());
    }

    pid_t pid2 = fork();
    if (pid2 < 0){

        cout << "fork failed";
        exit(1);

    }else if(pid2 == 0){
        //child2
        exit(prodotto());
    }

    pid_t pid3 = fork();
    if (pid3 < 0){
        cout << "fork failed";
        exit(1);

    }else if(pid3 == 0){
         //child3
        srand(time(NULL));
        int random_N = rand()%3+1;
        sleep(random_N);
        exit(random_N);
    }
    else if (pid1 > 0){
        //parent
        for(int i=0; i<3; i++){
            int status = 0, exit_status;

            pid_t pid_terminated = wait(&status);
            cout << "-Parent in wait;" << endl;
            if (WIFEXITED(status)) {
                exit_status = WEXITSTATUS(status);
            } 

            cout << "-Il processo child con PID " << pid_terminated << " è terminato con codice di uscita: " << exit_status << ";" << endl;
        }
    }

   cout << "-TUTTI I PROCESSI SONO TERMINATI.";
}

int main(){

    cout << "Gestione dei processi tramite funzioni fork() wait() ed exit()" << endl << endl;

    processi();

    return 0;
}