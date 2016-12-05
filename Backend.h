#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;
#define MAX_COMMAND 256
#define MAX_COMMAND_CHAR 256
#define MAX_STUDENTS 256
#define INVAILD_INPUT 0x01
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
#define MAX_LESSON_OF_TERM 128
#define MAX_TERM_OF_STUDENT 32
#define DURATION_OF_LESSON 45
char* strcpy_s(char *dest,size_t destsz, const char *src);
int select(int argc, char *argv[]);
int add(int argc, char *argv[]);
int del(int argc, char *argv[]);
int find(int argc, char *argv[]);
int sort(int argc, char *argv[]);
int promote();
int vaildStudentId(char InputStudentId[]);
int vaildTerm(char InputTerm[]);
int vaildYear(char InputYear[]);
int MY_Find(const string Method, const string Content);
int MY_strcmp(const char *Command, const char *Input, bool EnableShort=true);
extern string Weekdays[7];
extern string Lesson_Type[4];
typedef struct Error_Struct{
    int ErrorLevel;
    char ErrorArgv[256];
    string ErrorProcedure;
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
    string Name;
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
        Lesson Lessons[MAX_LESSON_OF_TERM];
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
        bool TermsChanged;
        Term Terms[MAX_TERM_OF_STUDENT];
        Student(){
            Name="N/S";
            StudentId=-1;
            EntranceYear=1924;
            OverallGrade=-1;
            OverallCredit=0;
            TermsChanged=false;
            NumberOfTerm=0;
        }
        void reNew()
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
extern Selection CurrentSelect;

