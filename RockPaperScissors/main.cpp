#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;
enum Compnents {Siccors = 1, Rock = 2, Paper = 3};
struct stGameResults
{
    int Rounds=0,ComWins=0,UserWins=0,Tie=0;
    bool Reset;
};

int RandomNumber(int from, int to){
    int Number;
    Number = rand() % (to - from + 1 ) + from;
    return Number;
}
int ReadRounds(){
    int Rounds;
    do{
        cout << "How Many Rounds You want to play 1-10" << endl;
        cin >> Rounds;
    }while(Rounds < 1 || Rounds > 10);
    return Rounds;
}
Compnents ReadUserInput(){
    Compnents choice;
    int Cho;
    do{
        cout << "Choose : [1]Scissors [2]Rock [3]Paper ";
        cin >> Cho;
    }while(Cho < 1 || Cho > 3);
    choice = (Compnents)Cho;
    return choice;
}
Compnents ReadComputerChoice(){
    return (Compnents)RandomNumber(1,3);
}
string DecideWhoWinner(Compnents Computer, Compnents User){
    if(Computer == User){
        return "Tie";
    }else if(Computer == Compnents::Paper && User == Compnents::Rock){
        return "Computer";
    }else if(Computer == Compnents::Rock && User == Compnents::Siccors){
        return "Computer";
    }else if(Computer == Compnents::Siccors && User == Compnents::Paper){
        return "Computer";
    }else if(User == Compnents::Paper && Computer == Compnents::Rock){
        return "User";
    }else if(User == Compnents::Rock && Computer == Compnents::Siccors){
        return "User";
    }else if(User == Compnents::Siccors && Computer == Compnents::Paper){
        return "User";
    }
    return " ";
}
string CheckComputer(Compnents Choice){
    switch(Choice){
        case Compnents::Rock:
            return "Rock";
            break;
        case Compnents::Paper:
            return "Paper";
            break;
        case Compnents::Siccors:
            return "Scissors";
            break;
    }
}
void PrintChoices(Compnents User,Compnents Computer){
    cout << "You Picked " << CheckComputer(User) << endl;
    cout << "The Computer Picked " << CheckComputer(Computer) << endl;
}
void PlayRounds(int Rounds, int &Comwins,int &UserWins,int& Tie){
    for(int i = 0; i < Rounds;i++){
        Compnents Computer = ReadComputerChoice(),User = ReadUserInput();
        string Winner = DecideWhoWinner(Computer,User);
        cout << "-------------Round " << i << " ------------------" << endl;
        PrintChoices(User,Computer);
        cout << "The Winner is: " << Winner << endl;
        cout << "---------------------------------------" << endl;
        if(Winner == "Computer"){
            Comwins +=1;
            continue;
        }else if(Winner == "User"){
            UserWins +=1;
            continue;
        }else{
            Tie += 1;
            continue;
        }
    }
}
string CheckWinner(int Comwins,int Userwins){
    if(Comwins == Userwins){
        return "Tie";
    }else if(Comwins > Userwins){
        return "Computer";
    }else{
        return "User";
    }
}
void ResetGame(bool &Reset){
    cout << "\t \t Do You Want To Play Again: [0]No,[1]Yes"<< endl; cin >> Reset;
}
void GameOver(int Comwins,int Userwins, int Tie,int Rounds,bool &Reset){
    cout << "\t\tGame Rounds: " << Rounds << endl;
    cout << "\t\tComputer Win Rounds: " << Comwins << endl;
    cout << "\t\tUser Win Rounds: " << Userwins << endl;
    cout << "\t\tTie Counter: " << Tie << endl;
    cout << "\t\t The Winner of the Game is: " << CheckWinner(Comwins,Userwins) << endl;
    Reset = false;
    ResetGame(Reset);
}

void StartGame(bool& Reset){
    int Rounds,Comwins=0,UserWins=0,Tie=0;
    stGameResults GameRs;
    Reset = true;
    cout << "Enter How Many Rounds Do You Want ? 1-10" << endl;
    cin >> Rounds;
    PlayRounds(Rounds,Comwins,UserWins,Tie);
    GameOver(Comwins,UserWins,Tie,Rounds,Reset);
}
int main(){
    bool Reset;
    do{
        StartGame(Reset);
    }while(Reset == true);
    return 0;
}