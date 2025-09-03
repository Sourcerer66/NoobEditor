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

void create_node(int c);

void append_node(node **head, int *c);

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
	for (int i = 0; i < size_buffer; ++i){
		if (buffer[i] == '\n'){
			foo++;
		}
		append_node(arr,buffer[i]);

	}
	int current = 0;

	initscr();

	
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

void create_node(int c){
	node *new_node = (node*)malloc(sizeof(node));
	new_node->data = c;
	new_node->next = NULL;
	new_node->prev = NULL;
}

void append_node(node **head, int *c){
	node *new_node = create_node(c);
	if(*head == NULL){
		*head = new_node;
		return;
	}
	node *temp = *head;
	while(temp->next != NULL){
		temp = temp->next;	
	}
	temp->next = new_node;
	new_node->prev = temp;
}
