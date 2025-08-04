/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:10:50 by lpin              #+#    #+#             */
/*   Updated: 2025/08/01 20:08:12 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H   
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
/*
//@brief Checks for an alphabetic character; in the standard "C" locale, 
it is equivalent to (isupper(c) || islower(c)). In some locales, 
there may be additional characters for which isalpha() is true—letters 
which are neither uppercase nor lowercase.
//@param c The character to be checked.
//@return The value returned is nonzero if the character c falls into the 
tested class, and zero if not.
*/

int		ft_isdigit(int c);
/*
//@brief Checks for a digit (0 through 9).
//@param c The character to be checked.
//@return The value returned is nonzero if the character c falls into 
the tested class, and zero if not.
*/

int		ft_isalnum(int c);
/*
//@brief Checks for an alphanumeric character; it is equivalent 
to (isalpha(c) || isdigit(c)).
//@param c The character to be checked.
//@return The value returned is nonzero if the character c falls 
into the tested class, and zero if not.
*/

int		ft_isascii(int c);
/*
//@brief Checks whether c is a 7-bit unsigned char value 
that fits into the ASCII character set.
//@param c The character to be checked.
//@return The value returned is nonzero if the character c 
falls into the tested class, and zero if not.
*/

int		ft_isprint(int c);
/*
//@brief Checks for any printable character including space.
//@param c The character to be checked.
//@return The value returned is nonzero if the character c falls 
into the tested class, and zero if not.
*/

size_t	ft_strlen(const char *s);
/*
//@brief Computes the length of the string s.
//@param s The pointer to the string to be measured.
//@return The length of the string.
*/

void	*ft_memset(void *s, int c, size_t n);
/*
//@brief Writes len bytes of value c (converted to an unsigned char) 
to the string b.
//@param s The pointer to the string to be filled.
//@param c The character to fill the string with.
//@param n The number of bytes to be filled.
//@return The pointer to the string.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n);
/*
//@brief Copies n bytes from memory area src to memory area dst. 
If dst and src overlap, behavior is undefined. Applications in 
which dst and src might overlap should use memmove(3) instead.
//@param dst The pointer to the destination string.
//@param src The pointer to the source string.
//@param n The number of bytes to be copied.
//@return The pointer to the destination string.
*/

void	ft_bzero(void *s, size_t n);
/*
//@brief Writes n zeroed bytes to the string s. If n is zero, 
bzero() does nothing.
//@param s The pointer to the string to be zeroed.
//@param n The number of bytes to be zeroed.
//@return None.
*/

void	*ft_memmove(void *dst, const void *src, size_t len);
/*
//@brief Copies len bytes from string src to string dst. 
The two strings may overlap; the copy is always done in a non-destructive manner
//@param dst The pointer to the destination string.
//@param src The pointer to the source string.
//@param len The number of bytes to be copied.
//@return The pointer to the destination string.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
/*
//@brief Copies up to size - 1 characters from the NUL-terminated 
string src to dst, NUL-terminating the result.
//@param dst The pointer to the destination string.
//@param src The pointer to the source string.
//@param dstsize The size of the destination string.
//@return The length of the string src.
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
/*
//@brief Appends the NUL-terminated string src to the end of dst. 
It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the result.
//@param dst The pointer to the destination string.
//@param src The pointer to the source string.
//@param dstsize The size of the destination string.
//@return The length of the string src.
*/

int		ft_toupper(int c);
/*
//@brief Converts a lower-case letter to the corresponding upper-case letter.
//@param c The character to be converted.
//@return The converted character.
*/

int		ft_tolower(int c);
/*
//@brief Converts an upper-case letter to the corresponding lower-case letter.
//@param c The character to be converted.
//@return The converted character.
*/

char	*ft_strchr(const char *s, int c);
/*
//@brief Locates the first occurrence of c (converted to a char)
in the string pointed to by s. The terminating null character is considered
to be part of the string; therefore if c is `\0', the functions locate the
terminating `\0'.
//@param s The pointer to the string to be searched.
//@param c The character to be searched.
//@return The pointer to the located character, 
or NULL if the character does not appear in the string.
*/

char	*ft_strrchr(const char *s, int c);
/*
//@brief Locates the last occurrence of c (converted to a char)
in the string pointed to by s. The terminating null character is considered
to be part of the string; therefore if c is `\0', the functions locate the
terminating `\0'.
//@param s The pointer to the string to be searched.
//@param c The character to be searched.
//@return The pointer to the located character,
or NULL if the character does not appear in the string.
*/

int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*
//@brief Compares the two strings s1 and s2. It returns an integer less than,
equal to, or greater than zero if s1 is found, respectively, to be less than,
to match, or be greater than s2.
//@param s1 The pointer to the first string to be compared.
//@param s2 The pointer to the second string to be compared.
//@param n The maximum number of characters to be compared.
//@return The difference between the first two differing characters
(when interpreted as unsigned char values, they are compared).
*/

int		ft_strcmp(const char *s1, const char *s2);
/*
//@brief Compares the two strings s1 and s2. It returns an integer less than,
equal to, or greater than zero if s1 is found, respectively, to be less than,
to match, or be greater than s2.
//@param s1 The pointer to the first string to be compared.
//@param s2 The pointer to the second string to be compared.
//@return The difference between the first two differing characters
(when interpreted as unsigned char values, they are compared).
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
/*
//@brief Locates the first occurrence of the null-terminated string needle
in the string haystack, where not more than len characters are searched.
Characters that appear after a `\0' character are not searched.
//@param haystack The pointer to the string to be searched.
//@param needle The pointer to the string to be searched for.
//@param len The maximum number of characters to be searched.
//@return The pointer to the located character,
or NULL if the character does not appear in the string.
*/

char	*ft_memchr(const void *s, int c, size_t n);
/*
//@brief Locates the first occurrence of c (converted to an unsigned char)
in string s.
//@param s The pointer to the string to be searched.
//@param c The character to be searched.
//@param n The maximum number of characters to be searched.
//@return The pointer to the located character,
or NULL if the character does not appear in the string.
*/

int		ft_memcmp(const void *s1, const void *s2, size_t n);
/*
//@brief Compares byte string s1 against byte string s2. Both strings are
assumed to be n bytes long.
//@param s1 The pointer to the first string to be compared.
//@param s2 The pointer to the second string to be compared.
//@param n The maximum number of characters to be compared.
//@return The difference between the first two differing characters
(when interpreted as unsigned char values, they are compared).
*/

int		ft_atoi(const char *str);
/*
//@brief Converts the initial portion of the string pointed to by str to int.
//@param str The pointer to the string to be converted.
//@return The converted value.
*/

void	*ft_calloc(size_t count, size_t size);
/*
//@brief Allocates memory for an array of count elements of size bytes each
and returns a pointer to the allocated memory. The memory is set to zero.
If count or size is 0, then calloc() returns either NULL, or a unique pointer
value that can later be successfully passed to free().
//@param count The number of elements to be allocated.
//@param size The size of elements to be allocated.
//@return The pointer to the allocated memory.
*/

char	*ft_strdup(const char *s1);
/*
//@brief Allocates sufficient memory for a copy of the string s1, does the copy,
and returns a pointer to it. The pointer may subsequently be used as an argument
to the function free(3). If insufficient memory is available, NULL is returned
and errno is set to ENOMEM.
//@param s1 The pointer to the string to be copied.
//@return The pointer to the allocated memory.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len);
/*
//@brief Allocates (with malloc(3)) and returns a substring from the string s.
The substring begins at index start and is of maximum size len.
//@param s The pointer to the string to be copied.
//@param start The start index of the substring.
//@param len The maximum size of the substring.
//@return The pointer to the allocated memory.
*/

char	*ft_strjoin(char const *s1, char const *s2);
/*
//@brief Allocates (with malloc(3)) and returns a new string, which is the result
of the concatenation of s1 and s2.
//@param s1 The pointer to the first string to be concatenated.
//@param s2 The pointer to the second string to be concatenated.
//@return The pointer to the allocated memory.
*/

char	*ft_strtrim(char const *s1, char const *set);
/*
//@brief Allocates (with malloc(3)) and returns a copy of s1 with the characters
specified in set removed from the beginning and the end of the string.
//@param s1 The pointer to the string to be copied.
//@param set The pointer to the set of characters to be removed.
//@return The pointer to the allocated memory.
*/

char	**ft_split(char const *s, char c);
/*
//@brief Allocates (with malloc(3)) and returns an array of strings obtained by
splitting ’s’ using the character ’c’ as a delimiter. The array must be ended
by a NULL pointer.
//@param s The pointer to the string to be splitted.
//@param c The character to be used as delimiter.
//@return The pointer to the allocated memory.
*/

char	*ft_itoa(int n);
/*
//@brief Allocates (with malloc(3)) and returns a string representing the integer
received as an argument. Negative numbers must be handled.
//@param n The integer to be converted.
//@return The pointer to the allocated memory.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*
//@brief Applies the function ’f’ to each character of the string ’s’ to create
a new string (with malloc(3)) resulting from successive applications of ’f’.
//@param s The pointer to the string to be modified.
//@param f The pointer to the function to be applied.
//@return The pointer to the allocated memory.
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *));
/*
//@brief Applies the function f to each character of the string
passed as argument,and passing its index as first argument. 
Each character is passed by address to f to be modified if necessary.
//@param s The pointer to the string to be modified.
//@param f The pointer to the function to be applied.
//@return None.
*/

void	ft_putchar_fd(char c, int fd);
/*
//@brief Outputs the character ’c’ to the given file descriptor.
//@param c The character to output.
//@param fd The file descriptor on which to write.
//@return None.
*/

void	ft_putstr_fd(char *s, int fd);
/*
//@brief Outputs the string ’s’ to the given file descriptor.
//@param s The string to output.
//@param fd The file descriptor on which to write.
//@return None.
*/

void	ft_putendl_fd(char *s, int fd);
/*
//@brief Outputs the string ’s’ to the given file descriptor, followed by a
newline.
//@param s The string to output.
//@param fd The file descriptor on which to write.
//@return None.
*/

void	ft_putnbr_fd(int n, int fd);
/*
//@brief Outputs the integer ’n’ to the given file descriptor.
//@param n The integer to output.
//@param fd The file descriptor on which to write.
//@return None.
*/

t_list	*ft_lstnew(void *content);
/*
//@brief Allocates (with malloc(3)) and returns a new element. The variable
’content’ is initialized with the value of the parameter ’content’. The
variable ’next’ is initialized to NULL.
//@param content The content to be added to the new element.
//@return The new element.
*/

void	ft_lstadd_front(t_list **lst, t_list *new);
/*
//@brief Adds the element ’new’ at the beginning of the list.
//@param lst The address of a pointer to the first link of a list.
//@param new The address of a pointer to the element to be added to the list.
//@return None.
*/

int		ft_lstsize(t_list *lst);
/*
//@brief Counts the number of elements in a list.
//@param lst The beginning of the list.
//@return Length of the list.
*/

t_list	*ft_lstlast(t_list *lst);
/*
//@brief Returns the last element of the list.
//@param lst The beginning of the list.
//@return The last element of the list.
*/

void	ft_lstadd_back(t_list **lst, t_list *new);
/*
//@brief Adds the element ’new’ at the end of the list.
//@param lst The address of a pointer to the first link of a list.
//@param new The address of a pointer to the element to be added to the list.
//@return None.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*));
/*
//@brief Takes as a parameter an element and frees the memory of the element’s
content using the function ’del’ given as a parameter and free the element.
The memory of ’next’ must not be freed.
//@param lst The element to free.
//@param del The address of the function used to delete the content.
//@return None.
*/

void	ft_lstclear(t_list **lst, void (*del)(void*));
/*
//@brief Deletes and frees the given element and every successor of that element,
using the function ’del’ and free(3). Finally, the pointer to the list must be
set to NULL.
//@param lst The address of a pointer to an element.
//@param del The address of the function used to delete the content.
//@return None.
*/

void	ft_lstiter(t_list *lst, void (*f)(void *));
/*
//@brief Iterates the list ’lst’ and applies the function ’f’ to the content of
each element.
//@param lst The address of a pointer to an element.
//@param f The address of the function used to iterate on the list.
//@return None.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*
//@brief Iterates the list ’lst’ and applies the function ’f’ to the content of
each element. Creates a new list resulting of the successive applications of
the function ’f’. The ’del’ function is used to delete the content of an
element if needed.
//@param lst The address of a pointer to an element.
//@param f The address of the function used to iterate on the list.
//@param del The address of the function used to delete the content.
//@return The new list. NULL if the allocation fails.
*/

void	*ft_destroyer(char **to_destroy);
/*
@brief Frees a 2D pointer array if it is not NULL.
@param to_destroy The pointer to the 2D array to be freed.
@return NULL.
*/

char	*ft_strjoin_free_s2(char const *s1, char *s2);
/*
@brief Allocates (with malloc(3)) and returns a new string, which is the result
of the concatenation of s1 and s2. ALso frees the second string.
@param s1 The pointer to the first string to be concatenated.
@param s2 The pointer to the second string to be concatenated.
@return The pointer to the allocated memory.
NOTE: The second string has to be an allocated memory.
*/

char	*ft_strjoin_free_s1(char *s1, char const *s2);
/*
@brief Allocates (with malloc(3)) and returns a new string, which is the result
of the concatenation of s1 and s2. ALso frees the first string.
@param s1 The pointer to the first string to be concatenated.
@param s2 The pointer to the second string to be concatenated.
@return The pointer to the allocated memory.
NOTE: The first string has to be an allocated memory.
*/

void	*ft_split_destroyer(char **split);
/*
@brief Frees a 2D pointer array if it is not NULL.
@param split The pointer to the 2D array to be freed.
@return NULL.
*/

void	ft_del(void *s);
/*
*/

#endif