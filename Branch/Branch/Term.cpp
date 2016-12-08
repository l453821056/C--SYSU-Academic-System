#include "Term.h"
Term::Term(){
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
int Term::setYear(int Year)
{
    this->Year=Year;
    for(int i=1;i<=MAX_LESSON_OF_TERM;i++)
        Lessons[i].Year=Year;
    return 0;
}
int Term::setRank(int Rank)
{
    this->Rank=Rank;
    for(int i=1;i<=MAX_LESSON_OF_TERM;i++)
        Lessons[i].Term=Rank;
    return 0;
}
int Term::setTotalRank(int TotalRank)
{
    this->TotalRank=TotalRank;
    return 0;
}

void Term::reNew()
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
int Term::getCredit()
{
    reNew();
    return TotalCredit;
}
int Term::getCreditExpectPubEle()
{
    reNew();
    return TotalCreditExpectPubEle;
}
int Term::getAverage()
{
   reNew();
   return Average;
}
int Term::getAverageExpectPubEle()
{
   reNew();
   return AverageExpectPubEle;
}
int& Term::getNumberOfLessonRefer()
{
    return NumberOfLesson;
}
int Term::Add()
{
    if(NumberOfLesson==MAX_LESSON_OF_TERM)
        throwError(STORAGE_FULL,"Add Lesson",string("You CANNOT Storage More Lesson in This Term"));
    this->Lessons[getNumberOfLessonRefer()].init();
    getNumberOfLessonRefer()++;
}
int Term::print()
{
    return 0;
}
