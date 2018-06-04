/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash-table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:23:53 by rnugroho          #+#    #+#             */
/*   Updated: 2018/06/04 16:11:48 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

typedef struct	s_data_item
{
	char	*key;
	int		data;
} t_data_item;

t_data_item		*g_hash_array[SIZE];

int
	hash_code_str(char *key)
{
	int hash_index;
	int	i;

	hash_index = 0;
	i = 0;
	while (key[i] != '\0')
	{
		hash_index = key[i] + (hash_index << 6) +
			(hash_index << 16) - hash_index;
		i++;
	}
	return (hash_index % SIZE);
}

t_data_item
	*search(char *key)
{
	int	hash_index;

	hash_index = hash_code_str(key);
	while (g_hash_array[hash_index] != NULL)
	{
		if (strcmp(g_hash_array[hash_index]->key, key) == 0)
			return (g_hash_array[hash_index]);
		hash_index++;
		hash_index %= SIZE;
	}
	return (NULL);
}

void
	insert(char *key, int data)
{
	int			hash_index;
	t_data_item	*item;

	item = (t_data_item*)malloc(sizeof(t_data_item));
	item->data = data;
	item->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(item->key, key);

	hash_index = hash_code_str(key);
	while (g_hash_array[hash_index] != NULL &&
		g_hash_array[hash_index]->key != NULL)
	{
		++hash_index;
		hash_index %= SIZE;
	}

	g_hash_array[hash_index] = item;
}

t_data_item
	*delete(t_data_item *item)
{
	int			key;
	int			hash_index;
	t_data_item	*temp;

	if (!item)
		return (NULL);
	hash_index = hash_code_str(item->key);
	while (g_hash_array[hash_index] != NULL)
	{
		if (strcmp(g_hash_array[hash_index]->key, item->key) == 0)
		{
			temp = g_hash_array[hash_index];
			g_hash_array[hash_index] = NULL;
			return (temp);
		}
		hash_index++;
		hash_index %= SIZE;
	}
	return (NULL);
}

void
	display(void)
{
	int i;

	i = 0;
	while (i < SIZE)
	{
		if (g_hash_array[i] != NULL)
			printf(" (%s,%d)", g_hash_array[i]->key, g_hash_array[i]->data);
		else
			printf(" ~~ ");
		i++;
	}
	printf("\n");
}

int
	main(void)
{
	t_data_item		*item;

	insert("hello", 20);
	insert("how", 70);
	insert("are", 80);
	insert("you", 25);
	insert("you", 25);

	display();
	item = search("O");
	if (item != NULL)
		printf("Element found: %s => %d\n", item->key, item->data);
	else
		printf("Element not found\n");

	delete(item);
	item = search("are");

	if (item != NULL)
		printf("Element found: %d\n", item->data);
	else
		printf("Element not found\n");
	display();
	return (0);
}
