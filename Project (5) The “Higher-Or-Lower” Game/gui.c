#include <gtk/gtk.h> 
#include "gui.h"

//void on_click_higher(); 
//void on_click_lower(); 
//void on_click_hint(); 
//void new_game(); 

void clear_child(GtkWidget* container){
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(container));
    for(iter = children; iter != NULL; iter = g_list_next(iter))
    gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);
}

void clear_container(int container_id){
    if (container_id == 0){
        clear_child(north_container);
    }else{
        clear_child(south_container);
    }
}

void set_prompt(char * prompt){
    gtk_text_buffer_set_text (buffer_prompt, prompt, -1);
}

void show_ingame_buttons(){
    gtk_widget_show(button_higher);
    gtk_widget_show(button_lower);
    //gtk_widget_show(button_hint);
}

void hide_ingame_buttons(){
    gtk_widget_hide(button_higher);
    gtk_widget_hide(button_lower);
    //gtk_widget_hide(button_hint);
}

void get_image_path(int card, char *fileName){
    /************CODE HERE**************/ 
//	char fileName[64];
	memset(fileName, 0, 64);
        sprintf(fileName, "./picture/%d.png", card); 
// return fileName;
    /************CODE END***************/
}

void add_image(int container_id, int card){
    GtkWidget *image;
    GtkWidget *container;
    if (container_id == 0){
        container = north_container;
    }else{
        container = south_container;
    }
    char file_name[64];
    memset(file_name,0,64);
    get_image_path(card,file_name);
    image = gtk_image_new_from_file (file_name); 
// image = gtk_image_new_from_file ("picture/44.png");
    gtk_container_add (GTK_CONTAINER(container), image); 
// gtk_box_pack_start (GTK_BOX (north_container), image, FALSE, FALSE, 2);
    gtk_widget_show_all (container);
}
void quit_game(GtkWindow *window){
    /************CODE HERE**************/
    // close the game
	exit(0);
    /************CODE END***************/
}
void activate (GtkApplication *app, gpointer user_data){
    GtkWidget *window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "HighLow");
    gtk_window_set_default_size (GTK_WINDOW (window), 1200, 400);
    int padding = 2;
    frame_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    north_container = gtk_box_new(FALSE, 0);
    panel_container = gtk_box_new(FALSE, 0);
    button_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    info_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    south_container = gtk_box_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(north_container), 60);
    gtk_container_set_border_width(GTK_CONTAINER(panel_container), 20);
    gtk_container_set_border_width(GTK_CONTAINER(button_container), 20);
    gtk_container_set_border_width(GTK_CONTAINER(info_container), 20);
    gtk_container_set_border_width(GTK_CONTAINER(south_container), 60);
    button_higher = gtk_button_new_with_label ("Higher!");
    button_lower = gtk_button_new_with_label ("Lower!");
    button_new = gtk_button_new_with_label ("New Game");
    button_quit = gtk_button_new_with_label ("Quit Game");
    //button_hint = gtk_button_new_with_label ("Hint");
    text_prompt = gtk_text_view_new ();
    buffer_prompt = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_prompt));

    gtk_container_add (GTK_CONTAINER (window), frame_box); 
// gtk_container_add (GTK_CONTAINER (window), button_higher); 
// gtk_container_add (GTK_CONTAINER (window), button_lower); 
// gtk_container_add (GTK_CONTAINER (window), button_new); 
// gtk_container_add (GTK_CONTAINER (window), button_quit);
    gtk_box_pack_start (GTK_BOX (frame_box), north_container, FALSE, FALSE, padding);
    gtk_box_pack_start (GTK_BOX (frame_box), panel_container, FALSE, FALSE, padding);
    gtk_box_pack_start (GTK_BOX (panel_container), button_container, FALSE, FALSE, padding);
    gtk_box_pack_start (GTK_BOX (panel_container), info_container, FALSE, FALSE, padding);
    gtk_box_pack_start (GTK_BOX (frame_box), south_container, FALSE, FALSE, padding);
    gtk_box_pack_start (GTK_BOX (button_container), button_higher, FALSE, FALSE, padding);
    gtk_box_pack_start (GTK_BOX (button_container), button_lower, FALSE, FALSE, padding);
    gtk_box_pack_start (GTK_BOX (button_container), button_new, FALSE, FALSE, padding);
    gtk_box_pack_start (GTK_BOX (button_container), button_quit, FALSE, FALSE, padding);
    //gtk_box_pack_start (GTK_BOX (button_container), button_hint, FALSE, FALSE, padding);
    g_signal_connect_swapped (button_quit, "clicked", G_CALLBACK (quit_game), window);
    gtk_box_pack_start (GTK_BOX (info_container), text_prompt, FALSE, FALSE, padding);
    g_signal_connect (button_new, "clicked", G_CALLBACK (new_game), NULL);
    g_signal_connect (button_higher, "clicked", G_CALLBACK (on_click_higher), NULL);
    g_signal_connect (button_lower, "clicked", G_CALLBACK (on_click_lower), NULL);
    //g_signal_connect (button_hint, "clicked", G_CALLBACK (on_click_hint), NULL);
    gtk_text_buffer_set_text (buffer_prompt, "", -1);
    gtk_widget_show_all (window);
    hide_ingame_buttons();
}
