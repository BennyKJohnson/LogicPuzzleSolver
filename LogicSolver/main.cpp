//
//  main.cpp
//  LogicSolver
//
//  Created by Ben Johnson on 14/06/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//


#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>


using namespace std;

vector<int> people;
vector<int> combination;

struct statement {
    char  name;
    bool truth;
};
struct character {
    char name;
  vector<statement> statements;
};

template <typename Iter>
bool next(Iter begin, Iter end)
{
    if (begin == end)      // changed all digits
    {                      // so we are back to zero
        return false;      // that was the last number
    }
    --end;
    if ((*end & 1) == 0)   // even number is treated as zero
    {
        ++*end;            // increase to one
        return true;       // still more numbers to come
    }
    else                   // odd number is treated as one
    {
        --*end;            // decrease to zero
        return next(begin, end);   // RECURSE!
    }
}
int getIndexOfCharacterWithName(vector<character> characters, char name)
{
    for (int i =0; i < characters.size(); i++) {
        character currentCharacter = characters[i];
        if (currentCharacter.name == name) {
            return i;
        }
    }
    //Not found there is a problem
    return -1;
}
char evaluateStatement(statement currentStatment,string currentResult, vector<character> characters)
{
    int indexOfName = getIndexOfCharacterWithName(characters, currentStatment.name);
    
    if (currentStatment.truth && (currentResult[indexOfName] == '1')) {
        return '1';
    }
    else if((currentStatment.truth == false) && (currentResult[indexOfName] == '0'))
    {
    
        return '1';
    }
    else
        return '0';
}
void printCharacter(char character,int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << character;
    }
}
void breakLine()
{
    cout << endl << endl;
}
void printTitle(string title)
{
    int length = 50;
    printCharacter('-', length);
    
    cout << endl << endl;
    int offset = int((length - title.length()) / 2);
    printCharacter(' ', offset);
    cout << title;
    breakLine();
    printCharacter('-', length);
    breakLine();
}

int main(int argc, const char * argv[])
{

    printTitle("Welcome to Logic Solver");
    bool continueInput = true;
    int numberOfCharacts = 0;
    vector<character> characters;
    
    while (continueInput) {
        cout << "Enter a new character: ";
        string result;
        getline(cin, result);
        if (!result.empty()) {
            character newCharacter;
          //  cout << "Enter a new Character: ";
            newCharacter.name = result[0];
           // cout << endl;
            characters.push_back(newCharacter);
            
            numberOfCharacts++;
        }
        else
        {
            continueInput = false;
        }
    }
    for (int i = 0; i < numberOfCharacts; i++) {
        character currentCharacter = characters[i];
        bool continueStatements = true;
        int currentStatement = 0;
        while (continueStatements)
        {
            cout << "Enter Statement for " << currentCharacter.name << ": ";
            string inputStatement;
            getline(cin, inputStatement);
            if (!inputStatement.empty()) {
                struct statement newStatement;
                if (inputStatement[0] == '!') {
                    newStatement.truth = false;
                    newStatement.name = inputStatement[1];
                }
                else
                {
                    newStatement.truth = true;
                    newStatement.name = inputStatement[0];
                }
                currentCharacter.statements.push_back(newStatement);
                
                currentStatement++;
                characters[i] = currentCharacter;
            }
            else
            {
                continueStatements = false;
            }
        }
            
       
    }
    cout << endl;
    
    for (int i = 0; i < numberOfCharacts; i++) {
        character currentCharacter = characters[i];
        cout << setw(5) << currentCharacter.name;
    }
    cout << endl;
    char test[numberOfCharacts + 1];
    for (int i = 0; i < numberOfCharacts; i++) {
        test[i] = '0';
    }
    test[numberOfCharacts] = '\0';
    vector<string> result;
    
    do
    {
        result.push_back(test);
        for (int i = 0; i < numberOfCharacts; i++) {
            cout << setw(5) << test[i];
        }
        cout << endl;
    } while (next(test + 0, test + numberOfCharacts));
    
    string finalResult;
    for (int i = 0; i < result.size(); i++) {
        bool contine = true;
        string currentResult = result[i];
        
        for (int j = 0; j < numberOfCharacts && contine; j++) {
            character currentCharacter = characters[j];
            vector<char> evaluatedStatements;
            for (int s =0; s < currentCharacter.statements.size(); s++) {
                statement currentStatement = currentCharacter.statements[s];
                char evaluateResult = evaluateStatement(currentCharacter.statements[s], result[i], characters);
           //     int index = getIndexOfCharacterWithName(characters, currentStatement.name);
                //currently using the wrong index
                
                evaluatedStatements.push_back(evaluateResult);
                
                if (currentCharacter.statements.size() > 1) {
                    for (int a = 0; a < evaluatedStatements.size(); a++) {
                        if (evaluatedStatements[a] == '1' && evaluateResult == '1') {
                            evaluateResult = '1';
                        }
                        else
                            evaluateResult = '0';
                    }
                }
            
                    if (currentResult[j] != evaluateResult) {
                        contine = false;
                    }
              
             
            //    evaluatedStatements++;

            }
           
        }
        if (contine) {
            finalResult = result[i];
            cout << endl << "Final Result: " << result[i];
        }
    }
    cout << endl;
   // cout << "Evaluated Statements: " << evaluatedStatements;
    for (int i = 0; i < finalResult.size(); i++) {
        if (finalResult[i] == '0') {
            character lyingCharacter = characters[i];
            cout << lyingCharacter.name << " is lying!" << endl;
            
        }
    }
    

    return 0;
}

