#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int roll_a_dice();
int decideWhoStarts();
int play_user(int);
int play_computer();
int calculateScore();
void scoresheet(int playerScore, int computerScore);
int howManyAreEqual(int dice1, int dice2, int dice3, int dice4, int dice5);
int checkForFullHouse(int d1, int d2, int d3, int d4, int d5);
int checkForStraight(int d1, int d2, int d3, int d4, int d5);
int doesItHaveThisValue(int value,int d1,int d2, int d3,int d4,int d5);
int mostRepeatedNumber(int dice1, int dice2, int dice3, int dice4, int dice5);
int findOddDice(int d1, int d2, int d3, int d4, int d5);
void print_line(void);


int main(void)
{
    srand(time(NULL));
    char answerToPlayAgain;

    /*1st Question: I used do-while for game's main loop which is a post-test loop
     *I also used post-test loop do while to ask the user a  Y or N question and to repeat it until the user gives proper input
     *I used while which is a pre-test loop to repeat the rounds
     *Pre-test loops check the condition before starting to execute the loops body
     *Post-test loops execute the body regardless of the condition at least once and then checks the condition
     */
    //Main game loop
    do {
        int numberOfRounds, roundsPlayed = 0;
        int playerScore = 0;
        int computerScore = 0;
        int actualRound = 1;

       printf("How many rounds would you like to play? ");
        scanf("%d", &numberOfRounds);

        int isPlayersTurn = decideWhoStarts();

        //Game loop to play multiple rounds
        while (actualRound < numberOfRounds + 1)
        {
            if (isPlayersTurn)
            {
                printf("\nRound %d --- Your Turn\n",actualRound);
                print_line();

                int scoreEarned = play_user(playerScore);
                playerScore += scoreEarned;

                if (scoreEarned == 50) {
                    //Generala finish the game
                    printf("Generala!\n");
                    actualRound += 999; // to get out of the game loop
                }

                isPlayersTurn = 0;
            }
            else {
                printf("\nRound %d --- Computer's Turn\n",actualRound);
                print_line();

                int scoreEarnedComp = play_computer();
                computerScore += scoreEarnedComp;

                if (scoreEarnedComp == 50) {
                    //Generala
                    printf("Generala!\n");
                    actualRound += 999; // to get out of the game loop
                }

                printf("Computer got %d points\n Computer's total score: %d\n",scoreEarnedComp,computerScore);
                isPlayersTurn = 1;
            }
            roundsPlayed++;

            if (roundsPlayed % 2 == 0) {
                actualRound++;
            }
        }

        scoresheet(playerScore, computerScore);

        if (playerScore > computerScore) {
            printf("Player wins\n");
        }
        else {
            printf("Computer wins\n");
        }

        //Ask for replay
        do {
            printf("Do you want to play again? ");
            scanf("\n%c",&answerToPlayAgain);
            answerToPlayAgain = toupper(answerToPlayAgain);

        }while (answerToPlayAgain != 'Y' && answerToPlayAgain != 'N');

    } while (answerToPlayAgain == 'Y');

    return 0;
}
//2nd Question: the datatype of the random number generated in this function is integer
int roll_a_dice()
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
        int startDiceComputer1 = roll_a_dice();
        int startDiceComputer2= roll_a_dice();
        int startDicePlayer_1 = roll_a_dice();
        int startDicePlayer_2 = roll_a_dice();
        printf("Computer rolled the dice and got: %d and %d\n",startDiceComputer1,startDiceComputer2);
        printf("You rolled the dice and got: %d and %d\n",startDicePlayer_1,startDicePlayer_2);

        playerSum = startDicePlayer_1 + startDicePlayer_2;
        computerSum = startDiceComputer1 + startDiceComputer2;
    }
    while (playerSum == computerSum);

    if (playerSum > computerSum) {
        return 1;
    }
    else {
        return 0;
    }

}


/*3rd Question: play_user returns an integer. It returns the score the user got in this round
 *This is because that value is used in main keep track of the total score the user got
 *Also if it returns 50 it means the user got generala and won the game
*/
int play_user(int startingTotalScore)
{
    int dice1 = roll_a_dice(), dice2 = roll_a_dice(), dice3 = roll_a_dice(), dice4 = roll_a_dice(), dice5 = roll_a_dice();
    printf("You got => [Dice 1:] %d [Dice 2:] %d [Dice 3:] %d [Dice 4:] %d [Dice 5:] %d\n",
        dice1, dice2, dice3, dice4, dice5);

    int score = calculateScore(dice1, dice2, dice3, dice4, dice5);
    printf("These would give you %d points \nYour total score would be if you don't reroll %d\n",score, startingTotalScore + score);

    //Ask user for re roll
    int rollsLeft = 2;
    while (rollsLeft > 0)
    {
        char answer;
        do {
            printf("Do you want to reroll: (Y/N)? ");
            scanf(" %c", &answer);
            getchar(); // To consume newline character

            answer = toupper(answer);

        } while (answer != 'Y' && answer != 'N');

        if (answer == 'Y') {
            int diceToKeep1 = 0;
            int diceToKeep2 = 0;

            do {
                printf("Which ones do you want to keep? ");
                scanf("%d %d",&diceToKeep1, &diceToKeep2);
            } while (diceToKeep1 < 1 || diceToKeep1 > 5 || diceToKeep2 < 1 || diceToKeep2 > 5);


            //Re-assigning the dice values
            if (diceToKeep1 != 1 && diceToKeep2 != 1) dice1 = roll_a_dice();
            if (diceToKeep1 != 2 && diceToKeep2 != 2) dice2 = roll_a_dice();
            if (diceToKeep1 != 3 && diceToKeep2 != 3) dice3 = roll_a_dice();
            if (diceToKeep1 != 4 && diceToKeep2 != 4) dice4 = roll_a_dice();
            if (diceToKeep1 != 5 && diceToKeep2 != 5) dice5 = roll_a_dice();

            printf("\nYou got => [Dice 1:] %d [Dice 2:] %d [Dice 3:] %d [Dice 4:] %d [Dice 5:] %d\n",
                dice1, dice2, dice3, dice4, dice5);

            score = calculateScore(dice1, dice2, dice3, dice4, dice5);
            printf("These would give you %d points \nYour total score will be %d\n",score, startingTotalScore + score);

            rollsLeft--;
            }
        else if (answer == 'N')
        {
            rollsLeft = 0;
        }
    }

    return score;
}



int doesItHaveThisValue(int value,int d1,int d2, int d3,int d4,int d5)
{
    int result = 0;
    if (value == d1 || value == d2 || value == d3 || value == d4 || value == d5) {
        result = 1;
    }
    return result;
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
/* Returns the most repeated dice value
 * if it has more than 1 most repeated dice value it will return the bigger one
 */
int mostRepeatedNumber(int dice1, int dice2, int dice3, int dice4, int dice5)
{
    int maxCount = 1;
    int mostRepeatedValue = dice1;

    int count1 = (dice1 == dice2) + (dice1 == dice3) + (dice1 == dice4) + (dice1 == dice5) + 1;
    int count2 = (dice2 == dice3) + (dice2 == dice4) + (dice2 == dice5) + 1;
    int count3 = (dice3 == dice4) + (dice3 == dice5) + 1;
    int count4 = (dice4 == dice5) + 1;

    if (count1 > maxCount  || (count1  == maxCount && dice1 > mostRepeatedValue))
    {
        maxCount = count1;
        mostRepeatedValue = dice1;
    }
    if (count2 > maxCount || (count2 == maxCount && dice2 > mostRepeatedValue)) {
        maxCount = count2;
        mostRepeatedValue = dice2;
    }
    if (count3 > maxCount || (count3 == maxCount && dice3 > mostRepeatedValue)) {
        maxCount = count3;
        mostRepeatedValue = dice3;
    }
    if (count4 > maxCount || (count4 == maxCount && dice4 > mostRepeatedValue)) {
        maxCount = count4;
        mostRepeatedValue = dice4;
    }

    return mostRepeatedValue;
}

int calculateScore(int dice1, int dice2, int dice3, int dice4, int dice5)
{
    int equalDiceNumber = howManyAreEqual(dice1, dice2, dice3, dice4, dice5);
    int mostRepeated = mostRepeatedNumber(dice1, dice2, dice3, dice4, dice5);

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

    //Straight
    if (checkForStraight(dice1, dice2, dice3, dice4, dice5)) {
        return 20;
    }

    //No repeated number
    if (equalDiceNumber == 1) {
        return 1;
    }

    // Normal Calculation
    return  mostRepeated * equalDiceNumber;

}

int checkForStraight(int d1, int d2, int d3, int d4, int d5)
{
    // 1 2 3 4 5
    if (d1 == 1 && d2 == 2 && d3 == 3 && d4 == 4 && d5 == 5)
    {
        return 1;
    }
    // 2 3 4 5 6
    if (d1 == 2 && d2 == 3 && d3 == 4 && d4 == 5 && d5 == 6)
    {
        return 1;
    }
    return 0;
}

int checkForFullHouse(int d1, int d2, int d3, int d4, int d5)
{
    if ((d1 == d2 && d1 == d3) && d4 == d5) return 1;
    if ((d1 == d2 && d1 == d4) && d3 == d5) return 1;
    if ((d1 == d2 && d1 == d5) && d3 == d4) return 1;
    if ((d1 == d3 && d1 == d4) && d2 == d5) return 1;
    if ((d1 == d3 && d1 == d5) && d2 == d4) return 1;
    if ((d1 == d4 && d1 == d5) && d2 == d3) return 1;
    if ((d2 == d3 && d2 == d4) && d1 == d5) return 1;
    if ((d2 == d3 && d2 == d5) && d1 == d4) return 1;
    if ((d2 == d4 && d2 == d5) && d1 == d3) return 1;
    if ((d3 == d4 && d3 == d5) && d1 == d2) return 1;

    return 0;
}

int play_computer()
{
    int dice1 = roll_a_dice(), dice2 = roll_a_dice(), dice3 = roll_a_dice(), dice4 = roll_a_dice(), dice5 = roll_a_dice();

    printf("Computer got => [Dice 1:] %d [Dice 2:] %d [Dice 3:] %d [Dice 4:] %d [Dice 5:] %d\n",
       dice1, dice2, dice3, dice4, dice5);



    int mostRepeated = mostRepeatedNumber(dice1, dice2, dice3, dice4, dice5);
    int howManySame = howManyAreEqual(dice1,dice2,dice3,dice4,dice5);

    //Reroll
    if (howManySame == 4) {

        int diceToRoll = findOddDice(dice1, dice2, dice3, dice4, dice5);

        if (diceToRoll == 1) dice1 = roll_a_dice();
        if (diceToRoll == 2) dice2 = roll_a_dice();
        if (diceToRoll == 3) dice3 = roll_a_dice();
        if (diceToRoll == 4) dice4 = roll_a_dice();
        if (diceToRoll == 5) dice5 = roll_a_dice();

        printf("Rolled dice %d!\n",diceToRoll);


        printf("=> [Dice 1:] %d [Dice 2:] %d [Dice 3:] %d [Dice 4:] %d [Dice 5:] %d\n",
            dice1, dice2, dice3, dice4, dice5);

    }
    int score = calculateScore(dice1, dice2, dice3, dice4, dice5);

    return score;

}

int findOddDice(int d1, int d2, int d3, int d4, int d5)
{
    if (howManyAreEqual(d1, d2, d3, d4, d5) == 4 ) {
        if (d1 == d2 && d1 == d3 && d1 == d4 && d1 != d5) return 5;
        if (d1 == d2 && d1 == d3 && d1 == d5 && d1 != d4) return 4;
        if (d1 == d2 && d1 == d4 && d1 == d5 && d1 != d3) return 3;
        if (d1 == d3 && d1 == d4 && d1 == d5 && d1 != d2) return 2;
        if (d2 == d3 && d2 == d4 && d2 == d5 && d2 != d1) return 1;
    }
    return 0;
}

void print_line(void) {
    printf("-----------------------------------------------------------------------------------------------\n");
}

void scoresheet(int playerScore, int computerScore)
{
    print_line();
    printf("Computer scores: %d\n",computerScore);
    printf("Player scores: %d\n",playerScore);
}
