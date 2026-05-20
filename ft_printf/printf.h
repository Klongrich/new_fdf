#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

#define CHECK(format, ...) do { \
    int r1, r2; \
    printf("checking %s\n", format); \
    r1 = printf("ORIG: " format, __VA_ARGS__); \
    printf("\n"); \
    r2 = ft_printf("MINE: " format, __VA_ARGS__); \
    printf("\n"); \
    if (r1 != r2) { \
        printf("\033[31m[KO] Return values differ! (Orig: %d, Mine: %d)\033[0m\n", r1, r2); \
    } else { \
        printf("\033[32m[OK] Return values match: %d\033[0m\n", r1); \
    } \
    printf("--------------------\n"); \
} while (0)

int    ft_printf(char *str, ...); 

typedef struct args {
	int	zero;
	int	left;
	int	padding;
	int	pound;
	int	space;
	int 	plus;
	int	dot;
	int	is_uppercase;
	int	h;
	int	hh;
	int	l;
	int	ll;
	int	hex;
	int	octal;
	int	decimal;
	int	string;
	int	pointer;
	int	character;
	int	is_float;
	int	is_signed;
	int	is_unsigned;
	int	not_zero;
	int	positive;
	int	negative;
	int	is_L;
}		t_args;

typedef struct norm_struct {
	int	i;
	int	count;
}	t_norm;

int put_float(long double f, t_args args);
