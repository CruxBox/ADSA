#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char name[50];
	int level;
	int index;
	int numEmployeesUnder;
	struct node** employeesUnder;
	struct node* boss;
}company;

int maxLevel = 1;

company* createEmployee(char Name[],int lvl,int idx,company* boss){
	company* temp = (company*) malloc(sizeof(company));
	strcpy(temp->name,Name);
	temp->level = lvl;
	temp->index = idx;
	temp->numEmployeesUnder = 0;
	temp->employeesUnder = (company**) malloc(sizeof(company*));
	temp->boss = boss;
	return temp;
}

company** getEmployee(company** employee,char employeeName[], int level)
{
    if (employee != NULL && level == 1)
    {
        if(strcmp((*employee)->name,employeeName)==0){
        	return employee;
        }
        else
        	return NULL;
    }
    else if (employee != NULL)
    {
    	company** temp;
        for(int j=0;j<(*employee)->numEmployeesUnder;j++){
        	temp = getEmployee(&((*employee)->employeesUnder[j]),employeeName,level-1);
        	if(temp!=NULL)
        		return temp;
        }
    }
    return NULL;
}

company** searchEmployee(company** employee,char employeeName[]){
	if(employee==NULL || strcmp((*employee)->name,employeeName)==0){
		return employee;
	}

	company** temp;
	for (int i = 1; i <= maxLevel; i++){
        temp = getEmployee(employee,employeeName, i);
        if(temp!=NULL)
        	return temp;
	}
	return NULL;
}

company** AddEmployee(company** CEO,char employeeName[],char Boss[]){
	company** bossFound = searchEmployee(CEO,Boss);
	if(bossFound==NULL){
		printf("Boss not found!!\n");
	}
	else{
		(*bossFound)->employeesUnder = (company**) realloc((*bossFound)->employeesUnder,sizeof(company*)*((*bossFound)->numEmployeesUnder+2));
		(*bossFound)->employeesUnder[(*bossFound)->numEmployeesUnder] = createEmployee(employeeName,((*bossFound)->level)+1,(*bossFound)->numEmployeesUnder,(*bossFound));
		(*bossFound)->numEmployeesUnder += 1;
		if(maxLevel < ((*bossFound)->level)+1)
			maxLevel = ((*bossFound)->level)+1;
		printf("Inserted Successfully!\n");
	}
	return CEO;
}

void swap(company* x, company* y){
	company* temp = (company*) malloc(sizeof(company));
	*temp = *x;
	*x = *y;
	*y = *temp;
}

void deleteEmployee(company** CEO, char employeeName[],char collegueName[]){
	company** collegueFound = searchEmployee(CEO,collegueName);
	if(collegueFound==NULL){
		printf("%s collegue not found!!\n",collegueName);
		return;
	}
	else{
		company** employeeFound = searchEmployee(CEO,employeeName);
		if(employeeFound==NULL){
			printf("%s employee not found!!\n",collegueName);
			return;
		}
		else if((*employeeFound)->level != (*collegueFound)->level){
			printf("%s is not a collegue of %s\n",collegueName,employeeName);
			return;
		}
		else{
			for(int i = 0; i < (*employeeFound)->numEmployeesUnder; i++){
				(*collegueFound)->employeesUnder[(*collegueFound)->numEmployeesUnder] = (*employeeFound)->employeesUnder[i];
				(*collegueFound)->employeesUnder[(*collegueFound)->numEmployeesUnder]->boss = (*collegueFound);
				(*collegueFound)->employeesUnder[(*collegueFound)->numEmployeesUnder]->index = (*collegueFound)->numEmployeesUnder-1;
				(*collegueFound)->employeesUnder = (company**) realloc((*collegueFound)->employeesUnder,sizeof(company*)*((*collegueFound)->numEmployeesUnder+2));
				(*collegueFound)->numEmployeesUnder++;
			}
			if(strcmp((*collegueFound)->boss->name,(*employeeFound)->boss->name)==0){
				int i;
				for(i=(*employeeFound)->index;i<((*employeeFound)->boss->numEmployeesUnder - (*employeeFound)->index); i++)
					swap((*employeeFound)->boss->employeesUnder[i],(*employeeFound)->boss->employeesUnder[i+1]);
				(*employeeFound)->boss->numEmployeesUnder--;
				(*employeeFound)->boss->employeesUnder[i] = NULL;
				printf("Deleted Successfully!\n");
			}
			else{
				if((*employeeFound)->boss->numEmployeesUnder == (*employeeFound)->index+1){
					(*employeeFound)->boss->numEmployeesUnder--;
					(*employeeFound) = NULL;
					printf("Deleted Successfully!\n");
				}
				else{
					int i;
					for(i=(*employeeFound)->index;i<((*employeeFound)->boss->numEmployeesUnder - (*employeeFound)->index); i++)
						swap((*employeeFound)->boss->employeesUnder[i],(*employeeFound)->boss->employeesUnder[i+1]);
					(*employeeFound)->boss->numEmployeesUnder--;
					(*employeeFound)->boss->employeesUnder[i] = NULL;
					printf("Deleted Successfully!\n");
				}
			}
		}
	}
}


void lowestCommonBoss(company** CEO,char emp1[],char emp2[]){
	if(strcmp(emp1,(*CEO)->name)==0 || strcmp(emp2,(*CEO)->name)==0){
		printf("CEO doesn't have a boss!! Wrong entry!!\n");
		return;
	}

	company** emplye1 = searchEmployee(CEO,emp1);
	if(emplye1!=NULL){
		company* employee1 = *emplye1;
		company** emplye2 = searchEmployee(CEO,emp2);
		if(emplye2!=NULL){
			company* employee2 = *emplye2;
			if(strcmp(employee1->boss->name,employee2->boss->name)==0){
				printf("Lowest Common Boss is : %s\n",employee1->boss->name);
			}
			else{
				if(employee1->level > employee2->level){
					int count = (employee1->level - employee2->level);
					for(int i=0; i < count; i++)
						employee1 = employee1->boss;
					if(strcmp(employee1->boss->name,employee2->boss->name)==0)
						printf("Lowest Common Boss is : %s\n",employee1->boss->name);
					else{
						while(strcmp(employee1->boss->name,employee2->boss->name)!=0){
							employee1 = employee1->boss;
							employee2 = employee2->boss;
						}
						printf("Lowest Common Boss is : %s\n",employee1->boss->name);
					}
				}
				else if(employee1->level < employee2->level){
					int count = (employee2->level - employee1->level);
					for(int i=0; i < count; i++){
						employee2 = employee2->boss;
					}
					if(strcmp(employee1->boss->name,employee2->boss->name)==0)
						printf("Lowest Common Boss is : %s\n",employee2->boss->name);
					else{
						while(strcmp(employee1->boss->name,employee2->boss->name)!=0){
							employee1 = employee1->boss;
							employee2 = employee2->boss;
						}
						printf("Lowest Common Boss is : %s\n",employee1->boss->name);
					}
				}
				else{
					while(strcmp(employee1->boss->name,employee2->boss->name)!=0){
						employee1 = employee1->boss;
						employee2 = employee2->boss;
					}
					printf("Lowest Common Boss is : %s\n",employee1->boss->name);
				}
			}
		}
		else{
			printf("%s not found!!\n",emp2);
			return;
		}
	}
	else{
		printf("%s not found!!\n",emp1);
		return;
	}
}

void printLevel(company* employee, int level)
{
    if (employee != NULL && level == 1){
        printf("%s ", employee->name);
    }
    else if (employee != NULL){
    	for(int j=0;j<=employee->numEmployeesUnder;j++){
    		printLevel(employee->employeesUnder[j],level-1);
    	}
    }
}

void printTree(company* temp)
{
    for (int i = 1; i <= maxLevel; i++)
    {
        printLevel(temp, i);
        printf("\n");
    }
}

int main(){
	char ceoName[50];
	char name[50];
	char bossName[50];
	char collegueName[50];
	company* CEO = NULL;
	printf("Enter the name of CEO : ");
	scanf("%[^\n]%*c", ceoName);
	CEO = createEmployee(ceoName,1,0,NULL);
	while(1){
		printf("\n**********************************\n");
		printf("| Select from the menu:       	 |\n");
		printf("| 1) Add employee                |\n");
		printf("| 2) Delete Employee             |\n");
		printf("| 3) Lowest Common Boss       	 |\n");
		printf("| 4) Print the company heirarchy |\n");
		printf("**********************************\n");
		printf("Enter your choice : ");
		int choice;
		scanf("%d",&choice);
		getchar();
		switch (choice){
			case 1:
				printf("Enter the employee name : \n");
				scanf("%[^\n]%*c",name);
				printf("Enter the boss name : \n");
				scanf("%[^\n]%*c", bossName);
				printf("\n");
				printf("############################\n");
				AddEmployee(&CEO,name,bossName);
				printf("############################\n");
				break;
			case 2:
				printf("Enter the employee name : \n");
				scanf("%[^\n]%*c",name);
				printf("Enter the collegue name : \n");
				scanf("%[^\n]%*c", collegueName);
				printf("\n");
				printf("############################\n");
				deleteEmployee(&CEO,name,collegueName);
				printf("############################\n");
				break;
			case 3:
				printf("Enter the employee name : \n");
				scanf("%[^\n]%*c",name);
				printf("Enter the collegue name : \n");
				scanf("%[^\n]%*c", collegueName);
				printf("\n");
				printf("############################\n");
				lowestCommonBoss(&CEO,name,collegueName);
				printf("############################\n");
				break;
			case 4:
				printf("\n############################\n");
				printf("Level order printing: \n");
				printTree(CEO);
				printf("############################\n");
				printf("\n");
				break;
			default:
				printf("\nWrong choice entered!!\n");
		}
	}
	return 0;
}



