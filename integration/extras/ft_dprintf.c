#include "ft_printf.h"
#include "libft.h"
int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	char	*str;
	int		len;

	va_start(args, format);
	str = ft_vsprintf(format, args);
	va_end(args);
	if (!str)
		return (-1);
	len = write(fd, str, ft_strlen(str));
	free(str);
	return (len);
}

