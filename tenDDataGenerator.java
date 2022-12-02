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
        System.out.print("Enter min ");  
        int min = sc.nextInt();
        System.out.print("Enter max ");  
        int max = sc.nextInt();
        System.out.print("Enter number of rows ");  
        int rows = sc.nextInt();
        
        int[][] dataSet = new int[rows][10];
        
         
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < rows; j++) {
                dataSet[j][i] = getRandomNumber(min,max);
            }
        }
        System.out.print(Arrays.deepToString(dataSet));  

        // PrintWriter pr = new PrintWriter("10D Data");

        // for (int i=0; i<dataSet.length ; i++){
        // pr.println(Arrays.deepToString(dataSet));
        // }
        // pr.close();
     }
}