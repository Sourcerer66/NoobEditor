#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>


typedef struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
}node;

int get_lines(char *buffer);

node* create_node(int c);

void append_node(node **head, int c);

void get_text(char name[], node *arr0[], int *lines, int *size);

int main(int argc, char **argv){
	if(argc < 2){
		perror("Sem argumentos suficientes...");
		exit(1);
	}
	int size_buffer = 0;
	int lines_buffer = 0;
	node *arr[1024];
	get_text(argv[1], arr, &lines_buffer, &size_buffer);

	initscr();
	noecho();
	raw();
	cbreak();
	keypad(stdscr, TRUE);
	for (int i=0; i < lines_buffer; ++i){
		node *fakie = arr[i];
		while(fakie != NULL){
			printw("%c", fakie->data);
			fakie = fakie->next;
		}
	}
	
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

node* create_node(int c){
	node *new_node = (node*)malloc(sizeof(node));
	new_node->data = c;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

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
	//
	//construir sistema que guarda o caractere atual que voce esta qnd vc vai para outra linha
	//aplicar sistema completo de movimento pelo arquivo...
	//
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
