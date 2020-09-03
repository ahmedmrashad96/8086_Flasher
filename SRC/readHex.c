#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	int mapp(char x);
	
	char s[];
	int main(int argc, char** argv)
	{
		
		if (argc == 1 )
	   {
		   printf("No File entered"); exit(EXIT_FAILURE);
	   }
	 
		char ch;
		char **	file_name;
		file_name = argv[1];
		FILE *fp;

		//printf("\nfile name : %s\n",file_name);
		//printf("Enter name of a file you wish to see\n");
		//gets(file_name);

		fp = fopen(file_name, "r"); // read mode

		if (fp == NULL)
		{
		  perror("Error while opening the file.\n");
		  exit(EXIT_FAILURE);
		}

		printf("The contents of %s file are:\n", file_name);
		int i=0;
		int y=0;
		while((ch = fgetc(fp)) != EOF)
		{
		   s[i]=ch;
		   if (ch == '\n') 
		   {
				y++;		   
		   }
		   i++;
		}
		fclose(fp);
		s[i]='\0';
		
		printf("%s\n", s);
		printf("Number of lines is %d", y+1);
		printf("\n");
		printf("%d\n",mapp('F'));
		printf("%c",s[0]);
		printf("%c",s[16]);
		printf("%c\n",s[29]);
		int count , addh, addl,typ;
		for(int x = 0; x<i ; x++ )
		{
			
			if(s[x] == ':') 
			{
				//printf("%c",s[16]);
				printf("\n");
				x++;
				count = mapp(s[x])*16+mapp(s[x+1]);
				printf("c%d\n",count);
				x=x+2;
				addh = mapp(s[x])*16+mapp(s[x+1]);
				printf("a%d",addh);
				x=x+2;
				addl = mapp(s[x])*16+mapp(s[x+1]);
				printf("a%d\n",addl);
				x=x+2;
				typ = mapp(s[x])*16+mapp(s[x+1]);
				printf("t%d\n",typ);
				x=x+2;
			}
			for (int q = 0; q < count; q++)
			{
				//printf("%d ", q);
				printf("%d ", addh);
				
				printf("%d\t", addl+q);
				printf("%d\t", mapp(s[x]));x++;
				printf("%d\n", mapp(s[x]));
				x++;
			}
			x=x+2;
			if(s[x+1] == '\n')
			{
				x++;
				printf("\n");
			}
		}
		return 0;
	}
	
	int mapp(char x)
	{
		if (x  == '0' ) return 0;
		if (x  == '1' ) return 1;
		if (x  == '2' ) return 2;
		if (x  == '3' ) return 3;
		if (x  == '4' ) return 4;
		if (x  == '5' ) return 5;
		if (x  == '6' ) return 6;
		if (x  == '7' ) return 7;
		if (x  == '8' ) return 8;
		if (x  == '9' ) return 9;
		if (x  == 'A' ) return 10;
		if (x  == 'B' ) return 11;
		if (x  == 'C' ) return 12;
		if (x  == 'D' ) return 13;
		if (x  == 'E' ) return 14;
		if (x  == 'F' ) return 15;
		
		return 111;
		

	}
