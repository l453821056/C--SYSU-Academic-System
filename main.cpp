#include <iostream>
#include "Backend.h"
#include "main.h"
using namespace std;
int main(int argc, char *argv[])
{
    //Init Promote
    cout <<"Welcome to MUKS, a Multi-User Kechengbiao Software "<<endl;
    cout <<"Type "<<BOLDMAGENTA<<"help "<<RESET<<"for instructions on how to use MUKS"<<endl;
    promote();
    //Read Student Information Form File
/*  string Path="./";
    string FileNamePath="./data/";
    string StudentListFilePath="./data/list.txt"
    fstream StudentListFile(StudentListFilePath);
    while(!StudentListFile.eof()){
    string FileName;
    StudentListFile>>FileName;
*/  
    

    //Init Command stack
    char *iargv[MAX_COMMAND];
    for(int i=0;i<MAX_COMMAND;i++){
        iargv[i]=new char [MAX_COMMAND_CHAR];
        memset(iargv[i],0,sizeof(char)*MAX_COMMAND_CHAR);
    }
    for(int i=0;i<argc;i++)
        strcpy_s(iargv[i],MAX_COMMAND_CHAR,argv[i]);
    //read Command
    string Command;
    cin.sync_with_stdio(false);
    while(cin>>Command&&Command!="quit")
    {
        if(argc <= MAX_COMMAND){
            strcpy_s(iargv[argc],MAX_COMMAND_CHAR,Command.c_str());
            argc++;
        }
        if(cin.rdbuf()->in_avail()==1){
            if(argc != 1){
                try{
                if(!strcmp(iargv[1],"select"))
                    select(argc,iargv);
                else if(!strcmp(iargv[1],"add"))
                    add(argc,iargv);
                else if(!strcmp(iargv[1],"delete"))
                    del(argc,iargv);
                else if(!strcmp(iargv[1],"sort"))
                    sort(argc,iargv);
                else if(!strcmp(iargv[1],"find"))
                    find(argc,iargv);
                else if(!strcmp(iargv[1],"print"))
                    print(argc,iargv);
                else
                    cout<<"Wrong Input, enter"<<BOLDMAGENTA<<" help"<<RESET<<" to see manual"<<endl;
                }catch(Error ErrorInstance){
                    switch(ErrorInstance.ErrorLevel){
                        case INVAILD_INPUT:{
                            cout<<RED<<"Error: Invaild Input During "<<RED<<ErrorInstance.ErrorProcedure<<RESET<<endl;
                            break;
                        }
                        case INVAILD_SELECTION:{
                            cout<<RED<<"Error: Invaild Selection During "<<RED<<ErrorInstance.ErrorProcedure<<RESET<<endl;
                            break;
                        }
                        case NOT_HAVE_SELECTED:{
                            cout<<RED<<"Error: Invaild Selection During "<<RED<<ErrorInstance.ErrorProcedure<<RESET<<endl;
                            break;
                        }
                        case ACCESS_VIOLATION:{
                            cout<<RED<<"Error: Invaild Access During "<<RED<<ErrorInstance.ErrorProcedure<<RESET<<endl;
                            break;
                        }
                        case STORAGE_FULL:{
                            cout<<RED<<"Error: Storage is Full "<<RED<<ErrorInstance.ErrorProcedure<<RESET<<endl;
                            break;
                        }
                        default:
                            break;
                    }
                    cout<<"During Processing Argument "<<RED<<ErrorInstance.ErrorArgv<<RESET<<endl;    
                    if(!ErrorInstance.ErrorMessage.empty())
                        cout<<RED<<ErrorInstance.ErrorMessage<<RESET<<endl;
                }
                argc=1;//Clear Used Command
            }
            promote();
        }
    }
    return 0;
}
