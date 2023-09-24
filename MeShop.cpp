#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 100
struct product{
	char id[10];
	char name[50];
	char category[10];
	char date[15];
	int price;
	int stock;
	
	product *next;
}*head[SIZE];

int sum = 1;
product *newProduct(char tempid[], char name[], char category[], char date[], int price, int stock){
	product *curr = (product*)malloc(sizeof(product));
	strcpy(curr->id, tempid);
	strcpy(curr->name, name);
	strcpy(curr->category, category);
	strcpy(curr->date, date);
	curr->price = price;
	curr->stock = stock;
	
	curr->next = NULL;
	return curr;
}
int getKey(char x[]){
	int key = 0;
	key = x[0]*(x[3] + x[1] - x[2]);
	
	key = key%SIZE;
	return key;
}

//int getKey(char name[]){
//	int sum = 0;
//	for(int i = 0; i<strlen(name); i++){
//		sum += name[i];
//	}
//	sum = sum %SIZE;
//	return sum;
//}


void push(int key, product *curr){
	if(head[key] == NULL){
		head[key] = curr; 
	}else{
		curr->next = head[key];
		head[key] = curr;		
	}
}

void addProduct(){
	char name[50];
	char category[10];
	char date[15];
	int price;
	int stock;

	do{
		printf("Input product name [Product name must be more than 5 characters]: ");
		scanf("%[^\n]", name); getchar();
	}while(strlen(name) <= 5);
	
	do{
		printf("Input price [1000 - 150000]: ");
		scanf("%d", &price); getchar();
	}while(price < 1000 || price > 150000);
	
	do{
		printf("Input Stock[>0]: ");
		scanf("%d", &stock); getchar();
	}while(stock<=0);
	
	do{
		printf("Input Category [Food / Health / Digital] (Case Sensitive): ");
		scanf("%s", category); getchar();
	}while(strcmp(category, "Food") != 0 && strcmp(category, "Health") != 0 && strcmp(category, "Digital") != 0);
	
	printf("Succesfully Added New Product\n\n");
	//rand() % ((max + min) + 1) + min 
	int day = rand() % 30 + 1;
	int month = rand() % 12 + 1;
	int year = rand() % 5 + 20;
	
	sprintf(date, "%d/%d/20%d", day, month, year);
	char id[100];
    char satuan[10] = "00";
    char puluhan[10] = "0";
    char urutan[10]; 
    
    if(strcmp(category,"Health")==0){
    	strcpy(id,"H");
    	if(sum<10){
    		strcat(id, satuan);
		}
		else if(sum>=10 && sum<100){
			strcat(id, puluhan);
		}
			sprintf(urutan,"%d",sum);
			strcat(id, urutan);
			sum = sum+1;
	}
	else if(strcmp(category,"Food")==0){
		strcpy(id,"F");
    	if(sum<10){
    		strcat(id, satuan);
		}
		else if(sum>=10 && sum<100){
			strcat(id, puluhan);
		}
			sprintf(urutan,"%d",sum);
			strcat(id, urutan);
			sum = sum+1;
	}
	else if(strcmp(category,"Digital")==0){
	strcpy(id,"D");
    	if(sum<10){
    		strcat(id, satuan);
		}
		else if(sum>=10 && sum<100){
			strcat(id, puluhan);
		}
			sprintf(urutan,"%d",sum);
			strcat(id, urutan);
			sum = sum+1;
	}
	
	product *curr = newProduct(id, name, category, date, price, stock);
	int key = getKey(id);
	push(key, curr);
}

void viewProduct(){
	int sum = 0;
	for(int i = 0; i<SIZE; i++){
		if(head[i] == NULL){
			sum = sum + 1;
		}
	}
	if(sum != SIZE){
		for(int i=0; i<SIZE; i++){
			if(head[i] == NULL){
				continue;
			}else{	
				product *temp = head[i];
				while(temp != NULL){
				printf("Product ID	: %s\n", temp->id);
				printf("===============================\n");
				printf("Product Name	: %s\n", temp->name);
				printf("Product Category: %s\n", temp->category);				
				printf("Product Price	: %d\n", temp->price);
				printf("Product Stock	: %d\n", temp->stock);
				if(strcmp(temp->category, "Digital") == 0){
					printf("Expired Date	: -\n\n");
				}else{
					printf("Expired Date	: %s\n\n", temp->date);
				}
				
				temp = temp->next;
				}
			}
		}
	}else{
		printf("\nNo product Yet\n\n");
	}
}

void deleteProduct(char id[]){
	int key = getKey(id);
	
	if(head[key] != NULL){
		if(strcmp(head[key]->id, id) == 0){
			product *temp = head[key];
			
				char ans;
			do{
				printf("Sure to delete %s ? [Y/N] (Case Incensitive) : ", head[key]->id);
				scanf(" %c", &ans);
			}while(ans != 'Y' && ans!='y' && ans!='N' && ans!='n');
			
			if(ans == 'Y' || ans == 'y'){
				head[key] = head[key]->next;
				temp->next = NULL;
				temp = NULL;
				free(temp);
                printf("Successfully Delete product\n"); getchar();
                return;
			}else{
				return;
			}
		}else{
			product *temp2 = head[key];
			
			while(temp2->next != NULL && strcmp(temp2->next->id,id) != 0){
				temp2 = temp2->next;
			}
			
			if(temp2->next == NULL){
				printf("No data found. \n");
				return;
			}
			
			char ans;
			do{
					printf("Sure to delete %s ? [Y/N] (Case Incensitive) : ", temp2->next->id);
	                scanf(" %c", &ans);
	            }while(ans!='Y' && ans!='y' && ans!='N' && ans!='n');
	        
	            if(ans == 'Y' || ans == 'y'){
	                product *temp = temp2->next;
	                temp2->next= temp->next;    
	            	
	                free(temp);
	                temp = NULL;
	                printf("Successfully Delete product\n");getchar();
	                return;
	            }else{
	            	return;
				}
			}
		}else{
	    	printf("No data found. \n");
			getchar();
		}
}

int main(){
	srand(time(NULL));
	int choose = 0;
	menu:
		system("cls");
	do{
		printf("Welcome To MeShop!\n");
		printf("==================\n");
		printf("1. Add Product\n");
		printf("2. View Product\n");
		printf("3. Delete Product\n");
		printf("4. Exit\n");
		printf("Choose[1-4]> ");
		scanf("%d", &choose);getchar();
		
		switch(choose){
			case 1:
				addProduct();
				printf("Press any to continue..."); getchar();
				goto menu;
				break;
			case 2:
				viewProduct();
				printf("Press any to continue..."); getchar();
				goto menu;
				break;
			case 3:
				viewProduct();
				char dell[100];
				printf("Input Product ID to delete: ");
    			scanf(" %[^\n]",dell);
				deleteProduct(dell);
				printf("Press any to continue..."); getchar();
				goto menu;
				char name[50];
				
				break;
			case 4:
				system("cls");
				break;
		}
	}while(choose != 4);
	return 0;
}
