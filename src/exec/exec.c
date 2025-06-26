/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:41:38 by lpin              #+#    #+#             */
/*   Updated: 2025/05/30 18:26:01 by lpin             ###   ########.fr       */
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

    // Inicializar entorno
    built_env(envp, &_env);

    // Añadir variables
    built_export(&_env, export1);
    printf("Lista tras export a=1 b=2 c=3:\n");
    built_export(&_env, export2);
    printf("\n");
    // Eliminar 'b'
    built_unset(&_env, unset_b);
    printf("Tras built_unset 'b':\n");
    built_export(&_env, export2);
    printf("\n");

    // Eliminar 'a'
    built_unset(&_env, unset_a);
    printf("Tras built_unset 'a':\n");
    built_export(&_env, export2);
    printf("\n");

    // Eliminar 'c'
    built_unset(&_env, unset_c);
    printf("Tras built_unset 'c':\n");
    built_export(&_env, export2);
    printf("\n");

    // Eliminar 'd' con valor erroneo
    built_unset(&_env, unset_d);
    printf("Tras built_unset 'd' con value erroneo:\n");
    built_export(&_env, export2);
    printf("\n");

    // Eliminar 'e' con valor erroneo
    built_unset(&_env, unset_e);
    printf("Tras built_unset 'd' con value erroneo:\n");
    built_export(&_env, export2);
    printf("\n");
    
    // Eliminar variable que no existe
    built_unset(&_env, unset_noexiste);
    printf("Tras built_unset 'noexiste' (no debería cambiar nada):\n");
    built_export(&_env, export2);
    printf("\n");

    // Eliminar 'd' y 'e' con valores correctos
    built_unset(&_env, unset_d_e);
    printf("Tras built_unset 'd=4' y 'e=5':\n");
    built_export(&_env, export2);
    printf("\n");

    // Pruebas para built_cd
    char cwd[1024];
    printf("Directorio actual inicial: %s\n", getcwd(cwd, sizeof(cwd)));

    // Cambiar a /tmp (o cualquier directorio que exista en tu sistema)
    char *cd_tmp[] = {"cd", "/tmp", NULL};
    built_cd(&_env, cd_tmp);
    printf("Directorio tras built_cd /tmp: %s\n", getcwd(cwd, sizeof(cwd)));

    // Cambiar a un directorio inválido
    char *cd_invalido[] = {"cd", "/noexiste", NULL};
    built_cd(&_env, cd_invalido);
    printf("Directorio tras built_cd /noexiste (debe fallar y quedarse igual): %s\n", getcwd(cwd, sizeof(cwd)));

    // Cambiar a HOME (sin argumentos)
    char *cd_home[] = {"cd", NULL};
    built_cd(&_env, cd_home);
    printf("Directorio tras built_cd (HOME): %s\n", getcwd(cwd, sizeof(cwd)));

    return 0;
}
