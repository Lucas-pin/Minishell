/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:41:38 by lpin              #+#    #+#             */
/*   Updated: 2025/07/30 19:37:46 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

/*
echo	Imprimir texto
cd	Cambiar directorio actual
pwd	Mostrar el directorio actual
export	Establecer variables de entorno
unset	Eliminar variables de entorno
env	Mostrar variables de entorno
exit	Salir de la shell
*/

// export hola
// env | grep 'hola'
// export hola=
// env | grep 'hola'

// env, export y unset

// export -> ordena por ASCII
// env -> ordena como se le canta el orto
// agregar funciones de listas
// generar buble sort
// imprimir lista, si es env no imprime los hide

int main(int argc, char **argv, char **envp)
{
    t_env *_env = NULL;
    char *export1[] = {"export", "a=1", "b=2", "c=3", "d=4", "e=5", NULL};
    char *export2[] = {"export", NULL};
    char *unset_b[] = {"unset", "b", NULL};
    char *unset_a[] = {"unset", "a", NULL};
    char *unset_c[] = {"unset", "c=3", NULL};
    char *unset_d[] = {"unset", "d=3", NULL};
    char *unset_e[] = {"unset", "e=", NULL};
    char *unset_d_e[] = {"unset", "d=4", "e=5", NULL};
    char *unset_noexiste[] = {"unset", "noexiste", NULL};

    (void)argv;
    (void)argc;
    if (!envp || !*envp)
        create_default_env(&_env);
    else
    {
        while (*envp)
        {
            lst_add(&_env, lst_new(*envp, false));
            envp++;
        }
    }
    // Inicializar entorno
    built_env(envp, &_env);
/*------------------------------------------------------------------------------*/
    // Pruebas unitarias para export y unset
    // Añadir variables
    built_export(export1, &_env);
    printf("Lista tras export a=1 b=2 c=3:\n");
    built_export(export2, &_env);
    printf("\n");
    // Eliminar 'b'
    built_unset(unset_b, &_env);
    printf("Tras built_unset 'b':\n");
    built_export(export2, &_env);
    printf("\n");

    // Eliminar 'a'
    built_unset(unset_a, &_env);
    printf("Tras built_unset 'a':\n");
    built_export(export2, &_env);
    printf("\n");

    // Eliminar 'c'
    built_unset(unset_c, &_env);
    printf("Tras built_unset 'c':\n");
    built_export(export2, &_env);
    printf("\n");

    // Eliminar 'd' con valor erroneo
    built_unset(unset_d, &_env);
    printf("Tras built_unset 'd' con value erroneo:\n");
    built_export(export2, &_env);
    printf("\n");

    // Eliminar 'e' con valor erroneo
    built_unset(unset_e, &_env);
    printf("Tras built_unset 'd' con value erroneo:\n");
    built_export(export2, &_env);
    printf("\n");
    
    // Eliminar variable que no existe
    built_unset(unset_noexiste, &_env);
    printf("Tras built_unset 'noexiste' (no debería cambiar nada):\n");
    built_export(export2, &_env);
    printf("\n");

    // Eliminar 'd' y 'e' con valores correctos
    built_unset(unset_d_e, &_env);
    printf("Tras built_unset 'd=4' y 'e=5':\n");
    built_export(export2, &_env);
    printf("\n");
/*------------------------------------------------------------------------------*/
    // Pruebas para built_cd
    char cwd[1024];
    printf("Directorio actual inicial: %s\n", getcwd(cwd, sizeof(cwd)));

    // Cambiar a /tmp (o cualquier directorio que exista en tu sistema)
    char *cd_tmp[] = {"cd", "/tmp", NULL};
    built_cd(cd_tmp, &_env);
    printf("Directorio tras built_cd /tmp: %s\n", getcwd(cwd, sizeof(cwd)));

    // Cambiar a un directorio inválido
    char *cd_invalido[] = {"cd", "/noexiste", NULL};
    built_cd(cd_invalido, &_env);
    printf("Directorio tras built_cd /noexiste (debe fallar y quedarse igual): %s\n", getcwd(cwd, sizeof(cwd)));

    // Cambiar a HOME (sin argumentos)
    char *cd_home[] = {"cd", NULL};
    built_cd(cd_home, &_env);
    printf("Directorio tras built_cd (HOME): %s\n", getcwd(cwd, sizeof(cwd)));

    // Prueba: Cambiar a ruta relativa (directorio actual)
    char *cd_dot[] = {"cd", ".", NULL};
    built_cd(cd_dot, &_env);
    printf("Directorio tras built_cd .: %s\n", getcwd(cwd, sizeof(cwd)));

    // Prueba: Cambiar a ruta relativa superior
    char *cd_dotdot[] = {"cd", "..", NULL};
    built_cd(cd_dotdot, &_env);
    printf("Directorio tras built_cd ..: %s\n", getcwd(cwd, sizeof(cwd)));

    // Prueba: Cambiar a ruta anterior
    char *cd_dash[] = {"cd", "-", NULL};
    built_cd(cd_dash, &_env);
    printf("Directorio tras built_cd -: %s\n", getcwd(cwd, sizeof(cwd)));

    // Prueba: Cambiar a ruta root
    char *cd_slash[] = {"cd", "/", NULL};
    built_cd(cd_slash, &_env);
    printf("Directorio tras built_cd /: %s\n", getcwd(cwd, sizeof(cwd)));

    // Prueba: Cambiar a ruta ~
    char *cd_tilde[] = {"cd", "~", NULL};
    built_cd(cd_tilde, &_env);
    printf("Directorio tras built_cd ~: %s\n", getcwd(cwd, sizeof(cwd)));

    // Prueba: Cambiar a ruta ~/Github
    char *cd_tilde_github[] = {"cd", "~/Github", NULL};
    built_cd(cd_tilde_github, &_env);
    printf("Directorio tras built_cd ~/Github: %s\n", getcwd(cwd, sizeof(cwd)));

    // Prueba: Cambiar a ruta /Github
    char *cd_github[] = {"cd", "/Github", NULL};
    built_cd(cd_github, &_env);
    printf("Directorio tras built_cd /Github: %s\n", getcwd(cwd, sizeof(cwd)));
/*------------------------------------------------------------------------------*/
    // Pruebas unitarias para built_echo
    printf("\n--- Pruebas built_echo ---\n");

    char *echo1[] = {"echo", "Hola", "Mundo", NULL};
    printf("\nTest 1: echo Hola Mundo\n");
    printf("Esperado: >>>Hola Mundo\\n<<<\n");
    printf("Salida real: >>>");
    fflush(stdout);
    built_echo(echo1, &_env);
    printf("<<<\n");
    fflush(stdout);

    char *echo2[] = {"echo", "-n", "Hola", "Mundo", NULL};
    printf("\nTest 2: echo -n Hola Mundo\n");
    printf("Esperado: >>>Hola Mundo<<< (sin salto de linea)\n");
    printf("Salida real: >>>");
    fflush(stdout);
    built_echo(echo2, &_env);
    printf("<<<\n");
    fflush(stdout);

    char *echo3[] = {"echo", NULL};
    printf("\nTest 3: echo (sin argumentos)\n");
    printf("Esperado: >>>\\n<<< (solo salto de linea)\n");
    printf("Salida real: >>>");
    fflush(stdout);
    built_echo(echo3, &_env);
    printf("<<<\n");
    fflush(stdout);

    char *echo4[] = {"echo", "-n", NULL};
    printf("\nTest 4: echo -n (sin argumentos)\n");
    printf("Esperado: >>><<< (nada, sin salto de linea)\n");
    printf("Salida real: >>>");
    fflush(stdout);
    built_echo(echo4, &_env);
    printf("<<<\n");
    fflush(stdout);

    char *echo5[] = {"echo", "", NULL};
    printf("\nTest 5: echo '' (cadena vacía)\n");
    printf("Esperado: >>>\\n<<< (salto de linea vacio)\n");
    printf("Salida real: >>>");
    fflush(stdout);
    built_echo(echo5, &_env);
    printf("<<<\n");
    fflush(stdout);

/*------------------------------------------------------------------------------*/
    // Pruebas unitarias para built_pwd
    printf("\n--- Pruebas built_pwd ---\n");
    char *pwd_args1[] = {"pwd", NULL};
    printf("Test 1: pwd sin argumentos\n");
    printf("Esperado: ruta actual (verifica visualmente)\n");
    printf("Salida real: >>>");
    fflush(stdout);
    int ret1 = builtin_pwd(pwd_args1, &_env);
    printf("<<<\nRetorno: %d (esperado: 0)\n", ret1);

    char *pwd_args2[] = {"pwd", "extra", NULL};
    printf("Test 2: pwd con argumento extra\n");
    printf("Esperado: retorno 1 (no imprime ruta)\n");
    printf("Salida real: >>>");
    fflush(stdout);
    int ret2 = builtin_pwd(pwd_args2, &_env);
    printf("<<<\nRetorno: %d (esperado: 1)\n", ret2);

/*------------------------------------------------------------------------------*/
    // Pruebas unitarias de memoria
    printf("\n--- Pruebas de memoria ---\n");
    // Liberar memoria de la lista de entorno
    lst_free(&_env);
    printf("Memoria de la lista de entorno liberada.\n");

    //Compilar y ejecutar el programa utilizando valgrind o addressSanitizer
    // Para valgrind: valgrind --leak-check=full ./test_builtins
    // Para addressSanitizer: gcc -fsanitize=address -g -o test_builtins test_builtins.c -I../include -L../lib -lexecutor -lft
    // ./test_builtins

/*------------------------------------------------------------------------------*/
    // Pruebas unitarias para built_exit
    printf("\n--- Pruebas built_exit ---\n");
    pid_t pid;
    int status;
    // Test 1: exit sin argumentos (debe salir con 0)
    pid = fork();
    if (pid == 0)
    {
        char *args1[] = {"exit", NULL};
        built_exit(args1, &_env);
    }
    wait(&status);
    printf("Test 1: exit sin argumentos. Esperado: 0, Real: %d\n", WEXITSTATUS(status));

    // Test 2: exit 42 (debe salir con 42)
    pid = fork();
    if (pid == 0)
    {
        char *args2[] = {"exit", "42", NULL};
        built_exit(args2, &_env);
    }
    wait(&status);
    printf("Test 2: exit 42. Esperado: 42, Real: %d\n", WEXITSTATUS(status));

    // Test 3: exit argumento no numérico (debe salir con 2)
    pid = fork();
    if (pid == 0)
    {
        char *args3[] = {"exit", "foo", NULL};
        built_exit(args3, &_env);
    }
    wait(&status);
    printf("Test 3: exit foo. Esperado: 2, Real: %d\n", WEXITSTATUS(status));

    // Test 4: exit -5 (debe salir con -5)
    pid = fork();
    if (pid == 0)
    {
        char *args4[] = {"exit", "-5", NULL};
        built_exit(args4, &_env);
    }
    wait(&status);
    printf("Test 4: exit -5. Esperado: 251, Real: %d\n", WEXITSTATUS(status));
    // Nota: exit(-5) realmente retorna 251 (256-5) por conversión a unsigned char

    // Test 5: exit --42 (debe salir con 2 por argumento inválido)
    pid = fork();
    if (pid == 0)
    {
        char *args5[] = {"exit", "--42", NULL};
        built_exit(args5, &_env);
    }
    wait(&status);
    printf("Test 5: exit --42. Esperado: 2, Real: %d\n", WEXITSTATUS(status));

    exit(42); // Salida de prueba para verificar el comportamiento de exit
    return 0;
}
