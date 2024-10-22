#include <stdio.h>
char    *ft_strchr(char *s, char ch)
{
          char    *ref;
 
          if (!s)
                  return (NULL);
          ref = s;
          while (*ref)
          {
                  if (*ref == ch)
                          break ;
                  ref++;
          }
          if (*ref == '\0')
                return (NULL);
         return (ref);
}

int	main(void){
	char *x = "absdjn sdsdc";
	char	*y = ft_strchr(x, 'd');
	printf("%s", y);

}
