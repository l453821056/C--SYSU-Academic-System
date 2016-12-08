#ifndef TERM_H
#define TERM_H
#include "Lesson.h"
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
        int& getNumberOfLessonRefer()
        {
            return NumberOfLesson;
        }
        int Add()
        {
            if(NumberOfLesson==MAX_LESSON_OF_TERM)
                throwError(STORAGE_FULL,"Add Lesson",string("You CANNOT Storage More Lesson in This Term"));
            this->Lessons[getNumberOfLessonRefer()].init();
            getNumberOfLessonRefer()++;
        }
        int print()
        {
            return 0;
        }
};
#endif
