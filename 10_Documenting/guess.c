#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

char *roman[] = {
"I",
"II",
"III",
"IV",
"V",
"VI",
"VII",
"VIII",
"IX",
"X",
"XI",
"XII",
"XIII",
"XIV",
"XV",
"XVI",
"XVII",
"XVIII",
"XIX",
"XX",
"XXI",
"XXII",
"XXIII",
"XXIV",
"XXV",
"XXVI",
"XXVII",
"XXVIII",
"XXIX",
"XXX",
"XXXI",
"XXXII",
"XXXIII",
"XXXIV",
"XXXV",
"XXXVI",
"XXXVII",
"XXXVIII",
"XXXIX",
"XL",
"XLI",
"XLII",
"XLIII",
"XLIV",
"XLV",
"XLVI",
"XLVII",
"XLVIII",
"XLIX",
"L",
"LI",
"LII",
"LIII",
"LIV",
"LV",
"LVI",
"LVII",
"LVIII",
"LIX",
"LX",
"LXI",
"LXII",
"LXIII",
"LXIV",
"LXV",
"LXVI",
"LXVII",
"LXVIII",
"LXIX",
"LXX",
"LXXI",
"LXXII",
"LXXIII",
"LXXIV",
"LXXV",
"LXXVI",
"LXXVII",
"LXXVIII",
"LXXIX",
"LXXX",
"LXXXI",
"LXXXII",
"LXXXIII",
"LXXXIV",
"LXXXV",
"LXXXVI",
"LXXXVII",
"LXXXVIII",
"LXXXIX",
"XC",
"XCI",
"XCII",
"XCIII",
"XCIV",
"XCV",
"XCVI",
"XCVII",
"XCVIII",
"XCIX",
"C"
};

char *arabic[] = {
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"10",
"11",
"12",
"13",
"14",
"15",
"16",
"17",
"18",
"19",
"20",
"21",
"22",
"23",
"24",
"25",
"26",
"27",
"28",
"29",
"30",
"31",
"32",
"33",
"34",
"35",
"36",
"37",
"38",
"39",
"40",
"41",
"42",
"43",
"44",
"45",
"46",
"47",
"48",
"49",
"50",
"51",
"52",
"53",
"54",
"55",
"56",
"57",
"58",
"59",
"60",
"61",
"62",
"63",
"64",
"65",
"66",
"67",
"68",
"69",
"70",
"71",
"72",
"73",
"74",
"75",
"76",
"77",
"78",
"79",
"80",
"81",
"82",
"83",
"84",
"85",
"86",
"87",
"88",
"89",
"90",
"91",
"92",
"93",
"94",
"95",
"96",
"97",
"98",
"99",
"100"
};

int romanToArabic(char *num) {
    for (int i = 0; i < 100; i++) {
        if (!strcmp(roman[i], num)) {
            return i + 1;
        } 
    }
}

char *arabicToRoman(int num) {
    arabic[num - 1];
}

int main(int argc, const char **argv) { 
    setlocale (LC_ALL, "");
    
    int use_roman = argc > 1 && !strcmp(argv[1], "-r");

    int show_help = argc > 1 && !strcmp(argv[1], "--help");

    if (show_help) {
        printf(_("This is a program that guesses a number by midpoint division.\nCommand line arguments:\n     empty - the program will simply work as a guessing program.\n    -r - will force the program to use roman letters instead.\n    --help - brings up this help page.\n\n"));

        return 0;
    }

    int show_version = argc > 1 && !strcmp(argv[1], "--version");

    if (show_version) {
        printf("v0.0.1\n");

        return 0;
    }

    char **outputTable = NULL;

    if (use_roman) {
        outputTable = roman;
    } else {
        outputTable = arabic;
    }

    //bindtextdomain ("guess", "/usr/share/locale/");
    // For testing
    bindtextdomain ("guess", "po");
    
    textdomain ("guess");

    printf(_("Think of a number between %s and %s.\n"), outputTable[0], outputTable[99]);   
    
    int bot = 1, top = 100;

    do {
        int center = (top + bot) / 2;

        printf(_("Is number greater than %s\n"), outputTable[center - 1]);

        const char answer[256];

        scanf("%s", &answer);
        
        int isYes = !strcmp(answer, _("yes"));
        int isNo = !strcmp(answer, _("no"));
    
        if (isYes) {
            bot = center + 1;
        } else if (isNo) {
            top = center;
        } else {
            printf(_("Incorrect answer, input either 'yes' or 'no'.\n"));
        }
    } while (bot != top);

    printf(_("Your number is %s\n"), outputTable[bot - 1]);

    return 0;
}
