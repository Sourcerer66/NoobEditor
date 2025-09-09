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

int main(int argc, char **argv){
	if(argc < 2){
		perror("Sem argumentos suficientes...");
		exit(1);
	}
	FILE *f = fopen(argv[1], "r");
	
	if(f ==NULL){
		perror("Arquivo nao exite...");
		exit(1);
	}

	char buffer[1024] = {0};

	fread(buffer, 1024, 1, f);
	fclose(f);
	//colocar \0 no final do buffer...
	int lines_buffer = get_lines(buffer);
	int size_buffer = strlen(buffer);
	node *arr[lines_buffer];
	int foo = 0;
	//ta mais completo mas falta algo ainda...
	//continua dando erro!!!
	for (int i = 0; i < lines_buffer; ++i){
		while(buffer[foo] != '\n'){
			append_node(&arr[i], buffer[foo]);
			foo++;
		}
		foo++;

	}

	initscr();
	
	for (int i=0; i < lines_buffer; ++i){
		node *fakie = arr[i];
		while(fakie->next != NULL){
			printw("%c", fakie->data);
			fakie = fakie->next;
		}
	}
	
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
