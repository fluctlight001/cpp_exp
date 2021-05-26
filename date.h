#pragma once
 
class Date
{
public:
    Date(int year = 1900,int month = 1,int day = 1);
    ~Date(){}
    bool IsValid();
    int GetMonthDay(int year,int month);
    bool IsLeapYear(int year);
    void Show();
 
    Date& operator=(const Date& d);
    bool operator==(const Date& d);
    bool operator>=(const Date& d);
    bool operator<=(const Date& d);
    bool operator!=(const Date& d);
    bool operator>(const Date& d);
    bool operator<(const Date& d);
    Date operator+(int day);
    Date& operator+=(int day);
    Date operator-(int day);
    Date& operator-=(int day);
    int operator-(const Date& d);//日期-日期 返回天数
    Date& operator++();//默认前置
    Date operator++(int);//用参数标志后置++
    Date& operator--();
    Date operator--(int);
 
private:
    int _year;
    int _month;
    int _day;
};
