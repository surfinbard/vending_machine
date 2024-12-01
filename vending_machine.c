#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "utils.c"

char *selection = "000";
float amount_needed = 0;
float change_needed = 0;
float inserted_money = 0;
int coin_quantity[] = {10, 20, 20};
bool enough_money = false;
float product_price = 0;
float balance = 50;
int product_quantities[] = {5, 5, 5, 5, 5, 5, 5, 5};
char *product_names[] = {"Coke",           "Pepsi",       "Fanta",
                         "Sprite",         "Cup Noodles", "Top Ramen",
                         "Buldak noodles", "Kinder Bueno"};
int product_sales[] = {0, 0, 0, 0, 0, 0, 0, 0};
float product_prices[] = {3.5, 3, 1.5, 2, 1, 0.5, 4.5, 4};
int pieces[3] = {0, 0, 0};

void q0_q1(int selection) {
    printf("chegay");
    // produto escolhido
    // checar se available
    //  se sim, vai p insert money
    // se nao, productnotavailable
}
// q0 -> q1
int item_selection() {
    int selection_type;
    int selection;

    type_effect("\nWelcome!\n");
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
                int random_selection = get_random_between(0, 7);
                selection = random_selection;
                amount_needed = product_prices[random_selection];
                type_effect("You've chosen random selection.\n");
                printf("Selected %d: %s", selection, product_names[selection]);

                break;
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
                            break;
                        }
                    }
                }
            } else
                printf("Invalid input. Please enter 0 or 1: ");
        }
    }
    q0_q1(selection);
    return 0;
}

// q1 -> q0
void product_not_available() {
    printf("Selection not available.");
    selection = "000";
    amount_needed = 0;
}

// q1 -> q2
// q2 -> q2
// q2 -> q3
// q1 -> q3
/* void insert_money() {
    float amount;
    scanf("%f", amount) inserted_money += amount;
    amount_needed -= amount;
    if (amount_needed <= 0) enough_money = true;
} */

// q3 -> q4'
// q3 -> q5'
bool calculate_change() { return ((inserted_money - product_price) > 0); }

// q4 -> q0
// q9 -> q0
void drop_product() {
    int product_index =
        (selection[0] * pow(2, 2) + selection[1] * 2 + selection[2]) - 1;
    product_quantities[product_index] -= 1;
    product_sales[product_index] += 1;
    inserted_money = 0;
    selection = "000";
    amount_needed = 0;
}

// q5 -> q6
// q5 -> q7
bool check_balance() { return ((balance - change_needed) >= 0); }

// q6 -> q0
// q10 -> q0
void refund() {
    printf("Refund in order. Please wait...\n");
    printf("OUTPUT: inserted money (%f)", inserted_money);
    inserted_money = 0;
    selection = "000";
    amount_needed = 0;

    item_selection();
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
// q8 -> q9
void drop_change() {
    printf("OUTPUT: %d $2, %d $1, %d $0.5", pieces[0], pieces[1], pieces[2]);
    coin_quantity[0] -= pieces[0];
    coin_quantity[1] -= pieces[1];
    coin_quantity[2] -= pieces[2];
    balance -= (2 * pieces[0] + pieces[1] + 0.5 * pieces[2]);

    drop_product();
}

void change_required() {
    int option = -1;
    int change_needed_integer = change_needed * 10;
    switch (change_needed_integer) {
        case 45:
            int change_options_45[7][3] = {{2, 0, 1}, {1, 2, 1}, {0, 4, 1},
                                           {0, 3, 3}, {0, 2, 5}, {0, 1, 7},
                                           {0, 0, 9}};
            option = check_if_coins_available(7, change_options_45);
            if (option >= 0) {
                memcpy(pieces, change_options_45[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 40:
            int change_options_40[7][3] = {{2, 0, 0}, {1, 2, 0}, {0, 4, 0},
                                           {0, 3, 2}, {0, 2, 4}, {0, 1, 6},
                                           {0, 0, 8}};
            option = check_if_coins_available(7, change_options_40);
            if (option >= 0) {
                memcpy(pieces, change_options_40[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 35:
            int change_options_35[5][3] = {
                {1, 1, 1}, {0, 3, 1}, {0, 2, 3}, {0, 1, 5}, {0, 0, 7}};

            option = check_if_coins_available(5, change_options_35);
            if (option >= 0) {
                memcpy(pieces, change_options_35[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 30:
            int change_options_30[5][3] = {
                {1, 1, 0}, {0, 3, 0}, {0, 2, 2}, {0, 1, 4}, {0, 0, 6}};

            option = check_if_coins_available(5, change_options_30);
            if (option >= 0) {
                memcpy(pieces, change_options_30[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 25:
            int change_options_25[4][3] = {
                {1, 0, 1}, {0, 2, 1}, {0, 1, 3}, {0, 0, 5}};

            option = check_if_coins_available(4, change_options_25);
            if (option >= 0) {
                memcpy(pieces, change_options_25[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 20:
            int change_options_20[4][3] = {
                {1, 0, 0}, {0, 2, 0}, {0, 1, 2}, {0, 0, 4}};

            option = check_if_coins_available(4, change_options_20);
            if (option >= 0) {
                memcpy(pieces, change_options_20[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 15:
            int change_options_15[2][3] = {{0, 1, 1}, {0, 0, 3}};

            option = check_if_coins_available(2, change_options_15);
            if (option >= 0) {
                memcpy(pieces, change_options_15[option], sizeof(pieces));
                drop_change();
            }
            break;
        case 10:
            int change_options_10[2][3] = {{0, 1, 0}, {0, 0, 2}};

            option = check_if_coins_available(2, change_options_10);
            if (option >= 0) {
                memcpy(pieces, change_options_10[option], sizeof(pieces));
                drop_change();
            }
            break;
        default:
            int change_options_05[1][3] = {{0, 0, 1}};

            option = check_if_coins_available(1, change_options_05);
            if (option >= 0) {
                memcpy(pieces, change_options_05[option], sizeof(pieces));
                drop_change();
            }
            break;
    }
}
int main() {
    item_selection();
    return 0;
}