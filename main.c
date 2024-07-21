
#include <gtk/gtk.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define NUMS 10

GtkWidget *button;
GtkWidget *entries[NUMS];
int counter[NUMS];

void swap(GtkWidget *widget, gpointer data)
{
    char str[80];
    for (int i = 0; i < NUMS; i += 2)
    {
        sprintf(str, "%s", (char *)gtk_entry_get_text(GTK_ENTRY(entries[i])));
        char *temp = (char *)gtk_entry_get_text(GTK_ENTRY(entries[i + 1]));
        gtk_entry_set_text(GTK_ENTRY(entries[i]), temp);
        gtk_entry_set_text(GTK_ENTRY(entries[i + 1]), str);
    }
}

void callback_edited(GtkWidget *widget, gpointer data)
{
    counter[(int)data] = 1;
    char *text = (char *)gtk_entry_get_text(GTK_ENTRY(widget));
    if (strlen(text) == 0) {
        counter[(int)data] = 0;        
    }
    for (int i = 0; i < strlen(text); i++)
    {
        if (isdigit(text[i]) || (i == 0 && text[i] == '-'))
        {
            continue;
        }

        gtk_entry_set_text(GTK_ENTRY(widget), "");
        counter[(int)data] = 0;
        break;
    }

    gtk_widget_set_sensitive (button, TRUE);
    for(int i = 0; i < NUMS; i++) {
        if (counter[i] == 0) {
            gtk_widget_set_sensitive (button, FALSE);
            break;
        }
    }
}

void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    char label_text[80];
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *table;
    GtkWidget *entry;

    for (int i = 0; i < NUMS; i++) {
        counter[i] = 0;
    }

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(window, "destroy",
                     G_CALLBACK(destroy), NULL);
    /* Let's set the border width of the window to 20.
     * You may play with the value and see the
     * difference. */
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    table = gtk_table_new(5, 4, FALSE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 5);
    gtk_table_set_col_spacings(GTK_TABLE(table), 5);
    gtk_container_add(GTK_CONTAINER(vbox), table);

    for (int i = 0; i < NUMS / 2; i++)
    {
        sprintf(label_text, "Num %d:", 2 * i + 1);
        label = gtk_label_new(label_text);
        gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, i, i + 1);
        gtk_widget_show(label);

        entry = gtk_entry_new_with_max_length(11);
        gtk_entry_set_width_chars(GTK_ENTRY(entry), 11);
        g_signal_connect(G_OBJECT(entry), "changed", G_CALLBACK(callback_edited), (void *)(2 * i));
        gtk_table_attach_defaults(GTK_TABLE(table), entry, 1, 2, i, i + 1);
        gtk_widget_show(entry);
        entries[2 * i] = entry;

        sprintf(label_text, "Num %d:", 2 * i + 2);
        label = gtk_label_new(label_text);
        gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
        gtk_table_attach_defaults(GTK_TABLE(table), label, 2, 3, i, i + 1);
        gtk_widget_show(label);

        entry = gtk_entry_new_with_max_length(11);
        gtk_entry_set_width_chars(GTK_ENTRY(entry), 11);
        g_signal_connect(G_OBJECT(entry), "changed", G_CALLBACK(callback_edited), (void *)(2 * i + 1));
        gtk_table_attach_defaults(GTK_TABLE(table), entry, 3, 4, i, i + 1);
        gtk_widget_show(entry);
        entries[2 * i + 1] = entry;
    }

    button = gtk_button_new_with_label("Swap");
    gtk_widget_set_sensitive (button, FALSE);

    g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(swap), NULL);
    gtk_container_add(GTK_CONTAINER(vbox), button);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
