#include <gtk/gtk.h>

// Função chamada quando o botão "Calcular" é pressionado
void on_calculate_button_clicked(GtkWidget *widget, gpointer data) {
    // Aqui você pode adicionar o código para processar a função e resolver a equação
    g_print("Botão calcular pressionado!\n");
}

// Função para aplicar o CSS aos widgets
void apply_css(GtkWidget *widget) {
    // Cria um provedor de CSS
    GtkCssProvider *css_provider = gtk_css_provider_new();
    
    // Carrega o CSS para os botões, entradas e combo box
    gtk_css_provider_load_from_data(css_provider, 
        "button {"
        "   background-color: #007BFF;" // Cor de fundo do botão
        "   color: white;" // Cor do texto do botão
        "   padding: 10px 20px;" // Espaçamento interno do botão
        "   text-align: center;" // Alinhamento do texto
        "   text-decoration: none;" // Remove decoração do texto
        "   display: inline-block;" // Exibe o botão como um bloco inline
        "   font-size: 16px;" // Tamanho da fonte
        "   margin: 8px 0;" // Margem do botão
        "   cursor: pointer;" // Muda o cursor ao passar o mouse
        "   border: none;" // Remove borda padrão
        "   border-radius: 8px;" // Borda arredondada
        "   transition: background-color 0.3s;" // Transição suave ao mudar de cor
        "   box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);" // Sombra do botão
        "}"
        "button:hover {"
        "   background-color: #0056b3;" // Cor do botão ao passar o mouse
        "}"
        "entry {"
        "   padding: 10px;" // Espaçamento interno das entradas
        "   border: 2px solid #007BFF;" // Borda azul nas entradas
        "   border-radius: 5px;" // Borda arredondada das entradas
        "   font-size: 14px;" // Tamanho da fonte das entradas
        "}"
        "label {"
        "   font-size: 16px;" // Tamanho da fonte dos rótulos
        "   color: #333;" // Cor do texto dos rótulos
        "   font-family: Arial, sans-serif;" // Fonte dos rótulos
        "   margin-right: 10px;" // Margem à direita dos rótulos
        "}"
        "button:focus {"
        "   outline: none;" // Remove a borda de foco padrão
        "}"
        "entry:focus {"
        "   border-color: #0056b3;" // Cor da borda ao focar
        "}"
        "combo box {"
        "   padding: 10px;" // Espaçamento interno do combo box
        "   border: 2px solid #007BFF;" // Borda azul
        "   border-radius: 5px;" // Borda arredondada
        "   background-color: white;" // Cor de fundo do combo box
        "   font-size: 14px;" // Tamanho da fonte
        "   color: #333;" // Cor do texto
        "}"
        "combo box:active {"
        "   border-color: #0056b3;" // Cor da borda quando ativo
        "}"
        "combo box:hover {"
        "   border-color: #0056b3;" // Cor da borda ao passar o mouse
        "}"
        "body {"
        "   font-family: Arial, sans-serif;" // Fonte padrão do corpo
        "   background-color: #f8f9fa;" // Cor de fundo da janela
        "}", 
        -1, NULL);
    
    // Adiciona o provedor de estilo para a tela padrão
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

int main(int argc, char *argv[]) {
    GtkWidget *window; // Janela principal
    GtkWidget *grid; // Grid para organizar os widgets
    GtkWidget *function_entry; // Entrada para a função
    GtkWidget *derivative_entry; // Entrada para a derivada
    GtkWidget *interval_entry; // Entrada para o intervalo
    GtkWidget *tolerance_entry; // Entrada para a tolerância
    GtkWidget *max_iterations_entry; // Entrada para o número máximo de iterações
    GtkWidget *calculate_button; // Botão de calcular
    GtkWidget *method_box; // Caixa para os botões de método

    // Inicializa o GTK
    gtk_init(&argc, &argv);

    // Cria a nova janela
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Resolução de Equações Não Lineares");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800); // Tamanho dobrado

    // Conecta o evento de fechamento da janela
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Cria um grid para organizar os widgets
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Cria entradas de texto com rótulos
    GtkWidget *function_label = gtk_label_new("Função:");
    function_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(function_entry), "ex: x^2 - 4");
    gtk_grid_attach(GTK_GRID(grid), function_label, 0, 0, 1, 1); // Adiciona rótulo ao grid
    gtk_grid_attach(GTK_GRID(grid), function_entry, 1, 0, 1, 1); // Adiciona a entrada de função ao grid

    GtkWidget *derivative_label = gtk_label_new("Derivada:");
    derivative_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(derivative_entry), "ex: 2x");
    gtk_grid_attach(GTK_GRID(grid), derivative_label, 0, 1, 1, 1); // Adiciona rótulo ao grid
    gtk_grid_attach(GTK_GRID(grid), derivative_entry, 1, 1, 1, 1); // Adiciona a entrada de derivada ao grid

    GtkWidget *interval_label = gtk_label_new("Intervalo:");
    interval_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(interval_entry), "ex: 1,3");
    gtk_grid_attach(GTK_GRID(grid), interval_label, 0, 2, 1, 1); // Adiciona rótulo ao grid
    gtk_grid_attach(GTK_GRID(grid), interval_entry, 1, 2, 1, 1); // Adiciona a entrada de intervalo ao grid

    GtkWidget *tolerance_label = gtk_label_new("Tolerância:");
    tolerance_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(tolerance_entry), "ex: 0.001");
    gtk_grid_attach(GTK_GRID(grid), tolerance_label, 0, 3, 1, 1); // Adiciona rótulo ao grid
    gtk_grid_attach(GTK_GRID(grid), tolerance_entry, 1, 3, 1, 1); // Adiciona a entrada de tolerância ao grid
    
    GtkWidget *max_iterations_label = gtk_label_new("Máx. iterações:");
    max_iterations_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(max_iterations_entry), "ex: 100");
    gtk_grid_attach(GTK_GRID(grid), max_iterations_label, 0, 4, 1, 1); // Adiciona rótulo ao grid
    gtk_grid_attach(GTK_GRID(grid), max_iterations_entry, 1, 4, 1, 1); // Adiciona a entrada de iterações ao grid

    // Cria uma caixa vertical para os botões de método
    method_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // Cria uma caixa vertical com espaçamento de 5
    gtk_grid_attach(GTK_GRID(grid), method_box, 0, 5, 2, 1); // Adiciona a caixa ao grid

    // Cria os botões de rádio para seleção do método
    GtkWidget *bisection_button = gtk_radio_button_new_with_label(NULL, "Método de Bissecção");
    gtk_box_pack_start(GTK_BOX(method_box), bisection_button, TRUE, TRUE, 0); // Adiciona o botão de bissecção à caixa

    GtkWidget *false_position_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(bisection_button), "Método da Falsa Posição");
    gtk_box_pack_start(GTK_BOX(method_box), false_position_button, TRUE, TRUE, 0); // Adiciona o botão de falsa posição à caixa

    GtkWidget *newton_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(bisection_button), "Método de Newton");
    gtk_box_pack_start(GTK_BOX(method_box), newton_button, TRUE, TRUE, 0); // Adiciona o botão de Newton à caixa

    GtkWidget *secant_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(bisection_button), "Método das Secantes");
    gtk_box_pack_start(GTK_BOX(method_box), secant_button, TRUE, TRUE, 0); // Adiciona o botão de secantes à caixa

    // Cria o botão de calcular
    calculate_button = gtk_button_new_with_label("Calcular");
    gtk_grid_attach(GTK_GRID(grid), calculate_button, 0, 6, 2, 1); // Adiciona o botão ao grid
    g_signal_connect(calculate_button, "clicked", G_CALLBACK(on_calculate_button_clicked), NULL); // Conecta o botão ao evento

    // Aplica o CSS aos widgets
    apply_css(calculate_button);
    apply_css(bisection_button);
    apply_css(false_position_button);
    apply_css(newton_button);
    apply_css(secant_button);
    apply_css(function_entry);
    apply_css(derivative_entry);
    apply_css(interval_entry);
    apply_css(tolerance_entry);
    apply_css(max_iterations_entry);

    // Exibe todos os widgets
    gtk_widget_show_all(window);

    // Inicia o loop principal do GTK
    gtk_main();

    return 0;
}
