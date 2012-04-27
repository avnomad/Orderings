//	Copyright (C) 2007, 2008, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Orderings.
 *
 *	Orderings is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Orderings is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Orderings.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node_tag
{
	struct node_tag *next;
	struct node_tag *prev;
	int content;
} node;
	
typedef struct head_tag
{
	node *next;
	node *prev;
} head;

void orderings(int n,int k);

int main()
{
	unsigned int n,k;

	printf("Give the number of elements in the set and it's subsets: ");
	scanf("%u%u",&n,&k);
	orderings(n,k);
	system("PAUSE");
	return 0;
}

void orderings(int n,int k)
{
	node **subset,*temp;
	head set;
	int c,i;
		
	set.next = (node*)&set;
	set.prev = (node*)&set;
	for(c=0;c<n;c++)
	{
		temp = set.prev;
		set.prev = malloc(sizeof(node));
		set.prev->next = (node*)&set;
		set.prev->prev = temp;
		temp->next = set.prev;
		set.prev->content = c+1;
	}
	
	subset = malloc(k*sizeof(node*));	
	for(c=0;c<k-1;c++)
	{			
		*(subset+c) = set.next;
		(*(subset+c))->next->prev = (*(subset+c))->prev;
		(*(subset+c))->prev->next = (*(subset+c))->next;             		
	}
	*(subset+c) = set.next;
	
	i = 0;
	for(;;)
	{
		printf("%3.d:\t",++i);
		
		for(c=0;c<k;c++)
		{
			printf("%d\t",(*(subset+c))->content);
		}
		putchar('\n');
		c = k-1;
		*(subset+c) = (*(subset+c))->next;
		while(c && *(subset+c)==(node*)&set)
		{			
			c--;
			(*(subset+c))->next->prev = *(subset+c);
			(*(subset+c))->prev->next = *(subset+c);
			*(subset+c) = (*(subset+c))->next;
		}
		if(*(subset)==(node*)&set) break;
		while(c<k-1)
		{			
			(*(subset+c))->next->prev = (*(subset+c))->prev;
			(*(subset+c))->prev->next = (*(subset+c))->next;
			c++;
			*(subset+c) = set.next;
		}
	}
}
