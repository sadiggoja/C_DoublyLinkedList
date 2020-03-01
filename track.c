#include <stdio.h>	
#include<stdlib.h>

struct Track
{
	char * name;
	char * genre;
	char *artist;
	int dur;	
};


struct TrackNode
{
	struct Track * track;
	struct TrackNode * prev;
	struct TrackNode *next;
};

struct Playlist
{
char * title;
struct TrackNode *head;
struct TrackNode *tail;
int ntracks;
int tdur;
struct TrackNode *current;
int current_dur;	
};

struct Track *track_new(char *name, char *artist, char *genre, int dur){
	struct Track *new=(struct Track *)malloc(sizeof(struct Track));
	new->name=name;
	new->artist=artist;
	new->genre=genre;
	new->dur=dur;
	return new;
}

struct TrackNode *node_new(struct Track *track){
	struct TrackNode *new=(struct TrackNode*)malloc(sizeof(struct TrackNode));
	new->track=track;
	new->prev=NULL;
	new->next=NULL;
	return new;
}

struct Playlist * Pl_new (char *title){
	struct Playlist *new=(struct Playlist*)malloc(sizeof(struct Playlist));
	new->title=title;
	new->head=NULL;
	new->tail=NULL;
	new->ntracks=0;
	new->tdur=0;
	new->current=NULL;
	new->current_dur=0;
	return new;
}
void Pl_append(struct Playlist **list, struct  Track *track){
	(*list)->ntracks+=1;
	(*list)->tdur+=track->dur;
	struct TrackNode *node=node_new(track);
	struct TrackNode *temp=(*list)->tail;
	if((*list)->ntracks==1){
		(*list)->tail=(*list)->head=node;
	}
	else {
		temp->next=node;
		node->prev=temp;
		(*list)->tail=node;
	}
}

void pl_remove(struct Playlist **list, char * name){
	struct TrackNode *temp=(*list)->head;
	while(temp!=NULL){
		if(temp->track->name==name){
			(*list)->ntracks-=1;
			(*list)->tdur-=temp->track->dur;
			if (temp==(*list)->head){
				(*list)->head=temp->next;
				(*list)->head->prev=NULL;
				return;
			} 
			if(temp==(*list)->tail){
				(*list)->tail=temp->prev;
				(*list)->tail->next=NULL;
				return;
			}
			temp->prev->next=temp->next;
			temp->next->prev=temp->prev;
			return;
		}
	
	temp=temp->next;
	}
}

void ch_order(struct Playlist **list, char *name, int order){
	struct TrackNode * node=(*list)->head;
	 
	for (int i = 1; i < order; i++){
	  	node=node->next;
	 }

	struct TrackNode * temp=(*list)->head;
	struct TrackNode * temp2;
	int order2=1;
	while(temp!=NULL){
		if (temp->track->name==name){
			if (temp==node)
			{
				return;
			}	
			temp2=temp;
			pl_remove(&(*list), name);
			break;
		}
		temp=temp->next;
		order2++;
	}
	// printf("%s\n\n",temp2->track->name );
	// printf("%s\n\n",node->track->name );
	// printf("%d\n", a);
	if (order==1)
	{
		node->prev=temp2;
		temp2->next=node;
		(*list)->head=temp2;
	}else if (order-1==((*list)->ntracks)){
		Pl_append(&(*list), temp2->track);	
	}else if (order2<order){

		temp2->next=node->next;
		temp2->next->prev=temp2;
		temp2->prev=node;
		node->next=temp2;
	}else{
		temp2->next=node;
		temp2->prev=node->prev;
		temp2->prev->next=temp2;
		node->prev=temp2;
		
	}
}


void pr(struct Playlist **list){ //for printing
	if ((*list)->ntracks==0)
	{
		printf("no track\n");
		return;
	}
	struct TrackNode *temp= (*list)->head;
	while(temp!=NULL){
		printf("%s\n", temp->track->name );
		temp=temp->next;
	}
	printf("-----------\n");
	printf("head: %s \n",(*list)->head->track->name);
	printf("tail: %s \n",(*list)->tail->track->name);
	printf("-----------\n");
}

void pl_clear(struct Playlist **list){ //to 
	if ((*list)->tail->prev!=NULL){
		(*list)->tdur-=(*list)->tail->track->dur;
		(*list)->ntracks--;
		(*list)->tail->track=NULL;
		(*list)->tail=(*list)->tail->prev;
		(*list)->tail->next=NULL;
		pl_clear(&(*list));
	}else {
		(*list)->tdur-=(*list)->tail->track->dur;
		(*list)->ntracks--;
		(*list)->head=(*list)->tail=NULL;
		return;
	}
}



void main()
{
	struct Track* okaber=track_new("demedi deme", "okaber","rap", 15);
	//struct TrackNode * newnode=node_new(okaber);
	struct Playlist *newlist=Pl_new("rap");
	//printf("%s\n",annny->title );
	Pl_append(&newlist, okaber);
	struct Track* aid=track_new("uuaa", "aid", "rap", 25);
	struct Track* synaps=track_new("iricapli", "synaps", "rap", 35);
	struct Track* synaps2=track_new("cyber", "synaps", "rap", 55);
	struct Track* synaps3=track_new("saman", "xpert", "rap", 45);
	Pl_append(&newlist, aid);
	Pl_append(&newlist, synaps);
	Pl_append(&newlist, synaps2);
	Pl_append(&newlist, synaps3);
	// pl_remove(&newlist, "iricapli");
	// //pl_remove(&newlist, synaps);
	// printf("%d\n",newlist->ntracks );

	// printf("%d\n",newlist->tdur );
	// printf("%s\n",newlist->head->track->name );
	// printf("%s\n",newlist->head->next->track->name );
	// printf("%s\n",newlist->tail->track->name );		
	//pr(&newlist);
	//ch_order(&newlist, "cyber" ,5);
	//printf("%s\n", newlist->head->next->track->name );
	//pl_remove(&newlist, "demedi deme");
	pr(&newlist);
	pl_clear(&newlist);
	pr(&newlist);
}