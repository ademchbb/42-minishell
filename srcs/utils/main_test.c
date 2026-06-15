#include "lexer.h"
#include <stdio.h>

const char *get_token_type_name(t_token_type type)
{
    switch (type)
    {
        case WORD:     return "WORD";
        case PIPE:     return "PIPE";
        case RED_IN:   return "RED_IN";
        case RED_OUT:  return "RED_OUT";
        case READ_IN:  return "READ_IN";
        case READ_OUT: return "READ_OUT";
        default:       return "UNKNOWN";
    }
}

void print_tokens(t_token *token)
{
    printf("\n--- RESULTAT DU LEXER ---\n");
    if (!token)
    {
        printf("(Liste vide)\n");
        return;
    }
    while (token)
    {
        printf("Token: [%-10s] -> Type: %s\n", token->token, get_token_type_name(token->type));
        token = token->next;
    }
    printf("-------------------------\n");
}

int main(void)
{
    char *test_input[] = 
    {
        ft_strdup("cat"), 
        ft_strdup("<<"), 
        ft_strdup("LIMITER"), 
        ft_strdup("|"), 
        ft_strdup("grep"), 
        ft_strdup("pattern"), 
        ft_strdup(">>"), 
        ft_strdup("append.txt"), 
        NULL
    };
    printf("Input de test alloué avec ft_strdup.\n");
    t_token *result = lexer(test_input);
    print_tokens(result);
    clear_token(&result);
    if (result == NULL)
        printf("Mémoire libérée et pointeur remis à NULL\n");       
    return (0);
}