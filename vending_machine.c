#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "utils.c"

int item_selection();
void product_not_available();
void insert_money();
int check_if_coins_available(int length, int options[][3]);
void change_required();
void refund();
void drop_change();
void drop_product();

int selection = 0;
float change_needed = 0;
float inserted_money = 0;
int coin_quantity[] = {10, 20, 20};
float product_price = 0;
float balance = 50;
int product_quantities[] = {5, 5, 5, 5, 5, 5, 5, 5};
char *product_names[] = {"COKE",           "PEPSI",       "FANTA",
                         "SPRITE",         "CUP NOODLES", "TOP RAMEN",
                         "BULDAK NOODLES", "KINDER BUENO"};
int product_sales[] = {0, 0, 0, 0, 0, 0, 0, 0};
float product_prices[] = {3.5, 3, 1.5, 2, 1, 0.5, 4.5, 4};
int pieces[3] = {0, 0, 0};

// q0 -> q1
int item_selection() {
    int selection_type;
    int selection;

    type_effect("\n-----------WELCOME----------\n");
    type_effect("\nAVAILABLE ITEMS\n");
    type_effect("0. Coke             ($3.50)\n");
    type_effect("1. Pepsi            ($3)\n");
    type_effect("2. Fanta            ($1.5)\n");
    type_effect("3. Sprite           ($2)\n");
    type_effect("4. Cup Noodles      ($1)\n");
    type_effect("5. Top Ramen        ($0.5)\n");
    type_effect("6. Buldak noodles   ($4.5)\n");
    type_effect("7. Kinder Bueno     ($4)\n");
    type_effect(
        "\nWould you like to select an item or have it selected at random for "
        "you?");
    printf("\nEnter 0 for random selection and 1 for manual selection: ");

    while (1) {
        if (scanf("%d", &selection_type) != 1) {
            printf("Invalid input. Please enter 0 or 1: ");
            while (getchar() != '\n') {
                continue;
            }
        } else {
            if (selection_type == 0) {
                selection = get_random_between(0, 7);

                product_price = product_prices[selection];
                printf("\nYou've chosen random selection.\n");
                printf("Selected %d: %s ($%.2f)\n", selection,
                       product_names[selection], product_prices[selection]);

                if (product_quantities[selection] > 0) {
                    product_price = product_prices[selection];
                    insert_money();
                } else
                    product_not_available();

                return 0;
            } else if (selection_type == 1) {
                type_effect("Enter product code: ");

                while (1) {
                    if (scanf("%d", &selection) != 1) {
                        printf("Invalid input. Please enter a valid code: ");
                        while (getchar() != '\n') {
                            continue;
                        }
                    } else {
                        if (selection < 0 || selection > 7)
                            printf(
                                "Invalid input. Please enter a valid code: ");
                        else {
                            printf("Selected %d: %s ($%.2f)\n", selection,
                                   product_names[selection],
                                   product_prices[selection]);
                            if (product_quantities[selection] == 0)
                                product_not_available();
                            else {
                                product_price = product_prices[selection];
                                insert_money();
                            }
                            return 0;
                        }
                    }
                }
            } else
                printf("Invalid input. Please enter 0 or 1: ");
        }
    }
    return -1;
}

// q1 -> q0
void product_not_available() {
    printf("Selection not available.");
    selection = 0;
    product_price = 0;
}

// q1 -> q2
// q2 -> q2
// q2 -> q3
// q1 -> q3
void insert_money() {
    float amount;
    printf("\nINSERT MONEY\n");

    while (1) {
        printf("Amount inserted: $%.2f / $%.2f\n", inserted_money,
               product_price);
        if (scanf("%f", &amount) != 1) {
            printf("Invalid amount. Please enter a valid amount: ");
            while (getchar() != '\n') {
                continue;
            }
        } else {
            if (amount != 5 && amount != 2 && amount != 1 && amount != 0.5) {
                printf("\nInvalid input. Accepted pieces: $5 $2 $1 $0.50\n");
                printf("RETURNED $%.2f.\n\n", amount);
            }

            else {
                inserted_money += amount;

                if (inserted_money >= product_price) {
                    // q3 -> q4
                    if (inserted_money > product_price) {
                        change_needed = inserted_money - product_price;
                        printf("Amount inserted: $%.2f / $%.2f\n",
                               inserted_money, product_price);
                        sleep(1);
                        change_required();
                    }
                    // q3 -> q5
                    else
                        drop_product();
                }
            }
        }
    }
}

// q3 -> q5
int check_if_coins_available(int length, int options[][3]) {
    for (int i = 0; i < length; i++) {
        if (coin_quantity[0] >= options[i][0] &&
            coin_quantity[1] >= options[i][1] &&
            coin_quantity[2] >= options[i][2])
            return i;
    }
    return -1;
}

// q5 -> q6
// q5 -> q7
void change_required() {
    int option = -1;

    // q5 -> q6
    if ((balance - change_needed) < 0) {
        printf("\nNo change available. Please insert exact amount.\n");
        refund();
        return;
    }

    // q5 -> q7
    int change_needed_integer = change_needed * 100;
    switch (change_needed_integer) {
        case 450:
            int change_options_450[7][3] = {{2, 0, 1}, {1, 2, 1}, {0, 4, 1},
                                            {0, 3, 3}, {0, 2, 5}, {0, 1, 7},
                                            {0, 0, 9}};
            option = check_if_coins_available(7, change_options_450);
            if (option >= 0) {
                memcpy(pieces, change_options_450[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 400:
            int change_options_400[7][3] = {{2, 0, 0}, {1, 2, 0}, {0, 4, 0},
                                            {0, 3, 2}, {0, 2, 4}, {0, 1, 6},
                                            {0, 0, 8}};
            option = check_if_coins_available(7, change_options_400);
            if (option >= 0) {
                memcpy(pieces, change_options_400[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 350:
            int change_options_350[5][3] = {
                {1, 1, 1}, {0, 3, 1}, {0, 2, 3}, {0, 1, 5}, {0, 0, 7}};

            option = check_if_coins_available(5, change_options_350);
            if (option >= 0) {
                memcpy(pieces, change_options_350[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 300:
            int change_options_300[5][3] = {
                {1, 1, 0}, {0, 3, 0}, {0, 2, 2}, {0, 1, 4}, {0, 0, 6}};

            option = check_if_coins_available(5, change_options_300);
            if (option >= 0) {
                memcpy(pieces, change_options_300[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 250:
            int change_options_250[4][3] = {
                {1, 0, 1}, {0, 2, 1}, {0, 1, 3}, {0, 0, 5}};

            option = check_if_coins_available(4, change_options_250);
            if (option >= 0) {
                memcpy(pieces, change_options_250[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 200:
            int change_options_200[4][3] = {
                {1, 0, 0}, {0, 2, 0}, {0, 1, 2}, {0, 0, 4}};

            option = check_if_coins_available(4, change_options_200);
            if (option >= 0) {
                memcpy(pieces, change_options_200[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 150:
            int change_options_150[2][3] = {{0, 1, 1}, {0, 0, 3}};

            option = check_if_coins_available(2, change_options_150);
            if (option >= 0) {
                memcpy(pieces, change_options_150[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 100:
            int change_options_100[2][3] = {{0, 1, 0}, {0, 0, 2}};

            option = check_if_coins_available(2, change_options_100);
            if (option >= 0) {
                memcpy(pieces, change_options_100[option], sizeof(pieces));
                drop_change();
            }
            break;
        default:
            int change_options_050[1][3] = {{0, 0, 1}};

            option = check_if_coins_available(1, change_options_050);
            if (option >= 0) {
                memcpy(pieces, change_options_050[option], sizeof(pieces));
                drop_change();
            }
            break;
    }
}

// q6 -> q0
// q10 -> q0
void refund() {
    printf("Refund in order. Please wait...\n");
    printf("REFUNDING %.2f\n\n", inserted_money);
    inserted_money = 0;
    selection = 0;
    product_price = 0;

    item_selection();
}

// q8 -> q9
void drop_change() {
    char message[100] = "RETURNING CHANGE: ";
    int first = 1;

    if (pieces[0] > 0) {
        sprintf(message + strlen(message), "%s%d x $2", first ? "" : ", ",
                pieces[0]);
        first = 0;
    }
    if (pieces[1] > 0) {
        sprintf(message + strlen(message), "%s%d x $1", first ? "" : ", ",
                pieces[1]);
        first = 0;
    }
    if (pieces[2] > 0) {
        sprintf(message + strlen(message), "%s%d x $0.5", first ? "" : ", ",
                pieces[2]);
    }

    printf("\n%s\n", message);

    coin_quantity[0] -= pieces[0];
    coin_quantity[1] -= pieces[1];
    coin_quantity[2] -= pieces[2];
    balance -= (2 * pieces[0] + pieces[1] + 0.5 * pieces[2]);
    sleep(1);
    drop_product();
}

// q4 -> q0
// q9 -> q0
void drop_product() {
    printf("ENJOY YOUR %s\n\n", product_names[selection]);
    printf("----><----THANK YOU----><----\n");
    product_quantities[selection] -= 1;
    product_sales[selection] += 1;
    inserted_money = 0;
    selection = 0;
    product_price = 0;
    sleep(2);
    item_selection();
}

int main() {
    item_selection();
    return 0;
}