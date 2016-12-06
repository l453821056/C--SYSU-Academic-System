#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;
#define MAX_COMMAND 32//256
#define MAX_COMMAND_CHAR 256
#define MAX_STUDENTS_NUM 8//256
#define INVAILD_INPUT 0x01
#define NOT_HAVE_SELECTED 0x02
#define ACCESS_VIOLATION 0x04
#define ACCESS_UNREASONABLE 0x08
#define INVAILD_SELECTION -1
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define MAX_LESSON_OF_TERM 16//128
#define MAX_TERM_OF_STUDENT 16//32
#define DURATION_OF_LESSON 45
int select(int argc, char *argv[]);
int add(int argc, char *argv[]);
int del(int argc, char *argv[]);
int find(int argc, char *argv[]);
int sort(int argc, char *argv[]);
int promote();
int vaildStudentId(const char InputStudentId[]);
int vaildTerm(const char InputTerm[]);
int vaildYear(const char InputYear[]);
int MY_Find(const string Method, const string Content);
int MY_strcmp(const char *Command, const char *Input, bool EnableShort=true);
void throwError(int ErrorLevel,string ErrorProcedure, string ErrorMessage);
void throwError(int ErrorLevel,string ErrorProcedure, const char *agrv);
void throwWarning(int ErrorLevel, string ErrorProcedure,const char *argv,string ErrorMessage="");
extern string Weekdays[7];
extern string Lesson_Type[4];
typedef struct Error_Struct{
    int ErrorLevel;
    char ErrorArgv[MAX_COMMAND_CHAR];
    string ErrorProcedure;
    string ErrorMessage;
}Error;
typedef struct Selection_Struct{
    bool Selected=false;
    int StudentId=0;
    int CurrentYear=0;
    int CurrentTerm=0;
}Selection;
class Time{
    public:
    int Year;
    int Month;
    int Day;
    int Hour;
    int Min;
    int Second;
    Time()
    {
    reNew();
    }
    void reNew()
    {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y");
    Year=atoi((ss.str()).c_str());
    ss.sync();
    ss << std::put_time(std::localtime(&in_time_t), "%m");
    Month=atoi((ss.str()).c_str());
    ss.sync();
    ss << std::put_time(std::localtime(&in_time_t), "%d");
    Day=atoi((ss.str()).c_str());
    ss.sync();
    ss << std::put_time(std::localtime(&in_time_t), "%H");
    Hour=atoi((ss.str()).c_str());
    ss.sync();
    ss << std::put_time(std::localtime(&in_time_t), "%M");
    Min=atoi((ss.str()).c_str());
    ss.sync();
    ss << std::put_time(std::localtime(&in_time_t), "%S");
    Second=atoi((ss.str()).c_str());
    ss.sync();
    }
    int getYear()
    {
        return Year;
    }
    int getMonth()
    {
        return Month;
    }
    int getDay()
    {
        return Day;
    }
    int getHour()
    {
        return Hour;
    }
    int getMin()
    {
        return Min;
    }
    int getSecond()
    {
        return Second;
    }
};
class Lesson{
    public:
    int Term;
    int Year;
    string Name;
    string TeacherName;
    int Type;
    int Weekday;
    int StartWeek;
    int EndWeek;
    int StartTime;
    int EndTime;
    bool Finished;
    int Credit;
    int Grade;
    string GetTime(int StartTime)
    {
        int Hour=8+((StartTime-1)*55)/60;
        int Min=(StartTime-1)*55%60;
        return (to_string(Hour)+":"+to_string(Min));
    }
    Lesson(){
        Term=1;
        Name="NS";
        Type=0;
        Weekday=0;
        StartWeek=1;
        EndWeek=1;
        StartTime=1;
        EndTime=1;
        Finished=false;
        Credit=1;
        Grade=-1;
    }

};
class Term{
    private:
        int Average;
        int AverageExpectPubEle;
        int TotalCredit;
        int TotalCreditExpectPubEle;
    public:
        int Year;
        int TotalRank;
        int Rank;
        Lesson Lessons[MAX_LESSON_OF_TERM+1];
        bool LessonsChanged;
        int NumberOfLesson;
        Term(){
            NumberOfLesson=0;
            Year=1924;
            Rank=1;
            TotalRank=0;
            TotalCredit=0;
            Average=0;
            AverageExpectPubEle=0;
            LessonsChanged=false;
            TotalCreditExpectPubEle=0;
        }
        int setYear(int Year)
        {
            this->Year=Year;
            for(int i=1;i<=MAX_LESSON_OF_TERM;i++)
                Lessons[i].Year=Year;
            return 0;
        }
        int setRank(int Rank)
        {
            this->Rank=Rank;
            for(int i=1;i<=MAX_LESSON_OF_TERM;i++)
                Lessons[i].Term=Rank;
            return 0;
        }
        int setTotalRank(int TotalRank)
        {
            this->TotalRank=TotalRank;
            return 0;
        }

        void reNew()
        {
            if(LessonsChanged)
            {
                int SumOfCredit=0;
                int SumOfGrade=0;
                int SumOfCreditExpectPubEle=0;
                int SumOfGradeExpectPubEle=0;
                for(int i=0;i<NumberOfLesson;i++)
                {
                    SumOfCredit+=Lessons[i].Credit;
                    SumOfGrade+=Lessons[i].Credit*Lessons[i].Grade;
                    SumOfCreditExpectPubEle+=(Lessons[i].Type==3?0:Lessons[i].Credit);
                    SumOfGradeExpectPubEle+=(Lessons[i].Type==3?0:Lessons[i].Credit*Lessons[i].Grade);
                }
                this->TotalCredit=SumOfCredit;
                this->TotalCreditExpectPubEle=SumOfCreditExpectPubEle;
                this->Average=SumOfGrade/SumOfCredit;
                this->AverageExpectPubEle=SumOfGradeExpectPubEle/SumOfCreditExpectPubEle;
                this->LessonsChanged=false;
            }
        }
        int getCredit()
        {
            reNew();
            return TotalCredit;
        }
        int getCreditExpectPubEle()
        {
            reNew();
            return TotalCreditExpectPubEle;
        }
        int getAverage()
        {
           reNew();
           return Average;
        }
        int getAverageExpectPubEle()
        {
           reNew();
           return AverageExpectPubEle;
        }
};
class Student{
    public:
        int NumberOfTerm=0;
        string Name;
        int StudentId;
        int EntranceYear;
        int OverallCredit;
        int OverallGrade;
        int OverallCreditExpectPubEle;
        int OverallGradeExpectPubEle;
        bool TermsContentChanged;
        Term Terms[MAX_TERM_OF_STUDENT+1];
        bool TermsChanged;
        void calcTermTillNow()
        {
         Time CurrentTime;
         this->NumberOfTerm= getNumberOfTerm(CurrentTime.getYear(),(CurrentTime.getMonth()<9&&CurrentTime.getMonth()>=3)?2:1); 
        }
        int getOverallCredit()
        {
            reNewStudentContentAfterTermsChanged();
            return OverallCredit;
        }
        int getOverallGrade()
        {
            reNewStudentContentAfterTermsChanged();
            return OverallGrade;
        }
        int getOverallGradeExpectPubEle()
        {
            reNewStudentContentAfterTermsChanged();
            return OverallGradeExpectPubEle;
        }
        int getOverallCreditExpectPubEle()
        {
            reNewStudentContentAfterTermsChanged();
            return OverallCreditExpectPubEle;
        }
        Student(){
            Name="N/S";
            StudentId=-1;
            EntranceYear=1924;
            OverallGrade=-1;
            OverallCredit=0;
            TermsChanged=false;
            NumberOfTerm=0;
        }
        const Term& getTerm(int n)
        {
            char argv[MAX_COMMAND_CHAR];
            sprintf(argv,"%d",n);
            if(n>MAX_TERM_OF_STUDENT)
                throwError(ACCESS_VIOLATION,"Read Terms",argv);
            return Terms[n];
        }
        const Term& operator [](int n)
        {
            char argv[MAX_COMMAND_CHAR];
            sprintf(argv,"%d",n);
            if(n>MAX_TERM_OF_STUDENT)
                throwError(ACCESS_VIOLATION,"Read Terms",argv);
            return Terms[n];
        }
        void calcEntranceYear()
        {
            EntranceYear=2000+StudentId/1000000;
        }
        int getNumberOfTerm(int Year, int Term)
        {
            Time CurrentTime;
            char argv[MAX_COMMAND_CHAR];
            sprintf(argv,"%d",Year);
            argv[4]=',';
            sprintf(argv,"%d",Term);
            if(Year>CurrentTime.getYear())
                throwWarning(ACCESS_UNREASONABLE,"Read Terms",argv);
            int Part1=(Year-EntranceYear)*3+Term;
            int Part2=(EntranceYear<=2015?(2015-EntranceYear+1):0);                              
            int Part3=((Year-(EntranceYear<=2015?2016:EntranceYear))*2+Term);
            return (Year<=2015?Part1:(Part2*3+Part3));/*
            return (((Year<=2015?((Year-EntranceYear)*3+Term):
       \(((EntranceYear<=2015?(2015-EntranceYear+1):0)*3+
        \(Year-(EntranceYear<=2015?2016:EntranceYear)*2+Term))); 
        */
        }
        Term* getTermHandle(int n)
        {
            char argv[MAX_COMMAND_CHAR];
            sprintf(argv,"%d",n);
            if(n>MAX_TERM_OF_STUDENT)
                throwError(ACCESS_VIOLATION,"Write Terms",argv);
            return &Terms[n];
        }
        int setName(string Name)
        {
            this->Name=Name;
            return 0;
        }
        int getTotalTermOfYear(int Year)
        {
            return Year<=2015?3:2;
        }
        int setStudentId(int StudentId)
        {
            Time CurrentTime;
            this->StudentId=StudentId;
            this->calcEntranceYear();
            this->calcTermTillNow();
            for(int i=EntranceYear;i<=CurrentTime.getYear();i++)
            {
                for(int j=1;j<=getTotalTermOfYear(i);j++)
                {
                int TotalRank=getNumberOfTerm(i,j);
                this->getTermHandle(TotalRank)->setYear(i);
                this->getTermHandle(TotalRank)->setTotalRank(TotalRank);
                this->getTermHandle(TotalRank)->setRank(j);
                }
            }
            return 0;
        }
        string getName()
        {
            return this->Name;
        }
        int getStudentId()
        {
            return this->StudentId;
        }
        void reNewStudentContentAfterTermsChanged()
        {
            if(TermsChanged)
            {
                int SumOfCredit=0;
                int SumOfGrade=0;
                int SumOfCreditExpectPubEle=0;
                int SumOfGradeExpectPubEle=0;
                for(int i=0;i<NumberOfTerm;i++)
                {
                    SumOfCredit+=Terms[i].getCredit();
                    SumOfGrade+=Terms[i].getCredit()*Terms[i].getAverage();
                    SumOfCreditExpectPubEle=Terms[i].getCreditExpectPubEle();
                    SumOfGradeExpectPubEle+=Terms[i].getCreditExpectPubEle()*Terms[i].getAverageExpectPubEle();
                }
                this->OverallCredit=SumOfCredit;
                this->OverallGrade=SumOfGrade/SumOfCredit;
                this->OverallCreditExpectPubEle=SumOfCreditExpectPubEle;
                this->OverallGradeExpectPubEle=SumOfGradeExpectPubEle/SumOfCreditExpectPubEle;
                this->TermsChanged=false;
            }
        }
            
};
 class Storage{
    private:
        Student Students[MAX_STUDENTS_NUM];
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
            if(n>MAX_STUDENTS_NUM)
                throwError(ACCESS_VIOLATION,"Read Students",argv);
            return Students[n];
        }
        const Student& operator [](int n)
        {
            char argv[MAX_COMMAND_CHAR];
            sprintf(argv,"%d",n);
            if(n>MAX_STUDENTS_NUM)
                throwError(ACCESS_VIOLATION,"Read Students",argv);
            return Students[n];
        }
        Student* getStudentHandle(int n)
        {
            char argv[MAX_COMMAND_CHAR];
            sprintf(argv,"%d",n);
            if(n>MAX_STUDENTS_NUM)
                throwError(ACCESS_VIOLATION,"Write Students",argv);
            return &Students[n];
        }
        int Add()
        {
            string Input;
            cout <<"Input School ID"<<endl;
            cin>>Input;
            int result=vaildStudentId(Input.c_str());
            if(!result||result==INVAILD_SELECTION){
                throwError(INVAILD_INPUT,"add student",Input.c_str());
                }
            cout <<"Input Name"<<endl;
            cin>>Input;
            this->getStudentHandle(getTotalStudentNumberRefer())->setName(Input);
            this->getStudentHandle(getTotalStudentNumberRefer())->setStudentId(result);
            getTotalStudentNumberRefer()++;
			return 0;
        }

};

extern Selection CurrentSelect;
extern string Path;
extern string FileNamePath;
extern string StudentListFilePath;
