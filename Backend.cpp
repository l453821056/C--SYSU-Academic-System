#include "Backend.h"
#include <iostream>
using namespace std;
Selection CurrentSelect;
Time CurrentTime;
Student Students[MAX_STUDENTS];
string LessonsType[4]= {"PubReq","ProReq","PubEle","ProEle"};
string DaysOfWeekName[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
int MY_strcmp(const char* Command, const char* Input, bool EnableShort)
{
    if(EnableShort)
        return (strcmp(Input,Command)&&strcasecmp(Input,Command)&&!(Input[0]==Command[0]));
    else
        return (strcmp(Input,Command)&&strcasecmp(Input,Command));
}

char* strcpy_s(char *dest,size_t destsz, const char *src)
{
    size_t len=strlen(src);
    return len<=destsz?strcpy(dest,src):strcpy(dest,"");
}
int vaildStudentId(char InputStudentId[])
{
    int StudentId=atoi(InputStudentId);
    if(StudentId<0 || StudentId>100000000)
        return 0;
//  if(!findStudentId(StudentId))
//      return 0;
    return StudentId;
}
    
int vaildTerm(char InputTerm[])
{
    //To do
    int Term=atoi(InputTerm);
    if(Term<1||Term>MAX_TERM_OF_STUDENT)
        return 0;
    return Term;
}
int vaildYear(char InputYear[])
{
    int Year=atoi(InputYear);
    if(Year<1924||Year>CurrentTime.getYear())
        return 0;
    return Year;
}
void help(initializer_list<string> argv)
{
    bool found=true;
    auto beg=argv.begin();
    if(argv.size()==1)
    {
        bool found=true;
        if(!MY_strcmp("select",(*beg).c_str())){
            cout<<"可用参数    "<<"用法"<<RESET<<endl;
			cout<<"student     "<<"后接学生学号，如"<<BOLDMAGENTA<<"select student 15323032"<<RESET<<RESET<<endl;
			cout<<"year        "<<"后接学年    ，如"<<BOLDMAGENTA<<"select year    2016"<<RESET<<RESET<<endl;
			cout<<"term        "<<"后接学期    ，如"<<BOLDMAGENTA<<"select term    1"<<RESET<<RESET<<endl;
            ++beg;
        }
        else{
            found=false;
        }
    }
    if(!found)
    {
    cout <<"没有找到"<<BOLDMAGENTA<<(*(argv.begin()))<<RESET<<"的帮助。";
    for(auto beg=argv.begin()+1;beg!=argv.end();++beg)
        cout <<"在模块"<<BOLDMAGENTA<<*beg<<RESET<<"中";
    cout <<endl;
    return;
    }
}
int select(int argc, char *argv[])
{
    if(argc<=2 || argc%2!=0){
        help({"select"});
    }
    int i=2;
    while(i<argc){
        if(!MY_strcmp("student",argv[i])){
            if(!(CurrentSelect.StudentId=vaildStudentId(argv[++i]))){
                cout <<RED<<"Invaild Student Id"<<RESET<<endl;
                return INVAILD_INPUT;
                }
            cout <<"Successfully Selected Student "<<CYAN<<CurrentSelect.StudentId<<RESET<<", Now You Need To Select"<<BOLDMAGENTA<<" Year "<<RESET<<"and"<<BOLDMAGENTA<<" Term"<<RESET<<endl;   
            CurrentSelect.Selected=false;
        }
        else if (!MY_strcmp("year",argv[i])){
            int result=CurrentSelect.CurrentYear=vaildYear(argv[++i]);
            if(!result){
                cout <<RED<<"Invaild Year"<<RESET<<endl;
                return INVAILD_INPUT;
                }
            if(INVAILD_SELECTION==result){
                cout <<RED<<"Invaild Year,You Should Select Student First"<<RESET<<endl;
                return INVAILD_INPUT;
                }
            cout <<"Successfully Selected Year "<<CYAN<<CurrentSelect.CurrentYear<<RESET<<", Now You Need To Select"<<BOLDMAGENTA<<" Term"<<RESET<<endl;   
        }
        else if(!MY_strcmp("term",argv[i])){
            int result=CurrentSelect.CurrentTerm=vaildTerm(argv[++i]);
            if(!result){
                cout <<RED<<"Invaild Term"<<RESET<<endl;
                return INVAILD_INPUT;
                }
            if(INVAILD_SELECTION==result){
                cout <<RED<<"Invaild Term,You Should Select Student and Year First"<<RESET<<endl;
                return INVAILD_INPUT;
                }
            cout <<"Successfully Selected Term "<<CYAN<<CurrentSelect.CurrentTerm<<RESET<<endl;
            CurrentSelect.Selected=true;
        }
        else{
            Error ErrorInstance;
            ErrorInstance.ErrorLevel=INVAILD_INPUT;
            ErrorInstance.ErrorProcedure="Selection";
            strcpy_s(ErrorInstance.ErrorArgv,256,argv[i]);
            throw ErrorInstance;
        }
        i++;
    }
    return 0;
}
int add(int argc, char *argv[])
{
    if(argc<=2 || argc%2!=0){
        help({"add"});
    }
    int i=2;
    while(i<argc){
        if(!MY_strcmp("student",argv[i])){
                }
        else if(!MY_strcmp("lesson",argv[i])){
        }
        else
            Error ErrorInstance;
            ErrorInstance.ErrorLevel=INVAILD_INPUT;
            ErrorInstance.ErrorProcedure="Selection";
            strcpy_s(ErrorInstance.ErrorArgv,256,argv[i]);
            throw ErrorInstance;
    }
    return 0;
}
int del(int argc, char *argv[])
{
    return 0;
}
int find(int argc, char *argv[])
{
    return 0;
}
int sort(int argc, char *argv[])
{
    return 0;
}
int promote()
{
    if(!CurrentSelect.Selected)
       cout << "NS > ";
    else 
       cout <<CurrentSelect.StudentId<<"@"<<CurrentSelect.CurrentYear<<"T"<<CurrentSelect.CurrentTerm<<" > "; 
    return 0;
}
