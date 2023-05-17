#include<iostream>
using namespace std;
#include<fstream>
#include<string>
int main(){
    string line;
    ifstream ini_file("D:\\TRayCer\\t1.txt");
    //ofstream out_file("D:\\TRayCer\\t9.txt");
    while(getline(ini_file,line)){
       cout<<line<<"\n";
    }
    ini_file.close();


    ifstream ini_file2("D:\\TRayCer\\t2.txt");
    int count = 0;
    while(getline(ini_file2, line)){
        if(count <=2){
            count++;}
        else cout<<line<<"\n";
    }
    ini_file2.close();


    ifstream ini_file3("D:\\TRayCer\\t3.txt");
    count = 0;
    while(getline(ini_file3, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file3.close();


    ifstream ini_file4("D:\\TRayCer\\t4.txt");
    count = 0;
    while(getline(ini_file4, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file4.close();


    ifstream ini_file5("D:\\TRayCer\\t5.txt");
    count = 0;
    while(getline(ini_file5, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file5.close();


    ifstream ini_file6("D:\\TRayCer\\t6.txt");
    count = 0;
    while(getline(ini_file6, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file6.close();


    ifstream ini_file7("D:\\TRayCer\\t7.txt");
    count = 0;
    while(getline(ini_file7, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file7.close();


    ifstream ini_file8("D:\\TRayCer\\t8.txt");
    count = 0;
    while(getline(ini_file8, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file8.close();
    
}