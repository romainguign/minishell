#include <stdio.h>
#include <stdlib.h>


typedef enum e_token_type
{
	WORD,
	REDIRECT_IN,
	REDIRECT_OUT,
	PIPE,
	HERE_DOC
}	t_token_type;


// Structure pour représenter un nœud de la liste chaînée
typedef struct s_command_node {
    enum e_token_type type;
    char *value;
    struct s_command_node *next;
} t_command_node;

// Fonction pour créer un nouveau nœud de la liste chaînée
t_command_node* create_node(enum e_token_type type, char *value) {
    t_command_node *node = malloc(sizeof(t_command_node));
    if (node == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour un nouveau nœud");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->value = value;
    node->next = NULL;
    return node;
}

// Fonction pour ajouter un nœud à la fin de la liste chaînée
void append_node(t_command_node **head, t_command_node *new_node) {
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_command_node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Fonction pour parcourir et afficher la liste chaînée
void print_command_list(t_command_node *head) {
    t_command_node *current = head;
    while (current != NULL) {
        printf("Type: %d, Value: %s\n", current->type, current->value);
        current = current->next;
    }
}

int main() {
    // Création des nœuds de la liste chaînée à partir des tokens
    t_command_node *head = NULL;
    append_node(&head, create_node(WORD, "cat"));
    append_node(&head, create_node(HERE_DOC, "<<"));
    append_node(&head, create_node(WORD, "end"));
    append_node(&head, create_node(PIPE, "|"));
    append_node(&head, create_node(WORD, "wc"));
    append_node(&head, create_node(WORD, "-l"));
    append_node(&head, create_node(REDIRECT_OUT, ">>"));
    append_node(&head, create_node(WORD, "outfile"));

    // Affichage de la liste chaînée
    print_command_list(head);

    // Libération de la mémoire allouée pour la liste chaînée
    while (head != NULL) {
        t_command_node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}