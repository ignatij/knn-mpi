import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.lang.Math;
import java.util.*;

public class tenDDataGenerator{
    
    public static int getRandomNumber(int min, int max) {
    return (int) (Math.random() * (max - min));
    }


     public static void main(String []args){
        Scanner sc= new Scanner(System.in);    //System.in is a standard input stream  
        System.out.print("Enter min value for integer ");  
        int min = sc.nextInt();
        System.out.print("Enter max  value for integer ");  
        int max = sc.nextInt();
        System.out.print("Enter number of rows ");  
        int rows = sc.nextInt();
        
        int[][] dataSet = new int[rows][10];
        
         
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < 10; j++) {
                dataSet[i][j] = getRandomNumber(min,max);
                System.out.print(dataSet[i][j] + " ");
            }
            System.out.print(" \n");
        }
     }
}
