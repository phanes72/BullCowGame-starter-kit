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
    
    ValidWords = GetValidWords(Words);
           
    SetupGame();    
    
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{   
        ProcessGuess(Input);          
}

void UBullCowCartridge::SetupGame()
{
    ClearScreen();

    PrintLine(TEXT("Welcome to the Bulls and Cows Game!"));        
       
    //Generate a random number in the array to return the valid word
    HiddenWord = ValidWords[FMath::RandRange(0, ValidWords.Num() - 1)];
       
    Lives = HiddenWord.Len() * 2;    
    PrintLine(TEXT("Number of Lives = %i"), Lives);
    
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess."));    
    PrintLine(TEXT("--Press Enter to continue--")); //Prompt player for guess      
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);  //*******************TODO DEBUG ONLY display HiddenWord  
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
                PrintLine(TEXT("No words with repeating letters"));
                return;
            }       
            else
            {
                PrintLine(TEXT("Nope, try again."));

                 // Show the player Bulls and Cows 
                FBullCowCount Score = GetBullCows(Guess);
                //PrintLine(TEXT("Bulls = %i, Cows = %i"), Count.Bulls, Count.Cows);
                PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
                ShowBulls(Guess, HiddenWord);
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

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
       
    // if the index Guess is same as index HiddenWord, BullCount++
    // if not a bull was it a cow?  if yes CowCount++
     FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex] )
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
            }
        }
        
    }

    return Count;
    
}


//Show the letter that is a Bull along with underscores
void UBullCowCartridge::ShowBulls(FString Guess, FString HiddenWord) const
{
    FString HelpString;
    FString Miss = "_";
    FString LetterInGuess = "";

    for (int32 i = 0; i < HiddenWord.Len(); i++)    
    {
        PrintLine(TEXT("HiddenWord[i] is %c"),  HiddenWord[i]);
        
        TCHAR Letter = HiddenWord[i];
        int32 position = i;
        if (Guess.FindChar(Letter, position))
        {
            PrintLine(TEXT("Position %i was a hit at letter %c"),  position, HiddenWord[position]);          
            
        }     
                
       
    }

   
    //  TCHAR Letter1 = HiddenWord[0];
    //  int32 position1 = 0;
    //     if (Guess.FindChar(Letter1, position1))
    //     {
    //         PrintLine(TEXT("Position %i was a hit at letter %c"),  position1, HiddenWord[position1]);          
            
    //     }     

    // TCHAR Letter2 = HiddenWord[1];
    // int32 position2 = 1;
    //     if (Guess.FindChar(Letter2, position2))
    //     {
    //         PrintLine(TEXT("Position %i was a hit at letter %c"),  position2, HiddenWord[position2]);          
            
    //     } 
  
}