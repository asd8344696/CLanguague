#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define true 1
#define false 0


char monsters[][15]={ "Bulbassaur", "lvysaur",
 "Venusaur", "Charmander", "Charmeleon"
 ,"Charizard", "Squirtle", "Wartotle", 
 "Blastoise", "Caterpie", "Metapod", 
 "Butterfree", "Weedle", "Kakuna", "Beedrill"
, "Pidgey", "Pidgeotto", "Pidgeot" };

int max_I , min_I , player_Position=0 , ball = 0 , nearMonsterCount = 0 , obtainMonsterCount = 0 ;

void menu(int,int);

int registerForBall();

void monsterGenerator(char**,int[][2],int); // name, Dist_CP , check

void move(char**,int[][2],int[][2]); // name, Dist_CP

void checkNearMonster(char**,int[][2],int[][2]); // name, Dist_CP, nearMonster

void catchMonster(char**,int[][2],int[][2],int[][2]); // name, naerMonster, Dist_CP, catched


int main(void){
	
	srand(time(NULL));
	
	int input = 0;
	
	int registered = 0,monsterGenerated = 0;
	
	char *name[8] = {'\0'};
	
	int Dist_CP[8][2] = {0};
	
	int catched[8][2] = {0};
	
	while(true){
		
		menu(registered,monsterGenerated);
		
		if(registered == 1)
			printf("\nYour ball is %d now.\n",ball);
			
		if(registered == 1 && monsterGenerated == 1)
			printf("\nYour position is %dm.\n",player_Position);
		
		scanf("%d",&input);
		
		if(input == 1){
			
			ball += registerForBall();
			registered = 1;
			
		}else if(input == 2){
			
			if(registered == 0){
				
				printf("You must register first.\n\n");
				continue;
				
			}else{
				
				monsterGenerator(name,Dist_CP,monsterGenerated);
				monsterGenerated = 1;
				
			}
			
		}else if(input == 3){
			
			if(obtainMonsterCount == 8){
				printf("You have already obtained all monsters.");
				continue;
			}
			
			if(registered == 0 || monsterGenerated == 0){
				
				printf("You must generate monsters first.\n\n");
				continue;
				
			}else{
				
				move(name,Dist_CP,catched);
				
				
			}
			
		}else if(input == 4){
			break;
		}
	}
	
		
} 

void menu(int registered,int monsterGenerated){

		printf("\n[1].register and get balls\n");
		printf("[2].show all moster %s",(registered == 1)?"\n":"(must after step 1)\n");
		printf("[3].move and catch moster %s",(registered == 1 && monsterGenerated == 1)?"\n":"(must after step 2)\n");
		printf("[4].exit\n");

}

int registerForBall(){
	
	double height = 0, weight = 0 , bmi = 0;
	int obtainNumOfBall = 0;
	
	printf("\nPlease enter your height (cm) : ");
	scanf("%lf",&height);
	height /= 100.0;
	printf("\nPlease enter your weight (kg) : ");
	scanf("%lf",&weight);
	
	bmi = (weight/(height*height));
	
	obtainNumOfBall = (bmi>=25)?rand()%6+5:(bmi<=18.5)?rand()%4+1:5;
	
	printf("\nYour BMI is : %.2lf , and you obtain %d balls.\n\n",bmi,obtainNumOfBall);
	printf("\n\\------------------You have registered successfully, have fun!-------------------\\\n");
	return obtainNumOfBall;
	
}

void monsterGenerator(char **name,int Dist_CP[][2],int check){
	
	int max = INT_MIN , min = INT_MAX , max_Index = 0 , min_Index = 0;
	
	if(check == 0){
	
		for(int i=0;i<8;i++){
			char *temp = monsters[rand()%18];
			*(name+i) = temp;
			Dist_CP[i][0] = rand()%10+1;
			Dist_CP[i][1] = rand()%101+50;
			
			if(Dist_CP[i][1] > max){
				max = Dist_CP[i][1];
				max_Index = i;
			}
			
			if(Dist_CP[i][1] < min){
				min = Dist_CP[i][1];
				min_Index = i;
			}
			
			
		}
		
		max_I = max_Index;
		min_I = min_Index;
	}
	printf("\n\\----------------------------------------------------------\\\n");
	printf("\nThere are all the monsters have already generated.\n");
	
	for(int i=0;i<8;i++){
		if(i == min_I)
			printf("\n\"%s\" MIN : {CP : %d , Dist : %dm}\n",*(name+i),Dist_CP[i][1],Dist_CP[i][0]);
		else if(i == max_I)
			printf("\n\"%s\" MAX : {CP : %d , Dist : %dm}\n",*(name+i),Dist_CP[i][1],Dist_CP[i][0]);
		else
			printf("\n\"%s\" \n",*(name+i));
	}
	
	printf("\n\\----------------------------------------------------------\\\n");
	
}

void move(char **name,int Dist_CP[][2],int catched[][2]){
	printf("\n\\------------------Your are in move mode-------------------\\\n");
	printf("\n[1]Enter \'+\' to move forward 2m.\n");
	printf("[2]Enter \'-\' to move backward 2m.\n");
	printf("[3]Enter \'C\' or \'c\' to catch monsters.\n");
	printf("[4]Enter \'X\' or \'x\' to exit move mode.\n");
	
	
	char command = '0';
	
	int nearMonster[8][2]; //0 ¬° index , 1 ¬° ¼È®É¶ZÂ÷
	 
	checkNearMonster(name,Dist_CP,nearMonster);
	
	while(true){
		
		
		scanf("%c",&command);
		

		if(command == '+'){
			
			player_Position+=2;
			if(player_Position > 10)
				player_Position = 0;
			printf("\n\\----------------------------------------------------------\\\n");
			printf("Your position is %d now.\n",player_Position);
			
			checkNearMonster(name,Dist_CP,nearMonster);
			
			
		}
		
		if(command == '-'){
		
			player_Position-=2;
			if(player_Position < 0)
				player_Position = 10;
			printf("\n\\----------------------------------------------------------\\\n");	
			printf("Your position is %d now.\n",player_Position);
			
			checkNearMonster(name,Dist_CP,nearMonster);
		}
		
		if(command == 'x' || command == 'X'){
			printf("\n\\------------------Your are in the Menu-------------------\\\n");
			return;
		}
		
		if(command == 'c' || command == 'C'){

			catchMonster(name,nearMonster,Dist_CP,catched);
		}
		
	}
	
}

void checkNearMonster(char **name,int Dist_CP[][2],int nearMonster[][2]){
	

	printf("\nThe monster near your is : \n");
	
			
	int count = 0;
	
	for(int i=0;i<8;i++){
		nearMonster[i][0] = 0;
		nearMonster[i][1] = 0;
		if(abs(player_Position - Dist_CP[i][0]) <= 1){
			nearMonster[i][0] = 1;
			nearMonster[i][1] = rand()%21+60;
			printf("\n\"%s\"  CP : %d\n",*(name+i),Dist_CP[i][1]);
			count++;
		}
		
	}
	nearMonsterCount = count;
	
	
}

void catchMonster(char **name,int nearMonster[][2],int Dist_CP[][2],int catched[][2]){
	
	if(nearMonsterCount == 0){
		printf("\nThere is no monster near you.\n");
		printf("\n\\------------------Your are in move Mode-------------------\\\n");
		printf("\n[1]Enter \'+\' to move forward 2m.\n");
		printf("[2]Enter \'-\' to move backward 2m.\n");
		printf("[3]Enter \'C\' or \'c\' to catch monsters.\n");
		printf("[4]Enter \'X\' or \'x\' to exit move mode.\n");
		return;
	}
	
	
	printf("\n\\------------------Your are in catch Mode-------------------\\\n");
	printf("\nThe monster near your is : \n");
	
	int monsterNumber = 1;
	
	for(int i=0;i<8;i++){
		if(nearMonster[i][0] != 0){
			printf("\n(%d) \"%s\" CP : %d \n",monsterNumber++,*(name+i),Dist_CP[i][1]);
		}
	}
	
	int com = -1;
	
	printf("\n[1]Enter monster\'s number to start catch monster.\n");
	printf("[2]Enter \'0\' to exit catch mode.\n");
	
	
	scanf("%d\n",&com);
	
	
	if(com == 0){
		printf("\n\\------------------Your are in move Mode-------------------\\\n");
		printf("\n[1]Enter \'+\' to move forward 2m.\n");
		printf("[2]Enter \'-\' to move backward 2m.\n");
		printf("[3]Enter \'C\' or \'c\' to catch monsters.\n");
		printf("[4]Enter \'X\' or \'x\' to exit move mode.\n");
		return;
	}else if(com >= 1 && com <= nearMonsterCount){
		
		printf("\nstarted\n");
		
	}
	

}


