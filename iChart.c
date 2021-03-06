#include<graphics.h>
#include<dos.h>
#include<process.h>
#include<alloc.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<ctype.h>
#include<types.h>
#include<stat.h>

#define CGA 1
#define ENTRYOVER 1
#define ENTRYSTART 0
#define ESCAPE 27
#define END 79
#define LINE 1
#define XY 2

/*various menu definitions*/
/*character following ^ symbol is the hot key*/
char *mainmenu[]={ "^Data", "^Graph","^Files","^Exit"};
char *datamenu[]= { "^File", "^Keyboard","^Return" };
char *graphmenu[]={ "^Bar Chart","^Stacked chart","^Pie chart","^X Y chart","^Return" };
char *filesmenu[]={ "^Load", "^Save","^Print2,"^Return" };
char *keyboardmenu[]={ "^New data","^Edit data", "^Legend", "^Return"};
char *exitmenu[]={ "^Exit","^Shell","^Return"};
char *messages[]={"Main Menu", "Allows entry of data from file/keyboard", "Draws bar/stacked/X Y/pie chart","Loads/Saves/Prints a graph","Exit to DOS","Data Menu","Reads data from a file","Entry of data from keyboard", "Return to main menu", "Graph menu","Draws Bar chart","Draws stacked bar chart","Draws pie-chart","Reads data from a file","Entry of data from keyboard","Return to main menu""Graph Menu","Draws Bar Chart","Draws stacked bar chart", "Draws pie-chart","Draws X Y chart","Draws line chart","Return too main menu","File menu","Loads a graph","Saves a graph","Prints a graph","Return to main menu","File Menu","Loads a graph","Saves a graph","Prints a graph","Return to main menu","Keyboard Menu","Enter fresh data","Edit current data","Entry of leend","Return to Data Menu","Exit Menu","Exit to DOS","OS shell","Return to main menu","Chart Master","Memory Allocation Error","Press any key to continue...",
int count,ascii,scan data_type,max_x_entries,max_y_sets,gd,gm;
long starttime,endtime;
char y_sets_desc[6][31].titles[3][31],filenae[31],arr[]="ABCDEF";
char *graph_ptr;
char far*vid_mem;
double yrange[15][6],xrange[15];
/*symbols used for indicating points while drawing XY/Line chart*/
char *symbol[]={"+","*","","O","|","#"};
/*pops up a menu on the existing screen contents*/
popupmenu(menu,count,hotkeys,helpnumber)
int count,helpnumber;
char **menu,*hotkeys;
{
 int sr,sc, er,ec srmenu,scmenu,i,l=0,len,areareqd,choice;
 char *p;
 /*calculate starting row and ending row of menu box*/
 sr=(25-(count+10))/2;
 er=24-sr;
 if(count%2)
 er++;
 
 /*find the longest help message*/
 for(i=1;i<=count;i++)
 {
  len=strlen(messages[helpnumber+i]);
  if(len>1)
  l=len;
 }
 /*calculate starting column of menu box depending on longest help message*/
 sc=(80-(l+9)/2;
 /*calculate ending column of menu box*/
 ec=80-sc;
 /*calculate area required to save screen contents where menu is to be popped up*/
 areareqd=(er-sr+1)*(ec-sc+1)*2;
 
 /*allocate memory,if unsuccessful display error and terminate execution*/
 p=malloc(areaereqd);
 if(p==NULL)
 alloc_error_exit();
 
 /*sace screen contents into allocated memory*/
 savevideo(sr,sc,er,ec,p)
 /*give the effect of zooming menus*/
 delay(15);
 menubox(9,37,15,42,127,0);
 drawbox(9,37,15,42,127);
 delay(15);
 menubox(sr,sc,er,ec,127,07);
 drawbox(sr+1,sc+2.er-2,ec-4,127);
 
 /*determine length of current menu name*/
 l=strlen(messages[helpnumber]);
 /*calculate column from wher t he menu name is to be displayed*/
 l=39-l/2;
 /*display menu name*/
 writestring(messges[helpnumber],sr+2,l,127);
 /*draw two horizontal lines*/
 for(i=sc+3;i<=ec-4;i++)
 {
  writechar(sr+3,i,196,127);
  writechar(er-4,i,196,127);
}
/*display corner characters*/
writechcar(sr+3,sc+2,199,127);
writechar(er-4,sc+2,199,127);
writechar(sr+3,ec-4,182,127);
writechar(er-4,ec-4,182,127);

/*find the longest menu item in currrent menu*/
l=0;
for(i=0;i<count;i++)
{
len=strlen(menu[i]);
if(len>1)
l=len;
}

/*calculate starting row and starting column for displaying menu items*/
srmenu=((25-count)/2)-1;
scmenu=((80-(l+6)/2)-1;

/*display the menu in the menu box drawn earlier*/
displaymenu(menu,count,srmenu,scmenu);
/*display help message*/
writestring(messges[helpnumber+1],er-3,sc+4,127);
/*receive user's choice*/
choice=getresponse(menu,hotkeys,srmenu,scmenu,count,helpnumber+1,er,sc);
/*restore original screen contents*/
restorevideo(sr,sc,er,ec,p);
/*free allocated memory*/
free(p);
return(choice);
}


