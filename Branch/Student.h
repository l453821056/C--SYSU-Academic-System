#ifndef STUDENT_H
#define STUDENT_H
#include "Term.h"
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
#endif