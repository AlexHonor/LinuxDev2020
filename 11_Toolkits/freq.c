#include <glib.h>

#include <stdio.h>

gboolean StringComparator(gpointer key, gpointer value, gpointer data) {
    return !g_strcmp0(key, data);
}

void PrintKeyValue(gpointer key, gpointer map) {
    if (!key) return;

    printf("\"%s\" - %d\n", key, GPOINTER_TO_INT(g_hash_table_find(map, (GHRFunc)StringComparator, key)));
}

gint ListComparator(gconstpointer x, gconstpointer y, gpointer map) {
    return GPOINTER_TO_INT(g_hash_table_find(map, StringComparator, y)) - 
           GPOINTER_TO_INT(g_hash_table_find(map, StringComparator, x));
}

int main(int argc, const char **argv) {
    FILE *fp = NULL;
    
    if (argc > 1 && !(fp = fopen(argv[1], "r"))) {
        printf("Failed to open file \"%s\"\n", argv[1]);
        
        exit(-1);
    }

    if (!fp) {
        fp = stdin;
    }

    GHashTable *map = g_hash_table_new(g_str_hash, g_str_equal);
    
    char str[81];

    while (fgets(str, 81, fp)) {
        gchar **gline;
        gline = g_strsplit_set(str, " \n!\"#$%%&'()*+,-./:;?@[\\]^_`{|}~", -1);
        
        for (int i = 0; i < g_strv_length(gline); i++){
            gchar *word = g_ascii_strdown (gline[i], -1);
            
            if (!g_strcmp0(word, "")) continue;

            int *number = g_hash_table_lookup(map, word);
            
            g_hash_table_replace(map, word, GINT_TO_POINTER(number ? GPOINTER_TO_INT(number) + 1 : 1));
        }
        g_strfreev (gline);
    }

    GSList *list = g_hash_table_get_keys(map);

    list = g_slist_sort_with_data(list, (GCompareDataFunc)ListComparator, map);

    g_slist_foreach(list, PrintKeyValue, map);

    g_slist_free(list);
    g_hash_table_destroy(map);
    fclose(fp);

    return 0;
}