#include<iostream>
using namespace std;
#include<thread>
#include<fstream>
void run(int c, string path){
    ofstream f(path,std::ofstream::out);
    for(int i=0;i<=c;i++){
        f <<"The answer is "<<i<<"\n";
    }
    f.close();
}
int main(){
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
}