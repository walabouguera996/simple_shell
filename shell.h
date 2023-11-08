#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct list_s - singly linked list
 * @n: integer
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_s
{
	int n;
	char *str;
	struct list_s *next;
} list_t;

/**
 *struct pif - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@l_h: the error count
 *@err_num: the error code for exit()s
 *@lc_f: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@environ_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buff: address of pointer to cmd_buf, on if chaining
 *@cmd_b_t: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct pif
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int l_h;
	int err_num;
	int lc_f;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int environ_changed;
	int status;

	char **cmd_buff;
	int cmd_b_t;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct bsrf - contains a builtin string and related function
 *@type: the builtin command flag
 *@f: the function
 */
typedef struct bsrf
{
	char *type;
	int (*func)(info_t *);
} builtin_t;


int hsh(info_t *, char **);
int f_builtin(info_t *);
void f_cmd(info_t *);
void fork_cmd(info_t *);

int my_cmd(info_t *, char *);
char *dupli_chars(char *, int, int);
char *f_path(info_t *, char *, char *);

int loophsh(char **);

void _eputstr(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putstrfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchar(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);

int inter(info_t *);
int delim(char, char *);
int _alpha(int);
int _atoi(char *);

int _erroratoi(char *);
void print_error(info_t *, char *);
int print_decimal(int, int);
char *convert_num(long int, int, int);
void remove_comments(char *);

int _ourexit(info_t *);
int _ourcd(info_t *);
int _ourhelp(info_t *);

int _ourhistory(info_t *);
int _ouralias(info_t *);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_inf(info_t *);
void set_inf(info_t *, char **);
void free_inf(info_t *, int);

char *_getenv(info_t *, const char *);
int _ourenv(info_t *);
int _oursetenv(info_t *);
int _ourunsetenv(info_t *);
int populate_env_l(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *get_h_f(info_t *inf);
int write_h(info_t *inf);
int read_h(info_t *inf);
int build_h_l(info_t *inf, char *buf, int linecount);
int renumber_h(info_t *inf);

list_t *add_n(list_t **, const char *, int);
list_t *add_n_e(list_t **, const char *, int);
size_t print_l_s(const list_t *);
int delete_n_at_index(list_t **, unsigned int);
void free_l(list_t **);

size_t l_len(const list_t *);
char **l_to_strings(list_t *);
size_t print_l(const list_t *);
list_t *n_starts_with(list_t *, char *, char);
ssize_t get_n_index(list_t *, list_t *);

int my_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_vars(info_t *);
int rep_string(char **, char *);

#endif

