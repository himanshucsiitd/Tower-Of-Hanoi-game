#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>/*done*/
/*Defines stack size*/
#define size 30
/*Defines the spacing between disc*/
#define gap 0
/*Starting coordinates*/
#define startx 16
#define starty 5
int size_a=-1,size_b=-1,size_c=-1,w,moves=0;int n,dif,height,movetill,numb;
char moved_from, moved_to,tower_a='a',tower_b='b',tower_c='c';
/*Define a new strucure type(sort of stack) used to store the value of radius code and the number of elements */
struct tower
	{ 
	  int stack[size];
	  int top;
	};
/*Towers being defined*/
struct tower a,b,c;
/*Discs defined as boxed windows*/
WINDOW *hi,*ho;
/*function to store discs position before shifting*/
void store()
	{
	 size_a=a.top;
	 size_b=b.top;
	 size_c=c.top;
	}
/*moves the latest disc*/
void printing()
	{
	 /*Initialise cursor mode*/	
	 initscr();
	 cbreak();
	 noecho();
	 int r,h,g,d,e;
	 int maxy,maxx;
	 /*Gets boundary cordinates*/
	 getmaxyx(stdscr,maxy,maxx);
	 /*Determine from which tower to which the latest shift takes place*/
	 if(size_a>a.top)moved_from='a';
	 if(size_b>b.top)moved_from='b';
	 if(size_c>c.top)moved_from='c';
	 if(size_a<a.top)moved_to='a';
	 if(size_b<b.top)moved_to='b';
	 if(size_c<c.top)moved_to='c';
	 /*Bottom most point of discs*/
	 g=maxy-starty;
	 /*Depending on the tower*/
	 if(moved_from == 'a')
		{
		 /*Defines disc radius code*/
		 r=2*a.stack[a.top+1];
		 /*center point of tower*/
		 h=startx-1-r/2;
		 /*Defines topmost disc y coordinate*/
		 g=g-(dif*(a.top+1));
		 }
	 if(moved_from == 'b')
		{
		 r=2*b.stack[b.top+1];
		 h=startx+(maxx/3)-1-r/2;
 		 g=g-(dif*(b.top+1));
		}
	 if(moved_from == 'c')
		{
		 r=2*c.stack[c.top+1];
		 h=startx+((2*maxx)/3)-1-r/2;
		 g=g-(dif*(c.top+1));
		}
	 /*Depending on the tower*/
	 if(moved_to == 'a')
	 	{
		 /*Y coordinate of new disc position*/
		 d=(maxy-starty)-(dif*(a.top));
		 /*center point of tower*/
		 e=startx-1-r/2;
		}
	 if(moved_to == 'b')
		{
		 d=(maxy-starty)-(dif*(b.top));
		 e=startx+(maxx/3)-1-r/2;
		}
	 if(moved_to == 'c')
		{ 
		 d=(maxy-starty)-(dif*(c.top));
		 e=startx+((2*maxx)/3)-1-r/2;
		}
	 /*Prints the current disc movement using formatted text via ncurses*/
	 attron(A_BOLD);attron(A_UNDERLINE);
	 mvprintw(3,maxx/3,"The disc is moved from tower %c to tower %c",moved_from+32,moved_to+32);
	 attroff(A_BOLD);attroff(A_UNDERLINE);
	 refresh();
	 numb=r/2;
	 /*Movement of current disc takes place from here*/
 	 /*Vertical top movement*/
	 while(g>movetill)
		{ 
		 /*Deletes the topmost window(disc)*/
		 hi= newwin(height,r+2,g,h);
		 wrefresh(hi);
		 /*Moves 1 step up*/
		 g=g-1;
		 /*Creates a new disc*/
		 hi= newwin(height,r+2,g,h);
		 box(hi,0,0);
		 mvwprintw(hi,1,r/2,"%d",numb);
		 wrefresh(hi);
		 usleep(w*10000);
		}
	 /*Right movement*/
	 if(h<e)
		{
		/*while it does not reach tower's mid point*/
		while(h<e)
			{
			 hi= newwin(height,r+2,g,h);
			 wrefresh(hi);
			 /*MOves right*/
			 h=h+1;
			 hi= newwin(height,r+2,g,h);
			 box(hi,0,0);
			 mvwprintw(hi,1,r/2,"%d",numb);
			 wrefresh(hi);
			 usleep(w*10000);
			}
		}
	 /*Left movement*/
	 if(h>e)
		{
		while(h>e)
			{
			 hi= newwin(height,r+2,g,h);
			 wrefresh(hi);
			 /*Moves left*/
			 h=h-1;
			 hi= newwin(height,r+2,g,h);
			 box(hi,0,0);
			 mvwprintw(hi,1,r/2,"%d",numb);
			 wrefresh(hi);
			 usleep(w*10000);
			}
		}
 	/*Vertical Down movement*/
	/*While top of tower not reached*/
	while(g<d)
		{
		 hi= newwin(height,r+2,g,e);
		 wrefresh(hi);
		 /*Moves down*/
		 g=g+1;
		 hi= newwin(height,r+2,g,e);
		 box(hi,0,0);
		 mvwprintw(hi,1,r/2,"%d",numb);
		 wrefresh(hi);
		 usleep(w*10000);
		}
	 /*Prints no. of moves*/
	 attron(A_BOLD);attron(A_UNDERLINE);
	 mvprintw(2,maxx/3,"The no.of moves uptill now: %d.",moves);
	 attroff(A_BOLD);attroff(A_UNDERLINE);
	}
/*Adds element b to tower*/
void push(int b, int array[], int *x)
	{
	/*Increases top counter*/
	*x=*x+1;
	/*Adds element*/
	array[*x]=b;
	}
/*Deletes and returns topmost element of tower*/
int pop(int array[], int *x)
	{
	int e;
	e=*x;
	*x=*x-1;
	return(array[e]);
	}
/*Shifts topmost elementof "from" to "to" */
void swap(int from[], int *x,int to[], int *y)
	{
	int e;
	e=pop(from,&(*x));
	push(e,to,&(*y));moves++;
	}
/*Base case of shifting of two discsfrom one tower(from) to another(to) using third tower(using)*/
void twoshift(int from[],int *x, int to[], int *y, int using[], int *z)
	{
	store();swap(from,&(*x),using,&(*z));printing();
	store();swap(from,&(*x),to,&(*y));printing();
	store();swap(using,&(*z),to,&(*y));printing();
	}
/*Recursive function for shifting ..based on that to shift n discs from a to b , n-1 are shfted from a to c, then shift of nth disc takes to b, and finally n-1 disc tower is shifted to b*/
void shift(int n,int from[],int *x, int to[], int *y, int using[], int *z)
	{
	if(n>2)
		{
		shift(n-1,from,&(*x),using,&(*z),to,&(*y));
		store();swap(from,&(*x),to,&(*y));printing();
		shift(n-1,using,&(*z),to,&(*y),from,&(*x));
		}
	if(n==2)
		{
		twoshift(from,&(*x),to,&(*y),using,&(*z));
		}
	}
int main()
	{
	 int i,s,t;
	 /*Disc size enter*/
	 printf("What is the number of discs?(<16)\n");
	 scanf("%d",&n);
	 /*Input validation for disc size*/
	 for(i=0;(((n<=0) || (n>15)) && i<2);i++)
	 {
	 printf("Invalid Input, Please enter again\n");
	 scanf("%d",&n);
	 }
	 if((n<=0) || (n>15))
	 {
	 printf("Invalid Input. Program will exit.\n");
	 exit(0);
	 }
	 /*Disc movement speed input*/
 	 printf("Enter the speed(1-10):\n(1-fastest, 10-slowest)\n");
	 scanf("%d",&w);
	 for(i=0;((w<=0 || w>10) && i<2);i++)
	 {
	 printf("Invalid Input, Please enter again\n");
	 scanf("%d",&w);
	 }
	 /*Input validation for it*/
	 if(w<=0 || w>10)
	 {
	 printf("Invalid Input. Program will exit.\n");
	 exit(0);
	 }
	 /*Initialise no discs for each tower*/
	 a.top=-1;
	 b.top=-1;
	 c.top=-1;
	  /*Generates the stack(tower)*/
	 for(i=n;i>0;i--)
	 	{
	 	push(i,a.stack,&a.top);
	 	}
	 /*Curses mode*/
	 initscr();
	 start_color();
	 noecho();
	 cbreak();
	 /*Boundary coordinates and defining height as per no. of discs*/
 	 getmaxyx(stdscr,s,t);
	 height=(s-starty-5)/n;
	 if(height>=5)height=4;
	 if(height<=0)height=1;
	 dif=height+gap;
	 /*Junk Window*/
	 ho=newwin(2,3,(2),2);
 	 box(ho,0,0);
 	 wrefresh(ho);
 	 refresh();
	 init_pair(1, COLOR_RED, COLOR_BLACK);
	 /*Prints initial tower using boxed windows*/
	 attron(A_BOLD);attron(A_UNDERLINE);
	 attron(COLOR_PAIR(1));
	 mvprintw(1,t/3,"Generating the Tower");
	 mvprintw(2,5+(2*t)/3,"Press CTRL+Z to exit.");
	 attroff(COLOR_PAIR(1));
	 attroff(A_BOLD);attroff(A_UNDERLINE);
 	 for(i=0;i<=a.top;i++)
 		{mvprintw(1,(t/3)+i+20,".");
 		ho=newwin(height,2*a.stack[i]+2,(s-starty)-(dif*i),startx-1-(a.stack[i]));
 		box(ho,0,0);
		mvwprintw(ho,1,a.stack[i],"%d",a.stack[i]);
 		wrefresh(ho);
 		refresh();
 		usleep(700000);
 		}
	 movetill=(s-starty)-(dif*i)+2;
	 /*Deletes printed letters*/
	 mvprintw(1,t/3,"                                                          ");
	 mvprintw(1,1,"Number Of Discs: %d",n);
	 attron(A_BOLD);attron(A_UNDERLINE);
	 mvprintw(s+height-starty,startx-3,"TOWER A");
 	 mvprintw(s+height-starty,startx +t/3-3,"TOWER B");
	 mvprintw(s+height-starty,startx +(2*t)/3-3,"TOWER C");
	 attroff(A_BOLD);attroff(A_UNDERLINE);
	 /*For n=1*/
	 if(n==1)
	 {store();swap(a.stack,&a.top,c.stack,&c.top);printing();
	 }
	 if(n>1)
	 /*Initial base case shift*/
	 twoshift(a.stack,&a.top,b.stack,&b.top,c.stack,&c.top);
	 /*Shifting of individual discs towers i.e. assuming a tower of n discs to be of 1,2,3...n.discs*/
	 for(i=3;i<=n;i++)
		{
		store();swap(a.stack,&a.top,c.stack,&c.top);printing();
		shift(i-1,b.stack,&b.top,c.stack,&c.top,a.stack,&a.top);
		i++;
		if(i<=n)
			{
			store();swap(a.stack,&a.top,b.stack,&b.top);printing();
			shift(i-1,c.stack,&c.top,b.stack,&b.top,a.stack,&a.top);
			}	
		}

	 attron(COLOR_PAIR(1));
	 mvprintw((s-dif*(b.top))/2,t/3,"Shifting complete...");
 	 attroff(COLOR_PAIR(1));
	 refresh();
	 sleep(5);
	 endwin();
	}

