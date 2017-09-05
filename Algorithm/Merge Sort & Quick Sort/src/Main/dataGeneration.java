package Main;

/**
 * Created by ghost on 11/10/2016.
 */
public class dataGeneration {

    public static int[] ascending(int size)
    {
        int temp[] = new int[size];

        for(int i = 0; i<size; i++)
            temp[i] = i+1;

        return  temp;
    }

    public static int[] descending(int size)
    {
        int temp[] = new int[size];

        for(int i = 0; i<size; i++)
            temp[i] = size-i;

        return  temp;
    }


    public static int[] random(int size)
    {
        int temp[] = new int[size];

        for(int i = 0; i<size; i++)
            temp[i] = 1+ (int)(Math.random()*size);


        return temp;
    }


}
