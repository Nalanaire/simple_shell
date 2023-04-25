#ifndef _SIMPLE_H_
#define _SIMPLE_H_

/* included standard library headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* converting numbers */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - pseudo-arguements to pass into the function,
 *to allow uniform prototype for function pointer struct
 *@arg: string generated from getline containing arguments
 *@argv: array of strings generated from arg
 *@path: string path for the current command
 *@argc: argument count
 *@env: copy of environ
 *@environ: modified copy of environ from LL env
 *@alias: alias node
 *@line_count: error count
 *@err_num: error code for exit()s
 *@linecount_flag: counting line of input
 *@fname: filename
 *@env_changed: if environ was changed
 *@status: return status of the last executed command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: fd from which to read line input
 *@history: the history node
 *@histcount: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	char **environ;
	list_t *alias;
	list_t *env;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *history;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - builtin string with related function
 *@type: command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* _shloop.c */
void _find_cmd(info_t *);
void _fork_cmd(info_t *);
int _hsh(info_t *, char **);
int _find_builtin(info_t *);

/* parser.c */
int _iscmd(info_t *, char *);
char *_dupchars(char *, int, int);
char *_findpath(info_t *, char *, char *);

/* _loophsh.c */
int loophsh(char **);

/* errors0.c */
void rputs(char *);
int rputchar(char);
int putfd(char c, int fd);
int putsfd(char *str, int fd);

/* stringA.c */
int str_len(char *);
int str_cmp(char *, char *);
char *_starts_with(const char *, const char *);
char *str_cat(char *, char *);

/* stringB.c */
char *str_cpy(char *, char *);
char *str_dup(const char *);
void puts(char *);
int _putchar(char);

/* exit.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **_strtow(char *, char *);
char **_strtow0(char *, char);

/* realloc.c */
void *realloc(void *, unsigned int, unsigned int);
char *memset(char *, char, unsigned int);
void tfree(char **);

/* _memory.c */
int sfree(void **);

/* _isalpha.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errorsA.c */
int rratoi(char *);
void _print_error(info_t *, char *);
int print_j(int, int);
char *_convert_numb(long int, int, int);
void delete_comments(char *);

/* builtin.c */
int exit(info_t *);
int cd(info_t *);
int help(info_t *);

/* builtin1.c */
int _history(info_t *);
int _alias(info_t *);

/* getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *_find_history_file(info_t *info);
int type_history(info_t *info);
int do_history(info_t *info);
int _create_history_list(info_t *info, char *buf, int linecount);
int recount_history(info_t *info);

/* listsA.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* listsB.c */
char **_list_to_strings(list_t *);
size_t _list_len(const list_t *);
size_t _print_list(const list_t *);
list_t *_node_starts_with(list_t *, char *, char);
ssize_t _get_node_index(list_t *, list_t *);

/* vars.c */
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int _ischain(info_t *, char *, size_t *);
int _replace_string(char **, char *);
int _replace_alias(info_t *);
int _replace_vars(info_t *);

/* getline.c */
ssize_t _get_input(info_t *);
int getline(info_t *, char **, size_t *);
void _siginthandler(int);
ssize_t _read_buf(info_t *info, char *buf, size_t *i);
ssize_t _input_buf(info_t *info, char **buf, size_t *len);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char *_getenv(info_t *, const char *);
int _env(info_t *);
int _setenv(info_t *);
int _unsetenv(info_t *);
int occupy_env_list(info_t *);
#endif
