package Closed_Hash;

/**
 * Created by ghost on 29/9/2016.
 */
public class Close_Hash
{

    //Hash Functions
    public static int Hash(String car_plate, int table_Size)
    {
        /*int M_Digit = car_plate.charAt(5)*car_plate.charAt(6)*car_plate.charAt(7)*car_plate.charAt(8);
        int M_Alphabet = alpToDigit(car_plate.charAt(2)) * alpToDigit(car_plate.charAt(3)); //Alphablet
        M_Alphabet = M_Alphabet%10 + M_Alphabet/10%10 + M_Alphabet/100%10;

        return M_Digit % 22000 / M_Alphabet;
        */

        // A = 1, ..., Z = 26. Char(2) is Alphabet 2 and Char(3) is Alphabet 3
        // Char(5-8) is Digits/Numbers
        return alpToDigit(car_plate.charAt(1)) + alpToDigit(car_plate.charAt(2))+
                Integer.parseInt(Character.toString(car_plate.charAt(4)))+
                Integer.parseInt(Character.toString(car_plate.charAt(5)))*
                Integer.parseInt(Character.toString(car_plate.charAt(6)))*
                Integer.parseInt(Character.toString(car_plate.charAt(7)))
                %table_Size;
    }

    private static int alpToDigit(char ch){
        return Character.toLowerCase(ch) - 'a' + 1;
    }
}
