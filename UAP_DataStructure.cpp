#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Fossil{
	char fossilName[30];
	int year;
	char land[20];
	char discName[30];
	Fossil *left, *right;
	int height;
};

Fossil *createFossil (char *fossilName, int year, char *land, char *discName){
	Fossil *newFossil = (Fossil *)malloc(sizeof(Fossil));
	
	strcpy(newFossil->fossilName,fossilName);
	newFossil->year = year;
	strcpy(newFossil->land,land);
	strcpy(newFossil->discName,discName);
	newFossil->left = newFossil->right = NULL;
	newFossil->height = 1;
	
	return newFossil;
}

int max(int a,int b){
	if(a>b) return a;
	return b;
}

int getHeight(Fossil *curr){
	if(!curr) return 0;
	return curr->height;
}

int getBalanceFactor(Fossil *curr){
	if(!curr)return 0;
	return getHeight(curr->left) - getHeight(curr->right);
}

Fossil *rightRotate(Fossil *curr){
	Fossil *leftChild = curr->left;
	Fossil *leftChildRight = leftChild->right;
	
	curr->left = leftChildRight;
	leftChild->right = curr;
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	leftChild->height = max(getHeight(leftChild->left), getHeight(leftChild->right)) + 1;
	
	return leftChild;
}

Fossil *leftRotate(Fossil *curr){
	Fossil *rightChild = curr->right;
	Fossil *rightChildLeft = rightChild->left;
	
	curr->right = rightChildLeft;
	rightChild->left = curr;
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	rightChild->height = max(getHeight(rightChild->left), getHeight(rightChild->right)) + 1;
	
	return rightChild;
}

Fossil *insertFossilToAVL(Fossil *curr,char *fossilName, int year, char *land, char *discName){

	if (curr==NULL){
		return createFossil(fossilName, year, land, discName);
	}

	if( strcmp(fossilName,curr->fossilName) > 0){
		curr->left = insertFossilToAVL(curr->left,fossilName,year,land,discName);
	}

	else if( strcmp(fossilName,curr->fossilName) < 0){
		curr->right = insertFossilToAVL(curr->right,fossilName,year,land,discName);
	}
	
	else{
		return curr;
	}
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	
	int balanceFactor = getBalanceFactor(curr);
	

	if(balanceFactor > 1 && getBalanceFactor(curr->left) >= 0){
		return rightRotate(curr);
	}

	if(balanceFactor > 1 && getBalanceFactor(curr->left) < 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}

	if(balanceFactor < -1 && getBalanceFactor(curr->right) <= 0){
		return leftRotate(curr);
	}

	if(balanceFactor < -1 && getBalanceFactor(curr->right) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

Fossil *insertFossil(Fossil *root){
	char fossilName[30];
	do{
		printf("Input fossil species name [5 - 25 characters | only alphabets]: ");
		scanf("%[^\n]",fossilName);
		getchar();
	}while(strlen(fossilName) < 5 || strlen(fossilName) > 25);
	
	int year;
	do{
		printf("Input fossil year discovered [0 - 2021] : ");
		scanf("%d",&year);
		getchar();
	}while(year < 0 || year > 2021);
	
	char land[20];
	printf("Input fossil location discovered [ended with \" land\"]: ");
	scanf("%[^\n]",land);
	getchar();
	
	char discName[30];
	do{
		printf("Input fossil discoverer name[5 - 20 characters | min. 2 words]: ");
		scanf("%[^\n]",discName);
		getchar();
	}while(strlen(discName)<5 || strlen(discName)>20);
	
	root = insertFossilToAVL(root,fossilName,year,land,discName);
	return root;
}

void preOrder(Fossil *curr){
	if(!curr)return;
	printf("%s		%d		%s		%s\n",curr->fossilName,curr->year,curr->land,curr->discName);
	preOrder(curr->left);
	preOrder(curr->right);
}

void inOrder(Fossil *curr){
	if(!curr)return;
	inOrder(curr->left);
	printf("%s		%d		%s		%s\n",curr->fossilName,curr->year,curr->land,curr->discName);
	inOrder(curr->right);
}

void postOrder(Fossil *curr){
	if(!curr)return;
	postOrder(curr->left);
	postOrder(curr->right);
	printf("%s		%d		%s		%s\n",curr->fossilName,curr->year,curr->land,curr->discName);
}

Fossil *searchFossil(Fossil *curr, char *fossilName){
	if(!curr){
		return NULL;
	}
	if(strcmp(fossilName, curr->fossilName) < 0){
		return searchFossil(curr->left, fossilName);
	}
	else if(strcmp(fossilName,curr->fossilName) > 0){
		return searchFossil(curr->right,fossilName);
	}
	else{
		return curr;
	}
}

Fossil *findPrede(Fossil *curr){
	Fossil *temp = curr->left;
	while(temp->right){
		temp = temp->right;
	}
	return temp;
}

Fossil *deleteFossil(Fossil *curr, char *fossilName){
	if(!curr){
		return NULL;
	}
	
	if(strcmp(fossilName,curr->fossilName) < 0){
		curr->left = deleteFossil(curr->left,fossilName);
	}
	else if(strcmp(fossilName,curr->fossilName) > 0){
		curr->right = deleteFossil(curr->right,fossilName);
	}
	
	
	else{
		if(curr->left == NULL && curr->right == NULL){
			free(curr);
			curr = NULL;
			return NULL;
		}
		
		if(curr->left==NULL){
			Fossil *temp = curr->left;
			free(curr);
			curr = NULL;
			return temp;
		}
		
		if(curr->right==NULL){
			Fossil *temp = curr->right;
			free(curr);
			curr = NULL;
			return temp;
		}
		
		Fossil *temp = findPrede(curr);
		strcpy(curr->fossilName,temp->fossilName);
		curr->year = temp->year;
		strcpy(curr->land,temp->land);
		strcpy(curr->discName,temp->discName);
		
		curr->left = deleteFossil(curr->left,temp->fossilName);
	}
}

Fossil *deleteFossilMenu(Fossil *root){
	if(root == NULL){
		printf("No fossil yet!\n");
		return NULL;
	}
	
	char name[30];
	Fossil *toBeSearch = NULL;
	do{
		printf("Input fossil species name: ");
		scanf("%[^\n]",name);
		getchar();
	}while(toBeSearch == NULL);
	
	if(strcmp(name,toBeSearch->fossilName) == 0){
		root = deleteFossil(root,name);
	}
}

void deleteAllFossil(Fossil *curr){
	if(!curr){
		return;
	}
	deleteAllFossil(curr->left);
	deleteAllFossil(curr->right);
	free(curr);
	curr = NULL;
}

int main(){
	
	int input;
	Fossil *root = NULL;
	
	do{
		
		printf("Cron Fossil Museum - Records\n");
		printf("=====================================\n");
		printf("1. View Fossil\n");
		printf("2. Insert Fossil\n");
		printf("3. Delete Fossil\n");
		printf("4. Exit\n");
		printf("0> ");
		scanf("%d",&input);
		getchar();
		
		if(input == 1){
			if(root == NULL){
				printf("No fossil yet!\n");
			}
			else{
				char method[10];
				do{
					printf("Choose order [Pre | In | Post]): ");
					scanf("%s",method); getchar();
				}while( strcmp(method,"Pre") != 0 && strcmp(method,"In") != 0 && strcmp(method,"Post") != 0);
				
				if(strcmp(method,"Pre") == 0){
					printf("Species Name		Year		Location		Discoverer\n");
					preOrder(root);
				}
				else if(strcmp(method,"In") == 0){
					printf("Species Name		Year		Location		Discoverer\n");
					inOrder(root);
				}
				else if(strcmp(method,"Post") == 0){
					printf("Species Name		Year		Location		Discoverer\n");
					postOrder(root);
				}
			}
		}
		
		else if(input == 2){
			root = insertFossil(root);
		}
		
		else if(input == 3){
			root =deleteFossilMenu(root);
		}
		
		
	}while(input != 4);
	
	
	
	
	return 0;
}
