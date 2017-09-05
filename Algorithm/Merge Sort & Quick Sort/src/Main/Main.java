package Main;
import Mergesort.mergeSort;
import Quicksort.quickSort;
import Facade.File_IO;

import java.util.Scanner;
import java.util.concurrent.ExecutionException;


/**
 * Created by ghost on 11/10/2016.
 */
public class Main {

   // private static Scanner sc = new Scanner(System.in);
    private static long  startTime = 0;
    private static long  timeTaken = 0;

    public static void main(String[] args)
    {
        testRoutine(2000);
        testRoutine(4000);
        testRoutine(6000);
        testRoutine(8000);
        testRoutine(10000);
    }

    private static void testRoutine(int size)
    {
        int Incre_temp[] = dataGeneration.ascending(size);
        int Decre_temp[] = dataGeneration.descending(size);
        int Random_temp[] = dataGeneration.random(size);

        try {
            File_IO.writeToXML("Increment "+size, Incre_temp);
            File_IO.writeToXML("Decrement "+size, Decre_temp);
            File_IO.writeToXML("Random "+size, Random_temp);
        }
        catch (Exception e)
        {

        }

        int Incre_temp2[] = new int[size];
        System.arraycopy(Incre_temp,0,Incre_temp2,0,Incre_temp.length);

        int Decre_temp2[] = new int[size];
        System.arraycopy(Decre_temp,0,Decre_temp2,0,Incre_temp.length);

        int Random_temp2[] = new int[size];
        System.arraycopy(Random_temp,0,Random_temp2,0,Incre_temp.length);

        System.out.println("-----------------------");
        System.out.println("For Data Size Of "+size);
        System.out.println("-----------------------");

        sort("Merge Sort For Increment Data",true,Incre_temp);

        sort("Merge Sort For Decrement Data",true,Decre_temp);

        sort("Merge Sort For Random Data",true,Random_temp);

        sort("Quick Sort For Increment Data",false,Incre_temp2);

        sort("Quick Sort For Decrement Data",false,Decre_temp2);

        sort("Quick Sort For Random Data",false,Random_temp2);

    }

    private static void sort(String output, boolean sort, int[] data)
    {
        int count = 0;
        System.out.println(output);
        //printArr(data);
        if (sort)
        {
            startTime = System.nanoTime();
            count = mergeSort.sort(data);
            timeTaken = (System.nanoTime() - startTime)/1000;

        }else
        {
            startTime = System.nanoTime();
            count = quickSort.sort(data);
            timeTaken = (System.nanoTime() - startTime)/1000;
        }
        //printArr(data);
        System.out.println("Comparison Count: "+ count);
        System.out.println("Time taken in micro second:" + timeTaken+"\n");
    }

    public static void printArr(int[] arr) {
        for (int i : arr) System.out.print(i + ", ");
        System.out.println();
    }

}
