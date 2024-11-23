#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> insertingBullets(vector<int> &occupied, int n);
int gameLogic(vector<int> &occupied, string p1, string p2, int &lives1, int &lives2, int bullets);
void lives(int lives1, int lives2, string p1, string p2, string player)
{
    int maxLives = (player == p1) ? lives1 : lives2;
    for (int i = 0; i < 3; i++)
    {
        if (i < maxLives)
        {
            cout << "♥ ";
        }
        else
        {
            cout << "♡ ";
        }
    }
}

int gameLogic(vector<int> &occupied, string p1, string p2, int &lives1, int &lives2, int bullets)
{
    string player = p1;
    int i = 0, decision, n;
switchCon:
    if (i == 6)
    {
        cout << "All the chambers have been used.\nReshuffling";
        Sleep(1000);
        cout << ".";
        Sleep(1000);
        cout << ".";
        Sleep(1000);
        cout << "." << endl;
        cout << "Next Round: ";
        insertingBullets(occupied, bullets);
        i = 0;
    }
    cout << player;
    cout << " ( ";
    lives(lives1, lives2, p1, p2, player);
    cout << ")" << endl;
    cout << "1. Shoot Opponent\n2. Shoot Yourself\nMake your Decision: ";
    cin >> decision;
    switch (decision)
    {
    case 1:
        if (i % 2 == 0)
            player = p2;
        if (i % 2 != 0)
            player = p1;
        Sleep(1000);
        cout << ".";
        Sleep(1000);
        cout << ".";
        Sleep(1000);
        cout << "." << endl;
        if (occupied[i] == 1)
        {
            cout << "Bang! " << player << " died..." << endl;
            if (player == p1)
                lives1--;
            if (player == p2)
                lives2--;
            i++;
        }
        else
        {
            cout << player << " survived" << endl;
            i++;
        }
        if (lives1 != 0 && lives2 != 0)
        {
            if (i == 6)
                goto switchCon;
            cout << "Handing gun to " << player << endl;
        }
        else
        {
            player = (player == p1) ? p2 : p1;
            cout << player << " Won!";
            return 0;
        }
        while (lives1 != 0 && lives2 != 0)
        {
            goto switchCon;
        }
        break;
    case 2:
        Sleep(1000);
        cout << ".";
        Sleep(1000);
        cout << ".";
        Sleep(1000);
        cout << "." << endl;
        if (occupied[i] == 1)
        {
            cout << "Bang! " << player << " Shot himself and died..." << endl;
            if (player == p1)
                lives1--;
            if (player == p2)
                lives2--;
            i++;
        }
        else
        {
            cout << player << " Shot himself and survived" << endl;
            i++;
        }
        if (i % 2 == 0)
        {
            player = p1;
        }
        else
        {
            player = p2;
        }
        if (lives1 != 0 && lives2 != 0)
        {
            if (i == 6)
                goto switchCon;
            cout << "Handing gun to " << player << endl;
        }
        else
        {
            cout << player << " Won!";
            return 0;
        }
        while (lives1 != 0 && lives2 != 0)
        {
            goto switchCon;
        }
        break;
    }
}

vector<int> insertingBullets(vector<int> &occupied, int n)
{
    for (int i = 0; i < 6; i++)
    {
        if (i < n)
        {
            occupied[i] = 1;
        }
        else
        {
            occupied[i] = 0;
        }
    }
    random_shuffle(occupied.begin(), occupied.end());
    return occupied;
}

int main()
{
    int lives1 = 3, lives2 = 3;
    SetConsoleOutputCP(CP_UTF8);
    int n, Dicision;
    vector<int> occupied(6);
    string p1, p2;
    cout << "Enter player 1: " << endl;
    cin >> p1;
    cout << "Enter player 2: " << endl;
    cin >> p2;
again:
    cout << "Bullets count: ";
    cin >> n;
    if (n > 6 || n < 1)
    {
        cout << "Please choose between 1 and 6\n";
        goto again;
    }
    insertingBullets(occupied, n);
    gameLogic(occupied, p1, p2, lives1, lives2, n);
}
