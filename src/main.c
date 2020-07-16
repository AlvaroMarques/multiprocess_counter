/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#define _GNU_SOURCE 1
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int e_primo(int n){
	if (n == 1) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	int tmp = n/3;
	while (tmp > 2){
		if (n % tmp == 0){
			return 0;
		}
		tmp--;
	}
	return 1;
}

int main() {

  int x;
  int *nums = (int*) malloc(0 * sizeof(int));
  int size = 0;
  int *n = malloc(0 * sizeof(int));
  while (scanf("%d", &x) != EOF) {
	  n = realloc(n, ++size * sizeof(int));
	  n[size-1] = x;
		
  }


  unsigned int *numbers = (unsigned int*) mmap(NULL, size*sizeof(unsigned int), PROT_EXEC+PROT_READ + PROT_WRITE, MAP_SHARED + MAP_ANONYMOUS, -1, 0);
  int *primes = (int*) mmap(NULL, size*sizeof(int), PROT_EXEC+PROT_READ + PROT_WRITE, MAP_SHARED + MAP_ANONYMOUS, -1, 0);
  pid_t fork1 = fork();
  int i; 
  for (i = 0; i < size; i++){
  	numbers[i] = n[i];
	primes[i] = -1;
  }
  if (fork1 == 0){
	  int i;
	  for (i = 0; i < size; i++){
	  	if (primes[i] == -1){
			primes[i] = e_primo(numbers[i]);
		}
	  }
	  exit(0);
  } 
  pid_t fork2 = fork();
  if (fork2 == 0) {
	  int i;
	  for (i = 0; i < size; i++){
	  	if (primes[i] == -1){
			primes[i] = e_primo(numbers[i]);
		}
	  }
	  exit(0);
  }
  pid_t fork4 = fork();
  if (fork4 == 0) {
	  int i;
	  for (i = 0; i < size; i++){
	  	if (primes[i] == -1){
			primes[i] = e_primo(numbers[i]);
		}
	  }
	  exit(0);
  }
  pid_t fork3 = fork();
  if (fork3 == 0) {
	  int i;
	  for (i = 0; i < size; i++){
	  	if (primes[i] == -1){
			primes[i] = e_primo(numbers[i]);
		}
	  }
	  exit(0);
  }
  waitpid(fork1,NULL,0);
  waitpid(fork2,NULL,0);
  waitpid(fork3,NULL,0);
  waitpid(fork4,NULL,0);
  unsigned int c = 0;
  for (i = 0; i < size; i++){
	  c += primes[i];
  }
  printf("%u\n", c);
  return 0;
}
