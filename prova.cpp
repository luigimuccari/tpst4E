/*Modifica il seguente codice che fa capire come si comporta l'istruzione Fork() 
e rendi ancora più evidente la correttezza della spiegazione mediante l'introduzione di una variabile globale 
e la stampa dei suoi valori all'interno del codice stesso:

#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
void forkexample() 
{ 
    pid_t p; 
    p = fork(); 
    if(p<0) 
    { 
      perror("fork fail"); 
      exit(1); 
    } 
    // child process because return value zero 
    else if ( p == 0) 
        printf("Hello from Child!\n"); 
  
    // parent process because return value non-zero. 
    else
        printf("Hello from Parent!\n"); 
} 
int main() 
{ 
    forkexample(); 
    return 0; 
} 
*/

#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 

using namespace std;

int v_globale=50;

void forkexample() { 
    pid_t p; 
    p = fork(); 
    if(p<0) 
    { 
      perror("fork fail"); 
      exit(1); 
    } 
    // child process because return value zero 
    else if ( p == 0){
        cout << "il valore della variabile globale stampata dal processo child è " << v_globale << endl;

        // parent process because return value non-zero.
    } else {
        cout << "il valore della variabile globale stampata dal processo parent è " << v_globale << endl;
    }
} 
int main() 
{ 
    forkexample(); 
    return 0; 
} 
