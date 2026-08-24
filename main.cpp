#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>

using namespace std;

string Choices[3] = {"Stone", "Paper", "Scissors"};

struct stStatistic 
{
    int TotalGameRounds;
    string PlayerChoice;
    string ComputerChoice;
    string Winner;
    int PlayersWinCount = 0, ComputerWinCount = 0, DrawCount = 0;
};

int RandomNumber(int From, int To)
{
    int RandomNum = rand() % (To - From + 1) + From;
    return RandomNum;
}

int UserChoice(string Message, int From, int To)
{
    int R;

    do
    {
        cout << Message << endl;
        cout << "=> ";
        cin >> R;
    } while (R < From || R > To);

    return R;
}

stStatistic AssignChoices(stStatistic& Statistic, int PlayerChoice, int ComputerChoice)
{
    Statistic.PlayerChoice = Choices[PlayerChoice - 1];
    Statistic.ComputerChoice = Choices[ComputerChoice];

    return Statistic;
}

void UpdateScore(stStatistic& Statistic)
{
    if (Statistic.Winner == "Player")
    {
        Statistic.PlayersWinCount++;
    }
    else if (Statistic.Winner == "Computer")
    {
        Statistic.ComputerWinCount++;
    }
    else if (Statistic.Winner == "[No Winner]")
    {
        Statistic.DrawCount++;
    }
}

void ScreenEffects(string Winner)
{
    if (Winner == "Player")
    {
        system("color 27");
    }
    else if (Winner == "Computer")
    {
        system("color 47");
        cout << "\a";
    }
    else if (Winner == "[No Winner]")
    {
        system("color 07");
    }
} 

string DecideWinnerOf(string Type, stStatistic& Statistic)
{
    if (Type == "Round")
    {
        if (Statistic.PlayerChoice == Statistic.ComputerChoice)
        {
            Statistic.Winner = "[No Winner]";
        }

        else if (Statistic.PlayerChoice == "Stone")
        {
            if (Statistic.ComputerChoice == "Paper") Statistic.Winner = "Computer";
            else if (Statistic.ComputerChoice == "Scissors") Statistic.Winner = "Player";
        }

        else if (Statistic.PlayerChoice == "Paper")
        {
            if (Statistic.ComputerChoice == "Stone") Statistic.Winner = "Player";
            else if (Statistic.ComputerChoice == "Scissors") Statistic.Winner = "Computer";
        }

        else if (Statistic.PlayerChoice == "Scissors")
        {
            if (Statistic.ComputerChoice == "Stone") Statistic.Winner = "Computer";
            else if (Statistic.ComputerChoice == "Paper") Statistic.Winner = "Player";
        }

        return Statistic.Winner;
    }
    else if (Type == "Game")
    {
        int PlayerWins = Statistic.PlayersWinCount;
        int ComputerWins = Statistic.ComputerWinCount;

        if (PlayerWins > ComputerWins) return "Player";
        else if (PlayerWins < ComputerWins) return "Computer";
        else return "[No Winner]";
    }
    else return "Please the type should be only round or game";
}

void DisplayEndOfRoundStatistics(int CurrentRound, stStatistic Statistics)
{
    // change screen effect depends on the winner
    ScreenEffects(Statistics.Winner);

    cout << "---------------Round [" << CurrentRound << "]---------------" << endl;
    cout << endl;
    cout << "Player choice  : " << Statistics.PlayerChoice << endl;
    cout << endl;
    cout << "Computer Choice: " << Statistics.ComputerChoice << endl;
    cout << endl;
    cout << "Round winner is: " << Statistics.Winner << endl;
    cout << endl;
    cout << "--------------------------------------" << endl;
}

void PlayRound(int RoundNum, stStatistic& Statistics)
{
    cout << "Round " << RoundNum << " Begins:" << endl;

    // Read playes choice and asign random computer choice
    int PlayerChoice = UserChoice("Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?", 1, 3);
    int ComputerChoice = RandomNumber(0, 2);
    AssignChoices(Statistics, PlayerChoice, ComputerChoice);
    system("cls");

    // Decide round winner
    DecideWinnerOf("Round", Statistics);

    // update score 
    UpdateScore(Statistics);

    // display round stats
    DisplayEndOfRoundStatistics(RoundNum, Statistics);
}

void CustomMessage(string Msg, int TimeToRead)
{
    cout << "\n---------------" << endl;
    cout << Msg << endl;
    cout << "---------------" << endl;
    Sleep(TimeToRead);
}

void DisplayEndOfGameStatisics(stStatistic Statistics)
{
    string Winner = DecideWinnerOf("Game", Statistics);
    ScreenEffects(Winner);

    cout << "                --------------------------------------" << endl;
    cout << endl;
    cout << "                       +++ G a m e   O v e r +++" << endl;
    cout << endl;
    cout << "                --------------------------------------" << endl;
    cout << endl;
    cout << "                ------------[Game Results]------------" << endl;
    cout << endl;
    cout << "                Total Game Rounds    : " << Statistics.TotalGameRounds << endl;
    cout << "                Player 1 Total Wins  : " << Statistics.PlayersWinCount << endl;
    cout << "                Computer Total Wins  : " << Statistics.ComputerWinCount << endl;
    cout << "                Total Draws          : " << Statistics.DrawCount << endl;
    cout << "                Final Winner is      : " << Winner << endl;
    cout << endl;
    cout << "                --------------------------------------" << endl;
    cout << endl;
}

void ResetScore(stStatistic& Statistics)
{
    Statistics.TotalGameRounds = 0;
    Statistics.ComputerWinCount = 0;
    Statistics.PlayersWinCount = 0;
    Statistics.DrawCount = 0;
}

void GameStart()
{
    int Choice = 0;
    stStatistic Statistics;

    do
    {
        // Always resets the color to black
        system("color 07");
        system("cls");

        // Read How many round to play 
        Statistics.TotalGameRounds = UserChoice("How many rounds do you want to play ? (from 1 to 10) ", 1, 10);
        system("cls");

        // Game loop
        for (int i = 1; i <= Statistics.TotalGameRounds; i++)
        {
            // Each round from 1 to N
            PlayRound(i, Statistics);

            // Show a costume message, with a time limit to read in (ms)
            CustomMessage("Please wait ...", 4000);
            system("cls");
        }

        // Display end of game stats (total scores and game winner)
        DisplayEndOfGameStatisics(Statistics);

        // reset scores to 0
        ResetScore(Statistics);

        // ask the player if he wants to play again
        Choice = UserChoice("Do you want to play again [1]: Yes, [2]: No: ", 1, 2);
    } while (Choice == 1);
}

int main()
{
    srand((unsigned)time(NULL));

    GameStart();
}