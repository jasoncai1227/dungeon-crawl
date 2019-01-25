#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct room{
	char* name;
	struct room* NORTH;
	struct room* SOUTH;
	struct room* EAST;
	struct room* WEST;
};

struct room* rooms;
int num_room=1;
char* current_position;
char buffer[1000];

int find_room(char* room){
	int index;
	for(int n=0;n<num_room;n++){
		if(strcmp(rooms[n].name,room)==0){
			index=n;
		}
	}
	return index;
}

void add_paths(int current_room,char* direction,char* dest){
	char* north="NORTH";char* south="SOUTH";char* east="EAST";char* west="WEST";
	if(strcmp(direction,north)==0){   
		rooms[current_room].NORTH=&rooms[find_room(dest)];
	}
	else if(strcmp(direction,south)==0){
		rooms[current_room].SOUTH=&rooms[find_room(dest)];
	}
	else if(strcmp(direction,east)==0){
		rooms[current_room].EAST=&rooms[find_room(dest)];
	}
	else if(strcmp(direction,west)==0){
		rooms[current_room].WEST=&rooms[find_room(dest)];
	}
}


void print_room(char* room){
		printf("\n");
		printf("%s\n",room);
		if(rooms[find_room(room)].NORTH!=NULL){
			printf(" ---N--- \n");
		}else if(rooms[find_room(room)].NORTH==NULL){printf(" ------- \n");}
		if(rooms[find_room(room)].WEST==NULL&&rooms[find_room(room)].EAST==NULL){
			for(int i=0;i<5;i++){printf("|       |\n");}
		}else if(rooms[find_room(room)].WEST!=NULL&&rooms[find_room(room)].EAST!=NULL){
			for(int i=0;i<5;i++){
				if(i==2){printf("W       E\n");continue;}
				printf("|       |\n");
			}
		}else if(rooms[find_room(room)].WEST==NULL&&rooms[find_room(room)].EAST!=NULL){
			for(int i=0;i<5;i++){
				if(i==2){printf("|       E\n");continue;}
				printf("|       |\n");
			}
		}else if(rooms[find_room(room)].WEST!=NULL&&rooms[find_room(room)].EAST==NULL){
			for(int i=0;i<5;i++){
				if(i==2){printf("W       |\n");continue;}
				printf("|       |\n");
			}
		}
		if(rooms[find_room(room)].SOUTH!=NULL){
			printf(" ---S--- \n");printf("\n");
		}else if(rooms[find_room(room)].SOUTH==NULL){
			printf(" ------- \n");printf("\n");
		}
	
}

char* check_input(char* position,char* input){
	char* north="NORTH";char* south="SOUTH";char* east="EAST";char* west="WEST";
	char* quit="QUIT";
	if(strcmp(input,north)==0){
	if(rooms[find_room(position)].NORTH!=NULL){
	position=rooms[find_room(position)].NORTH->name;
	return position;
	}else {printf("No Path This Way\n");return NULL;}
	}
	else if(strcmp(input,south)==0){
	if(rooms[find_room(position)].SOUTH!=NULL){
	position=rooms[find_room(position)].SOUTH->name;
	return position;
	}else {printf("No Path This Way\n");return NULL;}
	}
	else if(strcmp(input,west)==0){
	if(rooms[find_room(position)].WEST!=NULL){
	position=rooms[find_room(position)].WEST->name;	
	return position;
	}else {printf("No Path This Way\n");return NULL;}
	}
	else if(strcmp(input,east)==0){
	if(rooms[find_room(position)].EAST!=NULL){
	position=rooms[find_room(position)].EAST->name;
	return position;
	}else {printf("No Path This Way\n");return NULL;}
	}
	else if(strcmp(input,quit)==0){
	return "QUIT";
	}
	else{
	printf("What?\n");
	return "What?";
	}
	return NULL;
}

int main(int argc, char** argv) {
	if(argc<=1){printf("No Level File Specified\n");return 1;}
	FILE* ptr=fopen(argv[1],"r");
	if(ptr==NULL){printf("No Level File Specified\n");return 1;}
	fgets(buffer,1000,ptr);
	char* token;
	token=strtok(buffer," \n");
	while(token!=NULL){
		if(num_room==1){
		rooms=(struct room*)malloc(sizeof(struct room)*num_room);
		rooms[0].name=token;
		rooms[0].NORTH=NULL;rooms[0].EAST=NULL;
		rooms[0].SOUTH=NULL;rooms[0].WEST=NULL;
		num_room++;continue;}
		if(num_room!=1){
		token=strtok(NULL," \n");
		if(token==NULL){num_room-=1;break;}
		rooms=(struct room*)realloc(rooms,sizeof(struct room)*num_room);
		rooms[num_room-1].name=token;
		rooms[num_room-1].NORTH=NULL;rooms[num_room-1].EAST=NULL;
		rooms[num_room-1].SOUTH=NULL;rooms[num_room-1].WEST=NULL;
		num_room+=1;
		}
	}
	
	int current_room;
	int count=0;
	char* direction;
	char* dest;
	char* garbage;
	
	char buffer2[1000];
	while((fgets(buffer2,1000,ptr)!=NULL)){
		token=strtok(buffer2," \n");
		current_room=find_room(token);
		count++;
		while(token!=NULL){
			if(count==1){
			token=strtok(NULL," \n");
			garbage=token;
			count++;
			continue;
			}
			if(count==2){
			token=strtok(NULL," \n");
			direction=token;
			count++;
			continue;
			}
			if(count==3){
			token=strtok(NULL," \n");
			garbage=token;
			count++;
			continue;
			}
			if(count==4){
			token=strtok(NULL," \n");
			dest=token;
			count=0;
			break;
			}
		}
		add_paths(current_room,direction,dest);
	}
	current_position=rooms[0].name;
	print_room(current_position);
	char input[1000];
	while(strcmp(input,"QUIT")!=0){
	scanf("%s",input);
	current_position=check_input(current_position,input);
	if(current_position==NULL){
		current_position=rooms[0].name;
		print_room(current_position);
		continue;
	}
	if((strcmp(current_position,"QUIT")==0)){
		break;
	}
	if(strcmp(current_position,"What?")==0){
		current_position=rooms[0].name;
		print_room(current_position);
		continue;
	}
	print_room(current_position);
	}
	return 0;
}

