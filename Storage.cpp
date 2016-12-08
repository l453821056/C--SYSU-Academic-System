#include "Storage.h"
int& Storage::getTotalStudentNumberRefer()
{
    return TotalStudentNumber;
}
Storage::Storage()
{
    getTotalStudentNumberRefer()=0;
}
const Student& Storage::getStudent(int n)
{
    char argv[MAX_COMMAND_CHAR];
    sprintf(argv,"%d",n);
    if(n>getTotalStudentNumberRefer())
        throwError(ACCESS_VIOLATION,"Read Students",argv);
    return Students[n];
}
const Student& Storage::operator [](int n)
{
    char argv[MAX_COMMAND_CHAR];
    sprintf(argv,"%d",n);
    if(n>getTotalStudentNumberRefer())
        throwError(ACCESS_VIOLATION,"Read Students",argv);
    return Students[n];
}
Student* Storage::getStudentHandle(int n)
{
    char argv[MAX_COMMAND_CHAR];
    sprintf(argv,"%d",n);
	if(n>getTotalStudentNumberRefer())
        throwError(ACCESS_VIOLATION,"Read Students",argv);
    return &Students[n];
}
Student* Storage::newStudentHandle(int n)
{
	char argv[MAX_COMMAND_CHAR];
	sprintf(argv, "%d", n);
	if (n == getTotalStudentNumberRefer()) {
		if (n == MAX_STUDENTS_NUM)
			throwError(STORAGE_FULL, "Write Students", argv);
		Student temp;
		Students.push_back(temp);
	}
	else if (n>getTotalStudentNumberRefer())
		throwError(ACCESS_VIOLATION, "Write Students", argv);
	return &Students[n];
}
int Storage::Add()
{
    bool OK=false;
    if(getTotalStudentNumberRefer()==MAX_STUDENTS_NUM)
        throwError(STORAGE_FULL,"Add Student",string("You can not storage more student"));
    string Input;
	cout <<"请输入学号"<<endl;
    while(!OK){
		promote("Input Student ID");
	    cin>>Input;
	    int result=vaildStudentId(Input.c_str());
	    if(!result){
	        throwWarning(INVAILD_INPUT,"add student",Input.c_str(),"Illegal Student ID");
	        }
	    else{
	        this->newStudentHandle(getTotalStudentNumberRefer())->setStudentId(result);
	        OK=true;
	    }
    }
    OK=false;
    cout <<"请输入姓名"<<endl;
	promote("Input Student Name");
    cin>>Input;
    this->getStudentHandle(getTotalStudentNumberRefer())->setName(Input);
	cout <<"请输入学院"<<endl;
    while(!OK){
		promote("Input School Name");
        cin >>Input;
        if(Input.size()>MAX_LENGTH_OF_SCHOOL){
            throwWarning(INVAILD_INPUT,"Set School Name",Input.c_str(),"Please Input a Shorter School Name");
            continue;
        }
        else{
            OK=true;
            this->getStudentHandle(getTotalStudentNumberRefer())->setSchool(Input);
        }
    }
    OK=false;
    cout <<"请输入专业"<<endl;
    while(!OK){
		promote("Input Major Name");
        cin >>Input;
        if(Input.size()>MAX_LENGTH_OF_MAJOR){
            throwWarning(INVAILD_INPUT,"Set Major Name",Input.c_str(),"Please Input a Shorter Major Name");
            continue;
        }
        else{
            OK=true;
            this->getStudentHandle(getTotalStudentNumberRefer())->setMajor(Input);
        }
    }
    getTotalStudentNumberRefer()++;
}
int Storage::Find(int StudentId)
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
int Storage::print()
{
    cout <<CYAN<<"  序号"<<"  姓名    "<<"  学号    "<<"  学院                  "<<"  专业                "<<RESET<<endl;
//  cout <<CYAN<<"  256 "<<"  木子雨辰"<<"  15323032"<<"  政治与公共事务管理学院"<<"  图书情报与档案管理类"
          cout <<"  ----"<<"  --------"<<"  --------"<<"  ----------------------"<<"  --------------------"<<endl;
    for(int i=0;i<getTotalStudentNumberRefer();i++)
    {
        cout<<left<<setfill(' ')<< "  "<<setw(4)<<i+1<<setw(2)<<"  "<<setw(8)<<Students[i].getName()<< setw(4) << "    " << setw(8)<<Students[i].getStudentId()<< setw(2) << "  " << setw(22)<<Students[i].getSchool()<< setw(2) << "  " << setw(20)<<Students[i].getMajor()<<endl;
    }
    return 0;
}
