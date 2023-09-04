#include <iostream>
#include <vector>
using namespace std;
unsigned int factorial(unsigned int n)
{
    int fact=1;
    for(int i=2;i<=n;i++){
        fact*=i;
    }
    return fact;
}
int recurstion(vector<char> vec,int index){
    if(index==vec.size()){
        vector<int> nums;
        bool equal= false;
        for(char i : vec){
            if(i=='='){
                if(equal) nums.back()++;
                else{
                    equal= true;
                    nums.push_back(1);
                }
            }
            else{
                if(equal) equal= false;
            }
        }
        int options= factorial(vec.size()+1);
        for(int num : nums){
            options/= factorial(num+1);
        }
        return options;

    }
    vec[index]='=';
    int sum1= recurstion(vec,index+1);
    vec[index]='<';
    return sum1+ recurstion(vec,index+1);

}
int calc(int n){
    vector<char> vec(n-1);
    return recurstion(vec,0);
}
void nothing(){
    /*vector<int> answers(11);
    for(int i=0;i<answers.size();i++)
    {
        answers[i]= calc(i+1);
        cout<<answers[i]<<",";
    }*/
}
int main() {
    vector<int> final={1,3,13,75,541,4683,47293,545835,7087261,102247563,1622632573};
    int n;
    scanf("%d",&n);
    int index;
    for(int i=0;i<n;i++){
        scanf("%d",&index);
        cout<<final[index-1]<<endl;
    }
    return 0;
}


