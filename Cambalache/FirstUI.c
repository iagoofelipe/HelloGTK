#include <gtk/gtk.h>

// Função de callback para o botão
static void
on_button_clicked(GtkButton *button, gpointer user_data)
{
    // Recuperamos o objeto label que passamos no g_signal_connect
    GtkLabel *label = GTK_LABEL(user_data);
    gtk_label_set_label(label, "Button clicked!");
}

static void
activate(GtkApplication *app, gpointer user_data)
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *label;

    // 1. Carrega o arquivo UI gerado pelo Cambalache
    builder = gtk_builder_new_from_file("firstui.ui");

    // 2. Obtém os objetos pelos IDs que você definiu no Cambalache
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));

    // 3. Configura a janela principal
    gtk_window_set_application(GTK_WINDOW(window), app);

    // 4. Conecta os sinais (eventos)
    // Passamos a 'label' como dado do usuário para que a função possa alterá-la
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), label);

    // 5. Exibe a janela
    gtk_window_present(GTK_WINDOW(window));

    // Como os widgets já foram criados, podemos liberar o builder
    g_object_unref(builder);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.exemplo.Cambalache", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}