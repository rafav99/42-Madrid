#ifndef FT_PRINTF_SHARED_H
# define FT_PRINTF_SHARED_H
# include <stdarg.h>
char *ft_vsprintf(const char *format, va_list args);
int ft_dprintf(int fd, const char *format, ...);
#endif
