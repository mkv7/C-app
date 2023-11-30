#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// TODO:: implement your project here!

void init_shop(GameShop *shop) 
{   
    shop->count = 0;
    shop->capacity = 10;
    shop->games = (Game *)malloc(shop->capacity * sizeof(Game));
    if (!shop->games) {
        perror("Error initializing shop");
        exit(EXIT_FAILURE);
    }
}


int add(GameShop *shop, const char *name, float price) 
{   
    if (price <= 0)
    {
        printf("Game price cannot be negative or zero.\n");
        return 0;
    }
    
    for (int i = 0; i < shop->count; i++) {
        if (strcmp(shop->games[i].name, name) == 0) {
            printf("Game %s is already in the database.\n", name);
            return 0;
        }
    }

    if (shop->count >= shop->capacity) {
        shop->capacity *= 2;
        Game* temp = (Game *)realloc(shop->games, shop->capacity * sizeof(Game));
        if (!temp) {
            printf("Memory allocation error.\n");
            return 0;
        }
        shop->games = temp;
    }

    strcpy(shop->games[shop->count].name, name);
    shop->games[shop->count].price = price;
    shop->games[shop->count].revenue = 0.0;
    shop->count++;
    printf("SUCCESS\n");
    return 1;
}

void buy(GameShop *shop, const char *name, int count) 
{   
    if (count <=0)
    {
        printf("Number of bought items cannot be less than 1.\n");
        return;
    }
    
    for (int i = 0; i < shop->count; i++) {
        if (strcmp(shop->games[i].name, name) == 0) {
            shop->games[i].revenue += shop->games[i].price * count;
            printf("SUCCESS\n");
            return;
        }
    }
    printf("Error: Game not found in the database.\n");
}

int compare_games(const void *a, const void *b) 
{
    const Game *gameA = (const Game *)a;
    const Game *gameB = (const Game *)b;
    
    if (gameA->revenue > gameB->revenue) {
        return -1;
    } else if (gameA->revenue < gameB->revenue) {
        return 1;
    }
    return 0;
}

void print(const GameShop *shop) 
{
    Game *sortedGames = (Game *)malloc(shop->count * sizeof(Game));
    if (!sortedGames) {
        printf("Memory allocation error.\n");
        return;
    }

    memcpy(sortedGames, shop->games, shop->count * sizeof(Game));
    qsort(sortedGames, shop->count, sizeof(Game), compare_games);

    for (int i = 0; i < shop->count; i++) {
        printf("%s %.2f %.2f\n", sortedGames[i].name, sortedGames[i].price, sortedGames[i].revenue);
    }
    printf("SUCCESS\n");
    free(sortedGames);
}

void save(const GameShop *shop, const char *filename) 
{   
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < shop->count; i++) {
        fprintf(file, "%s %.2f %.2f\n", shop->games[i].name, shop->games[i].price, shop->games[i].revenue);
        fflush(file);  // Flush the data immediately to the file.
    }
    printf("SUCCESS\n");
    fclose(file);
}

void load(GameShop *shop, const char *filename) 
{   
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    shop->count = 0;
    while (fscanf(file, "%s %f %f", shop->games[shop->count].name, &shop->games[shop->count].price, &shop->games[shop->count].revenue) == 3) {
        shop->count++;

        if (shop->count >= shop->capacity) {
            shop->capacity *= 2;
            Game* temp = (Game *)realloc(shop->games, shop->capacity * sizeof(Game));
            if (!temp) {
                printf("Memory allocation error.\n");
                return;
            }
            shop->games = temp;
        }
    }
    printf("SUCCESS\n");
    fclose(file);
}

int main() 
{   
    GameShop shop;
    init_shop(&shop);

    while (1) {
        char command[20], name[20], filename[20];
        float price;
        int count;

        printf("");
        scanf("%s", command);

        if (strcmp(command, "A") == 0) {
            if (scanf("%19s %f", name, &price) != 2) {
                printf("\"A\" should be followed by exactly 2 arguments.\n");
                continue;
            }
            add(&shop, name, price);
        } else if (strcmp(command, "B") == 0) {
            if (scanf("%19s %d", name, &count) != 2) {
                printf("\"B\" should be followed by exactly 2 arguments.\n");
                continue;
            }
            buy(&shop, name, count);
        } else if (strcmp(command, "L") == 0) {
            print(&shop);
        } else if (strcmp(command, "W") == 0) {
            if (scanf("%19s", filename) != 1) {
                printf("\"W\" should be followed by exactly 1 argument.\n");
                continue;
            }
            save(&shop, filename);
        } else if (strcmp(command, "O") == 0) {
            if (scanf("%19s", filename) != 1) {
                printf("\"O\" should be followed by exactly 1 argument.\n");
                continue;
            }
            load(&shop, filename);
        } else if (strcmp(command, "Q") == 0) {
            printf("SUCCESS\n");
            free(shop.games);
            return 0;
        } else {
            printf("Invalid command %s.\n", command);
        }
    }
}
