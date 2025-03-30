#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int rollDice();
int decideWhoStarts();
int play_user();
int play_computer();
int calculateScore();
int howManyAreEqual(int dice1, int dice2, int dice3, int dice4, int dice5);
int checkForFullHouse(int d1, int d2, int d3, int d4, int d5);


int main(void)
{
    int numberOfRounds;

    srand(time(NULL));


    printf("How many rounds would you like to play? ");
    scanf("%d", &numberOfRounds);

    int isPlayerStarting = decideWhoStarts();

    if (isPlayerStarting) {
        play_user();
    }
    else {

    }

    return 0;
}

int rollDice()
{
    int dice = rand() % 6 + 1;
    return dice;
}

/*
*Returns 1 if player starts
*Returns 0 if computer starts
*/
int decideWhoStarts()
{
    int playerSum = 0, computerSum = 0;
    do {
        int startDiceComp_1 = rollDice();
        int startDiceComp_2 = rollDice();
        int startDicePlayer_1 = rollDice();
        int startDicePlayer_2 = rollDice();
        printf("\nComputer rolled the dice and got: %d and %d",startDiceComp_1,startDiceComp_2);
        printf("\nYou rolled the dice and got: %d and %d",startDicePlayer_1,startDicePlayer_2);

        playerSum = startDicePlayer_1 + startDicePlayer_2;
        computerSum = startDiceComp_1 + startDiceComp_2;
    }
    while (playerSum == computerSum);

    if (playerSum > computerSum) {
        return 1;
    }
    else {
        return 0;
    }

}

int play_user()
{
    int dice1 = rollDice(), dice2 = rollDice(), dice3 = rollDice(), dice4 = rollDice(), dice5 = rollDice();
    printf("You got => [Dice 1:] %d [Dice 2:] %d [Dice 3:] %d [Dice 4:] %d [Dice 5:] %d\n",
        dice1, dice2, dice3, dice4, dice5);

    //Ask user for re roll
    char answer;
    do {
        printf("Do you want to ReRoll: (Y/N)? ");
        scanf(" %c", &answer);
        getchar(); // To consume newline character

        answer = toupper(answer);
        if (answer == 'Y') {
            int diceToKeep1;
            int diceToKeep2;

            printf("Which ones do you want to keep? ");
            scanf("%d %d",&diceToKeep1, &diceToKeep2);

            //Re-assigning the dice values
            if (diceToKeep1 != 1 && diceToKeep2 != 1) dice1 = rollDice();
            if (diceToKeep1 != 2 && diceToKeep2 != 2) dice2 = rollDice();
            if (diceToKeep1 != 3 && diceToKeep2 != 3) dice3 = rollDice();
            if (diceToKeep1 != 4 && diceToKeep2 != 4) dice4 = rollDice();
            if (diceToKeep1 != 5 && diceToKeep2 != 5) dice5 = rollDice();

            printf("\nYou got => [Dice 1:] %d [Dice 2:] %d [Dice 3:] %d [Dice 4:] %d [Dice 5:] %d\n",
                dice1, dice2, dice3, dice4, dice5);


        }
        else if (answer == 'N') {

        }
    } while (answer != 'Y' && answer != 'N');

}

int howManyAreEqual(int dice1, int dice2, int dice3, int dice4, int dice5)
{
    int maxCount = 1;

    int count1 = (dice1 == dice2) + (dice1 == dice3) + (dice1 == dice4) + (dice1 == dice5) + 1;
    if (count1 > maxCount) maxCount = count1;

    int count2 = (dice2 == dice3) + (dice2 == dice4) + (dice2 == dice5) + 1;
    if (count2 > maxCount) maxCount = count2;

    int count3 = (dice3 == dice4) + (dice3 == dice5) + 1;
    if (count3 > maxCount) maxCount = count3;

    int count4 = (dice4 == dice5) + 1;
    if (count4 > maxCount) maxCount = count4;

    return maxCount;
}

int calculateScore(int dice1, int dice2, int dice3, int dice4, int dice5)
{
    int equalDiceNumber = howManyAreEqual(dice1, dice2, dice3, dice4, dice5);

    //All are equal (Generala)
    if (equalDiceNumber == 5) {
        return 50;
    }

    // Four of a kind
    if (equalDiceNumber == 4) {
        return 40;
    }

    //Full house
    if(equalDiceNumber == 3) {
        if (checkForFullHouse(dice1, dice2, dice3, dice4, dice5)) {
            return 30;
        }
    }


}

int checkForFullHouse(int d1, int d2, int d3, int d4, int d5)
{
    int count1 = (d1 == d2) + (d1 == d3) + (d1 == d4) + (d1 == d5) + 1;
    int count2 = (d2 == d3) + (d2 == d4) + (d2 == d5) + 1;
    int count3 = (d3 == d4) + (d3 == d5) + 1;
    int count4 = (d4 == d5) + 1;

    if ( (count1 == 3 && count2 == 2) || (count1 == 3 && count3 == 2) || (count1 == 3 && count4 == 2)
        || (count2 == 3 && count1 == 2) || (count2 == 3 && count3 == 2) || (count2 == 3 && count4 == 2)
        ||  (count3 == 3 && count1 == 2) || (count3 == 3 && count2 == 2) || (count3 == 3 && count4 == 2)
        || (count4 == 3 && count1 == 2) || (count4 == 3 && count2 == 2) || (count4 == 3 && count3 == 2))
        { return 1; }


    return 0;

}

int play_computer()
{
    printf("Computer rolled the dice and got");
    int dice1 = rollDice(), dice2 = rollDice(), dice3 = rollDice(), dice4 = rollDice(), dice5 = rollDice();

}