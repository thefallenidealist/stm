
// ono sa cime serijski usporedjuje
char str_a[] = "ab";

void usart1_parse(void)
{
	printf("evo ga usart1_parse\n");

	char *usporedi = str_a;

	int compare = strncmp(rx_string, usporedi, USART_CMD_LENGTH);

	if (compare == 0)
	{
		printf("rx_string matcha \"%s\"\n", usporedi);
	}
	else
	{
		printf("rx_string nije dobio \"%s\" nego \"%s\"\n", usporedi, rx_string);
	}
}
