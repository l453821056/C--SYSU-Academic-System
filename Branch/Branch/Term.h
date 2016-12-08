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
        Term();
        int setYear(int Year);
        int setRank(int Rank);
        int setTotalRank(int TotalRank);
        void reNew();
        int getCredit();
        int getCreditExpectPubEle();
        int getAverage();
        int getAverageExpectPubEle();
        int& getNumberOfLessonRefer();
        int Add();
        int print();
};
#endif
