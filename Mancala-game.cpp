#include <iostream>

using namespace std;
int arr[14] = {4,4,4,4,4,4,0,0,4,4,4,4,4,4};
int player[2] = {0,1};

void print(){
    cout<<"  ";
    for(int i = 0; i < 6; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<arr[6];
    for(int i = 0; i < 13 ;i++){
        cout<<" ";
    }
    cout<<arr[7];
    cout<<endl;
    cout<<"  ";
    for(int i = 8; i < 14; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int next_step(int idx, bool upper)
{
    if (1 <= idx && idx <=5)
        return idx - 1;
    if (8 <= idx && idx <=12)
        return idx + 1;
    if (idx == 0)
        return upper ? 6 : 8;
    if (idx == 13)
        return upper ? 5 : 7;
    if (idx == 6)
        return 8;
    if (idx == 7)
        return 5;

}

int move (int idx)
{
    int curr ;
    bool upper; //true = up , false = down
    if (0 <= idx && idx <=5)
        upper = true;
    else if (8 <= idx && idx <=13)
        upper = false;
    curr = next_step(idx, upper);
    for (int i =0 ; i< arr[idx];i++)
    {
        arr[curr] += 1;
        if(i < arr[idx] - 1)
            curr = next_step(curr, upper);

    }
    arr[idx] = 0;
    return curr;

}

bool check_end()
{
    if (arr[0] == 0 && arr[1] == 0 && arr[2] == 0 && arr[3] == 0 && arr[4] == 0 && arr[5] == 0 )
        return true ;


    if (arr[8] == 0 && arr[9] == 0 && arr[10] == 0 && arr[11] == 0 && arr[12] == 0 && arr[13] == 0 )
        return true ;

    return false ;
}



string check_winner()
{
    if( arr[6] > arr [7] )
        return "player 2 is the winner" ;
    if( arr[6] < arr [7] )
        return "player 1 is the winner" ;
    if( arr[6] == arr [7] )
        return "its a draw" ;


}

bool check_input(int player, int i){
    bool wrong = false;
    if(i == 6 || i == 7 || i < 0 || i > 13 || arr[i] == 0)
        wrong = true;
    else if(player == 0 && i > 5)
        wrong = true;
    else if(player == 1 && i < 8)
        wrong = true;
    if(wrong){
        cout<<"Invalid input"<<endl;
        return false;
    }
    return true;

}

void take_input(int &i,int player){
    cin>>i;
    while(!check_input(player,i)){
        take_input(i,player);
    }
}

void check_last(int index,int player){
    if(player == 0 && arr[index] == 1 && index <= 5 && arr[index+8] != 0){
            arr[6] += (1+ arr[index+8]);
            arr[index] = 0;
            arr[index+8]= 0;
    }
    else if(player == 1 && arr[index] == 1 && index >= 8 && arr[index-8] != 0){
            arr[7] += (1+ arr[index-8]);
            arr[index] = 0;
            arr[index-8] = 0;
    }
}

void play(){
    int player = 1;
    int i;
    print();
    while(true){
        cout<<"player "<<player<<" Enter the index: "<<endl;
        take_input(i,player);
        int k = move(i);
        cout<<k<<endl;
        check_last(k,player);
        print();
        if(check_end()){
            cout<<check_winner();
            break;
        }
        if(player == 0 && k == 6 || player == 1 && k == 7)
            continue;
        player = 1 - player;
    }
}



int main()
{
    play();
}
