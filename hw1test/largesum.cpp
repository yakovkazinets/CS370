/*******************************************************************************
 * Name        : largesum.cpp
 * Author      : Jayson Infante, Yakov Kazinets, Abderahim Salhi
 * Date        : 2/7/21
 * Description : Solving Project Euler Problem 13.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

/*
Returns a reversed string representing the total sum excluding any trailing zeroes.
*/
string remove_trailing_and_reverse_number(string num)
{
  string temp="";
  int i=num.length()-1;
  int trailing_zero=0;
  while(i>=0) {
    //This is the first occurrence of a non-zero integer, marking where we will begin
    //to build our final answer. Otherwise, we will repeatedly skip over any trailing 0's
    if (trailing_zero==0 && num[i]!='0'){
      trailing_zero=1;
    }

    if (trailing_zero==1) {
      temp+=num[i];
    }
    i--;
  }
  
  return temp;
}

/*
Returns a string representing the total sum but in reversed form.
*/
string large_sum(string num1, string num2) 
{ 
    int len1 = num1.length(), len2 = num2.length(), temp; 
    int c = 0, i;
    string result = ""; 

    //Store shorter number in num1
    if (len1>len2) {
      string temp_str=num1;
      num1=num2;
      num2=temp_str;

      temp=len1;
      len1=len2;
      len2=temp;
    } 
    
    i=len1-1;

    //Calculate the total sum up to the length of the shorter number
    //E.g. num1 = 99, num2 = 1001, we calculate the sum up to the 10's place
    while(i>=0) { 
        temp = c + (num1[i]-'0') + (num2[i+(len2 - len1)]-'0') ; 
        result+=(temp%10 + '0'); 
        c = temp/10; 
        --i;
    } 
  
    i=len2-len1-1;

    //Calculate the total sum up to the length of the longer number
    //E.g. num1 = 99, num2 = 1001, we calculate the sum up to the 1000's place
    while(i>=0) { 
        temp = c+(num2[i]-'0'); 
        result+=(temp%10 + '0'); 
        c = temp/10; 
        --i;
    } 
  
    //If you had equal length numbers, say 500 and 500, this accounts for a carryover
    //in the 0th index of num1 and num2
    if (c>0) {
      result+=(c+'0'); 
    }    

    //Remove any excess 0's and reverse the string to get the total sum
    return remove_trailing_and_reverse_number(result); 
}

int main(){
  string line,full_sum="0",first_10_digits="";
  ifstream ifile("input.txt");

  //While lines in the input file exist, call the large_sum function to aggregate the total sum.
  while(ifile>>line)
  {
    full_sum=large_sum(full_sum,line);
  }

  //Don't forget to close the file you are reading from!
  ifile.close();
 
  //Parsing through the string if it happens to have a length greater than 10, otherwise return 
  //the entire digit.
  for (int i = 0; i < full_sum.length() && i<10; ++i)
  {
    first_10_digits+=full_sum[i];
  }

  cout<<"Full sum: "<<full_sum<<endl;
  cout<<"First 10 digits: "<<first_10_digits<<endl;

  return 0;
}
