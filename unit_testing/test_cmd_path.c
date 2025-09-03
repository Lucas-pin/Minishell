/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:14:46 by lpin              #+#    #+#             */
/*   Updated: 2025/09/02 19:10:36 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include "../../include/builtins.h"

// Helper para crear nodos de comandos
t_cmd *cmd_new(char *cmd, char **argv) {
    t_cmd *node = malloc(sizeof(t_cmd));
    node->cmd = cmd;
    node->argv = argv;
    node->cmd_path = NULL;
    node->next = NULL;
    return node;
}

// Test unitario para cmd_path
int main(void) {
    t_env *env = NULL;
    create_default_env(&env);

    // Comandos de prueba
    char *argv_echo[] = {"echo", "Hola", "Mundo", NULL};
    char *argv_pwd[] = {"pwd", NULL};
    char *argv_ls[] = {"ls", NULL};
    char *argv_cd[] = {"cd", "/", NULL};

    // Crear lista de comandos
    t_cmd *cmd1 = cmd_new("echo", argv_echo);
    t_cmd *cmd2 = cmd_new("pwd", argv_pwd);
    t_cmd *cmd3 = cmd_new("ls", argv_ls);
    t_cmd *cmd4 = cmd_new("cd", argv_cd);

    // Enlazar lista
    cmd1->next = cmd2;
    cmd2->next = cmd3;
    cmd3->next = cmd4;

    // Ejecutar cmd_path sobre la lista
    t_cmd *result = cmd_path(cmd1, &env);

    // Mostrar resultados
    printf("--- Test cmd_path ---\n");
    t_cmd *aux = result;
    while (aux) {
        int builtin_index = is_builtin(aux->cmd);
        if (builtin_index > -1) {
            printf("Comando '%s' es builtin. Puntero a función: %p\n", aux->cmd, aux->cmd_path);
            // Ejecutar la función builtin mediante el puntero
            int (*func)(char **, t_env **) = (int (*)(char **, t_env **))aux->cmd_path;
            printf("Ejecutando '%s':\n", aux->cmd);
            func(aux->argv, &env);
        } else {
            printf("Comando '%s' externo. Ruta encontrada: %s\n", aux->cmd, (char *)aux->cmd_path);
        }
        aux = aux->next;
    }

    // Liberar memoria (simplificado)
    aux = result;
    while (aux) {
        t_cmd *tmp = aux->next;
        if (is_builtin(aux->cmd) == -1 && aux->cmd_path)
            free(aux->cmd_path);
        free(aux);
        aux = tmp;
    }
    lst_free(&env);
    return 0;
}