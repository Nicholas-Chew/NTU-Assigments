package com.algo;
import Closed_Hash.Close_Hash_Entry;
import Open_Hash.Open_Hash_Entry;
import Open_Hash.Open_Hash_Map;
import Closed_Hash.Close_Hash_Map;
import java.util.Scanner;

public class Main
{
    private static Scanner  sc;
    private static String temp_result;
    private static int Pcount[] = {100, 200, 200, 200, 200};
    private static int Pcount_Total[] = {100, 300, 500, 700, 900};
    private static long start = 0, end = 0;

    public static void main(String[] args)
    {
        new Open_Hash_Map();
        new Close_Hash_Map();

        for (int i = 0; i<Pcount.length;i++) {
            System.out.println("Populating both table to "+Pcount_Total[i]+"");
            System.out.println("-----------------------------");

            populate(Pcount[i]);
            //Successful
            System.out.println("Comparing a Successful case. Using Key:"+temp_result);
            System.out.println("----------------------------------------------------------");
            Compare(temp_result);

            System.out.println("Comparing a Unsuccessful case. Using Key: SOI 8732 G");
            System.out.println("----------------------------------------------------------");
            //Not Successful
            Compare("SOI 8732 G");

            System.out.println();
        }

        Open_Hash_Map.save();
        Close_Hash_Map.save();


    }

    private static void Compare(String value)
    {
        Close_Hash_Map.comparison_Count = 1;
        Open_Hash_Map.comparison_Count = 1;

        start = System.nanoTime();
        Close_Hash_Entry che = Close_Hash_Map.get(value);
        end = System.nanoTime() - start;
        System.out.println("Comparison Count For Close Addressing Scheme: "+Close_Hash_Map.comparison_Count+ " Time used in nano second: "+end);


        if(che!= null)
            System.out.println("Car Found In Close Addressing: Car Plate: "+che.getValue().getCarPlate()+", Car Model: "+che.getValue().getCarModel()+"\n");
        else
            System.out.println("Car Found In Close Addressing: Car Plate:NULL, Car Model:NULL"+"\n");

        start = System.nanoTime();
        Open_Hash_Entry ohe = Open_Hash_Map.get(value);
        end = System.nanoTime() - start;
        System.out.println("Comparison Count For Open Scheme: "+Open_Hash_Map.comparison_Count + " Time used in nano second: "+end);

        if(che != null)
            System.out.println("Car Found In Open Addressing:  Car Plate: "+ohe.getValue().getCarPlate()+", Car Model: "+ohe.getValue().getCarModel()+"\n");
        else
            System.out.println("Car Found In Close Addressing:  Car Plate:NULL, Car Model:NULL"+"\n");
    }

    private static void populate(int times)
    {
        for (int i = 0 ; i <times; i++) {
            if (times / 2 == i) {
                temp_result = Data_Gen.car_Plate();
                setBoth(temp_result, Data_Gen.carModel());
            }
            else
            setBoth(Data_Gen.car_Plate(), Data_Gen.carModel());
        }
    }

    private static void setBoth(String plate, String model)
    {
        Open_Hash_Map.put(new car(plate,model));
        Close_Hash_Map.put(new car(plate, model));
    }

}
