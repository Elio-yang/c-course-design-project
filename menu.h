/*
 * @author Wang Jie
 * @update Yang Yang
 */

#ifndef CDESIGN_MENU_H
#define CDESIGN_MENU_H
#include <stdbool.h>
#include<stdio.h>
#define WIN
//if you want to compile under WIN10
#ifdef UNIX
#include "tools/print_color.h"
#endif

void print_menu();
void print_menu()
{
#ifdef UNIX
        printf( REVERSE L_BLUE  "***************************************************************************************\n"NONE
                REVERSE L_BLUE  "*                                      MENU                                           *\n"NONE
                REVERSE L_BLUE  "***************************************************************************************\n"NONE
                REVERSE WHITE"I. Wine                                                                                \n"
                "         1. Cointreau                       25.00 RMB/cup                              \n"
                "         2. Martini                         20.00 RMB/cup                              \n"
                "         3. Baileys                         25.00 Yuan/cup                             \n"
                "         4. Malibu                          20.00 Yuan/cup                             \n"
                "         5. Jack Danny                      35.00 Yuan/cup                             \n"
                "         6. BKD                             25.00 Yuan/cup                             \n"
                "         7. Gordon Gold                     20.00 Yuan/cup                             \n"
                "         8. Black                           30.00 Yuan/cup                             \n"
                "         9. Swedish Vodka                   25.00 Yuan/cup                             \n"
                "         10.Edinger                         35.00 Yuan/cup                             \n"
                "         11.Corona                          20.00 Yuan/cup                             \n"
                "         12.Heineken                        20.00 Yuan/cup                             \n"
                "         13.Carlsberg                       18.00 Yuan/cup                             \n"
                "         14.Qingdao                         15.00 Yuan/cup                             \n"
                "         15.Bosss                           20.00 Yuan/cup                             \n"
                "         16.Long Island Iced Tea            30.00 Yuan/cup                             \n"
                "         17.Gin and Tonic                   25.00 Yuan/cup                             \n"
                "         18.Beauty in Pink                  30.00 Yuan/cup                             \n"
                "         19.Black Russia                    35.00 Yuan/cup                             \n"
                "         20.Blue Hawaii                     33.00 Yuan/cup                             \n"
                "II.Snacks                                                                              \n"
                "         1. Tuna Bongo                      15.00 Yuan                                 \n"
                "         2. Pears in Red Wine               25.00 Yuan                                 \n"
                "         3. Roasted Chicken Wings           20.00 Yuan                                 \n"
                "         4. Garlic Minced Charmer           10.00 Yuan                                 \n"
                "         5. Vegetable cheese balls          15.00 Yuan                                 \n"
                "         6. Popcorn                         25.00 Yuan                                 \n"
                "         7. Shrimp pizza                    45.00 Yuan                                 \n"
                "         8. Sausage Pizza                   38.00 Yuan                                 \n"
                "         9. Vegetable cheese balls          15.00 Yuan                                 \n"
                "         10.Crispy Spicy Potato Cart        18.00 Yuan                                 \n"
                "         11.Coffee ice cream                15.00 Yuan                                 \n"
                "         12.Banana boat                     25.00 Yuan                                 \n"
                "         13.Banana milkshake                16.00 Yuan                                 \n"
                "III. Tea                                                                               \n"
                "         1. Lipton Black Tea                45.00 Yuan/pot                             \n"
                "         2. Rose milk tea                   58.00 Yuan/pot                             \n"
                "         3. Iced lemon tea                  15.00 Yuan/cup                             \n"
                "         4. West Lake Longjing              20.00 Yuan/cup                             \n"
                "         5. Biluochun                       25.00 Yuan/cup                             \n"
                "         6. Tie Guan Yin                    25.00 Yuan/cup                             \n"
                "IV. Drinks.                                                                            \n"
                "         1. Fresh milk                      25.00 Yuan                                 \n"
                "         2. Dried ginger water              16.00 Yuan                                 \n"
                "         3. pineapple juice                 27.00 Yuan                                 \n"
                "         4. Grapefruit juice                34.00 Yuan                                 \n"
                "         5. Orange Juice                    26.00 Yuan                                 \n"
                "         6. Mineral water                   8.00  Yuan                                 \n"
                "         7. Coke                            12.00 Yuan                                 \n"
                "         8. Sprite                          12.00 Yuan                                 \n"
                "         9. Mineral water                   12.00 Yuan                                 \n"NONE
                );
#endif
#ifdef WIN
        printf( ""
                "***************************************************************************************\n"
                "*                                      MENU                                           *\n"
                "***************************************************************************************\n"
                "I. Wine                                                                                \n"
                "         1. Cointreau                       25.00 RMB/cup                              \n"
                "         2. Martini                         20.00 RMB/cup                              \n"
                "         3. Baileys                         25.00 Yuan/cup                             \n"
                "         4. Malibu                          20.00 Yuan/cup                             \n"
                "         5. Jack Danny                      35.00 Yuan/cup                             \n"
                "         6. BKD                             25.00 Yuan/cup                             \n"
                "         7. Gordon Gold                     20.00 Yuan/cup                             \n"
                "         8. Black                           30.00 Yuan/cup                             \n"
                "         9. Swedish Vodka                   25.00 Yuan/cup                             \n"
                "         10.Edinger                         35.00 Yuan/cup                             \n"
                "         11.Corona                          20.00 Yuan/cup                             \n"
                "         12.Heineken                        20.00 Yuan/cup                             \n"
                "         13.Carlsberg                       18.00 Yuan/cup                             \n"
                "         14.Qingdao                         15.00 Yuan/cup                             \n"
                "         15.Bosss                           20.00 Yuan/cup                             \n"
                "         16.Long Island Iced Tea            30.00 Yuan/cup                             \n"
                "         17.Gin and Tonic                   25.00 Yuan/cup                             \n"
                "         18.Beauty in Pink                  30.00 Yuan/cup                             \n"
                "         19.Black Russia                    35.00 Yuan/cup                             \n"
                "         20.Blue Hawaii                     33.00 Yuan/cup                             \n"
                "II.Snacks                                                                              \n"
                "         1. Tuna Bongo                      15.00 Yuan                                 \n"
                "         2. Pears in Red Wine               25.00 Yuan                                 \n"
                "         3. Roasted Chicken Wings           20.00 Yuan                                 \n"
                "         4. Garlic Minced Charmer           10.00 Yuan                                 \n"
                "         5. Vegetable cheese balls          15.00 Yuan                                 \n"
                "         6. Popcorn                         25.00 Yuan                                 \n"
                "         7. Shrimp pizza                    45.00 Yuan                                 \n"
                "         8. Sausage Pizza                   38.00 Yuan                                 \n"
                "         9. Vegetable cheese balls          15.00 Yuan                                 \n"
                "         10.Crispy Spicy Potato Cart        18.00 Yuan                                 \n"
                "         11.Coffee ice cream                15.00 Yuan                                 \n"
                "         12.Banana boat                     25.00 Yuan                                 \n"
                "         13.Banana milkshake                16.00 Yuan                                 \n"
                "III. Tea                                                                               \n"
                "         1. Lipton Black Tea                45.00 Yuan/pot                             \n"
                "         2. Rose milk tea                   58.00 Yuan/pot                             \n"
                "         3. Iced lemon tea                  15.00 Yuan/cup                             \n"
                "         4. West Lake Longjing              20.00 Yuan/cup                             \n"
                "         5. Biluochun                       25.00 Yuan/cup                             \n"
                "         6. Tie Guan Yin                    25.00 Yuan/cup                             \n"
                "IV. Drinks.                                                                            \n"
                "         1. Fresh milk                      25.00 Yuan                                 \n"
                "         2. Dried ginger water              16.00 Yuan                                 \n"
                "         3. pineapple juice                 27.00 Yuan                                 \n"
                "         4. Grapefruit juice                34.00 Yuan                                 \n"
                "         5. Orange Juice                    26.00 Yuan                                 \n"
                "         6. Mineral water                   8.00  Yuan                                 \n"
                "         7. Coke                            12.00 Yuan                                 \n"
                "         8. Sprite                          12.00 Yuan                                 \n"
                "         9. Mineral water                   12.00 Yuan                                 \n"
        );
#endif
}
#endif //CDESIGN_MENU_H
