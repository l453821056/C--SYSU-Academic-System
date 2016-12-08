#ifndef STORAGE_H
#define STORAGE_H
#include "Student.h"
class Storage{
    private:
//        Student Students[MAX_STUDENTS_NUM];
        vector<Student> Students;
        int TotalStudentNumber;
    public:
        int& getTotalStudentNumberRefer()
        {
            return TotalStudentNumber;
        }
        Storage()
        {
            getTotalStudentNumberRefer()=0;
        }
        const Student& getStudent(int n)
        {
            char argv[MAX_COMMAND_CHAR];
            sprintf(argv,"%d",n);
            if(n>getTotalStudentNumberRefer())
                throwError(ACCESS_VIOLATION,"Read Students",argv);
            return Students[n];
        }
        const Student& operator [](int n)
        {
            char argv[MAX_COMMAND_CHAR];
            sprintf(argv,"%d",n);
            if(n>getTotalStudentNumberRefer())
                throwError(ACCESS_VIOLATION,"Read Students",argv);
            return Students[n];
        }
        Student* getStudentHandle(int n)
        {
            char argv[MAX_COMMAND_CHAR];
            sprintf(argv,"%d",n);
            if(n==getTotalStudentNumberRefer()){
                if(n==MAX_STUDENTS_NUM)
                    throwError(STORAGE_FULL,"Write Students",argv);
                Student temp;
                Students.push_back(temp);
            }
            else if(n>getTotalStudentNumberRefer())
                throwError(ACCESS_VIOLATION,"Write Students",argv);
            return &Students[n];
        }
        int Add()
        {
            if(getTotalStudentNumberRefer()==MAX_STUDENTS_NUM)
                throwError(STORAGE_FULL,"Add Student",string("You can not storage more student"));
            string Input;
            cout <<"请输入学号"<<endl;
            cin>>Input;
            int result=vaildStudentId(Input.c_str());
            if(!result||result==INVAILD_SELECTION){
                throwError(INVAILD_INPUT,"add student",Input.c_str());
                }
            cout <<"请输入姓名"<<endl;
            cin>>Input;
            this->getStudentHandle(getTotalStudentNumberRefer())->setName(Input);
            this->getStudentHandle(getTotalStudentNumberRefer())->setStudentId(result);
            getTotalStudentNumberRefer()++;
        }
        int Find(int StudentId)
        {
            bool found=false;
            for(int i=0;i<getTotalStudentNumberRefer();i++)
            {
                if(this->getStudentHandle(i)->getStudentId()==StudentId){
                    found=true;
                    return i;
                }
            }
            if(!found)
                return NOT_FOUND_STUDENTID;
        }
        int print()
        {
            cout<<((*this)[0]).Name<<endl;
            return 0;
        }
};
#endif
