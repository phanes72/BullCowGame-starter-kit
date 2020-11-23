// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <iostream>
using namespace std;

void UBullCowCartridge::BeginPlay() // When the game starts
{

    Super::BeginPlay();

    SetupGame(); 

    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);  //TODO Debug line


}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{   
        ProcessGuess(Input);

        // Show remaining number of lives and prompt to guess again
        // else
        
        // prompt to guess again or quit
    
}

void UBullCowCartridge::SetupGame()
{
    ClearScreen();

    PrintLine(TEXT("Welcome to the Bulls and Cows Game!"));

    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();    
    PrintLine(TEXT("Number of Lives = %i"), Lives);
    
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess."));    
    PrintLine(TEXT("--Press Enter to continue--")); //Prompt player for guess

    //const TCHAR HW[] = TEXT("cakes");
        
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    
    PrintLine(TEXT("YOU LOSE!!!!!!!!!!!!!!!"));
    // Show Game Over and display HiddenWord
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); 
    PrintLine(TEXT("\n--Press Enter to Play Again--"));
}


void UBullCowCartridge::ProcessGuess(FString Guess){
    
    if(bGameOver){
        ClearScreen();
        SetupGame();
        return;

    } else if (Lives > 1) // // Check if lives > 0
    {
        if (Guess.Equals(HiddenWord))
        {           
            PrintLine(TEXT("YOU guessed the hidden word!!"));    
            PrintLine(TEXT("--Press Enter to Play Again--"));     
            bGameOver = true;  
        }
               
        else
        {               
            //Check that the players guess equals the correct length
            // DO NOT Decrement a life just have them guess again
            if (HiddenWord.Len() != Guess.Len())
            {   
                PrintLine(TEXT("The hidden word is %i characters long."), HiddenWord.Len());
                PrintLine(TEXT("Number of Lives = %i"), Lives); 
                return;
                
            }    
            //Check if Isogram
            else if (IsIsogram(Guess)){
                PrintLine(TEXT("You can't have words with repeating letters"));
                return;
            }       
            else
            {
                PrintLine(TEXT("Nope, try again."));
                PrintLine(TEXT("Number of Lives = %i"), --Lives);  
                return;   
            }
                   
        }
    } else{
        EndGame();
    }   
}

bool UBullCowCartridge::IsIsogram(FString Guess) const
{      
    int32 counter = 0;
    while(counter < Guess.Len() - 1)
    {
        char letter = Guess[counter];
                
        for(int32 i = counter; i < Guess.Len() - 1; i++)
        {
            char nextLetter = Guess[i + 1];
            
            if(letter == nextLetter)
            {
                return true;
            }
        }
       counter++;
    }
     return false;

}