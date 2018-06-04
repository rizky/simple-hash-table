/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash-table-int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:23:53 by rnugroho          #+#    #+#             */
/*   Updated: 2018/06/04 15:28:19 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct	s_data_item
{
	int		key;
	int		data;

} t_data_item;

t_data_item		*hash_array[SIZE];

int
	hash_code(int key)
{
	return (key % SIZE);
}

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
	return (hash_index);
}

t_data_item
	*search(int key)
{
	int	hash_index;

	hash_index = hash_code(key);
	while (hash_array[hash_index] != NULL)
	{
		if (hash_array[hash_index]->key == key)
			return (hash_array[hash_index]);
		hash_index++;
		hash_index %= SIZE;
	}
	return (NULL);
}

void
	insert(int key, int data)
{
	int			hash_index;
	t_data_item	*item;

	item = (t_data_item*)malloc(sizeof(t_data_item));
	item->data = data;
	item->key = key;

	hash_index = hash_code(key);
	while (hash_array[hash_index] != NULL && hash_array[hash_index]->key != -1)
	{
		++hash_index;
		hash_index %= SIZE;
	}

	hash_array[hash_index] = item;
}

t_data_item
	*delete(t_data_item *item)
{
	int			key;
	int			hash_index;
	t_data_item	*temp;
	t_data_item	*deleted_item;

	deleted_item = (t_data_item*)malloc(sizeof(t_data_item));
	deleted_item->data = -1;
	deleted_item->key = -1;

	key = item->key;
	hash_index = hash_code(key);
	while (hash_array[hash_index] != NULL)
	{
		if (hash_array[hash_index]->key == key)
		{
			temp = hash_array[hash_index];
			hash_array[hash_index] = deleted_item;
			return (temp);
		}
		++hash_index;
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
		if (hash_array[i] != NULL)
			printf(" (%d,%d)", hash_array[i]->key, hash_array[i]->data);
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

	insert(1, 20);
	insert(2, 70);
	insert(2, 80);
	insert(4, 25);

	display();
	item = search(4);
	if (item != NULL)
		printf("Element found: %d => %d\n", item->key, item->data);
	else
		printf("Element not found\n");

	delete(item);
	item = search(4);

	if (item != NULL)
		printf("Element found: %d\n", item->data);
	else
		printf("Element not found\n");
	return (0);
}
