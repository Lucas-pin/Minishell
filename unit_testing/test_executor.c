/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:00:00 by lpin              #+#    #+#             */
/*   Updated: 2025/08/11 01:05:47 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/structs.h"
#include "../include/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static t_cmd *cmd_new(char *cmd, char **argv)
{
    t_cmd *n;
    size_t argc;
    size_t i;

    n = malloc(sizeof(t_cmd));
    if (!n)
        return (NULL);
    // duplicate cmd and argv so project free_cmds can safely free them
    n->cmd = ft_strdup(cmd);
    argc = 0;
    if (argv)
        while (argv[argc])
            argc++;
    n->argv = (char **)malloc(sizeof(char *) * (argc + 1));
    if (!n->argv)
        return (free(n->cmd), free(n), NULL);
    i = 0;
    while (i < argc)
    {
        n->argv[i] = ft_strdup(argv[i]);
        i++;
    }
    n->argv[argc] = NULL;
    n->fd_in = -1;
    n->fd_out = -1;
    n->cmd_path = NULL;
    n->next = NULL;
    return (n);
}

static int set_out_file(t_cmd *c, const char *path, int append)
{
    int fd;
    int flags;

    flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
    fd = open(path, flags, 0644);
    if (fd == -1)
    {
        perror("open");
        return (-1);
    }
    c->fd_out = fd;
    return (0);
}

static void show_file(const char *path, const char *tag)
{
    char    buf[256];
    ssize_t n;
    int     fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return ;
    }
    printf("%s", tag);
    while ((n = read(fd, buf, sizeof(buf))) > 0)
        write(1, buf, n);
    close(fd);
    write(1, "\n", 1);
}

static void log_cmds(t_cmd *head)
{
    int i;

    i = 0;
    while (head)
    {
        if (is_builtin(head->cmd) != -1)
            printf("  [%d] %s -> builtin %p\n", i, head->cmd,
                head->cmd_path);
        else
            printf("  [%d] %s -> path '%s'\n", i, head->cmd,
                (char *)head->cmd_path);
        head = head->next;
        i++;
    }
}

static void case_single_builtin(t_env **env)
{
    char *av1[] = {"echo", "hola", NULL};
    t_cmd *c1 = cmd_new("echo", av1);
    int   st;

    printf("\n== single builtin (echo)\n");
    set_out_file(c1, "ut_out1.txt", 0);
    printf("[setup] cmd_path...\n");
    cmd_path(c1, env);
    log_cmds(c1);
    printf("[exec] run...\n");
    st = executor(c1, env);
    printf("[exec] status=%d\n", st);
    show_file("ut_out1.txt", "out1: ");
    if (c1->fd_out != -1)
    {
        close(c1->fd_out);
        c1->fd_out = -1;
    }
    free_cmds(c1);
}

static void case_single_external(t_env **env)
{
    char *av1[] = {"ls", "-1", NULL};
    t_cmd *c1 = cmd_new("ls", av1);
    int   st;

    printf("\n== single external (ls)\n");
    set_out_file(c1, "ut_out2.txt", 0);
    printf("[setup] cmd_path...\n");
    cmd_path(c1, env);
    log_cmds(c1);
    printf("[exec] run...\n");
    st = executor(c1, env);
    printf("[exec] status=%d\n", st);
    show_file("ut_out2.txt", "out2: ");
    if (c1->fd_out != -1) { close(c1->fd_out); c1->fd_out = -1; }
    free_cmds(c1);
}

static void case_pipe_echo_cat(t_env **env)
{
    char *av1[] = {"echo", "hola", NULL};
    char *av2[] = {"cat", NULL};
    t_cmd *c1 = cmd_new("echo", av1);
    t_cmd *c2 = cmd_new("cat", av2);
    int   st;

    printf("\n== pipe echo | cat\n");
    c1->next = c2;
    set_out_file(c2, "ut_out3.txt", 0);
    printf("[setup] cmd_path...\n");
    cmd_path(c1, env);
    log_cmds(c1);
    printf("[exec] run...\n");
    st = executor(c1, env);
    printf("[exec] status=%d\n", st);
    show_file("ut_out3.txt", "out3: ");
    if (c2->fd_out != -1)
    {
        close(c2->fd_out);
        c2->fd_out = -1;
    }
    free_cmds(c1);
}

static void case_pipe_echo_grep(t_env **env)
{
    char *av1[] = {"echo", "hola mundo", NULL};
    char *av2[] = {"grep", "hola", NULL};
    t_cmd *c1 = cmd_new("echo", av1);
    t_cmd *c2 = cmd_new("grep", av2);
    int   st;

    printf("\n== pipe echo | grep hola\n");
    c1->next = c2;
    set_out_file(c2, "ut_out4.txt", 0);
    printf("[setup] cmd_path...\n");
    cmd_path(c1, env);
    log_cmds(c1);
    printf("[exec] run...\n");
    st = executor(c1, env);
    printf("[exec] status=%d\n", st);
    show_file("ut_out4.txt", "out4: ");
    if (c2->fd_out != -1) { close(c2->fd_out); c2->fd_out = -1; }
    free_cmds(c1);
}

static void case_not_found(t_env **env)
{
    char *av1[] = {"no_such_cmd_zzz", NULL};
    t_cmd *c1 = cmd_new("no_such_cmd_zzz", av1);
    int   st;

    printf("\n== not found\n");
    printf("[setup] cmd_path...\n");
    cmd_path(c1, env);
    log_cmds(c1);
    printf("[exec] run...\n");
    st = executor(c1, env);
    printf("[exec] status=%d\n", st);
    free_cmds(c1);
}

int main(void)
{
    t_env *env;

    env = NULL;
    printf("== create_default_env\n");
    create_default_env(&env);
    case_single_builtin(&env);
    case_single_external(&env);
    case_pipe_echo_cat(&env);
    case_pipe_echo_grep(&env);
    case_not_found(&env);
    printf("\n== cleanup env\n");
    lst_free(&env);
    return (0);
}
