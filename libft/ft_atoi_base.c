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
	short	len;
	short	i;

	if (!str)
		return (0);
	len = 0;
	while (ft_isalnum(str[len]))
		len++;
	dst = 0;
	i = 0;
	while (i < len)
	{
		dst = dst * base;
		dst += char_to_int_convert(str[i++]);
	}
	return (dst);
}