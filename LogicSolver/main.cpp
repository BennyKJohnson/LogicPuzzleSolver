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

int main(int argc, const char * argv[])
{
    cout << "Welcome to Logic Solver" << endl;
    bool continueInput = true;
    int numberOfCharacts = 0;
    vector<character> characters;
    
    while (continueInput) {
        cout << "Enter a new character? Y/N: ";
        char result;
        cin >> result;
        if (result == 'Y') {
            character newCharacter;
            cout << "Enter name: ";
            cin >>  newCharacter.name;
            cout << endl;
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
        do
        {
            cout << "Enter Statement for " << currentCharacter.name << ": ";
            char inputStatement[3];
            cin >> inputStatement;
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
            char result;
            cout << "Enter another statement: ";
            cin >> result;
            characters[i] = currentCharacter;
            
            if (result != 'Y') {
                continueStatements = false;
            }
        }while (continueStatements);
            
       
    }
    char test[numberOfCharacts + 1];
    for (int i = 0; i < numberOfCharacts; i++) {
        test[i] = '0';
    }
    test[numberOfCharacts] = '\0';
    vector<string> result;
    
    do
    {
        result.push_back(test);
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
            cout << "Final Result: " << result[i] << endl;
        }
    }
 
   // cout << "Evaluated Statements: " << evaluatedStatements;
    for (int i = 0; i < finalResult.size(); i++) {
        if (finalResult[i] == '0') {
            character lyingCharacter = characters[i];
            cout << lyingCharacter.name << " is lying!" << endl;
            
        }
    }
    

    return 0;
}

