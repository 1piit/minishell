# Minishell — How implement test

int	main(void)
{
	int	a;
	int	b;
	int	c;

	a = 1;
	b = 2;
	c = 2;
	printf("%sTest si a == b:\n", NC);
	assert_eq(2, b, __FILE__, __LINE__);
	printf("%sTest si b != c:\n", NC);
	assert_eq(b, c, __FILE__, __LINE__);
	return (0);
}

