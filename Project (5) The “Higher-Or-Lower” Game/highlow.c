#include <time.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include "gui.h" 
#include <gtk/gtk.h>
int add_new_card(int container_id, int step); 
char * get_prompt(); 
void new_game(); 
void card_shuffle(); 
void end_game(); 
void higher_lower(int is_higher); 
void on_click_higher(); 
void on_click_lower(); 
//void on_click_hint(); 

static int status[3]; // step, North's score, South's score 
static int card_deck[52]; 
const int rounds = 19; 
char prompt[100]; 
int card_initHigh,card_initLow; 
int card_init; 

GtkWidget *button_end; 
// container_id = 0 for North, 1 for South 
int add_new_card(int container_id, int step){
    int card = card_deck[step];
    add_image(container_id, card);
    return card;
}

char * get_prompt(){
    char north[] = "North";
    char south[] = "South";
    sprintf(prompt, "%s's turn\nNorth's score : %d\n South's score: %d", (status[0] % 2 == 0? north : south), status[1], status[2]);
    return prompt;
}
void new_game(){
    /************CODE HERE**************/
    // starts a new game,
    // all initialization useful for resetting should be done here
    // Hint:
    // 1. please don't forget the situation when we finish a game and start a new one.
    // 2. We should have two cards already shown at the start of the game.
    
    /************CODE END***************/ 
//	char *prompt;
	memset(prompt,0,128);
	clear_container(0);
	clear_container(1);
	status[0]=0;
	status[1]=0;
	status[2]=0;
	char *prompt = get_prompt();
	card_shuffle();
	set_prompt(prompt);
	card_initHigh = add_new_card(0, 4);
	card_init = add_new_card(1, 8);
	show_ingame_buttons();
}
void card_shuffle() {
    // this method prepares all cards in card_deck
    // this is the ONLY function that should apply RANDOMNESS
    int i,irandom,temp;
    for (i = 0; i < 52; i++) {
        card_deck[i] = i;
    }
    for (i = 0; i < 51; i++) {
        irandom = i + rand() % (52 - i);
        temp = card_deck[i];
        card_deck[i] = card_deck[irandom];
        card_deck[irandom] = temp;
    }
}
void end_game(){
    /************CODE HERE**************/
    // 1. Hide the higher and lower button
    // 2. show match results in buffer_prompt. If North wins, Please show "North wins.\nNorth's score : %d, South's score: %d"
    char prompt[128];
    memset(prompt,0,128);
    
    //set_prompt(prompt);
    hide_ingame_buttons();
    if(status[1] > status[2])
    {
	    sprintf(prompt, "North wins.\nNorth's score : %d, South's score: %d", status[1],status[2]);
	    gtk_text_buffer_set_text (buffer_prompt, prompt, -1);
    }
    else if(status[1] < status[2])
    {
	    sprintf(prompt, "North wins.\nNorth's score : %d, South's score: %d", status[1],status[2]);
            gtk_text_buffer_set_text (buffer_prompt, prompt, -1);
    }
    else
	    gtk_text_buffer_set_text (buffer_prompt, "draw\n", -1);
	
    /************CODE END***************/
}
void higher_lower(int is_higher){
    int step = status[0];
    int current_container = step % 2;
    int card = add_new_card(current_container, step);
    /************CODE HERE**************/
    // If current player predict correct card, he get 10 points. Otherwise, he loss 5 points.
	int card_bef;
    int shang_bef;
    int yushu_bef;
    int shang;
    int yushu;
    card_bef = card_init;
    yushu = card%3;
    shang = card/3;
    yushu_bef = card_bef%3;
    shang_bef = card_bef/3;
    if( (card<=3) && (card_bef) >3 )
    {
            if(is_higher == 0)
            {
                    if(0 == step%2)
                            status[1] = status[1] - 5;
                    else
                            status[2] = status[2] - 5;
            }
            else
            {
                    if(0 == step%2)
                            status[1] = status[1] + 10;
                    else
                            status[2] = status[2] + 10;
            }
    }
    else if( (card_bef <=3) && (card >3) )
    {
            if(is_higher == 1)
            {
                    if(0 == step%2)
                            status[1] = status[1] - 5;
                    else
                            status[2] = status[2] - 5;
            }
            else
            {
                    if(0 == step%2)
                            status[1] = status[1] + 10;
                    else
                            status[2] = status[2] + 10;
            }
    }
    else if(shang < shang_bef)
    {
	    if(is_higher == 1)
	    {
		    if(0 == step%2)
			    status[1] = status[1] - 5;
		    else
			    status[2] = status[2] - 5;
	    }
	    else
	    {
		    if(0 == step%2)
			    status[1] = status[1] + 10;
		    else
			    status[2] = status[2] + 10;
	    }
    }
    else if(shang == shang_bef)
    {
	    if(yushu == 3) //xin de da
	    {
	            if(is_higher == 1)
	            {
        	            if(0 == step%2)
                	            status[1] = status[1] - 5;
	                    else
        	                    status[2] = status[2] - 5;
            	    }
            	    else
            	    {
                    	if(0 == step%2)
                    	        status[1] = status[1] + 10;
                    	else
                        	    status[2] = status[2] + 10;
            	    }
	    }
	    else if(yushu == 1)
	    {
	            if(is_higher == 1)
	            {
        	            if(0 == step%2)
                	            status[1] = status[1] +10;
	                    else
        	                    status[2] = status[2] + 10;
            	    }
            	    else
	            {
        	            if(0 == step%2)
                	            status[1] = status[1] - 5;
	                    else
        	                    status[2] = status[2] - 5;
                    }
	    }
	    else if(yushu == 0)
	    {
		if(yushu_bef == 1)
		{
                    if(is_higher == 0)
                    {
                            if(0 == step%2)
                                    status[1] = status[1] +10;
                            else
                                    status[2] = status[2] + 10;
                    }
                    else
                    {
                            if(0 == step%2)
                                    status[1] = status[1] - 5;
                            else
                                    status[2] = status[2] - 5;
                    }
		}
	    }
	    else
	    {
                if(yushu_bef == 3)
                {
                    if(is_higher == 1)
                    {
                            if(0 == step%2)
                                    status[1] = status[1] +10;
                            else
                                    status[2] = status[2] + 10;
                    }
                    else
                    {
                            if(0 == step%2)
                                    status[1] = status[1] - 5;
                            else
                                    status[2] = status[2] - 5;
                    }
                }
	    }
    }
    else
    {
	if(is_higher == 1)
	{
		if(0 == step%2)
			status[1] = status[1] +10;
		else
			status[2] = status[2] +10;
	}
	else
	{
		if(0 == step%2)
                        status[1] = status[1] -5;
                else
                        status[2] = status[2] -5;
	}
    }
    card_init = card;
    /************CODE END***************/
    if (status[0] == rounds){
        end_game();
        return;
    }else{
        status[0]++;
        char * prompt = get_prompt();
        set_prompt(prompt);
    }   
}

void on_click_higher(){
    higher_lower(1);
}

void on_click_lower(){
    higher_lower(0);
}

//void on_click_hint(){ //
//}
