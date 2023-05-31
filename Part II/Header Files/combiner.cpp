#include<iostream>
using namespace std;
#include<fstream>
#include<string>
int main(){
    string line;
    ifstream ini_file("t1.txt");
    //ofstream out_file("D:\\TRayCer\\t9.txt");
    while(getline(ini_file,line)){
       cout<<line<<"\n";
    }
    ini_file.close();
     remove("t1.txt");


    ifstream ini_file2("t2.txt");
    int count = 0;
    while(getline(ini_file2, line)){
        if(count <=2){
            count++;}
        else cout<<line<<"\n";
    }
    ini_file2.close();
     remove("t2.txt");


    ifstream ini_file3("t3.txt");
    count = 0;
    while(getline(ini_file3, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file3.close();
     remove("t3.txt");


    ifstream ini_file4("t4.txt");
    count = 0;
    while(getline(ini_file4, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file4.close();
     remove("t4.txt");


    ifstream ini_file5("t5.txt");
    count = 0;
    while(getline(ini_file5, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file5.close();
     remove("t5.txt");


    ifstream ini_file6("t6.txt");
    count = 0;
    while(getline(ini_file6, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file6.close();
     remove("t6.txt");


    ifstream ini_file7("t7.txt");
    count = 0;
    while(getline(ini_file7, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file7.close();
     remove("t7.txt");


    ifstream ini_file8("t8.txt");
    count = 0;
    while(getline(ini_file8, line)){
        if(count <=2) {
            count++;}
        else cout<<line<<"\n";
    }
    ini_file8.close();
     remove("t8.txt");
    
}