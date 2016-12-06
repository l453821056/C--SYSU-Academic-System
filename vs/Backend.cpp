#include "stdafx.h"
#include "Backend.h"
#include <iostream>
using namespace std;
Selection CurrentSelect;
Time CurrentTime;
Storage Students;
string LessonsType[4]= {"PubReq","ProReq","PubEle","ProEle"};
string DaysOfWeekName[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
void throwError(int ErrorLevel, string ErrorProcedure,const char *argv)
{
            Error ErrorInstance;
            ErrorInstance.ErrorLevel=ErrorLevel;
            ErrorInstance.ErrorProcedure=ErrorProcedure;
            strcpy_s(ErrorInstance.ErrorArgv,MAX_COMMAND_CHAR,argv);
            throw ErrorInstance;
}
void throwError(int ErrorLevel, string ErrorProcedure,string ErrorMessage)
{
            Error ErrorInstance;
            ErrorInstance.ErrorLevel=ErrorLevel;
            ErrorInstance.ErrorProcedure=ErrorProcedure;
            ErrorInstance.ErrorMessage=ErrorMessage;
            memset(ErrorInstance.ErrorArgv,0,256);
            throw ErrorInstance;
}
void throwWarning(int ErrorLevel, string ErrorProcedure,const char *argv,string ErrorMessage)
{
    switch(ErrorLevel){
        case ACCESS_UNREASONABLE:{
            cout<<"Warning: Unreasonable Access During "<<RED<<ErrorProcedure<<RESET<<endl;
            break;
        }
        default:
            break;
    }
    cout<<"During Processing Argument "<<RED<<argv<<RESET<<endl;    
    if(!ErrorMessage.empty())
        cout<<RED<<ErrorMessage<<RESET<<endl;
}
int MY_strcmp(const char* Command, const char* Input, bool EnableShort)
{
    if(EnableShort)
        return (strcmp(Input,Command)&&stricmp(Input,Command)&&!(Input[0]==Command[0]));
    else
        return (strcmp(Input,Command)&&stricmp(Input,Command));
}


int vaildStudentId(const char InputStudentId[])
{
    int StudentId=atoi(InputStudentId);
    if(StudentId<0 || StudentId>100000000)
        return 0;
//  if(!findStudentId(StudentId))
//      return 0;
    return StudentId;
}
    
int vaildTerm(const char InputTerm[])
{
    //To do
    int Term=atoi(InputTerm);
    if(Term<1||Term>MAX_TERM_OF_STUDENT)
        return 0;
    return Term;
}
int vaildYear(const char InputYear[])
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
    cout <<"Not Found Help of "<<BOLDMAGENTA<<(*(argv.begin()))<<RESET;
    for(auto beg=argv.begin()+1;beg!=argv.end();++beg)
        cout <<"In module"<<BOLDMAGENTA<<*beg<<RESET;
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
                throwError(INVAILD_INPUT,"Select Student",argv[i]);
                }
            cout <<"Successfully Selected Student "<<CYAN<<CurrentSelect.StudentId<<RESET<<", Now You Need To Select"<<BOLDMAGENTA<<" Year "<<RESET<<"and"<<BOLDMAGENTA<<" Term"<<RESET<<endl;   
            CurrentSelect.Selected=false;
        }
        else if (!MY_strcmp("year",argv[i])){
            int result=CurrentSelect.CurrentYear=vaildYear(argv[++i]);
            if(!result){
                throwError(INVAILD_INPUT,"Select Year",argv[i]);
                }
            if(INVAILD_SELECTION==result){
                throwError(INVAILD_SELECTION,"Select Year",argv[i]);
                }
            cout <<"Successfully Selected Year "<<CYAN<<CurrentSelect.CurrentYear<<RESET<<", Now You Need To Select"<<BOLDMAGENTA<<" Term"<<RESET<<endl;   
        }
        else if(!MY_strcmp("term",argv[i])){
            int result=CurrentSelect.CurrentTerm=vaildTerm(argv[++i]);
            if(!result){
                throwError(INVAILD_INPUT,"Select Term",argv[i]);
                }
            if(INVAILD_SELECTION==result){
                throwError(INVAILD_SELECTION,"Select Term",argv[i]);
                }
            cout <<"Successfully Selected Term "<<CYAN<<CurrentSelect.CurrentTerm<<RESET<<endl;
            CurrentSelect.Selected=true;
        }
        else{
            throwError(INVAILD_INPUT,"Selection",argv[i]);
        }
        i++;
    }
    return 0;
}
int add(int argc, char *argv[])
{
    if(argc<=2){
        help({"add"});
    }
    int i=2;
    if(argc==3){
        if(!MY_strcmp("student",argv[i])){
            Students.Add();
        }
        else if(!MY_strcmp("lesson",argv[i])){
            if(CurrentSelect.Selected==false){
                throwError(NOT_HAVE_SELECTED,"add lesson",string("Now You Have Selected Student ")+string(to_string(CurrentSelect.StudentId))+string(" Year ")+string(to_string(CurrentSelect.CurrentYear))+string(" Term ")+string(to_string(CurrentSelect.CurrentTerm)));
            }
        }
        else{
            throwError(INVAILD_INPUT,"Addition",argv[i]);
        }
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
