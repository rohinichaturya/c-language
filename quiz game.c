#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store user details
struct User
{
    char username[50];
    int score;
};

// Global variables
struct User users[100];
int userCount = 0;

// Function prototypes
void registerUser();
void loginUser();
void startQuiz(char username[]);
void displayLeaderboard();
void saveUserScores();
void loadUserScores();
void askQuestion(char category[], char question[], char options[][50], int correctOption);
void quizMenu(char username[]);

int main() 
{
    int choice;
    loadUserScores();

    while (1) 
    {
        printf("\n===== QUIZ GAME SYSTEM =====\n");
        printf("1. Register\n2. Login\n3. View Leaderboard\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: displayLeaderboard(); break;
            case 4: printf("Exiting Quiz System...\n"); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load user scores from file
void loadUserScores() 
{
    FILE *fp = fopen("scores.dat", "rb");
    if (fp == NULL) return;
    while (fread(&users[userCount], sizeof(struct User), 1, fp))
      {
        userCount++;
    }
    fclose(fp);
}

// Save user scores to file
void saveUserScores() 
{
    FILE *fp = fopen("scores.dat", "wb");
    for (int i = 0; i < userCount; i++) 
    {
        fwrite(&users[i], sizeof(struct User), 1, fp);
    }
    fclose(fp);
}

// Register a new user
void registerUser() 
{
    struct User newUser;
    printf("\nEnter Username: ");
    scanf("%s", newUser.username);
    newUser.score = 0;

    users[userCount++] = newUser;
    saveUserScores();
    printf("Registration Successful! Please Login.\n");
}

// User login
void loginUser() 
{
    char username[50];
    printf("\nEnter Username: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++)
      {
        if (strcmp(users[i].username, username) == 0) 
        {
            printf("Login Successful! Welcome, %s\n", username);
            quizMenu(username);
            return;
        }
    }
    printf("User not found! Please register.\n");
}

// Display leaderboard
void displayLeaderboard() 
{
    printf("\n===== LEADERBOARD =====\n");
    for (int i = 0; i < userCount; i++)
      {
        printf("%s - Score: %d\n", users[i].username, users[i].score);
    }
}

// Ask a single quiz question
void askQuestion(char category[], char question[], char options[][50], int correctOption)
{
    int choice;
    printf("\n[%s] %s\n", category, question);
    for (int i = 0; i < 4; i++) {
        printf("%d) %s\n", i + 1, options[i]);
    }
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == correctOption)
    {
        printf("Correct Answer! +10 Points\n");
    } 
    else 
    {
        printf("Wrong Answer! Correct Answer: %s\n", options[correctOption - 1]);
    }
}

// Start Quiz
void startQuiz(char username[]) 
{
    char options[4][50];
    int score = 0;

    printf("\n===== QUIZ STARTED =====\n");

    // Question 1
    strcpy(options[0], "Paris");
    strcpy(options[1], "London");
    strcpy(options[2], "Berlin");
    strcpy(options[3], "Madrid");
    askQuestion("Geography", "What is the capital of France?", options, 1);
    score += 10;

    // Question 2
    strcpy(options[0], "5");
    strcpy(options[1], "10");
    strcpy(options[2], "15");
    strcpy(options[3], "20");
    askQuestion("Math", "What is 5 * 2?", options, 2);
    score += 10;

    // Question 3
    strcpy(options[0], "Jupiter");
    strcpy(options[1], "Mars");
    strcpy(options[2], "Earth");
    strcpy(options[3], "Saturn");
    askQuestion("Science", "Which planet is known as the Red Planet?", options, 2);
    score += 10;

    // Save Score
    for (int i = 0; i < userCount; i++) 
    {
        if (strcmp(users[i].username, username) == 0) 
        {
            users[i].score += score;
            break;
        }
    }
    saveUserScores();
    printf("Quiz Completed! Your Score: %d\n", score);
}

// Quiz Menu
void quizMenu(char username[]) 
{
    int choice;
    while (1) {
        printf("\n===== QUIZ MENU =====\n");
        printf("1. Start Quiz\n2. View Leaderboard\n3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: startQuiz(username); break;
            case 2: displayLeaderboard(); break;
            case 3: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    }
}
