/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:41:38 by lpin              #+#    #+#             */
/*   Updated: 2025/05/19 00:16:44 by lucas            ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_env *_env;
	char *pwd;
	char *prueba[] = {"export", "a=b", "pepito=convalor", "pepitoo", NULL};
	char *prueba_2[] = {"export", NULL};
	pwd = NULL;
	if (env == NULL)
	{
    	pwd = getenv("PWD");
		printf("pwd: %s", pwd);
	}
	if (argc > 1)
	{
		printf("El primer argumento es: %s\n", argv[1]);
	}
	else
	{
		printf("No se han pasado argumentos.\n");
	}
	printf("-------------------Se imprime el entorno--------------------\n");
	built_env(env, &_env);
	printf("-------------------Se añadieron variables-------------------------\n");
	built_export(&_env, prueba);
	printf("-------------------Se imprime el export-------------------------\n");
	built_export(&_env, prueba_2);
	printf("-------------------Se actualiza variables-------------------------\n");
	prueba[0] = "export";
	prueba[1] = "a=c";
	prueba[2] = "pepito";
	prueba[3] = "pepitoo=updated";
	prueba[4] = NULL;
	built_export(&_env, prueba);
	printf("-------------------Se imprime el export-------------------------\n");
	built_export(&_env, prueba_2);
	//Revisar que ocurre al eliminar el valor de una variable
	return (0);
}
