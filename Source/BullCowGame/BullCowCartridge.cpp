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

    if(bGameOver){
        ClearScreen();
        SetupGame();
    } else if (Lives > 1)
    {
        if (Input.Equals(HiddenWord))
        {           
            PrintLine(TEXT("YOU guessed the hidden word!!"));    
            PrintLine(TEXT("--Press Enter to Play Again--"));     
            bGameOver = true;  
        }
        else
        {   
            --Lives;
            
            //Check that the players guess equals the correct length
            if (HiddenWord.Len() != Input.Len())
            {   
                PrintLine(TEXT("The hidden word is %i characters long."), HiddenWord.Len());
                
            }
            
            PrintLine(TEXT("Nope, try again."));
            PrintLine(TEXT("Number of Lives = %i"), Lives);            
        }

        // Check if isogram
        // DO NOT Decrement a life just have them guess again

        // else Decrement a life

        // Check if lives > 0
        // Show remaining number of lives and prompt to guess again
        // else
        // Show Game Over and display HiddenWord
        // prompt to guess again or quit
    } else{
        EndGame();
    }

    
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
       
    
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    
    PrintLine(TEXT("YOU LOSE!!!!!!!!!!!!!!!"));
    PrintLine(TEXT("--Press Enter to Play Again--"));
}