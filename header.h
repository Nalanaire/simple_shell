#ifndef _SIMPLE_H_
#define _SIMPLE_H_

/* included standard library headers */
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

/* read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - linked list
 *@num: number
 *@str: string
 *@next: next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - pseudo-arguements to pass into the function,
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
 *struct builtin - builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* ---memory.c--- */
int sfree(void **);

/* ---loophsh.c--- */
int loophsh(char **);

/* ---shloop.c--- */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* ---string.c--- */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* ---string1.c--- */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* ---builtin.c--- */
int _mexit(info_t *);
int _mcd(info_t *);
int _mhelp(info_t *);

/* ---builtin1.c--- */
int _mhistory(info_t *);
int _malias(info_t *);

/* ---errors.c--- */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* ---errors1.c--- */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* ---lists.c--- */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* ---lists1.c--- */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* ---atoi.c--- */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* ---parser.c--- */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* ---getline.c--- */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* ---getinfo.c--- */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* ---getenv.c--- */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* ---environ.c--- */
char *_getenv(info_t *, const char *);
int _byenv(info_t *);
int _bysetenv(info_t *);
int _byunsetenv(info_t *);
int expand_env_list(info_t *);

/* ---history.c--- */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* ---exit.c--- */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* ---realloc.c--- */
char *_memset(char *, char, unsigned int);
void tfree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* ---tokenizer.c--- */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* ---vars.c--- */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
