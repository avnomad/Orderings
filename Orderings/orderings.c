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
