package Open_Hash;

/**
 * Created by ghost on 29/9/2016.
 */
public class Open_Hash {

    //Hash Functions
    //First Hash
    public static int Hash(String car_plate, int table_Size)
    {
        return alpToDigit(car_plate.charAt(1)) + alpToDigit(car_plate.charAt(2))+
                Integer.parseInt(Character.toString(car_plate.charAt(4)))+
                Integer.parseInt(Character.toString(car_plate.charAt(5)))*
                        Integer.parseInt(Character.toString(car_plate.charAt(6)))*
                        Integer.parseInt(Character.toString(car_plate.charAt(7)))
                        %table_Size;
    }

    //A Function to re-hash. Need a prime number at the back to prevent infinate loop
    public static int reHash(int key, int table_size)
    {
        return (key + 5) %table_size;
    }

            /*int M_Digit = car_plate.charAt(5)*car_plate.charAt(6)*car_plate.charAt(7)*car_plate.charAt(8);
        int M_Alphabet = alpToDigit(car_plate.charAt(2)) * alpToDigit(car_plate.charAt(3)); //Alphablet
        M_Alphabet = M_Alphabet%10 + M_Alphabet/10%10 + M_Alphabet/100%10;

        return M_Digit % 22000 / M_Alphabet;


        // A = 1, ..., Z = 26. Char(2) is Alphabet 2 and Char(3) is Alphabet 3
        // Char(5-8) is Digits/Numbers*/

    private static int alpToDigit(char ch) {
        return Character.toLowerCase(ch) - 'a' + 1;
    }
}
