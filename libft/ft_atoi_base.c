#include "libft.h"

static int	char_to_int_convert(char ch)
{
	if (ft_isdigit(ch))
		return ((int)(ch - '0'));
	if (ch >= 'a' && ch <= 'z')
		return ((int)(ch - 'a' + 10));
	if (ch >= 'A' && ch <= 'Z')
		return ((int)(ch - 'A' + 10));
	return (0);
}

int			ft_atoi_base(const char *str, int base)
{
	int		dst;
	short	i;

	if (!str)
		return (0);
	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	dst = 0;
	while (i >= 0)
	{
		dst = dst * base;
		dst += char_to_int_convert(str[i--]);
	}
	return (dst);
}