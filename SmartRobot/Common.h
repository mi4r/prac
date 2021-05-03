//
// Created by mi4r on 30.03.2021.
//

#ifndef PROJECTSMARTROBOT_COMMON_H
#define PROJECTSMARTROBOT_COMMON_H

enum TypeLexem {separator,assign, digit, string,
    varName, label, function, keyWord};

enum TypeState {s_start, s_digit, s_string, s_identifier,
    s_keyWord, s_assign, s_error};

enum TypeError {start_unknown, digit_letter, digit_unknown, id_unknown,
    keyWord_number, keyWord_unknown};

enum TypeReadiness {ready, unready, eof, err};



#endif //PROJECTSMARTROBOT_COMMON_H
