#include <iostream>
#include <string>
using namespace std;
class Time{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
public:
    Time(){
        year=2016;
    }
    int get(string method){
        return this->move(method);
        }
}
int main()
{
    Time CurrentTime;
    int year=get(year);
    cout <<year<<endl;
}
