#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main() {
    setlocale (LC_ALL, "");
    
    //bindtextdomain ("guess", "/usr/share/locale/");
    // For testing
    bindtextdomain ("guess", "po");
    
    textdomain ("guess");

    printf(_("Think of a number between 1 and 100.\n"));   

    int bot = 1, top = 100;

    do {
        int center = (top + bot) / 2;

        printf(_("Is number greater than %d\n"), center);

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

    printf(_("Your number is %d\n"), bot);

    return 0;
}
