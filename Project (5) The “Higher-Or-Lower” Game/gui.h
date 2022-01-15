#include<stdio.h> 
#include<gtk/gtk.h>
void clear_child(GtkWidget* container); 
void clear_container(int container_id); 
void set_prompt(char *); 
void show_ingame_buttons(); 
void hide_ingame_buttons(); 
void get_image_path(int card, char *fileName); 
void add_image(int container_id, int card); 
void quit_game(GtkWindow *window); 
void activate (GtkApplication *app, gpointer user_data); 
void on_click_higher(); 
void on_click_lower(); 
//void on_click_hint(); 
void new_game(); 

GtkWidget *button_higher; 
GtkWidget *frame_box; 
GtkWidget *north_container; 
GtkWidget *panel_container; 
GtkWidget *button_container; 
GtkWidget *info_container; 
GtkWidget *south_container; 
GtkWidget *button_higher; 
GtkWidget *button_lower; 
GtkWidget *button_new; 
GtkWidget *button_quit; 
//GtkWidget *button_hint; 
GtkWidget *text_prompt; 
GtkTextBuffer *buffer_prompt;
