#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

typedef struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
}node;
//criando um tipo que se chama node, que sera usado para construir as linked lists

int get_lines(char *buffer);

node* create_node(int c);

void append_node(node **head, int c);

void get_text(char name[], node *arr0[], int *lines, int *size);

int main(int argc, char **argv){
	if(argc < 2){
		perror("Sem argumentos suficientes...");
		exit(1);
	}
	//checa se tem algum argumento qnd roda o programa *PRECISA POLIR*
	int size_buffer = 0;
	//variavel que guardar o numero de caracteres no buffer
	int lines_buffer = 0;
	//variavel de numero de linhas do buffer
	node *arr[1024];
	//criando array que supostamente 1024 seria o numero maximo de linhas que um arquivo poderia ter...
	get_text(argv[1], arr, &lines_buffer, &size_buffer);
	//pego o texto do arquivo para o array
	initscr();
	noecho();
	raw();
	cbreak();
	keypad(stdscr, TRUE);
	//tudo isso é coisa para o ncurses
	for (int i=0; i < lines_buffer; ++i){
		node *fakie = arr[i];
		while(fakie != NULL){
			printw("%c", fakie->data);
			fakie = fakie->next;
		}
	}
	//loop que printa o array
	
	//int ch;
	//while(ch = getch() != KEY_F(1)){
	//	switch(ch){
	//	case KEY_BACKSPACE:
	//	break;
	//
	//	case KEY_LEFT:
	//	break;
	//
	//	case KEY_RIGHT:
	//	break;
	//
	//	default:
	//	break;
	//
	//	}
	//
	//}
	//
	
	getch();	
	endwin();
	return 0;
}

int get_lines(char *buffer){
        int x = 0;
        char *p = strchr(buffer, '\n');
        while(p != NULL){
                x++;
                p = strchr(p+1, '\n');
        }
        return x;
}
//função simples que pega o numero de linhas dentro de um arquivo

node* create_node(int c){
	node *new_node = (node*)malloc(sizeof(node));
	new_node->data = c;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}
//função que cria uma node do zero.

void append_node(node **head, int c){
	node *new_node = create_node(c);
	//checa se a head que voce passa para a função é NULL e se for só seta ela para a nova node
	if(*head == NULL){
		*head = new_node;
		return;
	}
	node *temp = *head;
	//chegando ao final da linked list para appenda a node
	while(temp->next != NULL){
		temp = temp->next;	
	}
	temp->next = new_node;
	new_node->prev = temp;
}
//coloca uma node nova no final de uma linked list

void get_text(char name[], node *arr[], int *lines, int *size){
	FILE *f = fopen(name, "r");
	
	if(f ==NULL){
		perror("Arquivo nao exite...");
		exit(1);
	}
	
	char buffer[2048] = {0};

	fread(buffer, 2048, 1, f);
	fclose(f);
	//colocar \0 no final do buffer...
	*lines = get_lines(buffer);
	*size = strlen(buffer);
	int foo = 0;
	//08/09/2025 EUREKAAAAA!!!!!
	for (int i = 0; i < *lines; ++i){
		arr[i] = NULL;
		while(buffer[foo] != '\n'){
			append_node(&arr[i], buffer[foo]);
			foo++;
		}
		if(buffer[foo] == '\n'){
			append_node(&arr[i], '\n');
			foo++;
		}
	}
}
//função principal para criar o array que é os ossos e os musculos do editor de texto
