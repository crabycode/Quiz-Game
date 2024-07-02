#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
typedef struct {
    char question[256];
    char options[4][64];
    char correctOption;
} Question;
Question questions[25] = {
    {"What is the capital of France?", {"a) Berlin", "b) Madrid", "c) Paris", "d) Rome"}, 'c'},
    {"Which planet is known as the Red Planet?", {"a) Earth", "b) Mars", "c) Jupiter", "d) Venus"}, 'b'},
    {"Who wrote 'To Kill a Mockingbird'?", {"a) Harper Lee", "b) J.K. Rowling", "c) Ernest Hemingway", "d) Mark Twain"}, 'a'},
    {"What is the largest ocean on Earth?", {"a) Atlantic", "b) Indian", "c) Arctic", "d) Pacific"}, 'd'},
    {"What is the square root of 64?", {"a) 6", "b) 7", "c) 8", "d) 9"}, 'c'},
    {"Who painted the Mona Lisa?", {"a) Vincent van Gogh", "b) Pablo Picasso", "c) Leonardo da Vinci", "d) Michelangelo"}, 'c'},
    {"What is the chemical symbol for gold?", {"a) Au", "b) Ag", "c) Gd", "d) Go"}, 'a'},
    {"What is the capital city of Japan?", {"a) Beijing", "b) Seoul", "c) Bangkok", "d) Tokyo"}, 'd'},
    {"In which year did the Titanic sink?", {"a) 1912", "b) 1913", "c) 1914", "d) 1915"}, 'a'},
    {"What is the hardest natural substance on Earth?", {"a) Gold", "b) Iron", "c) Diamond", "d) Platinum"}, 'c'},
    {"Which element has the chemical symbol 'O'?", {"a) Oxygen", "b) Gold", "c) Osmium", "d) Zinc"}, 'a'},
    {"Who is known as the 'Father of Computers'?", {"a) Charles Babbage", "b) Alan Turing", "c) Bill Gates", "d) Steve Jobs"}, 'a'},
    {"What is the longest river in the world?", {"a) Nile", "b) Amazon", "c) Yangtze", "d) Mississippi"}, 'a'},
    {"What is the powerhouse of the cell?", {"a) Nucleus", "b) Mitochondria", "c) Ribosome", "d) Golgi apparatus"}, 'b'},
    {"Which country is known as the Land of the Rising Sun?", {"a) China", "b) Japan", "c) South Korea", "d) India"}, 'b'},
    {"Who wrote '1984'?", {"a) George Orwell", "b) Aldous Huxley", "c) Ray Bradbury", "d) J.R.R. Tolkien"}, 'a'},
    {"What is the speed of light?", {"a) 300,000 km/s", "b) 150,000 km/s", "c) 75,000 km/s", "d) 1,000 km/s"}, 'a'},
    {"Who developed the theory of relativity?", {"a) Isaac Newton", "b) Nikola Tesla", "c) Albert Einstein", "d) Galileo Galilei"}, 'c'},
    {"Which gas do plants absorb from the atmosphere?", {"a) Oxygen", "b) Nitrogen", "c) Carbon Dioxide", "d) Hydrogen"}, 'c'},
    {"What is the capital of Australia?", {"a) Sydney", "b) Melbourne", "c) Brisbane", "d) Canberra"}, 'd'},
    {"Who discovered penicillin?", {"a) Marie Curie", "b) Alexander Fleming", "c) Louis Pasteur", "d) Robert Koch"}, 'b'},
    {"What is the main ingredient in guacamole?", {"a) Tomato", "b) Avocado", "c) Onion", "d) Pepper"}, 'b'},
    {"Which planet is closest to the sun?", {"a) Venus", "b) Earth", "c) Mercury", "d) Mars"}, 'c'},
    {"What is the largest continent?", {"a) Africa", "b) Asia", "c) Europe", "d) Antarctica"}, 'b'},
    {"Who invented the telephone?", {"a) Alexander Graham Bell", "b) Thomas Edison", "c) Nikola Tesla", "d) Guglielmo Marconi"}, 'a'}
};

int questionsCount = 25;
void removeQuestion(int index) {
    for (int i = index; i < questionsCount - 1; i++)
    {
        questions[i] = questions[i + 1];
    }
    questionsCount--;
}
void saveScore(char *nickname, float score)
{
    FILE *file = fopen("highscores.txt", "a");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    fprintf(file, "%s - %.2f\n", nickname, score);
    fclose(file);

}
void determineScore(float score)
{
    if(score<20)
    {
        printf("Better luck next time!\n");
    }
    else
    {
        printf("You beat the game!\n");
    }
}
void startGame()
{
    srand(time(NULL));
    int totalQuestions = 5;
    int score = 0;
    char answer;
    for (int i = 0; i < totalQuestions; i++)
    {
        if (questionsCount == 0)
        {
            printf("No more questions available.\n");
            break;
        }
        int questionIndex = rand() % questionsCount;
        Question selectedQuestion = questions[questionIndex];
        printf("%s\n", selectedQuestion.question);
        for (int j = 0; j < 4; j++)
        {
            printf("%s\n", selectedQuestion.options[j]);
        }
        scanf(" %c", &answer);
        answer = tolower(answer);
        if (answer == selectedQuestion.correctOption)
        {
            score += 20;
            printf("Correct!\n");
        }
        else
        {
            printf("Wrong. The correct answer was %c.\n", selectedQuestion.correctOption);
        }
        removeQuestion(questionIndex);
    }
    float finalScore = (float)score / totalQuestions;
    char nickname[32];
    printf("Enter your nickname: ");
    scanf("%s", nickname);
    printf("Your score is: %.2f\n", finalScore);
    determineScore(finalScore);
    saveScore(nickname, finalScore);
}
int viewHighScores()
{
    int quit = 0;
    FILE *file = fopen("highscores.txt", "r");
    if(!file)
    {
        printf("There are no high scores to display.\n");
        return quit;
    }
    char nickname[32];
    float score;
    while (fscanf(file, "%s - %f\n", nickname, &score) == 2)
    {
        printf("%s - %.2f\n", nickname, score);
    }
    fclose(file);
}
void gameRules()
{
    printf("           The game rules are simple\n");
    printf("You will be asked questions and you need to answer them.\n");
    printf("For every correct guess you receive +20 points and in the\n");
    printf("end you are going to get an average score based on the number\n");
    printf("of questions and collected points\n");
}
int main()
{
    printf("Hello and welcome to my quiz game!\n");
    int quit = 0;
    while(!quit)
    {
        printf("1) Start Game\n2) View High Scores\n3) Game Rules\n4) Exit\n");
        int choice = 0;
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                startGame();
                break;
            case 2:
                viewHighScores();
                break;
            case 3:
                gameRules();
                break;
            case 4:
                exit(1);
                break;
            default:
                printf("Please enter valid choice.(a number)");
        }
        printf("Exit? (1 = Yes/0 = No)\n");
        scanf("%d", &quit);
    }
    return 0;
}
