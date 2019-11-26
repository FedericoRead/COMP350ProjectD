//Giuseppe Carchidi, Federico Read, Joey Garuti, Fall 2019

//Joey Garuti, 11/7/19, user is reminded that file names need to be six characters long if a shorter string is input for both type and exec
//exec still doesn't work for files with names that are less than six characters long
void main(){
while(1){
	char command[80];
	char read[512];
	char file[7];
	char file2[7];
	int i;
	char buffer[90];
	int fileEntry;
	int fileFound;
	char dirFile[9];
	int* sector;
	int j=1;

	syscall(0,"Shell>");
	syscall(1,command);
	if(command[0]=='t' && command[1]=='y' && command[2]=='p' && command[3]=='e' && command[4]==' '){
		for(i=0;i<6;i++){
			if(command[i+5]=='\r'){
				//syscall(0,"File name must be six characters long.\r\n");
				file[i]='\0';
				break;
			}
			else{
				file[i]=command[i+5];
			}
		}
		file[6]='\0';
		syscall(3,file,read,0);
		syscall(0,read);
	}
	else if(command[0]=='e' && command[1]=='x' && command[2]=='e' && command[3]=='c' && command[4]==' '){
		for(i=0;i<6;i++){
			if(command[i+5]=='\r'){
			//	syscall(0,"File name must be six characters long.\r\n");
				file[i]='\0';
				break;
			}
			else{
				file[i]=command[i+5];
			}
		}
		file[6]='\0';
		syscall(4,file);
	}

	else if(command[0]=='d' && command[1]=='i' && command[2]=='r' && command[3]=='\r'){
		syscall(2,read,2);
		for(fileEntry=0; fileEntry<512; fileEntry+=32){
			if(read[fileEntry]=='\0'&& read[fileEntry+1]=='\0'){ //no more files to list
				break;
			}
			else{
				for(fileFound=0;fileFound<6;fileFound++){
					if(read[fileEntry+fileFound]==0){
						for(fileFound;fileFound<6;fileFound++){
							dirFile[fileFound]=' ';
						}
						dirFile[6]='\r';
						dirFile[7]='\n';
						dirFile[8]='\0';
						break;
					}
					else{
						dirFile[fileFound]=read[fileEntry+fileFound];
					}
					dirFile[6]='\r';
					dirFile[7]='\n';
					dirFile[8]='\0';
				}
	//			dirFile[6]='\r';	//These two lines are
	//			dirFile[7]='\n';	//what ate my time.
				syscall(0,dirFile);
				//syscall(0,"\r\n");	//THIS! This is what I needed.  The absence of this made files less than 6 characters long not display the next thing to its own line. Using '\r' and '\n' in the dirFile array instead of this is what made me sit and mess with this for HOURS!  It's 6:10 as I type this.  FINALLY the basic dir command works!
			}
		}
	}
	else if(command[0]=='d' && command[1]=='e' && command[2]=='l' && command[3]==' '){
		for(i=0;i<6;i++){
			if(command[i+4]=='\r'){
				file[i]='\0';
				break;
			}
			else{
				file[i]=command[i+4];
			}
		}
		file[6]='\0';
		syscall(7,file);
	}
	else if(command[0]=='c' && command[1]=='o' && command[2]=='p' && command[3]=='y' && command[4]==' '){
		for(i=0;i<6;i++){
			if(command[i+5]==' '){
				file[i]='\0';
				break;
			}else{
				file[i]=command[i+5];
			}
		}
		file[6]='\0';
		for(fileEntry=0;fileEntry<6;fileEntry++){
			if(command[i+6+fileEntry]=='\r'){
				file2[fileEntry]='\0';
				break;
			}else{
				file2[fileEntry]=command[i+6+fileEntry];
			}
		}
		file2[6]='\0';
		syscall(0,"file 2\r\n");
		syscall(0,file2);
		syscall(0,"\r\nfile 1\r\n");
		syscall(0,file);
		syscall(3,file,read,sector);
		syscall(8,read,file2,sector);
		syscall(0,"\r\ntest\r\n");
	}
	else if(command[0]='c' && command[1]=='r' && command[2]=='e' && command[3]=='a' && command[4]=='t' && command[5]=='e' && command[6]==' ' && command[7]=='t' && command[8]=='e' && command[9]=='x' && command[10]=='t' && command[11]=='f' && command[12]=='l'){
		for(i=0; i<7; i++){
			if(command[i+7]=='\r'){
				file[i]='\0';
				break;
			}else{
				file[i]=command[i+7];
			}
		}
		syscall(8,read,file,sector);
		while(j != 0){
			syscall(0,"Text: ");
			syscall(1,buffer);
			if(buffer[0]='\r'){
				syscall(3,file,read,sector);
				j=0;
			}
			else{
				//syscall(3,file,buffer,sector);
				syscall(0,"zebra");
			}
		}
	}
	else{
		syscall(0,"---ERROR---Command Does not exist");
	}
}
}
