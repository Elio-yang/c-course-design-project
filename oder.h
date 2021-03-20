//
// Created by elio on 2021/3/20.
//

#ifndef CDESIGN_ODER_H
#define CDESIGN_ODER_H


typedef struct drink{
        char drink_name[64];
        /* for single cup */
        char cup_price[5];
        /* for a whole bottle if necessary */
        bool bot_allowed;
        char bot_price[10];

        /* personal design if allowed:
         * ice
         * temperature
         * sugar
         * cup size
         *
         * true for allowed
         * */
        bool ice_allowed;
        bool t_allowed;
        bool sugar_allowed;
        bool cup_size_allowed;

        struct drink *next;
} Drink;


#endif //CDESIGN_ODER_H
