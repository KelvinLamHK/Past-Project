/**
 * CSCI1130 Java Assignment 6 BoardGame Reversi
 * Aim: Practise subclassing, method overriding
 *      Learn from other subclass examples
 * 
 * I declare that the assignment here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   http://www.cuhk.edu.hk/policy/academichonesty
 * Faculty of Engineering Guidelines to Academic Honesty:
 *   https://www.erg.cuhk.edu.hk/erg/AcademicHonesty
 *
 * Student Name: Lam Tat Yin    
 * Student ID  : 1155144730
 * Date        : 07/12/2021
 */

package boardgame;

import java.awt.Color;
import javax.swing.JButton;
import javax.swing.JOptionPane;

/**
 * Reversi is a TurnBasedGame
 */
public class Reversi extends BoardGame {
    
    public static final String BLANK = " ";
    String winner;
    protected String player1;
    protected String player2;
    protected String currentPlayer;
    protected int turn;
    protected int passNum;

    public Reversi(){
        this(8,8,"BLACK","WHITE");
    }

    private Reversi(int xCount, int yCount, String player1, String player2)
    {
        super(xCount, yCount);
        this.player1 = player1;
        this.player2 = player2;

        this.setTitle("Reversi " + xCount + "x" + yCount + ": " + player1 + " vs " + player2);
        turn = 0;
        changeTurn();
        this.passNum=0;
    }

    protected final int changeTurn()                 //chagne user
    {
        turn++;
        if (turn % 2 == 1)
            currentPlayer = player1;
        else
            currentPlayer = player2;
        addLineToOutput("Turn " + turn + " Current Player: " + currentPlayer);
        return turn;
    }

    @Override
    protected void initGame()
    {
        for (int y = 0; y < yCount; y++) {
            for (int x = 0; x < xCount; x++) {
                pieces[x][y].setText(BLANK);
                if(x==xCount/2-1 || x==xCount/2){
                    if(y==yCount/2-1 || y==yCount/2){
                        if(x==y){
                            pieces[x][y].setText("WHITE");
                            pieces[x][y].setBackground(Color.WHITE);
                        }else{
                            pieces[x][y].setText("BLACK");
                            pieces[x][y].setBackground(Color.BLACK);
                        }
                    }
                }
            }
        }
    }

    @Override
    protected void gameAction(JButton triggeredButton, int x, int y)
    {
        if(mustPass()){
            changeTurn();
            passNum+=1;
            if(passNum==2){
                gameEnded = true;
                getWinner();
            }
            return;
        }

        passNum=0;

        Color color = currentPlayer.equals("BLACK") ? Color.BLACK : Color.WHITE;
        boolean flag=false;
        for (int deltaX = -1; deltaX <= 1; deltaX++) {
            for (int deltaY = -1; deltaY <= 1; deltaY++) {
                if(isValidMove(x,y,deltaX,deltaY)){
                    flag=true;
                    fillBoard(x,y,deltaX,deltaY);
                }
            }
        }
        if(flag){
            pieces[x][y].setText(currentPlayer);
            pieces[x][y].setBackground(color);
            changeTurn();
        }

    }

    private void getWinner() {                      //test which color wim
        int a=0;
        int b=0;
        for(int i=0;i<xCount;i++) {
            for (int j = 0; j < yCount; j++) {
                String text = pieces[i][j].getText();
                if(text.equals("BLACK")){
                    a++;
                }else if(text.equals("WHITE")){
                    b++;
                }
            }
        }
        if(a==b){
            addLineToOutput("Draw game!");
        }else {
            winner=a>b?"BLACK":"WHITE";
            addLineToOutput(winner+"win!");
        }
        addLineToOutput("Game ended!");
        JOptionPane.showMessageDialog(null, "Game ended!");
    }

    private boolean mustPass() {                         //test if each color have chance to move. if no , turn to nrxt color
        for(int i=0;i<xCount;i++){
            for(int j=0;j<yCount;j++){
                for (int deltaX = -1; deltaX <= 1; deltaX++) {
                    for (int deltaY = -1; deltaY <= 1; deltaY++) {
                        if(isValidMove(i,j,deltaX,deltaY)){
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    private boolean isValidMove(int x, int y, int deltaX, int deltaY) {            //to test the move is valid or not
        if(!pieces[x][y].getText().equals(BLANK)) return false;
        if(deltaX==0&&deltaY==0) return false;
        int xPos=x+deltaX;
        int yPos=y+deltaY;
        String text = BLANK;
        try {
            while(true) {
                text = pieces[xPos][yPos].getText();
                if (text.equals(BLANK) || text.equals(currentPlayer)) {
                    break;
                }else{
                    xPos+=deltaX;
                    yPos+=deltaY;
                }
            }
        }catch (Exception e){}
        if(xPos>=0&&xPos<xCount&&yPos>=0&&yPos<yCount){
            if(text.equals(currentPlayer)&&!(xPos==x+deltaX && yPos==y+deltaY)){
                return true;
            }
        }
        return false;
    }

    private void fillBoard(int x, int y, int deltaX, int deltaY) {
        Color color = currentPlayer.equals("BLACK") ? Color.BLACK : Color.WHITE;

        int i=x+deltaX;
        int j=y+deltaY;
        while(true){
            if(pieces[i][j].getText().equals(currentPlayer)){
                return;
            }
            pieces[i][j].setText(currentPlayer);
            pieces[i][j].setBackground(color);
            i+=deltaX;
            j+=deltaY;
        }
    }

    /*** TO-DO: STUDENT'S WORK HERE ***/

    
    public static void main(String[] args)
    {
        Reversi reversi;
        reversi = new Reversi();
        
        // TO-DO: run other classes, one by one
        System.out.println("You are running class Reversi");
        
        // TO-DO: study comment and code in other given classes
        
        // TO-DO: uncomment these two lines when your work is ready
        reversi.setLocation(400, 20);
        reversi.verbose = false;

        // the game has started and GUI thread will take over here
    }
}
