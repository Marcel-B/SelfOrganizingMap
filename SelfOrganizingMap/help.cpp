//
// Created by marce on 03.09.2017.
//
#include "help.h"
#include <string>

using namespace std;

// a = unterer Zielwert, b = oberer Zielwert
double com_b_velop::Help::ScaleValue(double x, double min, double max, double a, double b){
  if (max - min == 0)
    return a;
  return x == 0 ? a : a + (b - a) * (x - min) / (max - min);
}

tm* ParseTime(const string &in_time_string){
  time_t rawtime;
  string timestr = in_time_string;
  string tmp("");
  struct tm* timeinfo = new tm();
  int n = 0;
  int cnt = 0;
  // 13.04.1976 12:55
//    cout << "String: " << in_time_string << endl;
  for(unsigned long long i = 0; i < in_time_string.size(); ++i) {
    int val = static_cast<int>(in_time_string.at(i));
//        cout << in_time_string.at(i) << " = " << val << endl;
    if (val >= 48 && val <= 57) {
//            cout << "It is a number" << endl;
      ++n;
    }
    else{
      tmp = timestr.substr(0, n);
//            cout << "Result: " << tmp << endl;
      timestr = timestr.substr(++n);
      int number = stoi(tmp);
//            cout << "As Int: " << number << endl;
//            cout << "Rest  : " << timestr << endl;
      n = 0;
      switch(cnt){
        case 0:
//                    cout << "Write into timeinfo" << endl;
          timeinfo->tm_mday = number;
          break;
        case 1:
          timeinfo->tm_mon = number - 1;
          break;
        case 2:
          timeinfo->tm_year = number - 1900;
          break;
        case 3:
          timeinfo->tm_hour = number;
          break;
        case 4:
          timeinfo->tm_min = number;
          break;
        default:
          break;
      }
      cnt++;
    }
  }
//    cout << timestr << endl;
  int number = stoi(timestr);
  timeinfo->tm_min = number;
//    cout << "As Int: " << number << endl;
//    char buffer [80];
//    strftime (buffer,80 ,"Result is %c.",timeinfo);
//    cout << buffer << endl;
  return timeinfo;
}
