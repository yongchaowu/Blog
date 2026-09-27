# ofstream_txt


#include <fstream>

string temp;
temp = "D://mess//"+m_stripaddr + ".txt";
ofstream outfile(temp.c_str(),std::ios::app|std::ios::out); 
CString strTime;

SYSTEMTIME st;
GetLocalTime(&st);
strTime.Format(_T(" %d-%02d-%02d %02d:%02d:%02d.%03d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);

outfile<<m_stripaddr<<"-"<<GetCurrentThreadId()<<"-"<<"TryConnect"<<"-"<<"errorNum"<<m_ierrNum<<strTime.GetBuffer()<<endl;
outfile.close();
strTime.ReleaseBuffer();
