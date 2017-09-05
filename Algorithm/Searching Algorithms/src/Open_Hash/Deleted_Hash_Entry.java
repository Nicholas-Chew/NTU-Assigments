package Open_Hash;
import com.algo.car;

/**
 * Created by ghost on 30/9/2016.
 */
public class Deleted_Hash_Entry extends Open_Hash_Entry {
    private static Deleted_Hash_Entry entry = null;

    private Deleted_Hash_Entry()
    {
        super(new car("",""));
    }

    public static Deleted_Hash_Entry getUniqueDeletedEntry()
    {
    if (entry == null)
        entry = new Deleted_Hash_Entry();
        return entry;
     }

}
