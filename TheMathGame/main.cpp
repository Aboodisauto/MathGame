#include <iostream>
#include <math.h>
#include <cstdlib>
enum enDifficulty {Easy = 1,Normal = 2,Hard = 3,Mix = 4};
enum enOPType{Add=1,Minus=2,Multipluy=3,Divide=4,Mixs=5};
using namespace std;
struct stRounds{
    int Answer=0,RightAnswer=0,Number1=0,Number2=0;
};
struct stGameStats{
    int RightAnswers=0,WrongAnswers=0,NumberOfQuestions=0;
    enDifficulty Difficult;
    enOPType OperationType;

};
int RandomNumber(int From, int To){
    int Number;
    Number = rand() % (To - From + 1 ) + From;
    return Number;
}
int ReadNumberOfQuestions(stGameStats Rounds){
    do{
    cout << "How Many Question Do You Want ? " << endl;
    cin >> Rounds.NumberOfQuestions;
    }while(Rounds.NumberOfQuestions < 0);
    return Rounds.NumberOfQuestions;
}
enDifficulty ChooseDifficulty(stGameStats Stats){
    int Diffi;
    do{
        cout << "Choose Your Difficulty: [1]Easy [2]Normal [3]Hard [4]Mix :" << endl;
        cin >> Diffi;
        Stats.Difficult = (enDifficulty)Diffi;
    }while(Diffi < 1 || Diffi > 4);
    return  Stats.Difficult;
}
enOPType ChooseOperation(stGameStats Stats){
    int Op;
    do{
        cout << "Enter Your Operation Type: [1]Add,[2]Minus,[3]Mul,[4]Div,[5]Mix" << endl;
        cin >> Op;
        Stats.OperationType = (enOPType)Op;
    }while(Op > 5 || Op < 0);
    return Stats.OperationType;
}
void IfMix(stRounds& Round,int Mix){
    if(Mix == 1){
        Round.Number1 = RandomNumber(1,10);
        Round.Number2 = RandomNumber(1,10);
        
    }else if(Mix == 2){
        Round.Number1 = RandomNumber(10,20);
        Round.Number2 = RandomNumber(10,20);
        
    }else if(Mix == 3){
        Round.Number1 = RandomNumber(20,80);
        Round.Number2 = RandomNumber(20,80);
        
    }
}
void GenerateQuestion(stRounds &Rounds,stGameStats Stats){
    switch(Stats.Difficult){
        case enDifficulty::Easy:
            Rounds.Number1 = RandomNumber(1,10);
            Rounds.Number2 = RandomNumber(1,10);
            break;
        case enDifficulty::Normal:
            Rounds.Number1 = RandomNumber(10,20);
            Rounds.Number2 = RandomNumber(10,20);
            break;
        case enDifficulty::Hard:
            Rounds.Number1 = RandomNumber(20,80);
            Rounds.Number2 = RandomNumber(20,80);
            break;
        case enDifficulty::Mix:
            int Mix = RandomNumber(1,3);
            IfMix(Rounds,Mix);
            break;
    }

}
int GetAnswerUser(){
    int Number;
    cin >> Number;
    return Number;
}
char IfMixs(int Number){
    switch(Number){
        case 1:
            return '+';
        case 2:
            return '-';
        case 3:
            return '*';
        case 4:
            return '/';
    }
}
char CheckOperation(stGameStats Stats){
    switch(Stats.OperationType){
        case enOPType::Add:
            return '+';
        case enOPType::Minus:
            return '-';
        case enOPType::Multipluy:
            return '*';
        case enOPType::Divide:
            return '/';
        case enOPType::Mixs:
            int Mixs = RandomNumber(1,4);
            return IfMixs(Mixs);
    }
}
int GetRightAnswer(stGameStats Stats, stRounds Round,char &Operation2){
    int Number1= Round.Number1;
    int Number2= Round.Number2;
    Operation2 = CheckOperation(Stats);
    switch(Operation2){
        case '+':
            return Number1 + Number2;
        case '-':
            return Number1 - Number2;
        case '*':
            return Number1 * Number2;
        case '/':
            return Number1 / Number2;
    }
}
bool CheckUserAnswer(stRounds Round,stGameStats& Stats){
    if(Round.Answer == Round.RightAnswer){
        Stats.RightAnswers++;
        return true;
    }else{
        Stats.WrongAnswers++;
        return false;
    }
}
void PrintQuestion(int Number, stRounds round, stGameStats Stats,char Operation){
    cout << "------------ Question " << Number << "-----------------" << endl;
    cout << round.Number1 << endl << Operation << round.Number2 << endl;
    cout << "--------------------------------------------------------"  << endl;
}
string PassorFail(bool Pass){
    if(Pass == true){
        return "Pass";
    }else{
        return "Fail";
    }
}
string GetDifficulty(stGameStats Stats){
    switch(Stats.Difficult){
        case enDifficulty::Easy:
            return "Easy";
        case enDifficulty::Normal:
            return "Normal";
        case enDifficulty::Hard:
            return "Hard";
        case enDifficulty::Mix:
            return "Mix";
    }
}
string GetOperation(stGameStats Stats){
    switch(Stats.OperationType){
        case enOPType::Add:
            return "Add";
        case enOPType::Divide:
            return "Divide";
        case enOPType::Minus:
            return "Minus";
        case enOPType::Multipluy:
            return "MultiPluy";
        case enOPType::Mixs:
            return "Mix";
    }
}
void PassorFailQuestion(bool Pass,stRounds Round){
    cout << "-----------------" << PassorFail(Pass) << "------------" << endl;
    cout << "The Right Answer: " << Round.RightAnswer << endl;
    cout << "Your Answer is: " << Round.Answer << endl;
    cout << "-------------------------------------------------------" << endl << endl << endl << endl;
}
string CheckWinorLoss(stGameStats Stats){
    if(Stats.RightAnswers > Stats.WrongAnswers){
        return "Passed";
    }else{
        return "Failed";
    }
}
void GameOverScreen(stGameStats Stats){
    cout << "----------------------- " << CheckWinorLoss(Stats) << "------------------" << endl;
    cout << "The amount of right answers you got: " << Stats.RightAnswers << endl;
    cout << "The amount of wrong answers you got: " << Stats.WrongAnswers << endl;
    cout << "The Difficulty Was on: " << GetDifficulty(Stats) << endl;
    cout << "The Operation Type You was using " << GetOperation(Stats) << endl;
    cout << "----------------------------------------------" << endl;
}
void AskTheQuestions(stRounds Round,stGameStats &Stats){
    
    for(int i = 1; i <= Stats.NumberOfQuestions ; i++){
        GenerateQuestion(Round,Stats);
        
        
        char Operation = ' ';
        Round.RightAnswer = GetRightAnswer(Stats,Round,Operation);
        
        PrintQuestion(i,Round,Stats,Operation);
        Round.Answer = GetAnswerUser();
        bool CheckAnswer = CheckUserAnswer(Round,Stats);
        PassorFailQuestion(CheckAnswer,Round);
    }
    GameOverScreen(Stats);
}
char PlayAgain(){
    char YesorNo;
    cout << "Do You want to play again? [Y]or[N]" << endl;
    cin >> YesorNo;
    return YesorNo;
}
void StartTheGame(){
    stRounds Round;
    stGameStats Stats;
    char PlayAgai = 'Y';
    do{
        Stats.NumberOfQuestions = ReadNumberOfQuestions(Stats);
        Stats.Difficult = ChooseDifficulty(Stats);
        Stats.OperationType = ChooseOperation(Stats);
        AskTheQuestions(Round,Stats);
        PlayAgai = PlayAgain();
    }while(PlayAgai == 'Y' || PlayAgai == 'y');
}
int main(){
    srand((unsigned)time(NULL));
    StartTheGame();
    return 0;
}