#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct President{
	char name[20];
	int nbVote;
	int num;
	struct President *next;
}President;

President* addPresident(President *head){
	President *neww;
	int a;
	neww = (President*)malloc(sizeof(President));
	printf("Enter president's name to add: ");
	scanf("%s",&neww->name);
	printf("Enter president's number to add:");
	scanf("%d",&neww->num);
	neww->nbVote=0;
	neww->next=head;
	head = neww;
	return head;
}

President* deletePresident(President *head,int num){
	President* tmp=head;
	President* p;
		if(head==NULL){ 
			printf("The list is empty, nothing to delete.\n");
		}
		if(head->num==num){
			p=head;
			head=head->next;
			free(p);
		}else{
			while(tmp!=NULL){
				if(tmp->next->num==num){
					p=tmp->next;
					tmp->next=tmp->next->next;
					free(p);
					break;	
				}	
			tmp=tmp->next;
			}	
		}
		return head;
}

int vote(President *head,char elector[],int dim){
	int a,i,x=0;
	President *neww=head;
	
		for(i=0;i<dim;i++){
			neww=head;
			while(neww!=NULL){
			printf("To vote for Mr/Ms %s type %d: \n",neww->name,neww->num);
			neww=neww->next;	
			}
		scanf("%d",&a);
		neww=head;
			while(neww!=NULL){
				if(a==neww->num){
					neww->nbVote+=1;	
					break;
				}
				neww=neww->next;
			}
		}
		neww=head;
			while(neww->next!=NULL){
			if(neww->nbVote!=neww->next->nbVote){
					x=1;
			}
			neww=neww->next;
			}
		return x;
	}

President* resetToZero(President* head){
	President* current=head;
	while(current!=NULL){
		current->nbVote=0;
		current=current->next;
	}
	return head;
}	

int main(){
	President *pre=NULL;
	printf("-------------------Filling the list of presidents:-----------------\n\n");
	int i,nbPre;
	do{
	 	printf("Enter the number of presidents: \n");
	 	scanf("%d",&nbPre);
	}while(nbPre<5);
	for(i=0;i<nbPre;i++){
	 	pre=addPresident(pre);
	}
	printf("\n------------------Filling the list of electors:-----------------\n\n");
	int dim;
	do{
		printf("Enter the number of electors: \n");
		scanf("%d",&dim);
	}while(dim<10);
	char* elector;
	elector=(char*)malloc(dim*sizeof(char));
	int j;
	for(j=0;j<dim;j++)
	{
		printf("Enter the elector's CIN number %d:\n",j+1);
		scanf("%s",&elector[j]);
	}
	printf("\n-------------------------First Round:--------------------------\n\n");
	int x=0,search;
	President* current=pre;
	search=vote(pre,elector,dim);
	do{
		if(search==0){
			printf("The round must be redone.\n");
			search = vote(pre,elector,dim);
		}else{
		while(current!=NULL){
				if((current->nbVote*100/dim<15)){
				printf("The person who will be excluded is: %s\n",current->name);
				pre=deletePresident(pre,current->num);	
				}
			current=current->next;
				}
			x=1;
		}
	}while(x==0);
	printf("\n-------------------------Second Round:--------------------------\n\n");
	pre=resetToZero(pre);
	x=0;
	search=vote(pre,elector,dim);
	current=pre;
	int min=pre->nbVote;
	do{
		if(search==0){
			printf("The round must be redone.\n");
			search = vote(pre,elector,dim);
		}else{
			while(current->next!=NULL){
				if(current->next->nbVote<min){
					min=current->next->nbVote;
				}
				current=current->next;	
			}
				current=pre;
			while(current!=NULL){
				if(current->nbVote==min){
					printf("The person who will be excluded is: %s\n",current->name);
					pre=deletePresident(pre,current->num);
				}
			current=current->next;	
			}
				x=1;	
		}
	}while(x==0);
	printf("\n-------------------------Last Round:--------------------------\n\n");
	pre=resetToZero(pre);
	x=0;
	search=vote(pre,elector,dim);
	current=pre;
	int nbr=0;
	int max=pre->nbVote;
	char winner[20];
	strcpy(winner,pre->name);
	do{
		if(search==0){
			printf("The turn must be redone.\n");
			search = vote(pre,elector,dim);
		}else{
			while(current->next!=NULL){
				if(current->next->nbVote>max){
					max=current->next->nbVote;
					strcpy(winner,current->next->name);
				}
				current=current->next;
			}
		current=pre;
			while(current!=NULL){
				if(current->nbVote==max){
					nbr+=1;
					
				}
				current=current->next;
			}
			if(nbr>1){
				search=0;
			}else{
				printf("The winner is Mr/Ms: %s",winner);
				x=1;
			}
		}	
	}while(x==0);
}