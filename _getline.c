#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * else_handle_input - if buffer does not include \n or EOF
 * @lineptr: the buffer to put the data in
 * @stream: the stream to read from
 * @input: buffer
 * @filled: size of buffer
 * Return: _getline function
 */
ssize_t else_handle_input(char *lineptr, int stream, char *input, int filled)
{
	int red;
	char tmp;

	/* if the buffer is full then read until \n or EOF */
	if (filled == 4096)
	{
		/* should always fill buffer with \n or EOF at end*/
		red = 1;
		while (red && tmp != '\n')
		{
			tmp = 0;
			red = read(stream, &tmp, 1);
		}
		input[4095] = '\n';
		return (_getline(lineptr, stream));
	}
	/* if the buffer isn't full, then fill it and try again. */
	else
	{
		red = read(stream, input + filled, 4096 - filled);
		/* ctrl D was pressed if red is less */
		if (red < (4096 - filled))
			input[filled + red] = '\n';
		filled = filled + red + 1;
		return (_getline(lineptr, stream));
	}
}

/**
 * _getline - reads a number of chars from stdin
 * @lineptr: the buffer to put the data in
 * @stream: the stream to read from
 * Return: the number of bytes read
 */
ssize_t _getline(char *lineptr, int stream)
{
	static char input[4096];
	static int filled;
	int newline_index = -1, i = 0, red = 0;
	ssize_t ret = 0;

	/* if the buffer is empty, fill it */
	if (!filled)
	{
		while ((red = read(stream, input, 4096)) < 0)
		{
			perror("Read Error\n");
			return (-1);
		}
		filled = red;
		if (!red)
			return (0);
	}

	/* if the buffer contains \n or EOF */
	newline_index = has_newline(input);
	if (newline_index != -1)
	{
		for (i = 0; i <= newline_index; i++)
			lineptr[i] = input[i];
		ret = newline_index;
		if (input[ret] == '\n')
			ret = ret + 1;
		/* Shift any remaining chars to the left */
		shiftbuffer(input, newline_index + 1, filled);
		filled = filled - ret;
		return (ret);
	}
	/* if the buffer doesn't contain \n or EOF */
	else
		else_handle_input(lineptr, stream, input, filled);
	return (-1);
}
