package Open_Hash;

import Closed_Hash.Close_Hash_Entry;
import Facade.File_IO;
import com.algo.car;

/**
 * Created by ghost on 29/9/2016.
 */
public class Open_Hash_Map {

    private final static int TABLE_SIZE = 1000;
    private final static String stored_File_Name = "open_Hash_Table";

    private static Open_Hash_Entry[] table;
    public static int comparison_Count = 0;

    public Open_Hash_Map()
     {
        table = new Open_Hash_Entry[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
             table[i] = null;
     }

     public static Open_Hash_Entry get(String key)
     {
        int hash = Open_Hash.Hash(key,TABLE_SIZE);
        int initialHash = -1;

         if(table[hash] == null)
         {
            comparison_Count = 0;
             return null;
         }

        while (hash != initialHash
            && (table[hash] == Deleted_Hash_Entry.getUniqueDeletedEntry() || table[hash] != null
                && table[hash].getKey() != key))
        {
            if (initialHash == -1)
                initialHash = hash;
            hash = Open_Hash.reHash(hash,TABLE_SIZE);
            comparison_Count++;
        }


         if (table[hash] == null || hash == initialHash)
             return null;
         else
             return table[hash];
     }

     public static void put(car value)
     {
         int hash = Open_Hash.Hash(value.getCarPlate(),TABLE_SIZE);
         int initialHash = -1;
         int indexOfDeletedEntry = -1;
         while (hash != initialHash
                 && (table[hash] == Deleted_Hash_Entry.getUniqueDeletedEntry() || table[hash] != null
                 && table[hash].getKey() != value.getCarPlate()))
         {
             if (initialHash == -1)
                 initialHash = hash;
             if (table[hash] == Deleted_Hash_Entry.getUniqueDeletedEntry())
                 indexOfDeletedEntry = hash;
             hash = Open_Hash.reHash(hash,TABLE_SIZE);
         }
         if ((table[hash] == null || hash == initialHash)
                 && indexOfDeletedEntry != -1)
             table[indexOfDeletedEntry] = new Open_Hash_Entry(value);
         else if (initialHash != hash)
             if (table[hash] != Deleted_Hash_Entry.getUniqueDeletedEntry()
                     && table[hash] != null && table[hash].getKey() == value.getCarPlate())
                 table[hash].setValue(value);
             else
                 table[hash] = new Open_Hash_Entry(value);
     }

     public static void remove(String key)
     {
         int hash = Open_Hash.Hash(key,TABLE_SIZE);
         int initialHash = -1;
         while (hash != initialHash
                 && (table[hash] == Deleted_Hash_Entry.getUniqueDeletedEntry() || table[hash] != null
                 && table[hash].getKey() != key))
         {
             if (initialHash == -1)
                 initialHash = hash;
             hash = Open_Hash.reHash(hash,TABLE_SIZE);
         }
         if (hash != initialHash && table[hash] != null)
             table[hash] = Deleted_Hash_Entry.getUniqueDeletedEntry();
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
