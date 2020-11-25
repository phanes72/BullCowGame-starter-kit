// Fill out your copyright notice in the Description page of Project Settings.
#include <iostream>
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

using namespace std;
void UBullCowCartridge::BeginPlay() // When the game starts
{

    Super::BeginPlay();
       
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    TArray<FString> ValidWords = GetValidWords(Words);
        
    SetupGame(); 

     
    PrintLine(TEXT("The number of possible words is %i "), Words.Num());
    PrintLine(TEXT("The number of valid possible words is %i "), ValidWords.Num());
    
   
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);  //TODO Debug line
   

}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{   
        ProcessGuess(Input);       
    
}

void UBullCowCartridge::SetupGame()
{
    ClearScreen();

    PrintLine(TEXT("Welcome to the Bulls and Cows Game!"));
    HiddenWord = "cakes";
    
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
    // Show Game Over and display HiddenWord
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); 
    PrintLine(TEXT("\n--Press Enter to Play Again--"));
}


void UBullCowCartridge::ProcessGuess(const FString& Guess){
    
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

bool UBullCowCartridge::IsIsogram(const FString& Guess) const
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


TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordsList) const
{
    TArray<FString> ValidWords;  
        
    for (FString Word: WordsList){
        if (Word.Len() >= 4 && Word.Len() <= 8 && !IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;   
}