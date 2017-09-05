package Closed_Hash;
import Facade.File_IO;
import Open_Hash.Open_Hash_Entry;
import com.algo.car;
import java.util.LinkedList;

/**
 * Created by ghost on 29/9/2016.
 */
public class Close_Hash_Map
{
    private final static int TABLE_SIZE = 1000;
    private final static String stored_File_Name = "closed_Hash_Table";

    private static Close_Hash_Entry[] table ;
    public static int comparison_Count = 0;

    public Close_Hash_Map()
    {
        table = new Close_Hash_Entry[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
             table[i] = null;
    }

    public static Close_Hash_Entry get(String key)
    {
        int hash = Close_Hash.Hash(key,TABLE_SIZE);

        if (table[hash] == null) {
            comparison_Count = 0;
            return null;
        }
        else
        {
            Close_Hash_Entry entry = table[hash];
            while (entry != null && entry.getKey() != key) {
                comparison_Count++;
                entry = entry.getNext();
            }
            if (entry == null)
                 return null;
            else
                return entry;
        }
    }

    public static void put(car value)
    {
        int hash = Close_Hash.Hash(value.getCarPlate(),TABLE_SIZE);
        if (table[hash] == null)
            table[hash] = new Close_Hash_Entry(value);
        else
        {
            Close_Hash_Entry entry = table[hash];
            while (entry.getNext() != null && entry.getKey() != value.getCarPlate())
                entry = entry.getNext();
            if (entry.getKey() == value.getCarPlate())
                entry.setValue(value);
            else
                entry.setNext(new Close_Hash_Entry( value));
        }
    }

    public static void remove(String key)
    {
        int hash = Close_Hash.Hash(key,TABLE_SIZE);
        if (table[hash] != null)
        {
            Close_Hash_Entry prevEntry = null;
            Close_Hash_Entry entry = table[hash];
            while (entry.getNext() != null && entry.getKey() != key)
            {
                 prevEntry = entry;
                 entry = entry.getNext();
            }

            if (entry.getKey() == key)
            {
                if (prevEntry == null)
                    table[hash] = entry.getNext();
                else
                    prevEntry.setNext(entry.getNext());
            }
        }
    }

    public static void save()
    {
        try
        {
            File_IO.writeToXML(stored_File_Name,table);

        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
    }


}
