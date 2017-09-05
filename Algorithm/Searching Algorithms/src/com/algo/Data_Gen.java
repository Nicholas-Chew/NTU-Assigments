package com.algo;

/**
 * Created by ghost on 1/10/2016.
 */
public class Data_Gen {
    static String abc = "ABCDEFGHJKLMNPQRSTUVWXYZ";
    static String carName[] = {"Toyota Prius", "Toyota Tacoma", "Toyota Yaris",
            "Toyota Camry", "Honda Civic Coupe", "Honda Civic Sedan",
            "Honda Accord Sedan", "Honda Accord Coupe", "Honda Accord Hybrid",
            "Ford 2016 FIESTA", "Ford 2016 FOCUS ", "Ford C-MAX",
            "Fiat Punto Pure", "Fiat Punto Evo", "Fiat Linea Classic",
            "Fiat Avventura", "Fiat Linea", "Fiat Abarth Punto"};

    public static String car_Plate()
    {

            return "S"+
                    abc.charAt((int)(Math.random() * abc.length()))+
                    abc.charAt((int)(Math.random() * abc.length()))+" "+
                    (int)(Math.random() * 10 )+ (int)(Math.random() * 10 )+
                    (int)(Math.random() * 10 )+ (int)(Math.random() * 10 )+ " "+
                    abc.charAt((int)(Math.random() * abc.length()));


    }

    public static String carModel()
    {
        return carName[(int)(Math.random() * carName.length)];
    }
}
