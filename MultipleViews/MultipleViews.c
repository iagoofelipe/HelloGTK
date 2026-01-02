#include <gtk/gtk.h>
#include <string.h>

GtkWidget *currentButton;

static void
change_page(const char* title, const char* child_name, GtkStack* stack, GtkWidget *button) {
    g_print("Trocando para a tela %s...\n", title);
    gtk_stack_set_visible_child_name(stack, child_name);

    if(currentButton != NULL) {
        gtk_widget_set_sensitive(currentButton, TRUE);
    }

    currentButton = button;
    gtk_widget_set_sensitive(button, FALSE);
}

// Callbacks
static void
on_btnSettings_clicked(GtkButton *button, gpointer user_data)
{
    change_page("Settings", "settingspage", GTK_STACK(user_data), GTK_WIDGET(button));
}

static void
on_btnHome_clicked(GtkButton *button, gpointer user_data)
{
    change_page("Home", "homepage", GTK_STACK(user_data), GTK_WIDGET(button));
}

static void
activate(GtkApplication *app, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget 
        *window,
        *btnHome, *btnSettings,
        *stack;

    builder = gtk_builder_new_from_file("multipleviews.ui");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    btnHome = GTK_WIDGET(gtk_builder_get_object(builder, "btnHome"));
    btnSettings = GTK_WIDGET(gtk_builder_get_object(builder, "btnSettings"));
    stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack"));

    gtk_window_set_application(GTK_WINDOW(window), app);

    // conectando eventos
    g_signal_connect(btnHome, "clicked", G_CALLBACK(on_btnHome_clicked), stack);
    g_signal_connect(btnSettings, "clicked", G_CALLBACK(on_btnSettings_clicked), stack);

    // definindo botão da tela atual
    const char* intialPageName = gtk_stack_get_visible_child_name(GTK_STACK(stack));
    if(strcmp(intialPageName, "settingpage") == 0) currentButton = btnHome;
    else if(strcmp(intialPageName, "homepage") == 0) currentButton = btnHome;
    else currentButton = NULL;

    if(currentButton != NULL) {
        gtk_widget_set_sensitive(currentButton, FALSE);
    }

    gtk_window_present(GTK_WINDOW(window));
    g_object_unref(builder);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("dev.iagocarvalho.MultipleViews", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    currentButton = NULL;
    g_object_unref(app);

    return status;
}